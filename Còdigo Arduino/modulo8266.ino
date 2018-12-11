#include <SoftwareSerial.h>
SoftwareSerial BT1(3, 2); // RX | TX
int n1;
float temp;
void setup()
 {Serial.begin(9600);
 BT1.begin(9600);
 pinMode(8,OUTPUT);
 pinMode(9,OUTPUT);
 }
void loop() 
{ while (BT1.available() >0 )
 {char c = BT1.read();
 if (c == 71) 
 {Serial.println("peticion web enviada");
 delay(500);
 servidor();
 }
 } 
}
void escribir(String text)
{BT1.print("AT+CIPSEND=0,"); 
 BT1.println(text.length());
 if (BT1.find(">")) // Si se recibe el mensaje
 {Serial.println(text);
 BT1.println(text); //mandamos el mensaje por el wifi 
 delay(10);
 while ( BT1.available() > 0 ) 
 {if ( BT1.find("SEND OK") ) //buscamos "ok" y luego salimos
 break; 
 }
 }
}
void servidor(void) 
 { escribir("<!DOCTYPE HTML>");
 escribir("<html>"); //una pagina web necesita esto <HTML> y </HTML> es el inicio y fin del documento
 escribir("<head><title>lm35 arduino esp8266 html</title>"); //nombre de la pestaña que llevara la pagina
 escribir("<meta http-equiv=\"refresh\" content=\"5\"></head>"); //tiempo para refrescar la pagina web
 escribir("<body><h1> <FONT SIZE=\"5\" COLOR=\"black\"> Informacion de flora </h1>"); //titulo del inicio de la pagina
 escribir(" <BODY BGCOLOR=\"blue\"> "); 
 temp = (5.0 * analogRead(0) * 100.0) / 1024;
 escribir("<FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"blue\"> la temperatura es </FONT>"); //escribimos y cambiamos el tamaño, letra y color
 escribir(String(temp)); //imprimimos la variable
 escribir(" grados <br /><br />");
 escribir("<DIV align=\"center\"><A HREF=\"http://www.hetpro.com\" target=\"_blank\">hetpro.com</a><BR></DIV>");
 delay(1);
 BT1.println("AT+CIPCLOSE=0");
 //delay(500);
 
