package models;

import play.cache.Cache;
import java.sql.SQLException;

import utils.DB;

public class User {

    private String ppId;
    private double x, y;
    private int visibility;

    public User(String ppId, double x, double y, int visibility) {
        this.ppId = ppId;
        this.x = x;
        this.y = y;
        this.visibility = visibility;
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

    public int getVisiblity() {
        return visibility;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public void setVisibility(int visibility) {
        this.visibility = visibility;
    }
}
