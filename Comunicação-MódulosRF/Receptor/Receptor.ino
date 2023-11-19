#include <RHReliableDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

#define TX_ADRESS 1
#define RX_ADRESS 2

uint8_t count = 0;
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
uint8_t tamanho;
uint8_t from;

RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO
RHReliableDatagram gerente(driver, RX_ADRESS);

int motorPin = A5; // Pino analógico A5

const int pinoLed = 8; //PINO DIGITAL UTILIZADO PELO LED

void setup(){
  Serial.begin(9600);

  if(!gerente.init()) {
    Serial.println("Falha na inicialização");
  }

  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
}

void loop(){
  if (gerente.available()) {
    tamanho = sizeof(buf);

    if(gerente.recvfromAck(buf, &tamanho, &from)) {
      Serial.println("");
      Serial.println("Mensagem:");
      Serial.println((char*)buf);

      if (strcmp((char*)buf, "Acionar Sistema") == 0) {
        digitalWrite(pinoLed, HIGH); //ACENDE O LED
        analogWrite(motorPin, 250);
        delay(1000);
        digitalWrite(pinoLed, LOW); //APAGA O LED
        analogWrite(motorPin, 10);
      } else {
        digitalWrite(pinoLed, LOW); //APAGA O LED
        analogWrite(motorPin, 10);
      }
    } 
  }
}