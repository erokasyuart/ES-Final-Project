#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 0, TXPin = 1;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup() {
  Serial.begin(GPSBaud);
  gpsSerial.begin(GPSBaud);
}

void loop() { //As long as the GPS is available
  if (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read())) {
      if(CheckValidLocation())
        DisplayLocation();
      else
        Serial.println("ERROR: Something went wrong while Retrieving Location Data");
    }
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
  }
}

bool CheckValidLocation() {
  return (gps.location.isValid());
}

void DisplayLocation() {
  Serial.print(gps.location.lat(), 6);
  Serial.print(F(","));
  Serial.print(gps.location.lng(), 6);
  Serial.println();
}
