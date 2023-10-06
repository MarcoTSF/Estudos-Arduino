#include <RH_ASK.h> //INCLUSÃO DE BIBLIOTECA
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA
#include <Ultrasonic.h> // Leitura de distância com o sensor Grove Ultrasonic Ranger v2.0

Ultrasonic ultrasonic(7);

long distancia;

RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO

void setup(){
  Serial.begin(9600); // Habilita a comunicação serial
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(motorPin, OUTPUT);

  driver.init(); //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
}

void loop(){
  distancia = ultrasonic.read();
  Serial.print(distancia); // 0~400cm
  Serial.println("cm");

  const char *msg = "vibrar"; //VARIÁVEL RECEBE O VALOR (motor)

  if (distancia < 100) {
    driver.send((uint8_t *)msg, strlen(msg)); //ENVIA AS INFORMAÇÕES PARA O RECEPTOR (PALAVRA: vibrar)
    driver.waitPacketSent(); //AGUARDA O ENVIO DAS INFORMAÇÕES

    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  else {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }

  delay(100);
}