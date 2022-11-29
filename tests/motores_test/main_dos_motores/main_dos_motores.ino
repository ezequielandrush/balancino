/*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+ do not put anything that doesn belong to the steppers here
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include <Arduino.h>
#include <math.h>


//conexionado físico motor1
const int stepPin1 = 45;
const int dirPin1 = 44;
const int m1M0 = 47;
const int m1M1 = 46;
const int m1M2 = 48;

//conexionado físico motor2
const int stepPin2 = 52;
const int dirPin2 = 53;
const int m2M0 = 51;
const int m2M1 = 50;
const int m2M2 = 49;

//variables aux. Las declaro acá para facilitar la pila de ejecucion

int gearM = 0;
int OCR1temp = 0;

void setup() {

  cli(); //PARO LAS INTERRUPCIONES

  // TIMER2 SETUP
  TCCR2A = 0;// Pongo el registro TCCR2A en 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;// Inicializo el contador del timer en 0
  //OCR2A = 255;
  // Prendo modo CTC del timer
  TCCR2A |= (1 << WGM21);
  // uno en bit CS21 y  bit CS22 para prescaler de 256
  TCCR2B |= (1 << CS22 | 1 << CS21);
  // activo interrupción por comparación
  TIMSK2 |= (1 << OCIE2A);
  sei();
  //TIMER SETUP

  //setup del motor 1
  pinMode(m1M0, OUTPUT);
  pinMode(m1M1, OUTPUT);
  pinMode(m1M2, OUTPUT);
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);

  digitalWrite(m1M0, LOW);
  digitalWrite(m1M1, LOW); //pines del microstepping en 0
  digitalWrite(m1M2, LOW);

  //setup del motor 2
  pinMode(m2M0, OUTPUT);
  pinMode(m2M1, OUTPUT);
  pinMode(m2M2, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  digitalWrite(m2M0, LOW);
  digitalWrite(m2M1, LOW); //pines del microstepping en 0
  digitalWrite(m2M2, LOW);

}

ISR(TIMER2_COMPA_vect){
  digitalWrite(stepPin1,LOW);
  digitalWrite(stepPin2,LOW);
  //delayMicroseconds(300);
  digitalWrite(stepPin1,HIGH);
  digitalWrite(stepPin2,HIGH);
}


void reduccion (int red, int m0, int m1, int m2){
  //un gigantesco switch para poner las reducciones del MS
  //según los valores m0, m1 y m2
  switch (red) {
    case 0:
    digitalWrite(m0, HIGH);
    digitalWrite(m1, LOW);   //muy lento velocidad menor a 64 1/32
    digitalWrite(m2, HIGH);
    break;
    case 1:
    digitalWrite(m0, LOW);
    digitalWrite(m1, LOW);   // 1/16
    digitalWrite(m2, HIGH);
    break;
    case 2:
    digitalWrite(m0, HIGH);
    digitalWrite(m1, HIGH); // 1/8
    digitalWrite(m2, LOW);
    break;
    case 3:
    digitalWrite(m0, LOW);
    digitalWrite(m1, HIGH); // 1/4
    digitalWrite(m2, LOW);
    break;
    case 4:
    digitalWrite(m0, HIGH);
    digitalWrite(m1, LOW);  // 1/2
    digitalWrite(m2, LOW);
    break;
    case 5:
    digitalWrite(m0, LOW);
    digitalWrite(m1, LOW); // sin microstepping
    digitalWrite(m2, LOW);
    break;
    default:
    break;
  }
}

void calcOCR(int vel){
  //Seteo todo junto para los dos MOTORES
  // 0 < velocidad <= 383
    gearM = int (vel/64);
    OCR1temp = 114 - (vel - (gearM * 64));
    reduccion (gearM, m1M0, m1M1, m1M2);
    reduccion (gearM, m2M0, m2M1, m2M2);
    OCR2A = OCR1temp;
}

void loop() {
//  for (int a = 254; a <=100; a--){
    calcOCR(300);
//    delay(500);
//  }
}
