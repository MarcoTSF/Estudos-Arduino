#include <Servo.h>

Servo servo1; // Cria um objeto baseado na biblioteca Servo
Servo servo2;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  servo1.attach(9); // Diz que o objeto "myservo" está ligado ao pino 9
  servo2.attach(11);
}

void loop() {
  int sensorVal = digitalRead(2);
  int sensorDoisVal = digitalRead(4);
  Serial.println(sensorVal + " = Interruptor 1");
  Serial.println(sensorDoisVal + " = Interruptor 2");

  if (sensorVal == HIGH && sensorDoisVal == HIGH) {
    servo1.write(90);
    servo2.write(90);
  } else if (sensorVal == HIGH && sensorDoisVal == LOW) {
    servo1.write(90);
    servo2.write(0);
  } else if (sensorVal == LOW && sensorDoisVal == HIGH) {
    servo1.write(0);
    servo2.write(90);
  } else {
    servo1.write(0);
    servo2.write(0);
  }
}
