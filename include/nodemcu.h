#ifndef NODEMCU
#define NODEMCU

#include<MUX74HC4067.h>
#include "DHT.h"

#define S0 D0
#define S1 D1
#define S2 D2
#define S3 D3
#define EN D4
#define SIG A0

#define DHTPIN D5
#define DHTTYPE DHT22

#define RELAY1 D7
#define RELAY2 D8

MUX74HC4067 mux(D4, D0, D1, D2, D3);
DHT dht(DHTPIN, DHTTYPE);

int rawValue = 0;
int dryValue = 1024;
int wetValue = 0;
int percentageValue = 0;
int percentageDryValue = 0;
int percentageWetValue = 100;

int rawValue1 = 0;
int rawValue2 = 0;
int percentageValue1 = 0;
int percentageValue2 = 0;

float temperature = 0;

float temperatureLimit = 35;
int dryPercentageLimit = 65;

bool isWaiting = false;
unsigned long start;
unsigned long timer;
unsigned long duration = 1000 * 60;

class Board
{
    private:
        static void Pump(int humidity, float temperature, u_int8_t relay)
        {
            bool ready = humidity <= dryPercentageLimit && temperature >= temperatureLimit;

            if(ready && !isWaiting)
            {
                digitalWrite(relay, LOW);
                delay(5000);
                digitalWrite(relay, HIGH);
                isWaiting = true;
                start = millis();
            }
        }

        static void TimerManager()
        {
            if(isWaiting)
            {
                int second = start + duration - timer;
                Serial.print("menunggu: ");
                Serial.print(second/1000);
                Serial.print(" detik");
                Serial.print(" | ");
                Serial.print("(");
                Serial.print((float) second/1000/60);
                Serial.print(" menit");
                Serial.print(")");
                Serial.println("\n");

                timer = millis();
                if(timer >= start + duration)
                {
                    isWaiting = false;
                }
            }
        }

    public:
        static void Setup()
        {
            Serial.begin(115200);

            mux.signalPin(SIG, INPUT, ANALOG);
            dht.begin();

            pinMode(RELAY1, OUTPUT);
            pinMode(RELAY2, OUTPUT);

            digitalWrite(RELAY1, HIGH);
            digitalWrite(RELAY2, LOW);

        }

        static void Loop()
        {
            temperature = dht.readTemperature();

            rawValue1 = mux.read(1);
            rawValue2 = mux.read(2);
            percentageValue1 = map(rawValue1, dryValue, wetValue, percentageDryValue, percentageWetValue);
            percentageValue2 = map(rawValue2, dryValue, wetValue, percentageDryValue, percentageWetValue);
                
            delay(1000);

            Pump(percentageValue1, temperature, RELAY1);
            //Pump(percentageValue2, temperature, RELAY2);

            TimerManager();
        }
};


#endif