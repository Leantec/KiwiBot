#include <Matriz.h>
Matriz matriz(6, 9, 5);

//Variables para leer el Sensor de temperatura
int temperaturaPin=A1;
long temperaturaValue=0;    
long temperatura=0;

//Variables para sustituir delay
long tiempoInicial = 0;
long tiempoActual = 0;

void setup(){
}

void loop(){
  //Cada medio segundo lee la temperatura
  tiempoActual = millis();
  if(tiempoActual - tiempoInicial > 500) { 
    tiempoInicial = tiempoActual;   
    temperaturaValue= analogRead(temperaturaPin);
    temperatura=(temperaturaValue*5*100)/1024;
  }
  matriz.imprimirNumero(temperatura); //Imprimir Temperatura
}
