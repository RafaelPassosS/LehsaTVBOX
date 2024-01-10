#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <ArduinoJson.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "TesteRede";
const char* password = "mqttteste";
const char* mqtt_server = "10.0.0.154";
const int mqtt_port = 1883;
const char* mqtt_topic = "TEMPERATURA_HUMIDADE";
const char* mqtt_client_id = "Temperatura_Humidade";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(9600);
  setup_wifi();
  dht.begin();
  mqttClient.setServer(mqtt_server, mqtt_port);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (!mqttClient.connected()) {
    Serial.print("Conectando ao servidor MQTT...");
    if (mqttClient.connect(mqtt_client_id)) {
      Serial.println("Conectado");
    } else {
      Serial.print("Falha na conexão. Tentando novamente em 5 segundos.");
      delay(5000);
      return;
    }
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Falha ao ler do sensor DHT!"));
    return;
  }

  String tempTopic = mqtt_topic;
  tempTopic += "/temperatura";

  String humiTopic = mqtt_topic;
  humiTopic += "/umidade";

  mqttClient.publish(tempTopic.c_str(), String(t).c_str());
  mqttClient.publish(humiTopic.c_str(), String(h).c_str());

  delay(2000);
}
