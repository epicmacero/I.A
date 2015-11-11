#include <Servo.h> 
 
Servo servo1;
Servo servo2;

const int ventilador1 = 3;// el pin del ventilador
const int btnventilador = 4;// el pin del boton
const int led1 = 5;// led rojo de la puerta
const int led2 = 6;// led amarillo de la puerta
const int led3 = 7;// led verde de la puerta

int pos = 0;

int enecender = 0; // si esta funcionando el ventilador
int anterior = 0; // pulsacion anterior
int estado = 0; // el estado actual del boton

void setup() 
{ 
  servo1.attach(1);//utilizamos 3 servos pero funciona
  servo2.attach(2); 
  pinMode(ventilador1,OUTPUT);
  pinMode(btnventilador,INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
} 
 
void loop() 
{ 
  digitalWrite(led1, HIGH); //la luz roja estara siempre en roja hasta que no se abra la puerta
  
  //apertura de puerta
  for(pos = 0; pos <= 90; pos += 1)  //if, para que tu lo enlaces a la web y uses el control de apertura
  {                                 
    servo1.write(pos);
    digitalWrite(led1,LOW);// la luz roja se apaga
    digitalWrite(led2,HIGH);//la luz amarilla se enciende
    delay(8000);//pasan 8 segundos
    digitalWrite(led2,LOW);// la luz amarilla se apaga
    digitalWrite(led3,HIGH);// la luz verde se enciende   
  } 
  
  //cierre de puerta
  for(pos = 90; pos>=0; pos-=1)  //if, para que tu lo enlaces a la web y uses el control de cierre   
  {                                
    servo1.write(pos);
    digitalWrite(led3,LOW);// la luz verde se apaga
    digitalWrite(led2,HIGH);//la luz amarilla se enciende
    delay(8000);// pasan 8 segundos
    digitalWrite(led2,LOW);// la luz amarilla se apaga
    digitalWrite(led1,HIGH);// la luz roja se enciende  
  } 
  
  
  //ventilador
  estado = digitalRead(btnventilador); // comprobamos el estado
  
   if (estado && anterior == 0) // comprobamos si el anterior era sin pulsar y el estado actual es pulsado
   {
     encender = 1 - encender; //asignamos el estado contrario
     delay(30);               //antirrebote 
   }
   
 anterior = estado; // Guardamos el estado actual para posteriores comprobaciones
 
 if (encender)
   digitalWrite(ventilador1, HIGH);
 else
  digitalWrite(ventilador1, LOW);
  
} 
