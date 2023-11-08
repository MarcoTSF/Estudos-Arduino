#include <RHReliableDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

#define TX_ADDRESS 1
#define RX_ADDRESS 2

RH_ASK driver;
RHReliableDatagram gerente(driver, TX_ADDRESS);

uint8_t count = 1;
uint8_t data[] = "Acionar LED";
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];

void setup() {
  Serial.begin(9600);

  if (!gerente.init()) {
    Serial.println("Falha na inicialização");
  }
}

void loop() {
  Serial.print("Transmitindo mensagem nº");
  Serial.println(count);

  if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS)) {
    count++;
  }

  delay(500);
}