#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

SoftwareSerial NodeMCU(D2,D3);


#define FIREBASE_HOST "xxxxxxx"                          // the project name address from firebase id
#define FIREBASE_AUTH "XXXXXXXX"   

#define WIFI_SSID "xxxxxx"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "xxxxxx"                                    //password of wifi ssid


void setup(){
  Serial.begin(9600);
  NodeMCU.begin(4800);
  pinMode(D3,INPUT);
  pinMode(D2,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
}

float val;
int flag=0;
String x;
void loop(){
  while(NodeMCU.available()>0)
  {
    
    val= NodeMCU.parseFloat();
    if(NodeMCU.read()=='\n'){
      Serial.println(val);
      flag=val;
    }
    x=String(flag);
    Serial.println(x);
    Firebase.pushString("/Home2/Supply", x);
    delay(5000);
  }
}  
