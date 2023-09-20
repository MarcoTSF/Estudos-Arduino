int ledPin1 = 9;   // Pino para o primeiro LED
int ledPin2 = 10;  // Pino para o segundo LED
int ledPin3 = 11;  // Pino para o terceiro LED
int potPin = A5;//Atribui o pino analógico A5 a variável potPin
int valorpot = 0;//Variável responsável pelo armazenamento da leitura bruta do potenciometro
int pwm = 0;//Variável responsável pelo armazenamento do valor convertido pela função map

void setup(){
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(potPin, INPUT);//Configura potPin como entrada
  Serial.begin(9600);//Inicializa a serial com velocidade de comunicação de 9600.
}

void loop(){
  valorpot = analogRead(potPin);
  pwm = map(valorpot, 0, 1023, 0, 255);
  Serial.println(pwm);

  analogWrite(ledPin1, pwm);  // Controla o primeiro LED
  analogWrite(ledPin2, pwm); // Controla o segundo LED
  analogWrite(ledPin3, pwm); // Controla o terceiro LED

  delay(500);
}