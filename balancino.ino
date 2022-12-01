#include <math.h>
void setup() {


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
int OCR1temp = 0

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

void loop() {
}
