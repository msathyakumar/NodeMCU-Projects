#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

#include <Servo.h>



Servo servo;



char auth[] = "JUZZjgtTIn-5-WSimZDTIllE79u2VIr8";

char ssid[] = "SATHYA";

char pass[] = "sathya_123";



void setup()

{

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);



  servo.attach(15); // NodeMCU D8 pin

  

 }

  

void loop()

{

  

  Blynk.run();

  

}

BLYNK_WRITE(V1)

{

   servo.write(param.asInt());

}



BLYNK_WRITE(V2)

{

  servo.write(0);

}

BLYNK_WRITE(V3)

{

  servo.write(179);

}
