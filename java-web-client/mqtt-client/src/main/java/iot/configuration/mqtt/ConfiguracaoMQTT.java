package iot.configuration.mqtt;

import iot.models.mqtt.MQTTClient;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;

import static iot.configuration.mqtt.Constantes.*;

/**
 * Created by bruno on 16/06/17.
 */
public class ConfiguracaoMQTT {

    public static void configura() {
        conecta();
    }

    private static void conecta() {
        try {
            MqttClient client = new MqttClient(BROKER, CLIENT_ID);
            if (!client.isConnected()) {
                MqttConnectOptions connOpts = new MqttConnectOptions();
                connOpts.setUserName(USERNAME);
                connOpts.setPassword(PASSWORD);
                connOpts.setCleanSession(true);
                System.out.println("Conectando ao broker: " + BROKER);
                client.setCallback(new Callback());
                client.connect(connOpts);
                System.out.println("Conectado no broker");
                MQTTClient.client = client;
            }
            client.subscribe(new String[]{TOPIC_AREA_1, TOPIC_AREA_2});
            System.out.println("Subscribe tópicos");
        } catch(MqttException me) {
            System.out.println("Erro de conexão com broker");
            System.out.println("Código da causa: "+me.getReasonCode());
            System.out.println("Mensagem de erro: "+me.getMessage());
            System.out.println("Causa: "+me.getCause());
            me.printStackTrace();
        }
    }
}
