// Bibliotecas e Definições
#include "Stepper.h"
const int stepsPerRevolution = 32;

volatile boolean GiroIdentificado;   // Variável para a interrupção
volatile boolean RotDirection;       // Direção rotação encoder

// Terminais de conexão do Encoder
const int PinoCLK = 2;   
const int PinoDT = 3;    
const int PinoSW = 4;    

// Declaração de variáveis utilizadas para a posição e led
int led = 6;    
int RotPosition = 0;    
int PrevPosition;     
int Steps;      

// Configuração do motor de passo
Stepper MotorStepper(stepsPerRevolution, 8, 10, 9, 11);

// Rotina da interrupção
void interrupt () {
  delay(4); 
  if (digitalRead(PinoCLK)) {
    RotDirection = digitalRead(PinoDT);
  } else {
    RotDirection = !digitalRead(PinoDT);
    GiroIdentificado = true;
  }
}

void setup () {
  pinMode(PinoCLK,INPUT);                // Configuração variáveis como entrada
  pinMode(PinoDT,INPUT);  
  pinMode(PinoSW,INPUT);
  digitalWrite(PinoSW, HIGH);            // Resistor de Pull-up para o botão
  attachInterrupt (0,interrupt,FALLING); // Configuração da interrupção
  pinMode(led,OUTPUT);                   // Config. Led como saída
}

void loop () {
  MotorStepper.setSpeed(600);
  
  // Teste se o botão for pressionado
  if (!(digitalRead(PinoSW))) {   
    if (RotPosition == 0) {
      // if vazio  
    } else {
      // Troca o estado do led
      digitalWrite(led, !digitalRead(led));
      delay(500);
    }
  }

  // Rotina caso o encoder seja rotacionado
  if (GiroIdentificado)  {
    PrevPosition = RotPosition; // Armazena Posição anterior
    if (RotDirection) {
      RotPosition = RotPosition - 1; // Decrementa
    } else {
      RotPosition = RotPosition + 1; // Incrementa
    }     
      
    // Para não repetir loop até nova rotação
    GiroIdentificado = false; 

    // Rotina da direção que o motor irá girar
    // Mover motor CW
    if ((PrevPosition + 1) == RotPosition) { 
      Steps = 50; 
      MotorStepper.step(Steps);
    }
    // Mover motor CCW
    if ((RotPosition + 1) == PrevPosition) { 
      Steps = -50;
      MotorStepper.step(Steps);
    }
  }
}