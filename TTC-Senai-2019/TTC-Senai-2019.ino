#include <Ultrasonic.h> // Leitura de distância com o sensor Grove Ultrasonic Ranger v2.0

Ultrasonic ultrasonic(7);

long distancia;

void setup() {
  // Função que roda apenas uma vez, quando ligada ou resetada
  Serial.begin(9600); // Habilita a comunicação serial
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  // Função que roda infinitamente depois que a placa é ligada
  distancia = ultrasonic.MeasureInCentimeters();
  Serial.print(distancia); // 0~400cm
  Serial.println("cm");

  if (distancia < 100) {
    analogWrite(10, 200);
    digitalWrite(8, HIGH);
  }
  else {
    analogWrite(10, 10);
    digitalWrite(8, LOW);
  }

  delay(100);
}