#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de Wi-Fi (Padrão do Wokwi)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do Broker MQTT (HiveMQ Público)
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* topico_publicacao = "cidade/qualidade_ar/luan";

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos ajustados para o ESP32
const int pinoSensorGas = 34; // Potenciômetro simulando o MQ-135 (Pino Analógico)
const int pinoAtuador = 2;    // LED de Alerta (Pino Digital)

long ultimaMensagem = 0;

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
  Serial.println("\nWiFi conectado.");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao Broker MQTT!");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(pinoAtuador, OUTPUT);
  digitalWrite(pinoAtuador, LOW);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long agora = millis();
  if (agora - ultimaMensagem > 2000) { // Envia dados a cada 2 segundos
    ultimaMensagem = agora;

    int nivelGas = analogRead(pinoSensorGas);
    
    // Lógica do Atuador Local
    if (nivelGas > 2000) {
      digitalWrite(pinoAtuador, HIGH); // Liga o Alerta
    } else {
      digitalWrite(pinoAtuador, LOW);  // Desliga o Alerta
    }

    // Estruturando os dados trafegados em JSON
    String payload = "{\"poluicao_ppm\": " + String(nivelGas) + "}";
    
    Serial.print("Publicando mensagem: ");
    Serial.println(payload);
    
    client.publish(topico_publicacao, payload.c_str());
  }
}
