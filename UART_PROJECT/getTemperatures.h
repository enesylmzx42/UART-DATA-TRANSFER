#include <OneWire.h>
#include <DallasTemperature.h>

// Sensörler için dijital pinlerin tanımlanması
#define ONE_WIRE_BUS 2

// OneWire nesnesi tanımlama
OneWire oneWire1(ONE_WIRE_BUS);

// DallasTemperature nesneleri tanımlama
DallasTemperature sensors(&oneWire1);

float temp1 = 0.0;

void getTemps(){
    sensors.requestTemperatures();

    temp1 = sensors.getTempCByIndex(0);

    Serial.print("Sensör 1 sicaklik: ");
    Serial.println(temp1);

    delay(400);
}
