#include "DHT.h"
#include <Wire.h>
#include "DS3231.h"

RTClib RTC;

#define DHTPIN 3
#define DHTTYPE DHT11   // DHT 11 

DHT dht(DHTPIN, DHTTYPE);

#if defined(ARDUINO_ARCH_AVR)
#define SERIAL  Serial

#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define SERIAL  SerialUSB
#else
#define SERIAL  Serial
#endif

DS3231 Clock;
int in1 = 6;
const int read = A0;   // Sensor AO pin to Arduino pin A0
int value;             // Variable to store the incomming data


void setup() 
{

    SERIAL.begin(115200); 
    Wire.begin();
    pinMode(in1, OUTPUT);
    digitalWrite(in1, HIGH);

    dht.begin();
}

void loop() 
{
    float temp_hum_val[2] = {0};
    DateTime now = RTC.now();
    value = analogRead(read);
    
    if(!dht.readTempAndHumidity(temp_hum_val)){
    Serial.print(now.year(), DEC);
    Serial.print(':');
    Serial.print(now.month(), DEC);
    Serial.print(':');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    SERIAL.print(" ");

    SERIAL.print(temp_hum_val[0]);
    SERIAL.print(" ");
    SERIAL.print(temp_hum_val[1]);
    SERIAL.print(" ");

    Serial.print(value);
    Serial.println();

    if(value<500){
      digitalWrite(in1, LOW);
      delay(1000);
      }
      
    else{
      digitalWrite(in1, HIGH);
      }
      
    }
    else{
       SERIAL.println("Failed to get temprature and humidity value.");
    }

   delay(1500);
}
