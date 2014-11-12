/* Vehiculo controlado por app
 Creado por Ramón Arjona Quiñones y Andrea Fernández García, 4ºESO del instituto IES Vicente Aleixandre, Sevilla
 Profesor: José Pujol 
 
 El programa funciona como un coche teledirigido desde el móvil, que envía bits a Arduino para que el coche funcione. Hecho con el software y hardware libre de Arduino.*/


// Pines de servotores:
int servoLPin = 4; //Los cuatro “in” son  los pines a los que va conectado el motor driver
int servoRPin=8;

// Variables de comunicacion:

int incomingByte; //Último bit recibido
                   // Cuando no recibe ningun dato nuevo se pone a 10

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
void loop() {

  if (Serial.available() > 0) { //Si recibe datos,
    incomingByte = Serial.read(); //Acumula el último byte en incomingByte
  }
  if (incomingByte == 'f') { //SI es “f” (botón de arriba)  
    go_forward(); //Va hacia alante 
  }
  if (incomingByte == 'b') { //Si es “b” (botón de abajo),
    go_back(); //Va hacia atrás
  }
  if (incomingByte == 'r') { //Si es “r” (botón de la derecha);
    turn_right(); //Gira a la derecha
  }
  if (incomingByte == 'l') { //Si es “l” (botón de la izquierda), 
    turn_left(); //Gira a la izquierda
  }
  if (incomingByte == 's') { //Si es “s”  (no se pulsa nada),
    parar();  //El coche se para.
  }
} 




