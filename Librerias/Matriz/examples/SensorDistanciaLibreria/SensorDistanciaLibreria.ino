#include <Matriz.h>
Matriz matriz(6, 9, 5);

//TIMER
volatile uint8_t columna=0;

volatile int a = 0;

int buzzerPin = 10;

//Variables para sustituir delay
long previousMillis = 0;
long currentMillis = 0;
long interval = 1000;

//Variables necesarias para imprimir en la matriz
int numero=0;

//Variables relacionadas al botón
int estadoBoton=0;
int botonPin = 3;
long TInicial = 0;
long TActual = 0;
int onOff=1;

//Variables para sustituir delay
volatile long tiempo;

//Variables para leer del LDR
int ldrPin=A0;
int ldrValue=0;

//Variables para leer el Sensor de distancia HC-SN04
volatile int trigPin=11;
volatile int echoPin=12;

//Variables para sustituir delay
long tiempoInicial = 0;
long tiempoActual = 0;

void setup(){
  pinMode(botonPin, INPUT);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
}

void loop(){
  estadoBoton=digitalRead(botonPin);
  if(estadoBoton == HIGH){
    a=estadoBoton;
  }

  if(a == HIGH){
    for(int x; x<128; x++){
     int x1=x/16;
      matriz.printLine(1, 3, x1, 3);
    }
    for(int i=0; i<5; i++){
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(956);
      digitalWrite(buzzerPin, LOW);
      delayMicroseconds(956);
    }
    digitalWrite(trigPin,LOW); 
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    tiempo=pulseIn(echoPin, HIGH);
    numero = int(0.017*tiempo); //V=e/t -->e=V*t
    a=LOW;
  }
  while(estadoBoton==HIGH){
    estadoBoton=digitalRead(botonPin);
  }
  matriz.imprimirNumero(numero);
}


