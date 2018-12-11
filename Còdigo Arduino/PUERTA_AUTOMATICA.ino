#include <Ultrasonic.h>




#include <Servo.h>

Ultrasonic ultrasonic(3,4); 
Servo miniservo1; 
Servo miniservo2; 
int led=7;
int distancia; 

void setup()
{
  miniservo1.attach(10); 
  miniservo2.attach(11); 
   
    miniservo1.write(90);
    miniservo2.write(90);
    pinMode(led, OUTPUT);
}

void loop()
{  
  
    distancia = ultrasonic.Ranging(CM); 
     
    if(distancia <= 20){ 
    
        miniservo1.write(180);
        miniservo2.write(0); 
        digitalWrite(led, HIGH);   
        delay(500);   
    }else{  
    miniservo1.write(90);
    miniservo2.write(90);
    digitalWrite(led, LOW);
    }  
    delay(500);  
}    
