package iot.controllers.socket;

import iot.models.mqtt.MQTTClient;
import iot.models.topico.Topico;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.messaging.handler.annotation.DestinationVariable;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.stereotype.Controller;

import static iot.configuration.mqtt.Constantes.QOS;

/**
 * Created by bruno on 09/07/17.
 */
@Controller
public class TopicoControllers {

    @MessageMapping("area/{idArea}/{tipo}/{idComponente}/altera/{acao}")
    public void recebeMensagemEEncaminhaParaBrokerMQTT(@DestinationVariable int idArea,
                                                       @DestinationVariable String tipo,
                                                       @DestinationVariable int idComponente,
                                                       @DestinationVariable String acao, // Altera 'estado' ou 'valor'
                                                       Topico mensagem) {
        enviaEstadoParaOBrokerMQTT(idArea, tipo, idComponente, acao, mensagem.valor);
    }

    private void enviaEstadoParaOBrokerMQTT(int idArea, String tipo, int idComponente, String acao, Integer valor) {
        String identificador = "arduino/area/" + idArea + "/componente/" + idComponente + "/" + tipo + "/" + acao;
        MqttMessage message = new MqttMessage(valor.toString().getBytes());
        message.setQos(QOS);
        try {
            MQTTClient.client.publish(identificador, message);
            System.out.println("PUB - MQTT");
            System.out.println("topic: "+ identificador + ", message: " + message);
        } catch (MqttException e) {
            e.printStackTrace();
        }

    }
}