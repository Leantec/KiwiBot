#ifndef Matriz_h
#define Matriz_h

#include "Arduino.h"

// library interface description
class Matriz{
public:
  Matriz(int setpinLatch, int setpinReloj, int setpinDatos);
  void shiftOutx(byte imprimir);
  void imprimirPantalla(byte fila, byte columna);
  void imprimirNumero(byte valor);
  void imprimirPixel(byte x0, byte y0);
  void printLine(byte x2, byte y2, byte x3, byte y3);
  void limpiarPantalla();

  // library-accessible "private" interface
private:
  static byte columna[5];
  static byte unidad[];
  static byte decena[];
  static byte x1[7];
  static byte y1[5];

  // variables
  static byte index;
  static byte fila;
  static byte columnaa;
  static int pinLatch;
  static int pinReloj;
  static int pinDatos;
};

#endif