//----------------------------------------Load libraries
#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Defines PIN Button and PIN LED.
#define LED_Pin   23
//----------------------------------------

int LED_State_Receive; //--> Variable to receive data to control the LEDs on the ESP32 running this code.

//----------------------------------------Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int led;
} struct_message;

struct_message receive_Data; // Create a struct_message to receive data.
//----------------------------------------


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receive_Data, incomingData, sizeof(receive_Data));
  Serial.println();
  Serial.println("<<<<< Receive Data:");
  Serial.print("Bytes received: ");
  Serial.println(len);
  LED_State_Receive = receive_Data.led;
  Serial.print("Receive Data: ");
  Serial.println(LED_State_Receive);
  Serial.println("<<<<<");

  digitalWrite(LED_Pin, LED_State_Receive);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
void setup() {
  Serial.begin(115200);

  pinMode(LED_Pin, OUTPUT);
  
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
