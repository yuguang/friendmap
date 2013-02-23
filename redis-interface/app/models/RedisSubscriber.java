package models;

import play.*;
import play.mvc.*;
import play.libs.*;

import org.codehaus.jackson.JsonNode;
import org.codehaus.jackson.node.ObjectNode;
import org.codehaus.jackson.node.ArrayNode;
import org.codehaus.jackson.map.ObjectMapper;

import redis.clients.jedis.JedisPubSub;

public class RedisSubscriber extends JedisPubSub {

    private WebSocket.In<JsonNode> in = null;
    private WebSocket.Out<JsonNode> out = null;

    public RedisSubscriber(WebSocket.In<JsonNode> in, WebSocket.Out<JsonNode> out) {
        this.in = in;
        this.out = out;
    }

    @Override
    public void onMessage(String channel, String message) {
        ObjectNode reply = Json.newObject();
        ArrayNode body = reply.putArray("SUBSCRIBE");
        body.add("message");
        body.add(channel);
        body.add(message);
        out.write(reply);
    }

    @Override
    public void onSubscribe(String channel, int subscribedChannels) {
        ObjectNode reply = Json.newObject();
        ArrayNode body = reply.putArray("SUBSCRIBE");
        body.add("subscribe");
        body.add(channel);
        body.add(subscribedChannels);
        out.write(reply);
    }

    @Override
    public void onUnsubscribe(String channel, int subscribedChannels) {
        ObjectNode reply = Json.newObject();
        ArrayNode body = reply.putArray("SUBSCRIBE");
        body.add("unsubscribe");
        body.add(channel);
        body.add(subscribedChannels);
        out.write(reply);
    }

    @Override
    public void onPSubscribe(String pattern, int subscribedChannels) {
        // TODO
    }

    @Override
    public void onPUnsubscribe(String pattern, int subscribedChannels) {
        // TODO
    }

    @Override
    public void onPMessage(String pattern, String channel, String message) {
        // TODO
    }

}
