package iot.configuration.mqtt;

/**
 * Created by bruno on 23/06/17.
 */
public class Constantes {
    public static final int QOS = 1;
    public static final String TOPIC_AREA_1 = "web/area/1/componente/#";
    public static final String TOPIC_AREA_2 = "web/area/2/componente/#";
    public static final String BROKER = "tcp://127.0.0.1:1883";
    public static final String CLIENT_ID = "java_client";
    public static final String USERNAME = "java_client";
    public static final char[] PASSWORD = "java".toCharArray();
}
