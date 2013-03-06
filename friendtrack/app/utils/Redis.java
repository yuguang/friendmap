package utils;

import redis.clients.jedis.Jedis;

public class Redis {

    private static Redis instance = null;
    private Jedis jedis = null;

    public static Redis getInstance() {
        if (instance == null) {
            instance = new Redis();
        }

        return instance;
    }

    private Redis() {
        jedis = new Jedis("127.0.0.1", 6379);
        jedis.auth("friendtracker-pass");
    }

    public void set(String key, String value) {
        String status = jedis.set(key, value);
    }

    public void publish(String key, String message) {
        Long result = jedis.publish(key, message);
    }

}
