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

import java.util.HashMap;

public class Application extends Controller {
  
    public static Result index() {
        return ok(index.render("Your new application is ready."));
    }

    static HashMap<String, String> ppIdToPinMap = new HashMap<String, String>();

    @BodyParser.Of(BodyParser.Json.class)
    public static Result loginUser() {
        String ipAddress = request().remoteAddress();
        JsonNode inputs = request().body().asJson();

        Logger.info("received " + inputs.toString() + " from " + ipAddress);

        String ppid = inputs.findPath("ppId").getTextValue();
        double x = inputs.findPath("x").getDoubleValue();
        double y = inputs.findPath("y").getDoubleValue();
        String devicePin = inputs.findPath("pin").getTextValue();

        System.out.println(devicePin);

       // create secure session key
       // TODO: doesn't handle multiple session key per user
        String sessionKey = SessionKeyGenerator.getInstance().nextSessionKey();

        ObjectNode reply = Json.newObject();
        User user = null;
        try {
            user = DB.getInstance().getUser(ppid);
            user.setX(x);
            user.setY(y);
            user.setPin(devicePin);
            user.setVisibility(1);
            user.save();        // update user on cache
            user.setSkey(sessionKey);
        } catch (Exception e) {
            // add a user if not in DB， default visibility 1
            user = new User(ppid, x, y, devicePin, 1);
            user.setSkey(sessionKey);
            try {
                user.save(true);
            } catch (Exception e2) {
                Logger.info("(2) " + e2.getMessage());
                reply.put("status", "FAIL");
                return ok(reply);
            }
        }

        ppIdToPinMap.put(ppid, devicePin);

        //put session key in cache
        Cache.set(sessionKey, user);
        reply.put("type", "login");
        reply.put("status", "OK");
        reply.put("sessionKey", sessionKey);
        ArrayNode friends = reply.putArray("friends");
        ArrayNode pins = reply.putArray("pins");

        for (JsonNode friend : inputs.findPath("friends")) {
            User obj = (User)Cache.get(friend.getTextValue());
            if (obj != null && !friend.getTextValue().equals(ppid)) {
                friends.add(friend);
                String pin = ppIdToPinMap.get(friend.getTextValue());
                pins.add((pin == null ? "" : pin));
            }
        }
/*
        String tmp = "[";  
        for (JsonNode friend : inputs.findPath("friends")) {
            User obj = (User)Cache.get(friend.getTextValue());
            try{
                if ((obj != null) && !friend.getTextValue().equals(ppid)){// && obj.getVisibility() == 1) {
                    //arrayNode.add(friend);
                    tmp = tmp + obj.getppId() + ", ";
                }
            }catch(Exception e){
                Logger.error("user " + friend.toString() + " does not exist");
                return ok("user not exist");
            }
        }
        if(tmp.length() > 2){
            tmp = tmp.substring(0,tmp.length()-2);
        }
        tmp = tmp + "]";
*/
        //reply.put("friends",tmp);
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
        int v = inputs.findPath("v").getIntValue(); 
        String sessionKey = inputs.findPath("sessionKey").getTextValue();
        //get ppid from Cache with session key
        User user = null;
        try{
            user = (User)Cache.get(sessionKey);
        }catch(Exception e){
            Logger.info("sessionKey " + sessionKey + " expired. Needs re-login");
            return ok("sessionKey expired. Need re-login");
        }

        // Cache.get() returns NULL
        if (user == null) {
            Logger.info("user not logged in");
            return ok("User not logged in.");
        }

        try{
            user.setX(x);
            user.setY(y);
            user.setVisibility(v);
            user.save();
            user.resettimer();
        }catch(Exception e){
            Logger.info("updating user " + user.getppId() + " failed.");
            return ok("User not logged in.");
            //System.out.println(e.getMessage());
        }

        ObjectNode reply = Json.newObject();
        reply.put("type", "update");
        //update only if ppid from cache matches ppid from input
        if (user.getppId().equals(ppid)) {
            StringBuilder location = new StringBuilder();
            location.append(Double.toString(x));
            location.append(",");
            location.append(Double.toString(y));
           //Add visibility to redis
            location.append(",");
            location.append(Integer.toString(v));
            Redis.getInstance().set(ppid, location.toString());
            Redis.getInstance().publish(ppid, location.toString());
            //setVisibility(v,ppid);
            reply.put("status", "OK");
        } else {
            reply.put("status", "FAIL");
        }

        return ok(reply);
    }

    @BodyParser.Of(BodyParser.Json.class)
    public statuc Result updateVisibility() {
        String ipAddress = request().remoteAddress();

        JsonNode inputs = request().body().asJson();
        Logger.info("received " + inputs.toString() + " from " + ipAddress);

        String ppid = inputs.findPath("ppId").getTextValue();
        int v = inputs.findPath("v").getIntValue();
        String sessionKey = inputs.findPath("sessionKey").getTextValue();

        User user = null;
        try {
            user = (User)Cache.get(sessionKey);
        } catch (Exception e) {
            Logger.info("sessionKey " + sessionKey + " expired. Needs re-login");
            return ok("sessionKey expired. Need re-login");
        }

        if (user == null) {
            Logger.info("user not logged in");
            return ok("User not logged in.");
        }

        try {
            user.setVisibility(v);
            user.save();
            user.resettimer();
        } catch (Exception e) {
            Logger.info("update visibility for user " + user.getppId() + " failed.");
        }
}
