#include <RH_ASK.h> //INCLUSÃO DE BIBLIOTECA
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA

RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO

int motorPin = A5; // Pino analógico A5

const int pinoLed = 8; //PINO DIGITAL UTILIZADO PELO LED
String str = ""; //VARIÁVEL DO TIPO STRING

void setup(){
  driver.init(); //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
}
void loop(){
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN]; //LÊ A MENSAGEM RECEBIDA (PALAVRA: vibrar)
  uint8_t buflen = sizeof(buf); //CRIA O COMPRIMENTO DO BUFFER PARA O TAMANHO DE buf

  if (driver.recv(buf, &buflen)) { //SE O DRIVER RECEBEU buf(INTEIRO) E buflen (COMPRIMENTO DE DADOS), FAZ
    str = ""; //VARIÁVEL RECEBE VAZIO
    int i; //VARIÁVEL LOCAL DO TIPO INTEIRO
      
    for (int i = 0; i < buflen; i++) { //PARA i IGUAL A 0, ENQUANTO i MENOR QUE buflen, INCREMENTA i
    str += (char)buf[i]; //VARIÁVEL RECEBE OS CARACTERES E FORMA A PALAVRA
    }
    
    if (str.equals("vibrar")) { //SE str FOR IGUAL A "vibrar", FAZ
      digitalWrite(pinoLed, HIGH); //ACENDE O LED
      analogWrite(motorPin, 250);
    }
    else {
      digitalWrite(pinoLed, LOW); //APAGA O LED
      analogWrite(motorPin, 10);
    }
  }
}