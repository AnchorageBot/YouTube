/*  

  This sketch uses a Adafruit Huzzah32 with a DHT22 sensor to measure temp and humidity every 60 seconds using Arduino IDE 1.8.10
  
  Engineering 
    Adafruit
      idea https://github.com/adafruit/DHT-sensor-library
    ATS
      https://www.youtube.com/channel/UCDuWq2wFqeVII1KC7grySRg
      https://github.com/AnchorageBot
      Feb 2020

*/  

#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(60000);  // 60 second delay
  
  float h = dht.readHumidity();
  Serial.print("Humidity: % ");
  Serial.print(h);
  Serial.println();  
  float t = dht.readTemperature();
  Serial.print("Temperature: C  ");
  Serial.print(t);  
  Serial.println();
  Serial.println();   

  if (isnan(h) || isnan(t)) {
  Serial.println("Failed to read from DHT sensor!");
  return;
  }
}
