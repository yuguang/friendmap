package utils;

import java.security.SecureRandom;
import java.math.BigInteger;

public class SessionKeyGenerator {

    private SecureRandom random = null;
    private static SessionKeyGenerator instance = null;

    public static synchronized SessionKeyGenerator getInstance() {
        if (instance == null) {
            instance = new SessionKeyGenerator();
        }

        return instance;
    }

    private SessionKeyGenerator() {
        random = new SecureRandom(); 
    }

    public String nextSessionKey() {
        return new BigInteger(130, random).toString(32);
    }

}
