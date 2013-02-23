package controllers;

import play.*;
import play.mvc.*;
import play.libs.*;
import play.libs.Json;
import play.libs.F.Function;
import play.libs.Akka;
import static play.mvc.Results.async;
import static akka.pattern.Patterns.ask;

import akka.actor.*;

import org.codehaus.jackson.JsonNode;
import org.codehaus.jackson.node.ObjectNode;
import org.codehaus.jackson.node.ArrayNode;
import org.codehaus.jackson.map.ObjectMapper;

import utils.Redis;
import models.RedisSubscriber;
import redis.clients.jedis.JedisPubSub;

import java.io.IOException;
import java.util.HashMap;

public class Application extends Controller {

    private static HashMap<WebSocket.In<JsonNode>, RedisSubscriber> PubSubMap
        = new HashMap<WebSocket.In<JsonNode>, RedisSubscriber>();

    @BodyParser.Of(BodyParser.Json.class)
    public static WebSocket<JsonNode> index() {
        return new WebSocket<JsonNode>() {
            // called when websocket handshake is done
            public void onReady(final WebSocket.In<JsonNode> in,
                                final WebSocket.Out<JsonNode> out) {
                // for each subscribe message
                in.onMessage(new F.Callback<JsonNode>() {
                    public void invoke(JsonNode event) {
                        final String channel = event.findPath("SUBSCRIBE").getTextValue();
                        System.out.println("Subscribing to " + channel);

                        RedisSubscriber sub = new RedisSubscriber(in, out);
                        PubSubMap.put(in, sub);
                        Redis.getInstance().getJedis().subscribe(sub, channel);
                        System.out.println("hello");
                    }
                });

                in.onClose(new F.Callback0() {
                    public void invoke() {
                        RedisSubscriber sub = PubSubMap.get(in);
                        if (sub != null) {
                            sub.unsubscribe();
                            System.out.println("unsubscribed!!");
                            PubSubMap.remove(in);
                        }
                    }
                });
            }
        };
    }
}
