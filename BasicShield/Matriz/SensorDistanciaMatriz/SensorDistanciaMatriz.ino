//TIMER
volatile uint8_t columna=0;

volatile int a = 0;

int buzzerPin = 10;

//74HC595 controla la matriz led
int pinLatch = 6;    //Pin para el latch de los 74CH495
int pinDatos = 5;    //Pin para Datos serie del 74CH495
int pinReloj = 9;     //Pin para reloj del 74CH495

//Variables para sustituir delay
long previousMillis = 0;
long currentMillis = 0;
long interval = 1000;

//Variables necesarias para imprimir en la matriz
volatile int numero=0;
int numeroimp=0;

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

//Byte para imprimir los numeros del 0 al 99
byte unidad[]= {
  7, 5, 5, 5, 7, //0
  2, 6, 2, 2, 7, //1
  2, 5, 1, 2, 7, //2
  6, 1, 6, 1, 6, //3
  5, 5, 7, 1, 1, //4
  7, 4, 6, 1, 6, //5 
  3, 4, 7, 5, 7, //6
  7, 1, 1, 2, 2, //7 
  7, 5, 7, 5, 7, //8
  7, 5, 7, 1, 6};//9

byte decena[]= {
  112, 80, 80, 80, 112,//00
  32, 96, 32, 32, 112,//10
  32, 80, 16, 32, 112,//20
  96, 16, 96, 16, 96,//30
  80, 80, 112, 16, 16,//40
  112, 64, 96, 16, 96,//50
  48, 64, 112, 80, 112,//60
  112, 16, 16, 32, 32,//70
  112, 80, 112, 80, 112,//80
  112, 80, 112, 16, 96};//90

byte fueraRango[]= {
  8, 8, 62, 8, 8};



byte fila[5]= {
  B1101111, B1110111, B1111011, B1111101, B1111110};

void setup(){
  attachInterrupt(0, SensorDistancia, HIGH);

  pinMode(pinLatch,OUTPUT);
  pinMode(pinDatos,OUTPUT);
  pinMode(pinReloj,OUTPUT);

  pinMode(botonPin, INPUT);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);
}

void loop(){
  a=0;
  if(numero > 98){
    digitalWrite(pinLatch, LOW);
    shiftOut(pinDatos, pinReloj, MSBFIRST, fila[columna]); 
    shiftOut(pinDatos, pinReloj, MSBFIRST, fueraRango[columna]);
    digitalWrite(pinLatch, HIGH);
  }
  else{
    numeroimp=numero%10;  
    digitalWrite(pinLatch, LOW);
    shiftOut(pinDatos, pinReloj, MSBFIRST, fila[columna]); 
    shiftOut(pinDatos, pinReloj, MSBFIRST, unidad[(columna+5*numeroimp)]);
    digitalWrite(pinLatch, HIGH);

    numeroimp=numero/10;  
    digitalWrite(pinLatch, LOW);
    shiftOut(pinDatos, pinReloj, MSBFIRST, fila[columna]); 
    shiftOut(pinDatos, pinReloj, MSBFIRST, decena[(columna+5*numeroimp)]);
    digitalWrite(pinLatch, HIGH);
  }
  if(columna==0){
    columna=5;
  }
  columna--;
}

void SensorDistancia (){
  if(a ==  0){
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
    a=1;
  }
}















