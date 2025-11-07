#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "54.172.140.81"; // seu IP AWS
const int mqtt_port = 1883; // porta padrão MQTT

#define DHTPIN 15
#define DHTTYPE DHT22
#define LDR_PIN 34

DHT dht(DHTPIN, DHTTYPE);

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32_PassaBola")) {
      Serial.println("Conectado!");
      client.publish("passabola/status", "ESP32 conectado ao MQTT!");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.print("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqtt_port);
  reconnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();


  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();
  int ldrValor = analogRead(LDR_PIN);
  float luminosidade = map(ldrValor, 0, 4095, 0, 100); // converter em %

 
  char mensagem[128];
  snprintf(mensagem, sizeof(mensagem),
           "{\"temperatura\":%.2f, \"umidade\":%.2f, \"luminosidade\":%.2f}",
           temperatura, umidade, luminosidade);

  Serial.print("Enviando MQTT: ");
  Serial.println(mensagem);


  client.publish("passabola/sensores", mensagem);

  delay(5000);
}
