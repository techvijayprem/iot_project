/*
  ESP32 LM35 temperature Sensor Code
  http:://www.electronicwings.com
*/
#include <WiFi.h>
#include <WebServer.h>
#include "html.h"

WebServer server(80);

const int turbidity_pin = A0;                /* Connect LM35 out pin to A0 of ESP32*/
int read_ADC;
int water_q;

const char* ssid = "realme111x";         /*Enter Your SSID*/
const char* password = "12345679"; /*Enter Your Password*/
 
void MainPage() {
  String _html_page = html_page;              /*Read The HTML Page*/
  server.send(200, "text/html", _html_page);  /*Send the code to the web server*/
}

void Purity() {
  String WatValue = String(water_q);    //Convert it into string
  server.send(200, "text/plane", WatValue);  //Send updated water value to the web server
}

void setup(void){\
  Serial.begin(115200);               /*Set the baudrate to 115200*/
  WiFi.mode(WIFI_STA);                /*Set the WiFi in STA Mode*/
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(100);                       /*Wait for 1000mS*/
  while(WiFi.waitForConnectResult() != WL_CONNECTED){Serial.print(".");}
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP());     /*Print the Local IP*/

  server.on("/", MainPage);           /*Display the Web/HTML Page*/
  server.on("/readPurity", Purity);       /*Display the updated Purity and Humidity value*/
  server.begin();                     /*Start Server*/
  delay(100);                        /*Wait for 1000mS*/
}

void loop(void){
read_ADC = analogRead(turbidity_pin);
if(read_ADC>208)read_ADC=208;

water_q = map(read_ADC, 0, 208, 300, 0); 
 
if(water_q < 10)            Serial.print("Water Very Clean");
if(water_q >= 10 && water_q < 30) Serial.print("Water Norm Clean");
if(water_q >= 100)           Serial.print("Water Very Dirty");
server.handleClient(); 
Serial.print("\n");

delay(100);                        /* Wait for 1000mS */
}