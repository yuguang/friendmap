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
    
    public static boolean Addnew(String ppid, double X, double Y){
        //Add to DB
        return true;
    }
    
    //add login verification here
    public static boolean verify(String ppid){
        //search SQL;
        return true;
    }
    
    public static void updateloc(){
        //update DB
    }
    
    @BodyParser.Of(BodyParser.Json.class)
    public static Result loginUser() {
        JsonNode inputs = request().body().asJson();
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
            user = new User(ppid, x, y);
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
            Object obj = Cache.get(friend.getTextValue());
            if ((obj != null) && !friend.getTextValue().equals(ppid)) {
                arrayNode.add(friend);
            }
        }

        return ok(reply);
    }
    
    @BodyParser.Of(BodyParser.Json.class)
	public static Result updateLocation(){
        JsonNode inputs = request().body().asJson();
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

}
