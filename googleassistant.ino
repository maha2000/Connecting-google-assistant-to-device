#include<ESP8266WiFi.h>
#include "Adafruit_MQTT_Client.h"


#define wifi "DIR-825"
#define password "anuradha2017"
#define server "io.adafruit.com"
#define port 1883
#define username "MaHa2000"
#define key "6e6b88a066b34608b37323d483f7ce1c"
#define led 16

WiFiClient esp;


Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Subscribe feed = Adafruit_MQTT_Subscribe(&mqtt,username"/feeds/ldr");



void setup(){
  Serial.begin(115200);
  delay(10);
  Serial.println("Adafruit MQTT");
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(wifi);
  WiFi.begin(wifi,password);
  pinMode(led,OUTPUT);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mqtt.subscribe(&feed);
  Serial.println("connecting to MQTT");

  while(mqtt.connect()){
    delay(500);
    Serial.print(".");
  }
}

void loop(){

  while(mqtt.readSubscription(5000)){

    Serial.print("Got: ");
    Serial.print((char*)feed.lastread);
    int a=atoi((char*)feed.lastread);

    Serial.print(" ");
    Serial.println(a);
    if(a==0){
      digitalWrite(led,0);
      
    }
    else{
      digitalWrite(led,1);
    }
  }
  
}
