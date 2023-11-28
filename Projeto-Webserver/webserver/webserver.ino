#include <Ethernet.h>
#include <ArduinoJson.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 100);

// Cria um servidor web na porta 80
EthernetServer server(80);

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Inicializa a conexão Ethernet e o servidor
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("Servidor Web Iniciado. Aguarde as requisições...");
}

void loop() {
  // Escutando novas conexões
  EthernetClient client = server.available();

  if (client) {
    Serial.println("Novo Cliente Conectado");
    // Aguardando a solicitação HTTP
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        // Verifica se a solicitação HTTP é concluída
        if (c == '\n') {
          // Leitura dos dados das portas analógicas A0, A1 e A2
          int analogValueA0 = analogRead(A0);
          int analogValueA1 = analogRead(A1);
          int analogValueA2 = analogRead(A2);

          // Cria um objeto JSON
          StaticJsonDocument<200> jsonDocument;
          jsonDocument["A0"] = analogValueA0;
          jsonDocument["A1"] = analogValueA1;
          jsonDocument["A2"] = analogValueA2;

          // Converte o objeto JSON em uma string
          String jsonString;
          serializeJson(jsonDocument, jsonString);

          // Envia os dados como resposta POST no formato JSON com cabeçalhos CORS
          client.println("HTTP/1.1 200 OK");
          client.println("Access-Control-Allow-Origin: *"); // Permitir qualquer origem (em produção, especifique origin(s) específico(s))
          client.println("Content-Type: application/json");
          client.println("Connection: close");
          client.println();
          client.println(jsonString);
          break;
        }
      }
    }

    // Fecha a conexão
    delay(1);
    client.stop();
    Serial.println("Cliente Desconectado");
  }
}
