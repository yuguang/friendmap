#!/usr/bin/env python

import redis
import threading
import time
import yaml
import math
import random
import sys

random.seed()
config = open('publisher.yaml', 'r')
parsed_config = yaml.load(config)
print "CONFIGURATION"
print parsed_config
locations = [
	[43.473321, -80.54178],		# Davis Center
	[43.472309, -80.544033],	# Mathematics & Computer
	[43.469783,-80.542312],		# Dana Porter
	[43.472262,-80.538044],		# Campus Pizza
	[43.470024,-80.535268],		# UWP residence
	[43.47807,-80.524918],		# Morty's pub
	[43.49862,-80.527128],		# Conestoga mall
	[43.473882,-80.528694],		# Wilfred Laurier University
]

speed = [4,				# 4km/h - walking
	 50,				# 50km/h - driving
]

earth_radius = 6371     # in km

def get_distance(loc1, loc2):
    lat = math.radians(loc2[0]-loc1[0])    # latitude diff in radians
    lon = math.radians(loc2[1]-loc1[1])    # longitude diff in radians
    a = math.sin(lat/2)*math.sin(lat/2) \
        + math.cos(math.radians(loc1[0])) * math.cos(math.radians(loc2[0])) \
        * math.sin(lon/2) * math.sin(lon/2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    return earth_radius * c

print "DC to MC is " + str(get_distance(locations[0], locations[1])) + "km"
print "MC to DP is " + str(get_distance(locations[1], locations[2])) + "km"
print "DP to Campus pizza is " + str(get_distance(locations[2], locations[3])) + "km"
print "Campus pizza to UWP is " + str(get_distance(locations[3], locations[4])) + "km"
print "UWP to Morty's pub is " + str(get_distance(locations[4], locations[5])) + "km"
print "Morty's pub to Conestoga mall is " + str(get_distance(locations[5], locations[6])) + "km"
print "Conestoga mall to Wilfrid Laurier is " + str(get_distance(locations[6], locations[7])) + "km"

loc_print = [ "DC", "MC", "DP", "Campus pizza", "UWP", "Morty's Pub", "Conestoga Mall", "Wilfrid Laurier"]
num_locations = len(locations)

def publisher_thread(user_ppid):
    ppid = user_ppid
    frequency = int(parsed_config['push_frequency'])
    start_pos = -1
    r = redis.StrictRedis(host='localhost', port=6379, password='friendtracker-pass')
    while True:
        if start_pos == -1:
            start_pos = random.randint(0, num_locations-1)

        dest_pos = random.randint(0, num_locations-1)
        while start_pos == dest_pos:
            dest_pos = random.randint(0, num_locations-1)

        print ppid + " Driving from " + loc_print[start_pos] + " to " + loc_print[dest_pos]
        dist = get_distance(locations[start_pos], locations[dest_pos])
        cur_location = locations[start_pos]
        lat_diff = locations[dest_pos][0] - locations[start_pos][0]
        lon_diff = locations[dest_pos][1] - locations[start_pos][1]
        travel_time = dist / speed[1] * 3600      # estimated walking time
        print "expected travel time " + str(travel_time) + " sec"
        while get_distance(cur_location, locations[dest_pos]) <= dist:
            r.set(ppid, str(cur_location[0]) + "," + str(cur_location[1]))
            r.publish(ppid, str(cur_location[0]) + "," + str(cur_location[1]))
            #print cur_location
            dist = get_distance(cur_location, locations[dest_pos])
            time.sleep(5)   # wait 5 sec
            cur_location[0] += lat_diff * 5 / travel_time
            cur_location[1] += lon_diff * 5 / travel_time
            #print "distance " + str(get_distance(cur_location, locations[dest_pos]))

        r.set(ppid, str(locations[dest_pos][0]) + "," + str(locations[dest_pos][1]))
        r.publish(ppid, str(locations[dest_pos][0]) + "," + str(locations[dest_pos][1]))

        print ppid + " arrived at " + loc_print[dest_pos] + str(locations[dest_pos])
        start_pos = dest_pos

try:
    for user_ppid in parsed_config['users']:
        thread = threading.Thread(target=publisher_thread, args=(user_ppid,))
        thread.daemon = True
        thread.start()
    while True: time.sleep(100)
except (KeyboardInterrupt, SystemExit):
    print "Received keyboard interrupt, quitting threads."
    sys.exit(0)
