/* Vehiculo controlado por app
 Creado por Ramón Arjona Quiñones y Andrea Fernández García, 4ºESO del instituto IES Vicente Aleixandre, Sevilla
 Profesor: José Pujol 
 
*/

int espera=1000;
int i=0;
// Pines de moservotores:
int servoLPin = 4; //Los cuatro “in” son  los pines a los que va conectado el motor driver
int servoRPin=8;

// Variables de comunicacion:

int incomingByte; //Último bit recibido
boolean lectura=0; //Puede ser uno o cero. Reconoce si estamos mandando algo.

void setup() {
  pinMode (servoRPin, OUTPUT);
  pinMode (servoLPin, OUTPUT);
  Serial.begin(9600); //Establece conexión con el puerto serie
}
void go_forward(){ //Rutina para que el coche avance
  //gira adelante
  digitalWrite(servoRPin,HIGH);
  digitalWrite(servoLPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(servoRPin,LOW);
  delayMicroseconds(1000);
  digitalWrite(servoLPin,LOW);
  delayMicroseconds(18000);
}
void go_back(){ //Rutina para que el coche retroceda
  digitalWrite(servoRPin,HIGH);
  digitalWrite(servoLPin,HIGH);
  delayMicroseconds(1000);// 1 - 1500 atras, de 1500 a 3000 delante 
  digitalWrite(servoLPin,LOW);
  delayMicroseconds(1000);
  digitalWrite(servoRPin,LOW);
  delayMicroseconds(18000);
}
void turn_left(){ //Rutina para que el coche gire a la derecha
  digitalWrite(servoRPin,HIGH);
  digitalWrite(servoLPin,HIGH);
  delayMicroseconds(2000);// 1 - 1500 atras, de 1500 a 3000 delante 
  digitalWrite(servoRPin,LOW);
  digitalWrite(servoLPin,LOW);
  delayMicroseconds(18000);
}
void turn_right(){ //Rutina para que el coche gire a la izquierda
  digitalWrite(servoRPin,HIGH);
  digitalWrite(servoLPin,HIGH);
  delayMicroseconds(1000);// 1 - 1500 atras, de 1500 a 3000 delante 
  digitalWrite(servoRPin,LOW);
  digitalWrite(servoLPin,LOW);
  delayMicroseconds(19000);
}
void parar(){ //Rutina para que el cohe pare
  digitalWrite(servoRPin,LOW);
  digitalWrite(servoLPin,LOW);
}

void loop(){

  for (i=0; i<500; i++){
    go_forward();
  }
  delay(espera);
  for (i=0; i<500; i++){
    go_back();
  }
  delay(espera);
  for (i=0; i<500; i++){
    turn_left();
  }
  delay(espera);
  for (i=0; i<500; i++){
    turn_right();
  }
  delay(espera);

}




