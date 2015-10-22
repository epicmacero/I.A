#include <Servo.h> 
 
Servo servo1;
Servo servo2;

int pos = 0;

int ventilador1 = 3;
 
void setup() 
{ 
  servo1.attach(1);//utilizamos 3 servos pero funciona
  servo2.attach(2); 
  pinMode(3,OUTPUT);
} 
 
void loop() 
{ 
  for(pos = 0; pos <= 180; pos += 1)  //if
  {                                 
    servo1.write(pos);               
    delay(15);                       
  } 
  for(pos = 180; pos>=0; pos-=1)     
  {                                
    servo1.write(pos);              
    delay(15);                       
  } 
  
  
  for(pos = 0; pos <= 180; pos += 1)  // if
  {                                 
    servo2.write(pos);               
    delay(15);                       
  } 
  for(pos = 180; pos>=0; pos-=1)     
  {                                
    servo2.write(pos);              
    delay(15);                       
  } 
} 
