#include <SPI.h>  //Importamos librería comunicación SPI
#include <Ethernet.h>  //Importamos librería Ethernet
#include <SD.h>
 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//Aqui va la direccion MAC de el arduino + shield
EthernetServer server(80); //Creamos un servidor Web con el puerto 80 que es el puerto HTTP por defecto
 
int led1=6;//Pin del led
int led2=7;
int led3=8;

String estado="OFF"; //Estado del Led inicialmente "OFF"
File AlmacenamientoArduino;
 
void setup()
{
  Serial.begin(9600);
 
  // Inicializamos la comunicación Ethernet y el servidor
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  Serial.print("leyendo tarjeta SD");
  pinMode(10, OUTPUT);
  if (!SD.begin(10)){
    sdsd
    Serial.println("Se ha producido un error al leer la tarjeta SD");
    return;
  }
  Serial.println("Tarjeta SD OK");
  
  AlmacenamientoArduino = SD.open("pruebasd.txt", FILE_WRITE);			  
  
  if (AlmacenamientoArduino){													  
  AlmacenamientoArduino.println("Esta modificando el AlmacenamientoArduino");
  AlmacenamientoArduino.close();
  Serial.println("Todos los datos salvados correctamente");
  }
  
  else
  {
    Serial.println("El AlmacenamientoArduino datos.txt no se abrió correctamente");
  }
  
  AlmacenamientoArduino = SD.open("datos.txt");
  

  if (AlmacenamientoArduino){
    
    Serial.println("Información contenida en pruebasd.txt:");
    
    //(AlmacenamientoArduino.available()==FALSE).
    while (AlmacenamientoArduino.available()){
      
     Serial.write(AlmacenamientoArduino.read());
    }
    

    AlmacenamientoArduino.close();
  }
  
  else{

    Serial.println("El Archivo "Serial.wirte(File.Name)" no se abrió correctamente");
  }
 
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
}
 
void loop()
{
  EthernetClient client = server.available(); //Cliente web de revision
  //Cuando un cliente se conecta
  if (client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true; //Petiticion que acaba en blanco
    String cadena=""; //Cadena de caracteres vacios 
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();//Peticion http procesada
        Serial.write(c);
        cadena.concat(c);
 
         int posicion=cadena.indexOf("LED="); //Instancia led guardada
 
          if(cadena.substring(posicion)=="LED=ON")//Si a la posición 'posicion' hay "LED=ON"
          {
            digitalWrite(led,HIGH);
            estado="ON";
          }
          if(cadena.substring(posicion)=="LED=OFF")//Si a la posición 'posicion' hay "LED=OFF"
          {
            digitalWrite(led,LOW);
            estado="OFF";
          }
 
        //Servidor listo para enviar una respuesta si recibe el mensaje vacio
        if (c == '\n' && currentLineIsBlank) {
 
            // Enviamos al cliente una respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();
 
            //Página web en formato HTML
            client.println("<html>");
            client.println("<head>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1 align='center'>Kike&Juan</h1><h3 align='center'>LED controlado por Servidor Web con Arduino</h3>");
            //Crar los botones en HTMl para enviar parametros. Simbolo utilizado '?'
            client.println("<div style='text-align:center;'>");
            client.println("<button onClick=location.href='./?LED=ON\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
            client.println("ON");
            client.println("</button>");
            client.println("<button onClick=location.href='./?LED=OFF\' style='margin:auto;background-color: #84B1FF;color: snow;padding: 10px;border: 1px solid #3F7CFF;width:65px;'>");
            client.println("OFF");
            client.println("</button>");
            client.println("<br /><br />");
            client.println("<b>LED = ");
            client.print(estado);
            client.println("</b><br />");
            client.println("</b></body>");
            client.println("</html>");
            break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    //Tiempo para el navegador de cambiar los datos
   
    delay(1);
    client.stop();// Cierra la conexión
  }
}

//Codigo programado por Kikerechu C
