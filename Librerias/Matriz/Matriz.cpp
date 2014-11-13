#include "Arduino.h"
#include "Matriz.h"

byte Matriz::columna[5] = {
B1101111, B1110111, B1111011, B1111101, B1111110};

byte Matriz::y1[5] = {
B1111110, B1111101, B1111011, B1110111, B1101111};

byte Matriz::x1[7] = {
B1000000, B0100000, B0010000, B0001000, B0000100, B0000010, B0000001};

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

byte Matriz::index;
byte Matriz::fila;
byte Matriz::columnaa;
int Matriz::pinLatch;
int Matriz::pinReloj;
int Matriz::pinDatos;

// Constructor /////////////////////////////////////////////////////////////////

Matriz::Matriz(int setpinLatch, int setpinReloj, int setpinDatos){
  pinLatch = setpinLatch;
  pinReloj = setpinReloj;
  pinDatos = setpinDatos;

  pinMode(pinLatch, OUTPUT);
  pinMode(pinReloj, OUTPUT);
  pinMode(pinDatos, OUTPUT);
}

void Matriz::imprimirNumero(byte valor){
  index=valor%10;
  byte i;
  for(i = 0; i < 5; i++){
    imprimirPantalla(columna[i], unidad[(i+5*index)]);
  }
  index=valor/10;
  for(i = 0; i < 5; i++){
    imprimirPantalla(columna[i], decena[(i+5*index)]);
  }
}

void Matriz::imprimirPixel(byte x0, byte y0){
  byte x=x0;
  byte y=y0;
  imprimirPantalla(y1[y-1], x1[x-1]);
}

void Matriz::imprimirPantalla(byte fila, byte columnaa){
    digitalWrite(pinLatch, LOW);
    shiftOut(pinDatos, pinReloj, MSBFIRST, fila);
    shiftOut(pinDatos, pinReloj, MSBFIRST, columnaa);
    digitalWrite(pinLatch, HIGH);
}