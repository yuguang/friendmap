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
//import utils.Channel;

import java.io.IOException;
import java.util.HashMap;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Application extends Controller {

    private static final int NTHREADS = 5;
    private static final ExecutorService executor
        = Executors.newFixedThreadPool(NTHREADS);

    // asynchronously send GET reply through out WebSocket
    private static void sendResponse(String userId, Future<String> futureVal, WebSocket.Out<JsonNode> out) {
        try {
            String val = futureVal.get();
            ObjectNode reply = Json.newObject();
            ArrayNode body = reply.putArray("GET");
            body.add("message");
            body.add(userId);
            body.add(val);
            out.write(reply);
        } catch (InterruptedException e) {
            Logger.error("sending response to " + userId + " was interrupted.");
        } catch (ExecutionException e) {
            Logger.error("execution exception " + userId + " " + e.getMessage());
        }
    }

    @BodyParser.Of(BodyParser.Json.class)
    public static Result getLocations() {
        String ipAddress = request().remoteAddress();
        JsonNode inputs = request().body().asJson();

        Logger.info("received " + inputs.toString() + " from " + ipAddress);

        // request format: "friends": [ ppId1, ppId2, ... ]
        // reply format: "location: [ {"ppId": ppId1, "x": x, "y": y, "v": 1}, ... ]
        ObjectNode reply = Json.newObject();
        reply.put("type", "location");
        reply.put("status", "OK");
        ArrayNode body = reply.putArray("friends");
        int count = 0;
        for (JsonNode friend : inputs.findPath("friends")) {
            String val = Redis.getInstance().getSync(friend.getTextValue());
            if (val != null) {
                body.add(val);
            }
        }
        return ok(reply);
    }

        
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
                        Logger.info("received " + event.toString() + " from " + ipAddress);
                        final String channel = event.findPath("SUBSCRIBE").getTextValue();
                        if (channel != null) {
                            // subscribe through async connection
                            Redis.getInstance().subscribe(channel, out);
                        } else if (event.findPath("GET").getTextValue() != null) {
                            final String userId = event.findPath("GET").getTextValue();
                            final Future<String> val = Redis.getInstance().get(userId);
                            executor.execute(new Runnable() {
                                public void run() {
                                    sendResponse(userId, val, out);
                                }
                            });
                        }
                    }
                });

                in.onClose(new F.Callback0() {
                    public void invoke() {
                        // remove websocket from subscription list
                        Redis.getInstance().unsubscribe(ipAddress, out);
                        Logger.info("unsubscribe client " + ipAddress);
                    }
                });
            }
        };
    }
}
