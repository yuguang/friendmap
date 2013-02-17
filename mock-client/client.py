#!/usr/bin/env python

import httplib
import requests
import sys
import socket
import yaml
import threading
import time

socket._fileobject.default_buffer = 0   # prevent read from blocking on small chunk

def subscribe(subscribe_url, channel_name):
    print 'subscribe to ' + subscribe_url + channel_name
    headers = { 'Accept-Encoding' : 'identity' }
    session = requests.sessions.Session()
    session.headers.update(headers)
    session.verify = False
    session.prefetch = False
    session.hooks.update(response=response_hook)
    resp = session.get(subscribe_url + channel_name, stream=True)
    for chunk in resp.iter_chunks():
        print chunk

def response_hook(response, *args, **kwargs):
    response.iter_chunks = lambda amt=None: iter_chunks(response.raw._fp, amt=amt)
    return response

# source - http://mihai.ibanescu.net/chunked-encoding-and-python-requests
def iter_chunks(response, amt=None):
    """
    A copy-paste version of httplib.HTTPConnection._read_chunked() that
    yields chunks served by the server.
    """
    if response.chunked:
        while True:
            line = response.fp.readline().strip()
            arr = line.split(';', 1)
            try:
                chunk_size = int(arr[0], 16)
            except ValueError:
                response.close()
                raise httplib.IncompleteRead(chunk_size)
            if chunk_size == 0:
                break
            value = response._safe_read(chunk_size)
            yield value
            # we read the whole chunk, get another
            response._safe_read(2)      # toss the CRLF at the end of the chunk

        # read and discard trailer up to the CRLF terminator
        ### note: we shouldn't have any trailers!
        while True:
            line = response.fp.readline()
            if not line:
                # a vanishingly small number of sites EOF without
                # sending the trailer
                break
            if line == '\r\n':
                break

        # we read everything; close the "file"
        response.close()
    else:
        # Non-chunked response. If amt is None, then just drop back to
        # response.read()
        if amt is None:
            yield response.read()
        else:
            # Yield chunks as read from the HTTP connection
            while True:
                ret = response.read(amt)
                if not ret:
                    break
                yield ret


config = open("client.yaml", "r")
parsed_config = yaml.load(config)
print "CONFIGURATION"
print parsed_config
if parsed_config['mode'] == 'realtime':
    print 'starting real-time mode!'
    subscribe_url = 'http://' + parsed_config['remote_host'] + ':' \
            + str(parsed_config['remote_port']) + '/subscribe/'
    try:
        for channel in parsed_config['friend_list']:
            thread = threading.Thread(target=subscribe, args=(subscribe_url, channel))
            thread.daemon = True
            thread.start()
        while True: time.sleep(100)
    except (KeyboardInterrupt, SystemExit):
        print "Received keyboard interrupt, quitting threads."
        sys.exit(0)
else:
    print "starting regular mode!"
    print "pull frequency set to " + str(parsed_config['pull_frequency']) + " sec"
    pull_url = 'http://' + parsed_config['remote_host'] + ':' \
            + str(parsed_config['remote_port']) + '/get/'
    while True:
        for friend in parsed_config['friend_list']:
            resp = requests.get(pull_url + friend)
            print friend + "@" + resp.text
        time.sleep(parsed_config['pull_frequency'])
