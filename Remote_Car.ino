
//--------------------------------------------------
//Declara puertos de entradas y salidas y variables
//--------------------------------------------------
int ledPin = 13;      // LED
int controlVelocidad1 = 9;
int motor1Pin1 = 2;   // Motor 1 adelante
int motor1Pin2 = 3;   // Motor 1 atras

int controlVelocidad2 = 10;
int motor2Pin1 = 4;   // Motor 2 adelante
int motor2Pin2 = 5;   // Motor 2 atras
 
//------------------------------------
//Funcion principal
//------------------------------------
void setup() // Se ejecuta cada vez que el Arduino se inicia
{
  //Establecemos el pin del led para
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600); //Inicia la comunicacion serial Arduino-PC o bluetooth
  
  // Control Motor 1
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(controlVelocidad1, OUTPUT);
  
  //Control Motro 2
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(controlVelocidad2, OUTPUT);
  
  // comprobacion de reseteo, si el led parpadea solo 3 veces, todo esta bien
  // si vuelve a parpadear, significa que ha hecho un reset, revisar conexiones
  // por si hubiera un corto
  blink(ledPin, 3, 100);
  stopAll();
}
 
//------------------------------------
//Funcion ciclicla
//------------------------------------
void loop() // Esta funcion se mantiene ejecutando
{           //  cuando este energizado el Arduino
 
  analogWrite(controlVelocidad2, 255); 
  digitalWrite(ledPin, HIGH);
  if (Serial.available()){
 
      //Variable donde se guarda el caracter enviado desde teclado
      char letter = Serial.read();
      rotate(letter);
      moveTo(letter);
  }
 
}

void moveTo(char option){
  if(option == 'S') //Tenemos que para el motor
  {
     digitalWrite(motor1Pin1, LOW);
     digitalWrite(motor1Pin2, LOW);
  }
  else if(option == 'F') //Tenemos que girar el motor hacia delante
  {
     digitalWrite(motor1Pin1, LOW);     
     digitalWrite(motor1Pin2, HIGH);
  }
  else if(option == 'B') //Tenemos que girar el motor hacia atras
  {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
  }
  else if (option>='0' && option<='9')
  {    
     //Variable para escalar el valor ingresado a rango de PWM
     int velocidad = map(option,'0','9',0,255);
     //Escritura de PWM al motor
     analogWrite(controlVelocidad1,velocidad); 
     Serial.print("El motor esta girando a la velocidad ");
     Serial.println(velocidad);
  }
}

void rotate(char option){
  if(option == 'C') //Tenemos que para el motor de girar
  {
     digitalWrite(motor2Pin1, LOW);
     digitalWrite(motor2Pin2, LOW);
  }
  else if(option == 'L') //Tenemos que girar el motor de la izquierda
  {
     digitalWrite(motor2Pin1, HIGH);
     digitalWrite(motor2Pin2, LOW);
  }
  else if(option == 'R') //Tenemos que girar el motor de la derecha
  {
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
  }
}


void stopAll(){
  analogWrite(controlVelocidad1, 0);
  analogWrite(controlVelocidad2, 0);
}
/*
Parpadeo del led, Significa que ha ejecutado la funcion setup()
si todo va bien, solo parpadea tres veces, si hay algun error que resetee el arduino,
volvera a verse el parpadeo del led
*/
void blink(int whatPin, int howManyTimes, int milliSecs) {
  int i = 0;
  for ( i = 0; i < howManyTimes; i++) {
    digitalWrite(whatPin, HIGH);
    delay(milliSecs/2);
    digitalWrite(whatPin, LOW);
    delay(milliSecs/2);
  }
}
