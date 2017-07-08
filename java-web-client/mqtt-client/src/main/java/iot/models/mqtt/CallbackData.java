package iot.models.mqtt;

import java.util.HashMap;

/**
 * Created by bruno on 17/06/17.
 */
public class CallbackData {
    public static HashMap<String, Integer> dadosMap = new HashMap<String, Integer>(){{
        put("area/1/componente/1/lampada/estado", 0);
        put("area/1/componente/1/lampada/valor", 0);
        put("area/1/componente/2/lampada/estado", 0);
        put("area/1/componente/2/lampada/valor", 0);

        put("area/2/componente/1/lampada/estado", 0);
        put("area/2/componente/1/lampada/valor", 0);
        put("area/2/componente/2/lampada/estado", 0);
        put("area/2/componente/2/lampada/valor", 0);
    }};
}
