#include <RHReliableDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

#define TX_ADRESS 1
#define RX_ADRESS 2

uint8_t count = 0;
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
uint8_t tamanho;
uint8_t from;

RH_ASK driver;
RHReliableDatagram gerente(driver, RX_ADRESS);

void setup() {
  Serial.begin(9600);

  if(!gerente.init()) {
    Serial.println("Falha na inicialização");
  }

  pinMode(8, OUTPUT);
}

void loop() {
  if (gerente.available()) {
    tamanho = sizeof(buf);

    if(gerente.recvfromAck(buf, &tamanho, &from)) {
      Serial.println("");
      Serial.println("Recebido de: Transmissor");
      Serial.println("");
      Serial.println("Mensagem:");
      Serial.println((char*)buf);

      if (strcmp((char*)buf, "Acionar LED") == 0) {
        digitalWrite(8, HIGH);
        delay(500);
        digitalWrite(8, LOW);
      }
    } 
  }
}