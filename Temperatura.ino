#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "LEHSA";
const char* password = "";
const char* mqtt_server = "10.0.0.154";
const int mqtt_port = 1883;
const char* mqtt_topic = "TEMPERATURA";
const char* mqtt_client_id = "arduino_client";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
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

  float aleatorio = random(2000, 2100) / 100.0;

  char temperaturaStr[10];
  dtostrf(aleatorio, 4, 2, temperaturaStr);

  mqttClient.publish(mqtt_topic, temperaturaStr);

  Serial.print("Publicado no tópico ");
  Serial.print(mqtt_topic);
  Serial.print(": ");
  Serial.println(temperaturaStr);

  delay(1000); 
}
