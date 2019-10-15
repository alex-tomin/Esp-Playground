#ifndef DHT_READER /* guard */
#define DHT_READER

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT11   

DHT_Unified dhtSensor(D6, DHTTYPE); //MOVE Inside

class DhtReader {

   public:
    DhtReader() {}

    float readTemperature() {
    
        sensors_event_t event;
        dhtSensor.temperature().getEvent(&event);
        if (isnan(event.temperature)) {
            Serial.println(F("Error reading temperature!"));
        }
        else {
            Serial.printf("Temperature: \t %f °C\n", event.temperature);
        }
               
        return event.temperature;
    }

    void printSensorDetails() {
        sensor_t sensor;
        dhtSensor.temperature().getSensor(&sensor);
        
         // Print temperature sensor details.
        Serial.println(F("------------------------------------"));
        Serial.println(F("Temperature Sensor"));
        Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
        Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
        Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
        Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
        Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
        Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
        Serial.println(F("------------------------------------"));
        
        // Print humidity sensor details.
        dhtSensor.humidity().getSensor(&sensor);
        Serial.println(F("Humidity Sensor"));
        Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
        Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
        Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
        Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
        Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
        Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
        Serial.println(F("------------------------------------"));

        Serial.printf("min delay %i", sensor.min_delay/1000);
    }
};
#endif

