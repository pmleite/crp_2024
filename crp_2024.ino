/**
 * ATENÇÃO
 * Todas a linhas que tenham no comentário um '*' 
 * são linhas obrigatórias para qualquer programa
 * com este carro
 */ 

#include <BnrOneA.h>    // *
#define SSPIN 2         // *
BnrOneA one;            // *


void setup(){
    Serial.begin(115200);
    one.spiConnect(SSPIN);  // *
}

void loop(){
    Serial.println("Hello World");
    delay(1000);
}