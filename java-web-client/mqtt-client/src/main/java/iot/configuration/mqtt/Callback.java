package iot.configuration.mqtt;

import iot.models.mqtt.CallbackData;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;

/**
 * Created by bruno on 16/06/17.
 */
public class Callback implements MqttCallback {

    public void connectionLost(Throwable t) {
        ConfiguracaoMQTT.configura();
        t.printStackTrace();
    }

    public void messageArrived(String topic, MqttMessage message) throws Exception {
        CallbackData.dadosMap.put(topic.replace("web/", ""), Integer.parseInt(message.toString()));
        System.out.println("SUB - MQTT");
        System.out.println("tópico: "+ topic + ", mensagem: " + message.toString());
    }

    public void deliveryComplete(IMqttDeliveryToken token) {}
}
