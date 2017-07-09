package iot.scheduleds;

import iot.configuration.mqtt.ConfiguracaoMQTT;
import iot.models.mqtt.CallbackData;
import iot.services.SocketScheduledService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import java.util.HashMap;

/**
 * Created by bruno on 09/07/17.
 */
@Component
public class SocketScheduledTasks {

    private ConfiguracaoMQTT configuracaoMQTT = new ConfiguracaoMQTT();
    private SocketScheduledService socketScheduledService;
    private HashMap<String, Integer> dadosMap = new HashMap<>();

    @Autowired
    public SocketScheduledTasks(SocketScheduledService socketScheduledService) {
        this.socketScheduledService = socketScheduledService;
    }

    @Scheduled(fixedRate = 100)
    public void enviaDadoAosSocketsClientesTask() {
        if (!CallbackData.dadosMap.isEmpty() && !dadosMap.equals(CallbackData.dadosMap)) {
            dadosMap.clear();
            dadosMap.putAll(CallbackData.dadosMap);
            socketScheduledService.enviaDadoAosSocketsClientes(dadosMap);
        }
    }
}
