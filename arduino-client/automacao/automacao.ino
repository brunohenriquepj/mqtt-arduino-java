#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define QOS 1
#define MQTT_PORT 1883
#define CLIENT_ID "arduino_client"
#define CLIENTE_USUARIO "arduino_client"
#define CLIENTE_SENHA "arduino"


byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 101); //IP do Arduino
IPAddress server(192, 168, 0, 102); //IP do Servidor Broker

EthernetClient ethClient;
PubSubClient client(ethClient);

void conecta_cliente();
void callback(char* topic, byte* payload, unsigned int length);
void imprime_erro_de_conexao_mqtt(int estado);

void setup() {
    Serial.begin(9600);
    while(!Serial) {}

    client.setServer(server, MQTT_PORT);
    client.setCallback(callback);
    Ethernet.begin(mac, ip);
    delay(1500);
}


void loop() {
    conecta_cliente();
    delay(1000);
    client.loop();
}


void conecta_cliente() {
    while(!client.connected()) {
        Serial.println("MQTT - Tentativa de conexao com broker...");
        if (client.connect(CLIENT_ID, CLIENTE_USUARIO, CLIENTE_SENHA)) {
            Serial.println("Cliente conectado.");
        }
        else {
            imprime_erro_de_conexao_mqtt(client.state());
            Serial.println("Nova tentativa de conexao em 2 segundos.");
            delay(2000);
        }
    }
}


void callback(char* topic, byte* payload, unsigned int length) {
    char mensagem[length+1];
    int i;
    for (i=0;i<length;i++) {
        mensagem[i] = (char)payload[i];
    }
    mensagem[i++] = '\0';
}


void imprime_erro_de_conexao_mqtt(int estado) {
    Serial.print("ERRO AO CONECTAR CLIENTE. Causa: ");
    Serial.println(estado); // http://pubsubclient.knolleary.net/api.html#state
}


