#include <Arduino.h>
#include "DHT.h"

// оставляем раскомментированной строчку, 
// соответствующую модели вашего датчика:
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// датчик DHT
const int DHTPin = 5;
// инициализируем датчик DHT:
DHT dht(DHTPin, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);
  dht.begin();
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  // данные от датчика могут запаздывать на 2 секунды
  // (это очень медленный датчик):
  float h = dht.readHumidity();
  // считываем температуру в Цельсиях (по умолчанию):
  float t = dht.readTemperature();
  // считываем температуру в Фаренгейтах
  // (isFahrenheit = true):
  float f = dht.readTemperature(true);
  // проверяем, прочитались ли данные от датчика, 
  // и если нет, то выходим и начинаем заново:
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
                // "Не удалось прочитать 
                // данные от датчика DHT"        
  }
  else{
    //выводим данные в Serial monitor
    Serial.print("Humidity: ");  //  "Влажность: "
    Serial.print(h);
    Serial.print(" %\t Temperature: ");  //  "Температура: "
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\n");
  }
  delay(10000);
}