#include <Matriz.h>
Matriz matriz(6, 9, 5);

//Variables para sustituir delay
long previousMillis = 0;
long currentMillis = 0;
long interval = 1000;

int numero=0;

void setup(){
}
void loop(){
  //Cada "intervalo" tiempo el numero mostrado aumentara en una unidad
  currentMillis=millis();
  if(currentMillis - previousMillis > interval) {
    numero=numero+1;
    previousMillis = currentMillis;
  }
  //Si el numero es mayor de 99, vuelva a 0 puesto que no caben mas numeros en la matriz
  if(numero>99){
    numero=0;
  }
  matriz.imprimirNumero(numero);
}
