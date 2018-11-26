#include "AIS_NB_BC95.h"
#include <IoTtweetNBIoT.h>
#include <AltSoftSerial.h>
#include "DHT.h"

#define DHTpin 7
#define DHTType DHT11
DHT dht(DHTpin, DHTType);

AltSoftSerial Serial2;

AIS_NB_BC95 modem;

String userid = "003894";                         /*IoTtweet account user ID (6 digits, included zero pre-fix)*/
String key = "3je3loww68jg";                      /*IoTtweet registered device key in "MY IOT Garage"*/
float data0, data1, data2, data3;                 /*Your sending data variable.*/
String private_tweet = "AIS NB-IoT";             /*Your private tweet meassage to dashboard*/
String public_tweet = "AIS NB-iot 01";           /*Your public tweet message to dashboard*/

const long looptime = 20;                         /* Loop delay time in sec. */
unsigned long previousMillis = 0;
long cnt = 0;
float t, h;

IoTtweetNBIoT myNBiot;

void setup() 
{
  
  myNBiot.init();
  previousMillis = millis();
  
}

void loop() 
{

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= looptime*1000)
    {
      cnt++;     
      

      t = dht.readTemperature();
      h = dht.readHumidity();

      if(isnan(t) || isnan(h)){
        Serial.println("Sensor read failed !");
        return;
      }
      Serial.println("t = " + String(t) + "celcuis");
      Serial.println("h = " + String(h) + "%RH");
      Serial.println();


      
      String rssi = myNBiot.readRSSI();
      String rssi_txt = "RSSI is " + rssi;

      byte buf[30];
      rssi.toCharArray(buf,30);
      
      int rssi_num = atoi(buf);
      rssi_num = rssi_num * (-1);



      /* Send data to IoTtweet dashboard */
      myNBiot.sendDashboard(userid,key,t,h,rssi_num,0,private_tweet,public_tweet);
     
      previousMillis = currentMillis;

    }
}




