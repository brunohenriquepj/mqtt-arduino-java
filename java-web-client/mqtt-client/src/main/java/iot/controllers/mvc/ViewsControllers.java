package iot.controllers.mvc;

import iot.models.mqtt.CallbackData;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by bruno on 09/07/17.
 */
@Controller
public class ViewsControllers {
    @GetMapping("/")
    public String index(Map<String, Object> model) {
        model.put("idArea", 0);
        return "index";
    }

    @GetMapping("/area/{id}")
    public String area(@PathVariable int id, Map<String, Object> model) {
        addDadosIniciaisDaAreaAoModel(model, id);
        model.put("idArea", id);
        return "area";
    }

    public void addDadosIniciaisDaAreaAoModel(Map<String, Object> model, int idArea) {
        HashMap<String, Integer> dadosMap = new HashMap<>();
        dadosMap.putAll(CallbackData.dadosMap);

        dadosMap.forEach((identificador, valor) -> {
            if (identificador.startsWith("area/" + idArea + "/")) {
                if (identificador.endsWith("/componente/1/temperatura/valor")) {
                    model.put("temperaturaValor", valor);
                } else if (identificador.endsWith("/componente/1/lampada/estado")) {
                    model.put("lampada1Estado", valor);
                } else if (identificador.endsWith("/componente/2/lampada/estado")) {
                    model.put("lampada2Estado", valor);
                } else if (identificador.endsWith("/componente/1/lampada/valor")) {
                    model.put("lampada1Valor", valor);
                } else if (identificador.endsWith("/componente/2/lampada/valor")) {
                    model.put("lampada2Valor", valor);
                }
            }
        });
    }
}
