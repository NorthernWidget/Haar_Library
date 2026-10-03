// Haar_Demo: one row per second from a Haar temperature, pressure and humidity
// sensor over I2C. Header once, then a reading and a row each loop.
#include <Haar.h>

Haar sensor;

void setup() {
    Serial.begin(9600);
    Serial.println("Haar temperature, pressure, and humidity sensor");
    if (!sensor.begin()) {
        Serial.print("Haar not found: ");
        sensor.printNote(Serial, true);  // NotAnswering, NotSchema1, WrongName, OldFirmware
        Serial.println();
        while (1);
    }
    sensor.printDataHeader(Serial);  // straight to the port: no row is built in RAM
    Serial.println();
}

void loop() {
    sensor.acquire();             // take the readings; printDataRow() prints what they left
    sensor.printDataRow(Serial);  // -9999.00 where a reading failed
    Serial.println();
    if (sensor.anyFault()) {
        sensor.printReport(Serial);  // e.g. "SHT31: checksum failed"
        Serial.println();
    }
    delay(1000);
}
