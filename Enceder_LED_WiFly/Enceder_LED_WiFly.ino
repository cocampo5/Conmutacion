#include <WiFly.h>
#include <SPI.h>
 
#define PIN 3 //led pin
Server server(80); //enables a webserver on port 80
void setup()
{
  Serial.begin(9600);//setting baud rate
  pinMode(PIN,OUTPUT);//set the LED pin as output
  
  Serial.println("connecting.........");
  WiFly.begin();   //starts the Wifly shield with the hotspot configuration
  Serial.println("Done!");
  
  if (!WiFly.join("TP-LINK_LCD", "controldigital"))//change ssid and passphrase to match your hotspot settings
  {
    Serial.println(F("Association failed."));
    while (1) {
      // Hang on failure.
    }
  }
  
  Serial.print("IP Address: ");
  Serial.println(WiFly.ip());//prints the ip address of the wifly shield
  
  server.begin();   // begin the server  
}
 
void loop()
{
  Client client = server.available();       
  if (client) 
  {                                   //checks if their is a connection
    while (client.connected()) 
    {
      if (client.available()) 
      {            //checks if the connection is still available
        char c = client.read();           // reads the http request
        if (c == '$') 
        {                        //if their is a char $ present
           c = client.read();             //the character after it is read
           if(c=='1')
           {
             Serial.println("LED off");
             digitalWrite(PIN, LOW);//switches off the LED
           }
           else if(c=='2')
           {
             Serial.println("LED on");
             digitalWrite(PIN, HIGH);//switches on the LED
           } 
         }
         if (c=='\n'||c=='r')break;//if end of line or carriage return, end    loop
       }
    }
    delay(4);        // gives some time to read
    //client.stop(); //stops client
  }
}
