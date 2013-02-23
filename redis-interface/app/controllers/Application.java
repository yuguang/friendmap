package controllers;

import play.*;
import play.mvc.*;
import play.libs.*;
import play.libs.Json;
import org.codehaus.jackson.JsonNode;
import org.codehaus.jackson.node.ObjectNode;
import org.codehaus.jackson.node.ArrayNode;
import org.codehaus.jackson.map.ObjectMapper;

import utils.Redis;
import redis.clients.jedis.JedisPubSub;

import java.io.IOException;
import java.util.HashMap;

public class Application extends Controller {

    private static HashMap<WebSocket.In<JsonNode>, JedisPubSub> PubSubMap = new HashMap<WebSocket.In<JsonNode>, JedisPubSub>();

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

                        final JedisPubSub jPubSub = new JedisPubSub() {
                            public void onMessage(String channel, String message) {
                                ObjectNode reply = Json.newObject();
                                ArrayNode body = reply.putArray("SUBSCRIBE");
                                body.add("message");
                                body.add(channel);
                                body.add(message);
                                out.write(reply);
                            }

                            public void onSubscribe(String channel, int subscribedChannels) {
                                ObjectNode reply = Json.newObject();
                                ArrayNode body = reply.putArray("SUBSCRIBE");
                                body.add("subscribe");
                                body.add(channel);
                                body.add(subscribedChannels);
                                out.write(reply);
                            }

                            public void onUnsubscribe(String channel, int subscribedChannels) {
                                ObjectNode reply = Json.newObject();
                                ArrayNode body = reply.putArray("SUBSCRIBE");
                                body.add("unsubscribe");
                                body.add(channel);
                                body.add(subscribedChannels);
                                out.write(reply);
                            }

                            public void onPSubscribe(String pattern, int subscribedChannels) {
                                // TODO
                            }

                            public void onPUnsubscribe(String pattern, int subscribedChannels) {
                                // TODO
                            }

                            public void onPMessage(String pattern, String channel, String message) {
                                // TODO
                            }
                        };

                        PubSubMap.put(in, jPubSub);

                        //new Thread(new Runnable() {
                        //   public void run() {
                                Redis.getInstance().getJedis().subscribe(jPubSub, channel);
                        //        System.out.println("return!");
                        //    }
                        //}).start();
                        System.out.println("hello");
                    }
                });

                in.onClose(new F.Callback0() {
                    public void invoke() {
                        JedisPubSub jPubSub = PubSubMap.get(in);
                        if (jPubSub != null) {
                            jPubSub.unsubscribe();
                            System.out.println("unsubscribed!!");
                            PubSubMap.remove(in);
                        }
                    }
                });
            }
        };
    }
  
}
