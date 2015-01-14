/*
Kiwibot - Basic Shield

Libreria para el control del Kiwibot Basic Shield
Creada por Alberto Pumar Jimenez, 
El dia 14 de enero de 2015
*/

#ifndef Matriz_h
#define Matriz_h

#include "Arduino.h"

// library interface description
class Matriz{
public:
  Matriz(int setpinLatch, int setpinReloj, int setpinDatos); //Inicializacion de la libreria se definen el pin de datos, reloj y latch y se definen como salida
  void imprimirPantalla(byte fila, byte columna);
  void imprimirNumero(byte valor); //Funcion para imprimir un numero
  void imprimirPixel(byte i0, byte j0); //Funcion para imprimir pixel en (i ,j)
  void printLine(byte i2, byte j2, byte i3, byte j3); //Funcion para imprmir una linea desde Iinicio, Jinicio hasta Ifinal, Ifinal
  void limpiarPantalla(); //Funcion para mandar valores a la placa

private:

  static byte unidad[]; //este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal se refiere a las columnas 5-7 donde se imprimira la unidad
  static byte decena[]; //este byte sirve para imprimir numeros, representa los LEDs que deben encenderse por cada columna en decimal se refiere a las columnas 1-3 donde se imprimira la decena
  static byte j1[7]; //este byte representa la columna en la que queremos encender el LED. Esta en binario
  static byte i1[5]; //este byte representa la fila en la que queremos encender el LED. Esta en binario y en logica negativa

  // variables
  static byte index; //variable auxiliar utilizada para almacenar la decena o unidad de un numero

  //variables usadas para almacenar los datos que eviaremos al registro de desplazamiento
  static byte fila;
  static byte columna;

  //Pines para la inicializacion de la libreria
  static int pinLatch;
  static int pinReloj;
  static int pinDatos;
};

#endif