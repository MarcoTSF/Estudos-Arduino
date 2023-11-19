#include <RHReliableDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

#define TX_ADDRESS 2
#define RX_ADDRESS 66

RH_ASK driver;
RHReliableDatagram gerente(driver, TX_ADDRESS);

uint8_t count = 1;
uint8_t data[] = "Acionar LED";
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
uint8_t tamanho;
uint8_t from;


void setup() {
  Serial.begin(9600);

  if (!gerente.init()) {
    Serial.println("Falha na inicialização");
  }
  pinMode(8, OUTPUT);
}

void loop() {
  // codigo transmissor

  Serial.print("Transmitindo mensagem nº");
  Serial.println(count);

  if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS)) {
    count++;
  }

  delay(500);

  // codigo receptor

  if (gerente.available()) {
    tamanho = sizeof(buf);

    if(gerente.recvfromAck(buf, &tamanho, &from)) {
      Serial.println("");
      Serial.println("Recebido de: Marco e Lucas");
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
