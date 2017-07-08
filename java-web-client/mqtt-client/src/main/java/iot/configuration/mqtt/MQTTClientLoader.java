package iot.configuration.mqtt;

import iot.models.mqtt.MQTTClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.boot.ApplicationArguments;
import org.springframework.boot.ApplicationRunner;
import org.springframework.stereotype.Component;

import static iot.configuration.mqtt.Constantes.QOS;

/**
 * Created by bruno on 18/06/17.
 */
@Component
public class MQTTClientLoader implements ApplicationRunner {

    private byte[] mensagemBytes = new Integer(1).toString().getBytes();

    @Override
    public void run(ApplicationArguments applicationArguments) throws Exception {
        ConfiguracaoMQTT.configura();

        MqttMessage mensagemMQTT = new MqttMessage(mensagemBytes);
        mensagemMQTT.setQos(QOS);
        try {
            MQTTClient.client.publish("arduino/atualiza/valores", mensagemMQTT);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }
}
