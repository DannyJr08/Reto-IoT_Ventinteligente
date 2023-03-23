#include <DHT.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address
int ledRojo = D2;
int ledAmarillo = D3;
int ledVerde = D4;
int ledRojoGrande = D5;
#define DHTTYPE DHT11
#define DHTPIN D1 
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "INFINITUMF69C_2.4";
const char* password = "NtNXDq6zjk";
float temperatureData;
int tiempoIntervalo = 5000;
float temp1 = 23;
float temp2 = 24;
float temp3 = 25;


char server[] = "192.168.1.69";
IPAddress ip(192,168,0,177); 

WiFiClient client;

/* Setup for Ethernet and RFID */
void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  setup_wifi();
  pinMode(ledRojo,OUTPUT);
  pinMode(ledAmarillo,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledRojoGrande,OUTPUT);
}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop(){
  temperatureData = dht.readTemperature(); 
  if (temperatureData >= temp3){
    digitalWrite(ledRojo,HIGH);
    digitalWrite(ledAmarillo,LOW);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledRojoGrande,LOW);
  }
  else if (temperatureData >= temp2){
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledAmarillo,HIGH);
    digitalWrite(ledVerde,LOW);
    digitalWrite(ledRojoGrande,LOW);
  }
  else if (temperatureData >= temp1){
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledAmarillo,LOW);
    digitalWrite(ledVerde,HIGH);
    digitalWrite(ledRojoGrande,LOW);
  }
  else{
    digitalWrite(ledRojo,LOW);
    digitalWrite(ledAmarillo,LOW);
    digitalWrite(ledVerde,LOW); 
    digitalWrite(ledRojoGrande,HIGH);
  }
  Sending_To_phpmyadmindatabase();
  delay(tiempoIntervalo);
}

  void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /testcode/dht3.php?valor_temperatura=");
    client.print("GET /testcode/dht3.php?valor_temperatura=");     //YOUR URL
    Serial.println(temperatureData);
    client.print(temperatureData);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.1.69");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }
