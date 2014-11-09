// Pines de moservotores:
int servoLPin = 4; // Pin del servo izquierda
int servoRPin=8;

// Pines de sensor de distancia:
const int trigger=11;
const int echo=12;

int distancia=0;// variable para almacenar la distancia en cm
// float distance=0;  

int i=0;    // variable para el bucle for
int t=0;    // variable para que gire cada vez en un sentido



// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long previousMillis = 0;        // 
unsigned long currentMillis =0;
long interval = 100;   // intervalo con el que revisa el sensor

void setup(){
  pinMode (servoRPin, OUTPUT);
  pinMode (servoLPin, OUTPUT);
  Serial.begin(9600);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
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
void medir(){
  //Inicializamos el sensor
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);
  // Comenzamos las mediciones
  // Enviamos una señal activando la salida trigger durante 10 microsegundos
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  // Adquirimos los datos y convertimos la medida a metros
  distancia=pulseIn(echo,HIGH); // Medimos el ancho del pulso
  // (Cuando la lectura del pin sea HIGH medira
  // el tiempo que transcurre hasta que sea LOW
  distancia=distancia*0.0175;
  // Enviamos los datos medidos a traves del puerto serie y al display LCD
  Serial.println(distancia);
}

void loop(){

  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    // save the last time
    previousMillis = currentMillis;   
    medir();
  }
  if(distancia >= 20){
    go_forward();
  }
  if (distancia>0 && distancia<20){
    if (t==0){
      for (i=0; i<150; i++){
        turn_right();
      }
      t=1;
    }
    else{
      for (i=0; i<150; i++){
        turn_left();
      }
      t=0;
    }
  } 
}










