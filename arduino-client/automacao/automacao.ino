#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

#define QOS 1
#define MQTT_PORT 1883
#define CLIENT_ID "arduino_client"
#define CLIENTE_USUARIO "arduino_client"
#define CLIENTE_SENHA "arduino"

#define LAMPADA1_AREA1_ESTADO_TOPICO_SUB "arduino/area/1/componente/1/lampada/estado"
#define LAMPADA1_AREA1_VALOR_TOPICO_SUB "arduino/area/1/componente/1/lampada/valor"
#define LAMPADA2_AREA1_ESTADO_TOPICO_SUB "arduino/area/1/componente/2/lampada/estado"
#define LAMPADA2_AREA1_VALOR_TOPICO_SUB "arduino/area/1/componente/2/lampada/valor"
#define LAMPADA1_AREA2_ESTADO_TOPICO_SUB "arduino/area/2/componente/1/lampada/estado"
#define LAMPADA1_AREA2_VALOR_TOPICO_SUB "arduino/area/2/componente/1/lampada/valor"
#define LAMPADA2_AREA2_ESTADO_TOPICO_SUB "arduino/area/2/componente/2/lampada/estado"
#define LAMPADA2_AREA2_VALOR_TOPICO_SUB "arduino/area/2/componente/2/lampada/valor"
#define ATUALIZA_VALORES_TOPICO_SUB "arduino/atualiza/valores"

#define LAMPADA1_AREA1_ESTADO_TOPICO_PUB "web/area/1/componente/1/lampada/estado"
#define LAMPADA1_AREA1_VALOR_TOPICO_PUB "web/area/1/componente/1/lampada/valor"
#define LAMPADA2_AREA1_ESTADO_TOPICO_PUB "web/area/1/componente/2/lampada/estado"
#define LAMPADA2_AREA1_VALOR_TOPICO_PUB "web/area/1/componente/2/lampada/valor"
#define TEMPERATURA_AREA1_RANGE_TOPICO_PUB "web/area/1/componente/1/temperatura/valor"
#define LAMPADA1_AREA2_ESTADO_TOPICO_PUB "web/area/2/componente/1/lampada/estado"
#define LAMPADA1_AREA2_VALOR_TOPICO_PUB "web/area/2/componente/1/lampada/valor"
#define LAMPADA2_AREA2_ESTADO_TOPICO_PUB "web/area/2/componente/2/lampada/estado"
#define LAMPADA2_AREA2_VALOR_TOPICO_PUB "web/area/2/componente/2/lampada/valor"
#define TEMPERATURA_AREA2_RANGE_TOPICO_PUB "web/area/2/componente/1/temperatura/valor"
#define ATUALIZA_VALORES_TOPICO_PUB "web/atualiza/valores"


byte mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 101); //IP do Arduino
IPAddress server(192, 168, 0, 102); //IP do Servidor Broker

EthernetClient ethClient;
PubSubClient client(ethClient);


struct AREA {
    int estado_lampada1;
    int estado_lampada2;
    int range_lampada1;
    int range_lampada2;
    int range_temperatura;
};

AREA area1 = { 0, 0, 0, 0, 0 }, area2 = { 0, 0, 0, 0, 0 };

int pino_area1_lampada1 = 2;
int pino_area1_lampada2 = 3;
int pino_area1_analogico_temperatura = 3;

int pino_area2_lampada1 = 4;
int pino_area2_lampada2 = 5;
int pino_area2_analogico_temperatura = 5;

int base_conversao = 10;
int tamanho_copy = 50;
int cont_segundo = 0;

void conecta_cliente();
void callback(char* topic, byte* payload, unsigned int length);
void imprime_erro_de_conexao_mqtt(int estado);
void subscribe_topicos();
void inicializa_componentes();
void configura_pin_mode();
void pega_valor_da_temperatura_e_publica(int delay_temperatura);

void setup() {
    Serial.begin(9600);
    while(!Serial) {}

    client.setServer(server, MQTT_PORT);
    client.setCallback(callback);
    Ethernet.begin(mac, ip);
    delay(1500);

    configura_pin_mode();
    inicializa_componentes();
}

void loop() {
    conecta_cliente();
    pega_valor_da_temperatura_e_publica(5);
    delay(1000);
    client.loop();
}

void conecta_cliente() {
    while(!client.connected()) {
        Serial.println("MQTT - Tentativa de conexao com broker...");
        if (client.connect(CLIENT_ID, CLIENTE_USUARIO, CLIENTE_SENHA)) {
            Serial.println("Cliente conectado.");
            subscribe_topicos();
            envia_informacoes();
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

void subscribe_topicos() {
    Serial.println("Inscrevendo em topicos.");
    if (client.connected()) {
        // AREA 1
        client.subscribe(LAMPADA1_AREA1_ESTADO_TOPICO_SUB, QOS);
        client.subscribe(LAMPADA1_AREA1_VALOR_TOPICO_SUB, QOS);
        client.subscribe(LAMPADA2_AREA1_ESTADO_TOPICO_SUB, QOS);
        client.subscribe(LAMPADA2_AREA1_VALOR_TOPICO_SUB, QOS);
        // AREA 2
        client.subscribe(LAMPADA1_AREA2_ESTADO_TOPICO_SUB, QOS);
        client.subscribe(LAMPADA1_AREA2_VALOR_TOPICO_SUB, QOS);
        client.subscribe(LAMPADA2_AREA2_ESTADO_TOPICO_SUB, QOS);
        client.subscribe(LAMPADA2_AREA2_VALOR_TOPICO_SUB, QOS);

        // Atualiza valores
        client.subscribe(ATUALIZA_VALORES_TOPICO_SUB, QOS);
    }
}

void envia_informacoes() {
    Serial.println("Publicando (enviando) informacoes.");
    char copy[tamanho_copy];

    // AREA 1
    itoa(area1.estado_lampada1, copy, base_conversao);
    client.publish(LAMPADA1_AREA1_ESTADO_TOPICO_PUB, copy);
    itoa(area1.range_lampada1, copy, base_conversao);
    client.publish(LAMPADA1_AREA1_VALOR_TOPICO_PUB, copy);
    itoa(area1.estado_lampada2, copy, base_conversao);
    client.publish(LAMPADA2_AREA1_ESTADO_TOPICO_PUB, copy);
    itoa(area1.range_lampada2, copy, base_conversao);
    client.publish(LAMPADA2_AREA1_VALOR_TOPICO_PUB, copy);

    // AREA 2
    itoa(area2.estado_lampada1, copy, base_conversao);
    client.publish(LAMPADA1_AREA2_ESTADO_TOPICO_PUB, copy);
    itoa(area2.range_lampada1, copy, base_conversao);
    client.publish(LAMPADA1_AREA2_VALOR_TOPICO_PUB, copy);
    itoa(area2.estado_lampada2, copy, base_conversao);
    client.publish(LAMPADA2_AREA2_ESTADO_TOPICO_PUB, copy);
    itoa(area2.range_lampada2, copy, base_conversao);
    client.publish(LAMPADA2_AREA2_VALOR_TOPICO_PUB, copy);

    pega_valor_da_temperatura_e_publica(0);
}

void configura_pin_mode() {
    Serial.println("Configura pinMode");
    // AREA 1
    pinMode(pino_area1_lampada1, OUTPUT);
    pinMode(pino_area1_lampada2, OUTPUT);

    // AREA 2
    pinMode(pino_area2_lampada1, OUTPUT);
    pinMode(pino_area2_lampada2, OUTPUT);
    delay(1000);
}

void inicializa_componentes() {
    Serial.println("Inicializa componentes");
    // AREA 1
    digitalWrite(pino_area1_lampada1, LOW);
    digitalWrite(pino_area1_lampada2, LOW);

    // AREA 2
    digitalWrite(pino_area2_lampada1, LOW);
    digitalWrite(pino_area2_lampada2, LOW);
    delay(1000);
}

void pega_valor_da_temperatura_e_publica(int delay_temperatura) {
    char buffer[50];

    if (cont_segundo >= delay_temperatura) {
        float temperatura_area1 = (5.0 * analogRead(pino_area1_analogico_temperatura) * 100.0) / 1024.0;
        float temperatura_area2 = (5.0 * analogRead(pino_area2_analogico_temperatura) * 100.0) / 1024.0;
        client.publish(TEMPERATURA_AREA1_RANGE_TOPICO_PUB, itoa(temperatura_area1, buffer, base_conversao));
        client.publish(TEMPERATURA_AREA2_RANGE_TOPICO_PUB, itoa(temperatura_area2, buffer, base_conversao));
        cont_segundo = 0;
    }
    cont_segundo++;
}
