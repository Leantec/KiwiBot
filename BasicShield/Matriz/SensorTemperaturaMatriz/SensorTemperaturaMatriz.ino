//TIMER
uint8_t columna=0;

//74HC595 controla la matriz led
int pinLatch = 6;    //Pin para el latch de los 74CH495
int pinDatos = 5;    //Pin para Datos serie del 74CH495
int pinReloj = 9;     //Pin para reloj del 74CH495

//Variables necesarias para imprimir en la matriz
int numero=0;
int numeroimp=0;

//Variables para leer el Sensor de temperatura
int temperaturaPin=A1;
long temperaturaValue=0;    
long temperatura=0;

//Variables para sustituir delay
long tiempoInicial = 0;
long tiempoActual = 0;

//Byte para imprimir los numeros del 0 al 99
byte unidad[]= {
  7, 5, 5, 5, 7,  //0
  2, 6, 2, 2, 7,  //1
  2, 5, 1, 2, 7,  //2
  6, 1, 6, 1, 6,  //3
  5, 5, 7, 1, 1,  //4
  7, 4, 6, 1, 6,  //5 
  3, 4, 7, 5, 7,  //6
  7, 1, 1, 2, 2,  //7 
  7, 5, 7, 5, 7,  //8
  7, 5, 7, 1, 6}; //9

byte decena[]= {
  112, 80, 80, 80, 112,  //00
  32, 96, 32, 32, 112,   //10
  32, 80, 16, 32, 112,   //20
  96, 16, 96, 16, 96,    //30
  80, 80, 112, 16, 16,   //40
  112, 64, 96, 16, 96,   //50
  48, 64, 112, 80, 112,  //60
  112, 16, 16, 32, 32,   //70
  112, 80, 112, 80, 112, //80
  112, 80, 112, 16, 96}; //90
  
//byte para elegir la fila en la que se quiere escribir
byte fila[5]= {
  B1101111, B1110111, B1111011, B1111101, B1111110};

void setup(){
  pinMode(pinLatch,OUTPUT);
  pinMode(pinDatos,OUTPUT);
  pinMode(pinReloj,OUTPUT);
}

void loop(){
  //Cada medio segundo lee la temperatura
  tiempoActual = millis();
  if(tiempoActual - tiempoInicial > 500) { 
    tiempoInicial = tiempoActual;   
    temperaturaValue= analogRead(temperaturaPin);
    temperatura=(temperaturaValue*5*100)/1024;
  }
  
  //Imprimimos los valores en la matriz
  numeroimp=temperatura%10;  
  digitalWrite(pinLatch, LOW);
  shiftOut(pinDatos, pinReloj, MSBFIRST, fila[columna]); 
  shiftOut(pinDatos, pinReloj, MSBFIRST, unidad[(columna+5*numeroimp)]);
  digitalWrite(pinLatch, HIGH);

  numeroimp=temperatura/10;  
  digitalWrite(pinLatch, LOW);
  shiftOut(pinDatos, pinReloj, MSBFIRST, fila[columna]); 
  shiftOut(pinDatos, pinReloj, MSBFIRST, decena[(columna+5*numeroimp)]);
  digitalWrite(pinLatch, HIGH);
  
  if(columna==0){
    columna=5;
  }
  columna--;
}

