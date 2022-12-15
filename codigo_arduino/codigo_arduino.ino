#include "stuff.h"

#define SOLENOID_1_CH_0 2
#define SOLENOID_1_CH_1 3
#define SOLENOID_2_CH_0 4
#define SOLENOID_2_CH_1 5

const int PWMA = 8;
const int AIN2 = 9;
const int AIN1 = 10;
const int STBY = 11;

#define RED_READ 7
#define BLUE_READ 8

const int pinMotorA[3] = {PWMA, AIN2, AIN1};
const int solenoidR[2] = {SOLENOID_1_CH_1, SOLENOID_1_CH_0};
const int solenoidB[2] = {SOLENOID_2_CH_1, SOLENOID_2_CH_0};

char buf[6];

int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
        switch (readch) {
            case '\r': // Ignore CR
                break;
            case '\n': // Return on new-line
                rpos = pos;
                pos = 0;  // Reset position index ready for next time
                return rpos;
            default:
                if (pos < len-1) {
                    buffer[pos++] = readch;
                    buffer[pos] = 0;
                }
        }
    }
    return 0;
}

void setup() {
  Serial.begin(9600);

  Serial.println("Configurando...");
  
  // SOLENOIDS
  pinMode(SOLENOID_1_CH_0, OUTPUT);
  pinMode(SOLENOID_1_CH_1, OUTPUT);
  pinMode(SOLENOID_2_CH_0, OUTPUT);
  pinMode(SOLENOID_2_CH_1, OUTPUT);

  // MOTOR CONTROLLER
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(STBY, OUTPUT);

  // COLOR READ INPUTS
  pinMode(RED_READ, INPUT);
  pinMode(BLUE_READ, INPUT);
  delay(1000);
  
  actionSolenoid(backward, solenoidR);
  actionSolenoid(backward, solenoidB);

  disableMotor();

  Serial.println("Listo !");
}

void loop(){
  int red_read = digitalRead(RED_READ); // Realiza lectura constante del color rojo
  int blue_read = digitalRead(BLUE_READ); // Realiza lectura constante del color azul
  enableMotor();
  if(red_read || blue_read){
    stopMotor(pinMotorA);
     delay(500);
    if(red_read){ // si detecta color rojo
      moveMotorForward(pinMotorA, 180); // Mueve el motor
      delay(2000); // Durante 3.5 segundos
      stopMotor(pinMotorA);
      actionSolenoid(forward, solenoidR); // Activa la selenoide (retraerse)
      delay(200); // Dura activa 200 ms
      actionSolenoid(backward, solenoidR); // Activa la selenoide (retraerse)
    }else if(blue_read) { // si detecta color azul
      moveMotorForward(pinMotorA, 180); // Mueve el motor
      delay(1100); // Durante 2.5 segundos
      stopMotor(pinMotorA);
      actionSolenoid(forward, solenoidB); // Activa la selenoide (retraerse)
      delay(200); // Dura activa 200 ms
      actionSolenoid(backward, solenoidB); // Activa la selenoide (contraerse)
    }
  }
  
  moveMotorForward(pinMotorA, 175); // Mueve continuamente el motor
  delay(100);
}


// Accionamiento de la solenoide
void actionSolenoid(moveDirection _direction, const int solenoid[2] ){
  if(_direction == forward){ // Retrae
    digitalWrite(solenoid[0], HIGH); // Activa el canal 0
    digitalWrite(solenoid[1], LOW); // Desactiva el canal 1
  }else{ // Contrae
    digitalWrite(solenoid[0], LOW); // Desactiva el canal 0
    digitalWrite(solenoid[1], HIGH); // Activa el canal 1
  }
}

void disableSolenoid(const int solenoid[2]){
  digitalWrite(solenoid[0], LOW); // Desactiva el canal 0
    digitalWrite(solenoid[1], LOW); // Desactiva el canal 1
}

void moveMotorForward(const int pinMotor[3],int speed){
  digitalWrite(pinMotor[1], HIGH);
  digitalWrite(pinMotor[2], LOW);
  analogWrite(pinMotor[0],speed);
}
void moveMotorBackward(const int pinMotor[3],int speed){
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], HIGH);
  analogWrite(pinMotor[0],speed);
}

void stopMotor(const int pinMotor[3]){
  digitalWrite(pinMotor[1], LOW);
  digitalWrite(pinMotor[2], LOW);
  analogWrite(pinMotor[0],0);
}

void enableMotor() {
  digitalWrite(STBY,HIGH);
}

void disableMotor(){
  digitalWrite(STBY, LOW);
}
