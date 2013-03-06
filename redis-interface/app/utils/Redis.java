package utils;

import play.*;
import play.mvc.*;

import com.lambdaworks.redis.RedisClient;
import com.lambdaworks.redis.RedisAsyncConnection;
import com.lambdaworks.redis.pubsub.RedisPubSubConnection;

import org.codehaus.jackson.JsonNode;
import org.codehaus.jackson.node.ObjectNode;
import org.codehaus.jackson.node.ArrayNode;

import java.util.HashMap;
import java.util.HashSet;
import java.util.concurrent.Future;

public class Redis {

    private static Redis instance = null;
    private RedisClient client = null;
    private RedisAsyncConnection<String, String> asyncConn = null;
    private RedisPubSubConnection<String, String> pubsubConn = null;

    HashMap<String, HashSet<WebSocket.Out<JsonNode>>> channelToWebSocket
        = new HashMap<String, HashSet<WebSocket.Out<JsonNode>>>();

    HashMap<WebSocket.Out<JsonNode>, HashSet<String>> webSocketToChannel
        = new HashMap<WebSocket.Out<JsonNode>, HashSet<String>>();

    public static Redis getInstance() {
        if (instance == null) {
            instance = new Redis();
        }

        return instance;
    }

    private Redis() {
        client = new RedisClient("127.0.0.1", 6379);
        // initialize both async and pubsub connections
        asyncConn = client.connectAsync();
        String status = asyncConn.auth("friendtracker-pass");
        Logger.debug("asyncConn auth status - " + status);
        pubsubConn = client.connectPubSub();
        status = pubsubConn.auth("friendtracker-pass");
        Logger.debug("pubsubConn auth status - " + status);
        pubsubConn.addListener(new PubSubListener(channelToWebSocket));
    }

    public void set(String key, String value) {
        // TODO
    }

    public Future<String> get(String key) {
        return asyncConn.get(key);
    }

    public void publish(String key, String message) {
        // TODO
    }

    public void subscribe(String channel, WebSocket.Out<JsonNode> out) {
        // remember that this websocket is subscribed to the channel
        HashSet<WebSocket.Out<JsonNode>> websockets = channelToWebSocket.get(channel);
        if (websockets == null) {
            websockets = new HashSet<WebSocket.Out<JsonNode>>();
        }
        websockets.add(out);
        channelToWebSocket.put(channel, websockets);

        // reverse mapping from websocket to channels
        HashSet<String> channels = webSocketToChannel.get(out);
        if (channels == null) {
            channels = new HashSet<String>();
        }
        channels.add(channel);
        webSocketToChannel.put(out, channels);

        // subscribe to the channel
        pubsubConn.subscribe(channel);
    }

    public void unsubscribe(String ipAddress, WebSocket.Out<JsonNode> out) {
        HashSet<String> channels = webSocketToChannel.get(out);
        if (channels == null) {
            Logger.error("client " + ipAddress + " has empty subscription list");
            return;
        }
        for (String channel : channels) {
            HashSet<WebSocket.Out<JsonNode>> websockets
                = channelToWebSocket.get(channel);
            if (websockets == null) {
                Logger.error("list of websockets is empty");
            } else {
                // remove websocket
                websockets.remove(out);
            }
        }
        webSocketToChannel.remove(out);    // remove websocket
    }
}
