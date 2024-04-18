/*
  ESP32 LM35 temperature Sensor Code
  http:://www.electronicwings.com
*/
#include <WiFi.h>
#include <WebServer.h>
#include "html.h"

WebServer server(80);

#define vRef 3.30
#define ADC_Resolution 4095
#define LM35_Per_Degree_Volt 0.01
#define Zero_Deg_ADC_Value 879.00

const int lm35_pin = A0;                /* Connect LM35 out pin to A0 of ESP32*/
float _temperature, temp_val, ADC_Per_Degree_Val;
int temp_adc_val;

const char* ssid = "*Your SSID*";         /*Enter Your SSID*/
const char* password = "*Your Password*"; /*Enter Your Password*/
 
void MainPage() {
  String _html_page = html_page;              /*Read The HTML Page*/
  server.send(200, "text/html", _html_page);  /*Send the code to the web server*/
}

void Temp() {
  String TempValue = String(temp_adc_val);    //Convert it into string
  server.send(200, "text/plane", TempValue);  //Send updated temperature value to the web server
}

void setup(void){
  Serial.begin(115200);               /*Set the baudrate to 115200*/
  WiFi.mode(WIFI_STA);                /*Set the WiFi in STA Mode*/
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  delay(1000);                       /*Wait for 1000mS*/
  while(WiFi.waitForConnectResult() != WL_CONNECTED){Serial.print(".");}
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP());     /*Print the Local IP*/

  server.on("/", MainPage);           /*Display the Web/HTML Page*/
  server.on("/readTemp", Temp);       /*Display the updated Temperature and Humidity value*/
  server.begin();                     /*Start Server*/
  delay(1000);                        /*Wait for 1000mS*/
  ADC_Per_Degree_Val = (ADC_Resolution/vRef)*LM35_Per_Degree_Volt;
}

void loop(void){
  for (int i = 0; i < 10; i++) {
    temp_adc_val += analogRead(lm35_pin);  /* Read ADC value */
    delay(10);
  }
  temp_adc_val = temp_adc_val/10.0;
  temp_adc_val = temp_adc_val - Zero_Deg_ADC_Value;
 temp_adc_val=(temp_adc_val/ADC_Per_Degree_Val);

  server.handleClient(); 
  Serial.print("LM35 Temperature = ");
  Serial.print(temp_adc_val);           /* Print Temperature on the serial window */
  Serial.print("°C\n");
  delay(1000);                          /* Wait for 1000mS */
}