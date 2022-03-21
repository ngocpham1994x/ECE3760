//----------------------------------------Load libraries
#include <esp_now.h>
#include <WiFi.h>
//----------------------------------------

//----------------------------------------Defines PIN Button and PIN LED.
#define BTN_Pin   34
//----------------------------------------


int BTN_State; //--> Variable to hold the button state.

uint8_t broadcastAddressB[] = {0x3C, 0x61, 0x05, 0x3E, 0xD9, 0x4C}; //--> REPLACE WITH THE MAC Address of your receiver / ESP32 Receiver.
uint8_t broadcastAddressC[] = {0xC8, 0xC9, 0xA3, 0xC6, 0x26, 0x14};

int LED_State_Send = 0; //--> Variable to hold the data to be transmitted to control the LEDs on the paired ESP32.

String success; //--> Variable to store if sending data was successful

//----------------------------------------Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int led;
} struct_message;

struct_message send_Data; // Create a struct_message to send data.

//struct_message receive_Data; // Create a struct_message to receive data.
//----------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
  Serial.println(">>>>>");
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ VOID SETUP
void setup() {
  Serial.begin(115200);

  pinMode(BTN_Pin, INPUT);
  
  WiFi.mode(WIFI_STA); //--> Set device as a Wi-Fi Station

  //----------------------------------------Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------
  
  //----------------------------------------Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  //----------------------------------------
  
  //----------------------------------------Register peer
  esp_now_peer_info_t peerInfoB;
  memcpy(peerInfoB.peer_addr, broadcastAddressB, 6);
  peerInfoB.channel = 0;  
  peerInfoB.encrypt = false;

  esp_now_peer_info_t peerInfoC;
  memcpy(peerInfoC.peer_addr, broadcastAddressC, 6);
  peerInfoC.channel = 0;  
  peerInfoC.encrypt = false;
  //----------------------------------------
  
  //----------------------------------------Add peer        
  if (esp_now_add_peer(&peerInfoB) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  if (esp_now_add_peer(&peerInfoC) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //----------------------------------------
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop() {
  BTN_State = digitalRead(BTN_Pin); //--> Reads and holds button states.
  
  //----------------------------------------When the button is pressed it will send data to control the LED on the ESP32 Target.
  if(BTN_State == 1) {
    LED_State_Send = !LED_State_Send;
    send_Data.led = LED_State_Send;

    Serial.println();
    Serial.print(">>>>> ");
    Serial.println("Send data");
  
    //----------------------------------------Send message via ESP-NOW
    esp_err_t resultB = esp_now_send(broadcastAddressB, (uint8_t *) &send_Data, sizeof(send_Data));
    esp_err_t resultC = esp_now_send(broadcastAddressC, (uint8_t *) &send_Data, sizeof(send_Data));
    
    if (resultB == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }

    if (resultC == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
    
    //----------------------------------------
    
    //----------------------------------------Wait for the button to be released. Release the button first to send the next data.
    while(BTN_State == 1) {
      BTN_State = digitalRead(BTN_Pin);
      delay(10);
    }
    //----------------------------------------
  }
  //----------------------------------------
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
