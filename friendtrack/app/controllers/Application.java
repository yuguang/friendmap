package controllers;

import play.*;
import play.mvc.*;
import play.cache.Cache;
import java.sql.SQLException;

import views.html.*;
import views.txt.*;

import play.libs.Json;
import org.codehaus.jackson.JsonNode;
import org.codehaus.jackson.node.ObjectNode;
import org.codehaus.jackson.node.ArrayNode;

import models.User;
import utils.SessionKeyGenerator;
import utils.DB;
import utils.Redis;

public class Application extends Controller {
  
    public static Result index() {
        return ok(index.render("Your new application is ready."));
    }
    
    @BodyParser.Of(BodyParser.Json.class)
    public static Result loginUser() {
        String ipAddress = request().remoteAddress();

        JsonNode inputs = request().body().asJson();
        Logger.info("received " + inputs.toString() + " from " + ipAddress);

        String ppid = inputs.findPath("ppId").getTextValue();
        double x = inputs.findPath("x").getDoubleValue();
        double y = inputs.findPath("y").getDoubleValue();

        ObjectNode reply = Json.newObject();
        User user = null;
        try {
            user = DB.getInstance().getUser(ppid);
            user.setX(x);
            user.setY(y);
            user.save();        // update user on cache
        } catch (Exception e) {
            // add a user if not in DB
            user = new User(ppid, x, y, 1);
            try {
                user.save(true);
            } catch (Exception e2) {
                reply.put("status", "FAIL");
                return ok(reply);
            }
        }

        // create secure session key
        // TODO: doesn't handle multiple session key per user
        String sessionKey
            = SessionKeyGenerator.getInstance().nextSessionKey();
        Cache.set(sessionKey, ppid);

        reply.put("status", "OK");
        reply.put("sessionKey", sessionKey);
        ArrayNode arrayNode = reply.putArray("friends");

        for (JsonNode friend : inputs.findPath("friends")) {
            User obj = (User)Cache.get(friend.getTextValue());
            try {
                if ((obj != null) && !friend.getTextValue().equals(ppid)) {
                    arrayNode.add(friend);
                }
            } catch (Exception e) {
                Logger.error("user " + friend.toString() + " does not exist");
                return ok("user " + friend.toString() + " does not exist");
            }
        }

        return ok(reply);
    }
    
    @BodyParser.Of(BodyParser.Json.class)
	public static Result updateLocation(){
        String ipAddress = request().remoteAddress();

        JsonNode inputs = request().body().asJson();
        Logger.info("received " + inputs.toString() + " from " + ipAddress);

        String ppid = inputs.findPath("ppId").getTextValue();
        double x = inputs.findPath("x").getDoubleValue();
        double y = inputs.findPath("y").getDoubleValue();
        String sessionKey = inputs.findPath("sessionKey").getTextValue();

        Object obj = Cache.get(sessionKey);
        ObjectNode reply = Json.newObject();
        if (((String)obj).equals(ppid)) {
            StringBuilder location = new StringBuilder();
            location.append(Double.toString(x));
            location.append(",");
            location.append(Double.toString(y));
            Redis.getInstance().set(ppid, location.toString());
            Redis.getInstance().publish(ppid, location.toString());
            reply.put("status", "OK");
        } else {
            reply.put("status", "FAIL");
        }

        return ok(reply);
    }

    public static Result setVisibility(int State, String ppid) {
        User user = null;
        try {
            user = DB.getInstance().getUser(ppid);
            user.setVisibility(State);
            user.save(true);
        } catch (Exception e) {
            Logger.error("user " + ppid + " does not exist");
            return ok("user " + ppid + " does not exist");
        }

        String res = "";
        if (State == 0) {
            res = " Invisible";
        } else if (State == 1) {
            res = " visible";
        } else {
            res = " What????";
        }

        return ok(ppid + " is " + res + " now.");
    }
}
