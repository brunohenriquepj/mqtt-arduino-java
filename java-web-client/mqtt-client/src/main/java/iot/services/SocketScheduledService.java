package iot.services;

import iot.models.topico.Topico;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.stereotype.Service;

import java.util.HashMap;

/**
 * Created by bruno on 09/07/17.
 */
@Service
public class SocketScheduledService {

    private SimpMessagingTemplate template;

    @Autowired
    public SocketScheduledService(SimpMessagingTemplate template) {
        this.template = template;
    }

    public void enviaDadoAosSocketsClientes(HashMap<String, Integer> dadosMap) {
        dadosMap.forEach((identificador, valor) -> {
            Topico topico;
            if (identificador.startsWith("area/1/")) {
                topico = new Topico(identificador, valor);
                template.convertAndSend("/topic/area/1", topico);
            } else if (identificador.startsWith("area/2/")) {
                topico = new Topico(identificador, valor);
                template.convertAndSend("/topic/area/2", topico);
            }
        });
    }
}
