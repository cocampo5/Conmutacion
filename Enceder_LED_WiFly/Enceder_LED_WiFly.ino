#include <WiFly.h>
#include <SPI.h>
Server server(80); //enables a webserver on port 80
void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.println("connecting.........");
  WiFly.begin();   
  Serial.println("Done!");

  if (!WiFly.join("TP-LINK_LCD", "controldigital"))//change ssid and passphrase to match your hotspot settings
  {
    Serial.println(F("Association failed."));
    while (1) {

    }
  }

  Serial.print("IP Address: ");
  Serial.println(WiFly.ip());
  server.begin();   
}

void loop()
{
  Client client = server.available();
  if (client) 
  {                                  
    while (client.connected()) 
    {
      if (client.available()) 
      {            
        char c = client.read();          
        if (c == '$') 
        {                       
          c = client.read();             
          if(c=='1')
          {
            Serial.println("Verde");
            digitalWrite(2, HIGH);
            digitalWrite(3, LOW);
            digitalWrite(4, LOW);
          }
          if(c=='2')
          {
            Serial.println("Rojo");
            digitalWrite(3, HIGH);
            digitalWrite(4, LOW);
            digitalWrite(2, LOW);
          } 
          if(c=='3')
          {
            Serial.println("Azul");
            digitalWrite(4, HIGH);
            digitalWrite(3, LOW);
            digitalWrite(2
            , LOW);
            
          } 
        }
        if (c=='\n'||c=='r')break;
      }
    }
    delay(4);        

    client.stop(); 

  }
}



