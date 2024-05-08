/**
 * ATENÇÃO
 * Todas a linhas que tenham no comentário um '*' 
 * são linhas obrigatórias para qualquer programa
 * com este carro
 */ 

#include <Ultrasonic.h>
#include <Servo.h>
#include <BnrOneA.h>    // *
#define SSPIN 2         // *
BnrOneA one;            // *

// Constantes
const int servoGarraElevation = 5;    // Pino do servo de elevacao da garra
const int servoGarra          = 3;    // Pino do servo da garra
const int triggerPin          = 7;    // Pino do trigger do sensor ultrassonico
const int echoPin             = 6;    // Pino do echo do sensor ultrassonico

//Default Servo Positions
int servoPanDefault     = 100;   // Servo Pan aponta para a frente
int servoTiltDefault    = 120;   // Servo Tilt aponta para a frente
int garraElevation      = 0;     // Garra na posição de elevação
int garraOpen           = 80;    // Garra aberta

//Distâncias máximas e mínimas de leituras
int maxDistance = 100;
int minDistance = 20;

Servo garra;
Servo garraElev;

Ultrasonic ultrasonic(triggerPin, echoPin);


//Varoáveis
int distance = 0;

/**
 * @brief Função para colocar os servos na posição de montagem:
 */
void servosAtAssemblyMode(){
    one.servo1(servoPanDefault);
    delay(1500);
    one.servo2(servoTiltDefault);
    delay(1500);
    garraElev.write(garraElevation);
    delay(1500);
    garra.write(garraOpen);
    delay(1500);
} 

/**
 * @brief Função para ler a distância (maximo 40cm min 20cm)
 */
int readDistance(){
    int distance = ultrasonic.read();
    distance > maxDistance || distance << minDistance ? distance = -1 : distance = distance;
    return distance;
}

/**
 * @brief Função para imprimir no LCD
*/
void lcdPrint(String l1, String l2){
    //limpa linhas
    one.lcd1("               ");
    one.lcd2("               ");
    //imprime texto
    one.lcd1(l1);
    one.lcd2(l2);
}


/**
 * @brief Função para imprimir no LCD a distância
*/
void lcdPrintDistance(int distance){
    lcdPrint("", "Distancia: " + String(distance) + "cm");
}

void setup(){
    Serial.begin(115200);
    one.spiConnect(SSPIN);  // *
   
    // Inicializa os servos da garra
    garraElev.attach(servoGarraElevation);
    garra.attach(servoGarra);

    // Coloca os servos na posição de montagem (comentar depois de usar)
    // servosAtAssemblyMode();

    lcdPrint("  CRP24 - ENTA  ","");

}


void loop(){
    Serial.println(readDistance()); 
    lcdPrintDistance(readDistance());
}