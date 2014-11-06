//TIMER, variables utilizadas en el timer, necesitan ser volatile
volatile uint8_t columna=0;

volatile uint8_t  array_display[8] = {
  B1000000, B0100000, B0010000, B0001000, B0000100, B0000010, B0000001, 0};
volatile uint8_t  columnaa[6] = {
  B11111110, B11111101, B11111011, B11110111, B11101111, 0};

//74HC595 controla la matriz led
int pinLatch = 6;    //Pin para el latch de los 74CH495
int pinDatos = 5;    //Pin para Datos serie del 74CH495
int pinReloj = 9;     //Pin para reloj del 74CH495

//Valor y Pines del acelerometro
int xVal = 0;
int xPin = A3;
int yVal = 0;
int yPin = A2;

//PUNTO CONTROLADO CON EL ACELEROMETRO
//Posicion del punto
int posicionX = 0;
int posicionY = 0;
//Datos que le enviamos a los displays
int xPixel = 0;
int yPixel = 0;

//PUNTO PARPADEANTE
//Posicion del punto
int yPunto = 0;
int xPunto = 0;
//Datos que le enviamos a los displays
int Xp = 0;
int Yp = 0;

//Dificultad del juego. Mientras menor sea el numero, mayor sera la dificultad.
//Float para poder variar mas suavemente la dificultad (0.5)
float dificultad = 20;

//Variables para sustituir un delay por un millis()
long Tini=0;
long Tfin=0;

long Tinicial = 0;
long Tfinal = 0;

long Tespera = 0;

/////////////////

int tiempo = 0; //Variable que usamos para salir del while

int buzzerPin = 10; //Pin del zumbador

int gameOver = 0; //Variable para saber si el juego ha acabado o no

void setup(){
  iniciarTimer();

  pinMode(pinLatch,OUTPUT);
  pinMode(pinDatos,OUTPUT);
  pinMode(pinReloj,OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  randomSeed(analogRead(A0));
}

void loop(){

  if(gameOver == 0){
    //Las coordenadas del punto parpadeante se generan aleatoriamente
    yPunto = random(4);
    xPunto = random(6);

    //La dificultad aumenta
    dificultad=dificultad-0.5;

    //El tiempo que tarda en cambiar de posicion el punto parpadeante es igual a la dificultad
    tiempo = dificultad;

    //Desde que tiempo es igual a dificultad hasta que es igual a 0, las coordenadas del punto parpadeante y la dificultad no cambian,
    //a no ser que llegues hasta el con el punto que tu controlas.
    while(tiempo > 0){


      //PUNTO PARPADEANTE

      //Cuando falte poco tiempo para que el punto parpadeante cambie de posicion, su tiempo de parpadeo sera menor,
      //mientras tanto, este conservara su valor inicial: 0.5s
      if(tiempo < 7){
        if(tiempo < Tespera-50){
          Tespera = Tespera - tiempo;
        }
      }
      else{
        Tespera=500;
      }

      //La funcion de parpadeo consiste en alternar los valores del punto entre su (x, y) y 0, 
      //consiguiendo que se muestre el punto y la pantalla apagada sucesivamente.
      Tfinal=millis();
      if(Tfinal-Tinicial>Tespera){
        Tinicial = Tfinal;
        if (Yp == 7){
          Xp = xPunto;
          Yp = yPunto;
        }
        else{
          Xp = 7;
          Yp = 7;
        }
      }

      //Cada 0.5s la variable tiempo va disminuyendo
      Tfin=millis();
      if(Tfin-Tini>500){
        Tini = Tfin;
        tiempo --;
      }

      /*-----------------------------------------------*/


      //PUNTO CONTROLADO CON EL ACELEROMETRO

      //Leemos los valores del acelerómetro   
      xVal = analogRead(xPin);
      yVal = analogRead(yPin);

      //Movimiento del punto si esta dentro de los margenes
      //Movimiento de la y (depende del eje X del acelerometro)
      if(xVal>420 && yPixel>0){
        yPixel=yPixel-1;
      }
      if(xVal<320 && yPixel<4){
        yPixel=yPixel+1;
      }

      //Movimiento de la x (depende del eje Y del acelerometro)
      if(yVal>370 && xPixel>0){
        xPixel=xPixel-1;
      }
      if(yVal<270 && xPixel<6){
        xPixel=xPixel+1;
      }
      
      //Se le envian datos diferentes a la matriz cuando la X o la Y del punto ha cambiado.
      //Con esto conseguimos que el punto pueda moverse en diagonal y cada cierto tiempo.
      if(xPixel != posicionX || yPixel != posicionY){
        posicionX = xPixel;
        posicionY = yPixel;
        delay(200);
      }

      //Cada vez que alcanzas el punto parpadeante el zumbador pita y 
      //cambiamos la variable tiempo para poder salir del while y cambiar asi las coordenadas del punto parpadeante
      if(yPixel == yPunto && xPixel == xPunto){
        tiempo = -1;
        digitalWrite(buzzerPin, HIGH);
        delay(10);
        digitalWrite(buzzerPin, LOW);
      }
      //Si pasa mucho tiempo sin alcanzar el punto parpadeante el juego termina.
      if(Tespera == 51){
        gameOver=1;
      }
    }
  }


   //QUE OCURRE CUANDO EL JUEGO TERMINA
  if(gameOver == 1){
    //Escribimos en la matris de tal manera que no salga nada en ella
    xPixel = 7;
    yPixel = 5;
    Xp = 7;
    Yp = 5;
    //Emitimos un pitido 
    for(int i=0; i<50; i++){
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(1915);
      digitalWrite(buzzerPin, LOW);
      delayMicroseconds(1915);
    }
    delay(50);
    for(int i=0; i<100; i++){
      digitalWrite(buzzerPin, HIGH);
      delayMicroseconds(1915);
      digitalWrite(buzzerPin, LOW);
      delayMicroseconds(1915);
    }
    //Dejamos abierta la posibilidad de resetear el juego para volver a empezar
    while(gameOver == 1){
      dificultad = 20;
      xPixel = 7;
      yPixel = 5;
      Xp = 7;
      Yp = 5;
      if(digitalRead(3) == HIGH){
        gameOver = 0;
        xPixel = 0;
        yPixel = 0;
      }
    }
  }
}



void iniciarTimer(void){
  TCNT2=0;
  TCCR2A = 0;
  TCCR2B = 5;
  TIMSK2 |= (1>>TOIE1);
  sei();
}

SIGNAL(TIMER2_OVF_vect){
  TCNT2 = 0; 
  digitalWrite(pinLatch, LOW);
  shiftOut(pinDatos, pinReloj, MSBFIRST, columnaa[yPixel]);
  shiftOut(pinDatos, pinReloj, MSBFIRST, array_display[xPixel]); 
  digitalWrite(pinLatch, HIGH);

  digitalWrite(pinLatch, LOW);
  shiftOut(pinDatos, pinReloj, MSBFIRST, columnaa[Yp]);
  shiftOut(pinDatos, pinReloj, MSBFIRST, array_display[Xp]); 
  digitalWrite(pinLatch, HIGH);
}
