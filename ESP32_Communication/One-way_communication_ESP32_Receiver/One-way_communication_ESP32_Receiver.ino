/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp32/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

//----------------------------------------Load libraries
#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Define variables to store incoming readings
int receive_rnd_val_1;
int receive_rnd_val_2;
//----------------------------------------

//----------------------------------------Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int rnd_1;
    int rnd_2;
} struct_message;

struct_message receive_Data; //--> Create a struct_message to receive data.
//----------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  Serial.print("Bytes received: ");
  Serial.println(len);
  receive_rnd_val_1 = receive_Data.rnd_1;
  receive_rnd_val_2 = receive_Data.rnd_2;
  Serial.println("Receive Data: ");
  Serial.println(receive_rnd_val_1);
  Serial.println(receive_rnd_val_2);
  Serial.println("<<<<<");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station

  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------
  
  esp_now_register_recv_cb(OnDataRecv); //--> Register for a callback function that will be called when data is received
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID LOOP
void loop() {
  
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
