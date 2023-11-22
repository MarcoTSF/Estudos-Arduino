#include <RHReliableDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>

#define TX_ADDRESS 1
#define RX_ADDRESS_2 2
#define RX_ADDRESS_3 3
#define RX_ADDRESS_4 4

RH_ASK driver;
RHReliableDatagram gerente(driver, TX_ADDRESS);

uint8_t count = 1;
uint8_t data[] = "Acionar LED";
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];

const int button_1 = 8;
const int button_2 = 9;
const int button_3 = 10;

void setup() {
  Serial.begin(9600);

  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);

  if (!gerente.init()) {
    Serial.println("Falha na inicialização");
  }
}

void loop() {
  if (digitalRead(button_1) == LOW) {
    Serial.print("");
    Serial.print("Transmitindo mensagem nº");
    Serial.println(count);
    Serial.print("");
    Serial.print("Enviado para: RX_ADDRESS_2");

    if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS_2)) {
      count++;
    }

  } else if (digitalRead(button_2) == LOW) {
    Serial.print("");
    Serial.print("Transmitindo mensagem nº");
    Serial.println(count);
    Serial.print("");
    Serial.print("Enviado para: RX_ADDRESS_3");

    if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS_3)) {
      count++;
    }

  } else if (digitalRead(button_3) == LOW) {
    Serial.print("");
    Serial.print("Transmitindo mensagem nº");
    Serial.println(count);
    Serial.print("");
    Serial.print("Enviado para: RX_ADDRESS_4");

    if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS_4)) {
      count++;
    }

  } else {
    delay(200);
  }
  
  delay(500);
}