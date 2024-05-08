/**
 * ATENÇÃO
 * Todas a linhas que tenham no comentário um '*' 
 * são linhas obrigatórias para qualquer programa
 * com este carro
 */ 
#include <Ultrasonic.h>
#include <Servo.h>
#include <EEPROM.h>
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

//Distâncias máximas e mínimas de leituras (sensor ultrasom)
int maxDistance = 100;
int minDistance = 20;

//Variáveis dos sensores de linha (os sensores são da esquerda para a direita)
int sensor0, sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7;
int transistionVal = 60;

Servo garra;
Servo garraElev;

Ultrasonic ultrasonic(triggerPin, echoPin);


//Variáveis
int distance = 0;

void setup(){
    Serial.begin(115200);
    one.spiConnect(SSPIN);  // *
   
    // Inicializa os servos da garra
    garraElev.attach(servoGarraElevation);
    garra.attach(servoGarra);

    // Coloca os servos na posição de montagem (comentar depois de usar)
    servosAtAssemblyMode();

    one.lcd1("  CRP24 - ENTA  ");
    delay(2000);

}

void loop(){

    readBoleanLineSensors(); 
    readDistance();
    lcdPrintDistance(distance);
    lcdPrintLineSensors();
}


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
 * @brief Função para imprimir no LCD a distância
*/
void lcdPrintDistance(int distance){
    one.lcd2("Distancia: " + String(distance) + "cm");
}

/**
 * @brief Função para ler os sensores de linha
*/
void readBoleanLineSensors(){
    // Leitura dos sensores de linha
    one.readAdc(7) > transistionVal ? sensor0 = 1 : sensor0 = 0;
    one.readAdc(6) > transistionVal ? sensor1 = 1 : sensor1 = 0;
    one.readAdc(5) > transistionVal ? sensor2 = 1 : sensor2 = 0;
    one.readAdc(4) > transistionVal ? sensor3 = 1 : sensor3 = 0;
    one.readAdc(3) > transistionVal ? sensor4 = 1 : sensor4 = 0;
    one.readAdc(2) > transistionVal ? sensor5 = 1 : sensor5 = 0;
    one.readAdc(1) > transistionVal ? sensor6 = 1 : sensor6 = 0;
    one.readAdc(0) > transistionVal ? sensor7 = 1 : sensor7 = 0;
}

/**
 * @brief Função para imprimir no LCD os sensores de linha
*/
void lcdPrintLineSensors(){
    String lineSensors = String(sensor0) + String(sensor1) + String(sensor2) + String(sensor3) + 
                         String(sensor4) + String(sensor5) + String(sensor6) + String(sensor7);
    one.lcd1("    " + String(lineSensors));
    Serial.println(lineSensors);
}