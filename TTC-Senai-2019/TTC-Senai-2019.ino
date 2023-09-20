#include <Ultrasonic.h> // Leitura de distância com o sensor Grove Ultrasonic Ranger v2.0

Ultrasonic ultrasonic(7);

long distancia;

int motorPin = A5;

void setup() {
  // Função que roda apenas uma vez, quando ligada ou resetada
  Serial.begin(9600); // Habilita a comunicação serial
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // Função que roda infinitamente depois que a placa é ligada
  distancia = ultrasonic.read(); // Correção aqui, remova "CM"
  Serial.print(distancia); // 0~400cm
  Serial.println("cm");

  if (distancia < 100) {
    analogWrite(motorPin, 250);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
  }
  else {
    analogWrite(motorPin, 0);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }

  delay(100);
}