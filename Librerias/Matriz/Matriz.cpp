/*
Kiwibot - Basic Shield

Libreria para el control del Kiwibot Basic Shield
Creada por Alberto Pumar Jimenez, 
El dia 14 de enero de 2015
*/

#include "Arduino.h"
#include "Matriz.h"

//este byte representa la fila en la que queremos encender el LED. Esta en binario y en logica negativa
byte Matriz::i1[5] = {
B1101111, B1110111, B1111011, B1111101, B1111110};

//este byte representa la columna en la que queremos encender el LED. Esta en binario
byte Matriz::j1[7] = {
B1000000, B0100000, B0010000, B0001000, B0000100, B0000010, B0000001};

//este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal
//se refiere a las columnas 5-7 donde se imprimira la unidad
byte Matriz::unidad[] = {
7, 5, 5, 5, 7,
2, 6, 2, 2, 7,
2, 5, 1, 2, 7,
6, 1, 6, 1, 6,
5, 5, 7, 1, 1,
7, 4, 6, 1, 6,
3, 4, 7, 5, 7,
7, 1, 1, 2, 2,
7, 5, 7, 5, 7,
7, 5, 7, 1, 6};

//este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal
//se refiere a las columnas 1-3 donde se imprimira la decena
byte Matriz::decena[]= {
112, 80, 80, 80, 112,
32, 96, 32, 32, 112,
32, 80, 16, 32, 112,
96, 16, 96, 16, 96,
80, 80, 112, 16, 16,
112, 64, 96, 16, 96,
48, 64, 112, 80, 112,
112, 16, 16, 32, 32,
112, 80, 112, 80, 112,
112, 80, 112, 16, 96};

byte Matriz::index; //variable auxiliar utilizada para almacenar la decena o unidad de un numero

//variables usadas para almacenar los datos que eviaremos al registro de desplazamiento
byte Matriz::fila;
byte Matriz::columna;

//Pines para la inicializacion de la libreria
int Matriz::pinLatch;
int Matriz::pinReloj;
int Matriz::pinDatos;

//Inicializacion de la libreria se definen el pin de datos, reloj y latch y se definen como salida
Matriz::Matriz(int setpinLatch, int setpinReloj, int setpinDatos){
  pinLatch = setpinLatch;
  pinReloj = setpinReloj;
  pinDatos = setpinDatos;

  pinMode(pinLatch, OUTPUT);
  pinMode(pinReloj, OUTPUT);
  pinMode(pinDatos, OUTPUT);
}

//Funcion para imprimir un numero
void Matriz::imprimirNumero(byte valor){
  index=valor%10; //Extraemos la unidad del numero
  byte i; //byte auxiliar para contar en que fila estamos
  for(i = 0; i < 5; i++){
    imprimirPantalla(i1[i], unidad[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
  }
  index=valor/10; //Extraemos la decena del numero
  for(i = 0; i < 5; i++){
    imprimirPantalla(i1[i], decena[(i+5*index)]); //Imprimimos en la pantalla la fila y la/las columnas indicadas
  }
}

//Funcion para imprmir una linea desde Iinicio, Jinicio hasta Ifinal, Ifinal
void Matriz::printLine(byte i2, byte j2, byte i3, byte j3){
  byte i;
  byte j;
  byte iIni=i2;
  byte iFin=i3;
  byte jIni=j2;
  byte jFin=j3;
  for(j=1; j<8; j++){ //recorremos todas las columnas
    if(j>=jIni && j<=jFin){ //restringimos el recorrido al dominio de la linea
      i=(((iFin-iIni)*(j-jIni))/(jFin-jIni))+iIni; //Ecuacion de una recta en forma vectorial donde hemos despejado i
      imprimirPixel(i, j); //Imprimimos pixel a pixel la linea
    }
  }
}

//Funcion para imprimir pixel en (i ,j)
void Matriz::imprimirPixel(byte i0, byte j0){
  byte i=i0;
  byte j=j0;
  imprimirPantalla(i1[i-1], j1[j-1]); //Imprimimos en la pantalla la fila y columna necesaria para encender el pixel correspondiente
}

//Funcion para mandar valores a la placa
void Matriz::imprimirPantalla(byte fila, byte columna){

    //Como usamos un regirtro de desplazamiento utilizamos la funcion shiftOut para enviarle los datos enviando primero el bit mas significativo
    digitalWrite(pinLatch, LOW);
    shiftOut(pinDatos, pinReloj, MSBFIRST, fila);
    shiftOut(pinDatos, pinReloj, MSBFIRST, columna);
    digitalWrite(pinLatch, HIGH);
}