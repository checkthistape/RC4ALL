#define ESP_DRD_USE_SPIFFS true

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <spiffs_api.h>

#include <string>

// #define JSON_CONFIG_FILE "/test_config.json"
// bool shouldSaveConfig=false;


const int BUTTON_PIN = D7;
const int BUTTON_PIN2 = D2;

int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin

int lastState2 = HIGH;
int currentState2;

WiFiUDP Udp;
unsigned int localUdpPort = 54000; // local port to listen on
char incomingPacket[2]; // buffer for incoming packets

char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back
char  replyPacket2[] = "Shift";
char  replyPacket3[] = "IDK";
char testPacket[]="t";
char buttonTxt[] = "r";
char buttonTxt2[] = "l";

void saveConfigFile(){
  //StaticJsonDocument<512> json;

}

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  Serial.println();

  WiFiManager wfm;
  wfm.setDebugOutput(true);
  //wfm.resetSettings();

  //wfm.

  //WiFiManagerParameter custom_text_box("my_text", "Enter your string here!", "default string",50);

  //wfm.addParameter(&custom_text_box);

  if(!wfm.autoConnect("ESP8266_AP", "password")){
    Serial.println("failed to connect and hit timeout");
    ESP.restart();
    delay(1000);
  }
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Serial.print(WiFi.SSID().c_str()); // Serial.print(WiFi.psk());
  
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

}




void loop() {
  // put your main code here, to run repeatedly:
  currentState = digitalRead(BUTTON_PIN);
  currentState2 = digitalRead(BUTTON_PIN2);


  int packetSize = Udp.parsePacket();

  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 2);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.println(Udp.remoteIP());
    Serial.printf("UDP packet contents: %s\n", incomingPacket);


    if(incomingPacket=="a"){
      Serial.print(Udp.remoteIP());
      Udp.beginPacket(Udp.remoteIP(), 54000);
      Udp.write(replyPacket);
      Udp.endPacket();
    }
    else if(incomingPacket=="b"){
      Udp.beginPacket(Udp.remoteIP(), 54000);
      Udp.write(replyPacket2);
      Udp.endPacket();
    }
    else {
      Udp.beginPacket(Udp.remoteIP(), 54000);
      Udp.write(incomingPacket);
      Udp.endPacket();
    }
    // send back a reply, to the IP address and port we got the packet from
  
    
  }
  if(lastState == HIGH && currentState == LOW){ 
    
    Serial.printf("The state changed from LOW to HIGH, MESSAGE replyPacket SENT TO %s ",Udp.remoteIP());
    //Serial.printf("quantity %d\n\n", quantity);
    Serial.println("\n");
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.beginPacket(Udp.remoteIP(), 54000);
    Udp.write(buttonTxt);
    Udp.endPacket();
    delay(200);

    
    }
  if(lastState2 == HIGH && currentState2 == LOW){
    Serial.printf("The state changed from LOW to HIGH, MESSAGE replyPacket SENT TO %s ",Udp.remoteIP());
    Serial.println("\n");
    Udp.beginPacket(Udp.remoteIP(), 54000);
    Udp.write(buttonTxt2);
    Udp.endPacket();
    delay(200);
  }

  // save the last state
  lastState = currentState;
  lastState2 = currentState2;
}