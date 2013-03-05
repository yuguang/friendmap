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
import redis.clients.jedis.Jedis;

import java.io.IOException;
import java.util.HashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Application extends Controller {

    private static HashMap<WebSocket.In<JsonNode>, RedisSubscriber> PubSubMap
        = new HashMap<WebSocket.In<JsonNode>, RedisSubscriber>();

    private static final int NTHREADS = 20;

    private static final ExecutorService exec
        = Executors.newFixedThreadPool(NTHREADS);

    @BodyParser.Of(BodyParser.Json.class)
    public static WebSocket<JsonNode> index() {

        final String ipAddress = request().remoteAddress();

        return new WebSocket<JsonNode>() {
            // called when websocket handshake is done
            public void onReady(final WebSocket.In<JsonNode> in,
                                final WebSocket.Out<JsonNode> out) {
                // for each subscribe message
                in.onMessage(new F.Callback<JsonNode>() {
                    public void invoke(JsonNode event) {
                        final String channel = event.findPath("SUBSCRIBE").getTextValue();
                        if (channel != null) {
                            Logger.info("Subscribing to " + channel + " from " + ipAddress);

                            final RedisSubscriber sub = new RedisSubscriber(in, out);
                            PubSubMap.put(in, sub);
                            exec.execute(new Runnable() {
                                public void run() {
                                    Redis.getJedisInstance().subscribe(sub, channel);
                                }
                            });
                        } else if (event.findPath("GET").getTextValue() != null) {
                            Logger.info("Got GET request from " + ipAddress);
                            final String userId = event.findPath("GET").getTextValue();
                            String value = Redis.getInstance().get(userId);
                            ObjectNode reply = Json.newObject();
                            ArrayNode body = reply.putArray("GET");
                            body.add("message");
                            body.add(userId);
                            body.add(value);
                            out.write(reply);

                            Logger.debug("Get reply - " + value + " sent");
                        }
                    }
                });

                in.onClose(new F.Callback0() {
                    public void invoke() {
                        RedisSubscriber sub = PubSubMap.get(in);
                        if (sub != null) {
                            sub.unsubscribe();
                            Logger.info("Unsubscribed");
                            PubSubMap.remove(in);
                        }
                    }
                });
            }
        };
    }
}
