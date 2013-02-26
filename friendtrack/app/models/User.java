package models;

import play.cache.Cache;
import java.sql.SQLException;

import utils.DB;

public class User {

    private String ppId;
    private double x, y;

    public User(String ppId, double x, double y) {
        this.ppId = ppId;
        this.x = x;
        this.y = y;
    }

    public boolean save() throws SQLException {
        return save(false);
    }

    public boolean save(boolean saveToDB) throws SQLException {
        boolean result = true;

        if (saveToDB) {
            DB db = DB.getInstance();
            result = db.insertUser(this);
        }
        Cache.set(ppId, this);

        return result;
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

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

}
