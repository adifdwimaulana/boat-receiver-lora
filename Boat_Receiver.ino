#include <SPI.h> //SPI Library 
#include <LoRa.h> //LoRa Library 

String slatitude;
String slongitude;
float latitude;
float longitude;
//float ownLatitude = -7.288996; 
//float ownLongitude = 112.814819;
float ownLatitude = -7.288985;
float ownLongitude = 112.814788;
bool latState = false;
bool longState = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Serial for Debugging  
    if (!LoRa.begin(915E6)) { //Operate on 433MHz
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("Setup Success");
}

void loop() {
  String message;
  // put your main code here, to run repeatedly:
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {     // If packet received
//    Serial.print("Received packet '");

    if(LoRa.available() > 0) {
      for(int i = 0; i < 20; i++){
        char incoming = (char)LoRa.read();
        if(incoming != '\n'){
            message += incoming;
            // buffer[i] = incoming;
        } else {
          break;  
        }
      slatitude = message.substring(0,9);
      slongitude = message.substring(10,19);
      latitude = slatitude.toFloat();
      longitude = slongitude.toFloat();
//      Serial.print("Location = "); Serial.print(latitude, 6); Serial.print(", "); Serial.println(longitude, 6);

      if(latitude != 0.0 && longitude != 0.0){
//          float dLat = radians(latitude - ownLatitude);
//          float dLong = radians(longitude - ownLongitude);
//          int radius = 6731000;
//
//          float a = sin(dLat/2) * sin(dLat/2) + cos(radians(ownLatitude)) * cos(radians(latitude)) * sin(dLong/2) * sin(dLong/2);
//          float c = 2*atan2(sqrt(a), sqrt(1-a));
//          float distance = abs(radius * c);

          float distLat = abs(latitude - ownLatitude) * 111194.9;
          float distLong = 111194.9 * abs(longitude - ownLongitude) * cos(radians((latitude + ownLatitude) / 2));
          float distance = sqrt(pow(distLat, 2) + pow(distLong, 2));
          if(distance <= 70){
            Serial.print("Jarak Aktual = "); Serial.print(distance); Serial.println(" meter");
            if(distance > 5) {
              distance = distance - 5;  
              Serial.print("Jarak Toleran = "); Serial.print(distance); Serial.println(" meter");
            } 
          }
      }
    }
  }
}
}
