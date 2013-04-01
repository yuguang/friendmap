package utils;

import play.*;
import play.mvc.*;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.Statement;

import models.User;

public class DB {

    private Connection con = null;
    private static DB instance = null;

    private final String dbConn = "jdbc:mysql://localhost:3306/friendtrackerdb";

    private DB() throws SQLException {
        con = DriverManager.getConnection(dbConn, "root", "FriendTracker");
    }

    public static DB getInstance() throws SQLException {
        if (instance == null) {
            instance = new DB();
        }
        return instance;
    }

    private Connection getConnection() throws SQLException {
        if (con == null) {
            con = DriverManager.getConnection(dbConn, "root", "FriendTracker");
        }
        return con;
    }

    public boolean insertUser(User user) throws SQLException {
        String query = "replace into user(ppId,x,y,pin,visibility) values (?,?,?,?,?)";
        int retry = 3;
        while (retry > 0) {
            try {
                PreparedStatement st = getConnection().prepareStatement(query);
                st.setString(1, user.getppId());
                st.setDouble(2, user.getX());
                st.setDouble(3, user.getY());
                st.setString(4, user.getPin());
                st.setInt(5, user.getVisibility());
                st.executeUpdate();
            } catch (SQLException e) {
                con = DriverManager.getConnection(dbConn, "root", "FriendTracker");
                retry--;
                continue;
            }
            break;
        }
        
        if (retry == 0) {
            Logger.error("Failed insertUser due to closed SQLConnection");
        }

        return true;
    }

    public User getUser(String ppId) throws SQLException {
        String query = "select * from user where ppId = ?";
        int retry = 3;
        ResultSet rs = null;
        while (retry > 0) {
            try {
                PreparedStatement st = getConnection().prepareStatement(query);
                st.setString(1, ppId);
                rs = st.executeQuery();
            } catch (SQLException e) {
                con = DriverManager.getConnection(dbConn, "root", "FriendTracker");
                retry--;
                continue;
            }
            break;
        }

        if (retry == 0) {
            Logger.error("Failed insertUser due to closed SQLConnection");
        }


        if (rs != null && rs.next()) {
            User user = new User(ppId, rs.getDouble(3), rs.getDouble(4), rs.getString(5), rs.getInt(6));
            return user;
        } else {
            return null;
        }
    }
}
