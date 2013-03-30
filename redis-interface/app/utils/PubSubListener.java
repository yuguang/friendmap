package utils;

import play.*;
import play.mvc.*;
import play.libs.*;

import com.lambdaworks.redis.pubsub.RedisPubSubListener;

import org.codehaus.jackson.JsonNode;
import org.codehaus.jackson.node.ObjectNode;
import org.codehaus.jackson.node.ArrayNode;

import java.util.HashMap;
import java.util.HashSet;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import utils.Channel;

public class PubSubListener implements RedisPubSubListener<String, String> {

    // use unlimited thread pool with garbage collections (reaping unused threads)
    private static final ExecutorService executor = Executors.newCachedThreadPool();

    private HashMap<String, HashSet<WebSocket.Out<JsonNode>>> channelToWebSocket = null;

    public PubSubListener(HashMap<String, HashSet<WebSocket.Out<JsonNode>>> channelToWebSocket){
        this.channelToWebSocket = channelToWebSocket;
    }

    HashSet<WebSocket.Out<JsonNode>> getWebSockets(String channel) {
        HashSet<WebSocket.Out<JsonNode>> websockets = channelToWebSocket.get(channel);
        if (websockets == null) {
            Logger.warn("websockets set is empty for channel " + channel);
        }
        return websockets;
    }

    @Override
    public void message(final String channel, final String message) {
        // construct json response
        final ObjectNode reply = Json.newObject();
        ArrayNode body = reply.putArray("SUBSCRIBE");
        body.add("message");
        body.add(channel);
        body.add(message);
        String[] fields = message.split(",");
        String v = fields[2];

//        if(v == "1"){
            executor.execute(new Runnable() {
                public void run() {
                    HashSet<WebSocket.Out<JsonNode>> websockets = getWebSockets(channel);
            
                    for (WebSocket.Out<JsonNode> out : websockets) {
                        //Logger.info("channel: " + channel + " message: " + message);
                        out.write(reply);
                    }
                }
            });
//        }
    }

    @Override
    public void message(String pattern, String channel, String message) {
        // TODO
    }

    @Override
    public void subscribed(final String channel, long count) {
        final ObjectNode reply = Json.newObject();
        ArrayNode body = reply.putArray("SUBSCRIBE");
        body.add("subscribe");
        body.add(channel);
        body.add(count);

        executor.execute(new Runnable() {
            public void run() {
                HashSet<WebSocket.Out<JsonNode>> websockets = getWebSockets(channel);

                for (WebSocket.Out<JsonNode> out : websockets) {
                        out.write(reply);
                }
            }
        });
    }

    @Override
    public void psubscribed(String pattern, long count) {
        // TODO
    }

    @Override
    public void unsubscribed(final String channel, long count) {
        final ObjectNode reply = Json.newObject();
        ArrayNode body = reply.putArray("UNSUBSCRIBE");
        body.add("unsubscribe");
        body.add(channel);
        body.add(count);

        executor.execute(new Runnable() {
            public void run() {
                HashSet<WebSocket.Out<JsonNode>> websockets = getWebSockets(channel);

                for (WebSocket.Out<JsonNode> out : websockets) {
                    out.write(reply);
                }
            }
        });
    }

    @Override
    public void punsubscribed(String pattern, long count) {
        // TODO
    }
}
