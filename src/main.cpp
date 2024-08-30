#include <M5Stack.h>
#include <ArduinoJson.h>

#ifndef MC_NAME
#define MC_NAME "default_name"
#endif

#ifndef SERVICE_UUID
#define SERVICE_UUID "00000000-0000-0000-0000-000000000000"
#endif

#ifndef CHARACTERISTIC_UUID
#define CHARACTERISTIC_UUID "00000000-0000-0000-0000-000000000000"
#endif

std::unique_ptr<char[]> sendJsonDocument(JsonDocument &doc) {
    
    size_t bufferSize = measureJson(doc) + 1;
    std::unique_ptr<char[]> buffer(new char[bufferSize]);
    serializeJson(doc, buffer.get(), bufferSize);
    
    return buffer;
}

void setup() {
  // Initialize the M5Stack object
  M5.begin();

  // Set up the serial communication at a baud rate of 115200
  Serial.begin(115200);

  // Set the LCD to display in landscape mode
  
    int battery = M5.Power.getBatteryLevel();
    bool isCharging = M5.Power.isCharging();

    JsonDocument doc;

    doc["name"] = String(MC_NAME);
    doc["percentage"] = String(battery);
    doc["charging"] =  String(isCharging);
    doc["service_uuid"] = String(SERVICE_UUID);
    
    Serial.println(sendJsonDocument(doc).get());
}

void loop() {  
  delay(1000);
}
