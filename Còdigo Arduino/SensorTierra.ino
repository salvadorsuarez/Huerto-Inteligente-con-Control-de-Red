#include <LiquidCrystal.h>
#include <DHT11.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pin=7;
int v_suelo;
DHT11 dht11(pin);

#define LED 9     //El LED esta conectado en el pin 9 
#define LDR 0     //El LDR esta conectador en el pin A0

int luz = 0;       
int valor_sensor = 0;       
int valor_limite = 490;  //Este valor hara que el LED cambie de estado a una determinada luminosidad (podeis con distintos valores para ajustar la sensibilidad)


void setup() {
  // Definimos la LCD con dimension 2x16 y definimos 
//los caracteres que deben salir en las filas:
lcd.begin(16,2);
lcd.print("T=      H=");

  Serial.begin(9600);    
  pinMode(LED,OUTPUT);
  pinMode(LDR,INPUT);
}

//Hasta aquí hemos definido qué queremos que 
//salga impreso por la pantalla y el tamaño de ésta.
void loop() { 
 //Sensor de Humedad
  //0 - 250 seco
  //250 - 600 húmedo
  //600 - 950 Encharcado
      v_suelo= analogRead(0);
       int error;
       float temperatura, humedad;
       if((error = dht11.read(humedad, temperatura)) == 0){
        
  lcd.setCursor(2,0);
  lcd.print(temperatura);
  lcd.setCursor(10,0);
  lcd.print(humedad);
       }

       else{
        lcd.setCursor(0,0);
        lcd.print("ERROR");
       } 
 
 //condiciones de aviso de riego
  if(v_suelo<=250){
       lcd.setCursor(0,1);
lcd.print("Me Ahogo!     ");}
  if((v_suelo>250)&&(v_suelo<=600)){
  lcd.setCursor(0,1);
lcd.print("Estoy bien :)   ");
}
  if(v_suelo>600){
  lcd.setCursor(0,1);
lcd.print("Necesito Agua!   ");
}  
  delay(1000);

    valor_sensor = analogRead(LDR); 
  luz = (5.0 * valor_sensor * 100.0)/1024.0; //Para entender esta formula visitar: http://programarfacil.com/podcast/48-sensor-de-temperatura-en-arduino/
  Serial.print(luz);  
  Serial.println(" Luz");             
  delay(300);                       
  
  if (luz <= valor_limite)   //Si el valor de luz es menor o igual que el valor limite
  {
    digitalWrite (LED, LOW);  //El led se apaga
  }
  if (luz > valor_limite)   //Si es mayor que el valor limite
  {
    digitalWrite (LED, HIGH);  //El led se eniende
  }
} 
