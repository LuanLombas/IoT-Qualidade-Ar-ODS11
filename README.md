# IoT-Qualidade-Ar-ODS11

# Sistema IoT de Monitoramento da Qualidade do Ar (ODS 11)

## 1. Descrição do Funcionamento e Uso
Este projeto é um protótipo IoT focado no monitoramento de poluição do ar em ambientes urbanos (ODS 11). Ele lê dados de um sensor analógico e, em caso de alerta (limite > 2000), aciona um LED de aviso. Simultaneamente, envia os dados via Wi-Fi e protocolo MQTT para um broker público em formato JSON.
Para reproduzir:
1. Acesse o simulador Wokwi (ou monte na protoboard).
2. Carregue o código fonte `main.ino`.
3. Conecte-se a um cliente MQTT (como o MQTT Explorer) no broker `broker.hivemq.com`, assinando o tópico `cidade/qualidade_ar/luan`.

## 2. Software e Documentação do Código
O firmware foi desenvolvido em C++ para a Arduino IDE. Utiliza as bibliotecas `ESP8266WiFi.h` (gestão de rede) e `PubSubClient.h` (mensageria MQTT). O código estrutura o *payload* da poluição em JSON e envia a cada 2 segundos.

## 3. Descrição do Hardware
- **Microcontrolador:** NodeMCU (ESP8266) - atua como processador central e gateway Wi-Fi.
- **Sensor:** Potenciômetro (emulando a resposta analógica de um Sensor de Gás MQ-135). Ligado ao pino A0.
- **Atuador:** LED Vermelho de 5mm com resistor de 220 ohms (emulando sinalizador/buzzer). Ligado ao pino D1.

## 4. Interfaces, Protocolos e Comunicação
- **Protocolo de Rede:** TCP/IP via rede Wi-Fi (Padrão 802.11 b/g/n).
- **Protocolo de Mensageria:** MQTT operando na porta 1883. Arquitetura Publish/Subscribe.
