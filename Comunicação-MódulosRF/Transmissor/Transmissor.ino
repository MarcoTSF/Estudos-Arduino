#include <RH_ASK.h> //INCLUSÃO DE BIBLIOTECA
#include <SPI.h> //INCLUSÃO DE BIBLIOTECA

RH_ASK driver; //CRIA O DRIVER PARA COMUNICAÇÃO

const int pinoBotao = 2; //PINO DIGITAL UTILIZADO PELO PUSH BUTTON

void setup(){
    driver.init(); //INICIALIZA A COMUNICAÇÃO RF DO DRIVER
    pinMode(pinoBotao, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
    //DO ARDUINO PARA GARANTIR QUE NÃO EXISTA FLUTUAÇÃO ENTRE 0 (LOW) E 1 (HIGH)
}
void loop(){
    const char *msg = "vibrar"; //VARIÁVEL RECEBE O VALOR (led)

    if(digitalRead(pinoBotao) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
        driver.send((uint8_t *)msg, strlen(msg)); //ENVIA AS INFORMAÇÕES PARA O RECEPTOR (PALAVRA: led)
        driver.waitPacketSent(); //AGUARDA O ENVIO DAS INFORMAÇÕES
        delay(200); //INTERVALO DE 200 MILISSEGUNDOS
    }
}