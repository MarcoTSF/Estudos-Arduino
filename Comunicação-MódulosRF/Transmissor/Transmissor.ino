#include <RHReliableDatagram.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <Ultrasonic.h> // Leitura de distância com o sensor Grove Ultrasonic Ranger v2.0

Ultrasonic ultrasonic(7);

long distancia;

#define TX_ADDRESS 1
#define RX_ADDRESS 2

RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO
RHReliableDatagram gerente(driver, TX_ADDRESS);

uint8_t count = 1;
uint8_t data[] = "Acionar Sistema";
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];

void setup(){
  Serial.begin(9600); // Habilita a comunicação serial

  if (!gerente.init()) {
    Serial.println("Falha na inicialização");
  }

  pinMode(7, OUTPUT); // Ultrasonic
  pinMode(8, OUTPUT); // Led
  pinMode(9, OUTPUT); // Led
}

void loop(){
  distancia = ultrasonic.read();
  Serial.print(distancia); // 0~400cm
  Serial.println("cm");

  if (distancia < 150) {
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    
    Serial.print("Transmitindo mensagem nº");
    Serial.println(count);
    Serial.print("");

    if (!gerente.sendtoWait(data, sizeof(data), RX_ADDRESS)) {
      count++;
    }
  } else {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }

  delay(200);
}