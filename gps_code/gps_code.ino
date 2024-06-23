#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const uint32_t BaudRate = 9600; //Baud Rate for the Serial Connections

static const int GPS_RX = 0, GPS_TX = 1; //Digital Pins for the Gps module

static const int BT_RX = 12, BT_TX = 11; //Digital pins for the BT Module

// Setting up the TinyGPSPlus object
TinyGPSPlus gps;

// Initalise the serial connection to the GPS device
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
// Initalise the serial connection to the Bluetooth Module
SoftwareSerial BTSerial(BT_RX, BT_TX);

void setup() {
  Serial.begin(BaudRate);
  BTSerial.begin(BaudRate);
  gpsSerial.begin(BaudRate);

  BTSerial.println("Beginning Connection");
}

void loop() {  //As long as the GPS is available
  GetGPSData();
  CheckConnectionTimeout();
}
void GetGPSData() {
  if (gpsSerial.available() > 0)  //If there is at least 1 gps connection
    if (gps.encode(gpsSerial.read())) {
      if (CheckValidLocation())
        DisplayLocation();
      else
        BTSerial.println("ERROR: The Location Data was retrieved but it was INVALID");
    }
}

void CheckConnectionTimeout() { //After 5 seconds this will print a message informing the user that there was a timeout
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    BTSerial.println(F("TIMEOUT: GPS has not been synced with the satellite"));
  }
}
bool CheckValidLocation() { //Returns whether the encoded gps data was valid or not
  return (gps.location.isValid());
}

void DisplayLocation() { //Prints out Lat and Long to the Bluetooth Serial Connection 

  BTSerial.print(gps.location.lat(), 6);
  BTSerial.print(F(","));
  BTSerial.print(gps.location.lng(), 6);
  BTSerial.println();
}
