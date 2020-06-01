#include <Arduino.h>
#include "DHT.h"
// библиотека для монитора
#include "SSD1306.h" 

// оставляем раскомментированной строчку, 
// соответствующую модели вашего датчика:
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// инициализация OLED-дисплея:
SSD1306 display(0x3c, D3, D5);

// датчик DHT
const int DHTPin = 5;
// инициализируем датчик DHT:
DHT dht(DHTPin, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10);

  // с инициализацией UI будет инициализирован и дисплей: 
  display.init();
  // переворачивает дисплей на 180 градусов по вертикали
  display.flipScreenVertically();
  // установка шрифта
  display.setFont(ArialMT_Plain_16);
  // выравние текста
  display.setTextAlignment(TEXT_ALIGN_LEFT);

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
    display.clear();  //  очищаем дисплей
    display.drawString(5, 0, "Failed DHT");  // "Не удалось прочесть данные от датчика DHT"  
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

    // выводим на дисплей
    display.clear();
    display.drawString(0, 0, "Humidity: " + String(h) + "%\t");
    // "Влажность: "
    display.drawString(0, 16, "Temp: " + String(t) + "C");
    // "Температура: "
    display.drawString(0, 32, "Temp: " + String(f) + "F");
    // "Температура: "
  }
  display.display();
  delay(10000);
}