#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "TesteRede";
const char* password = "mqttteste";
const char* mqtt_server = "192.168.137.1";
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

  // Gere um número aleatório entre 20.0 e 21.0
  float aleatorio = random(2000, 2100) / 100.0;

  // Converta o número para uma string
  char temperaturaStr[10];
  dtostrf(aleatorio, 4, 2, temperaturaStr);

  // Publique a temperatura no tópico "TEMPERATURA"
  mqttClient.publish(mqtt_topic, temperaturaStr);

  Serial.print("Publicado no tópico ");
  Serial.print(mqtt_topic);
  Serial.print(": ");
  Serial.println(temperaturaStr);

  delay(1000); // Aguarde 1 segundo antes de publicar o próximo valor
}
