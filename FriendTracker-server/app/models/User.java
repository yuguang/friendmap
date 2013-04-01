package models;

import play.*;
import play.mvc.*;
import play.cache.Cache;
import java.sql.SQLException;

import utils.DB;
import java.util.*;

public class User {

    private String ppId;
    private double x, y;
    private int visibility;
    private String devicePin;
    private String skey;

    private static long timelimit = 600000;
    public Timer timer;
    //timer task
    class timeout extends TimerTask {
        public void run() {
            System.out.println(ppId + " timeout!");
            try{
                DB db = DB.getInstance();
                User tmp = new User(ppId, x, y, devicePin, visibility);

                boolean t = db.insertUser(tmp);
            }catch(Exception e){
                Logger.error("(1) " + e.getMessage());
            }
            //if timeout, remove user from cache, and its session key
            //Cache.remove(ppId);
            //Cache.remove(skey);
        }
    }

    public User(String ppId, double x, double y, String devicePin, int visibility) {
        this.ppId = ppId;
        this.x = x;
        this.y = y;
        this.visibility = visibility;
        this.devicePin = devicePin;
        this.timer = new Timer();
        this.skey = "";
    }

    public boolean save(boolean saveToDB) throws SQLException {
        boolean result = true;

        if (saveToDB) {
            DB db = DB.getInstance();
            result = db.insertUser(this);
        }
        Cache.set(ppId, this);
        //start a timer when user enters cache
        timer.schedule(new timeout(),timelimit);
        return result;
    }
    
    public boolean save() throws SQLException {
        return save(false);
    }
    //restart timer
    public void resettimer(){
        timer.cancel();
        timer = new Timer();
        timer.schedule(new timeout(),timelimit);
    }

    public String getppId() {
        return ppId;
    }

    public double getX() {
        return x;
    }

    
    public double getY() {
        return y;
    }

    public String getPin() {
        return devicePin;
    }

    public int getVisibility(){
        return visibility;
    }
   
    public void setSkey(String skey){
        this.skey = skey;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public void setPin(String pin) {
        this.devicePin = pin;
    }
    
    public void setVisibility(int visibility){
        this.visibility = visibility;
    }

}
