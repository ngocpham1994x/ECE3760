
#include <esp_now.h>
#include <WiFi.h>

int L_BUTTON = 19;
int R_BUTTON = 17;
int S_BUTTON = 34;

int RED = 0;
int YELLOW = 1;
int GREEN = 2;

char LEFT = 'L';
char RIGHT = 'R';

typedef struct msg {
  int state;
  char broom;
};

struct msg sendMsg;

int yOn = 0;
int yOnB = 0;

uint8_t macAddressOne[] = {0xC8, 0xC9, 0xA3, 0xC6, 0x26, 0x14}; //--> REPLACE WITH THE MAC Address of your receiver / ESP32 Receiver.
uint8_t macAddressTwo[] = {0x3C, 0x61, 0x05, 0x3E, 0xD9, 0x4C};

esp_now_peer_info_t peerInfoOne;
esp_now_peer_info_t peerInfoTwo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfoOne.peer_addr, macAddressOne, 6);
  peerInfoOne.channel = 0;
  peerInfoOne.encrypt = false;

  memcpy(peerInfoTwo.peer_addr, macAddressTwo, 6);
  peerInfoTwo.channel = 0;
  peerInfoTwo.encrypt = false;

  if (esp_now_add_peer(&peerInfoOne) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  if (esp_now_add_peer(&peerInfoTwo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  pinMode(L_BUTTON, INPUT);
  pinMode(R_BUTTON, INPUT);
  pinMode(S_BUTTON, INPUT);
}

void loop() {
  if (digitalRead(L_BUTTON)) {
    yOn = 1;
    delay(500);
    if (digitalRead(L_BUTTON)) {
      // Green
      sendMsg.state = GREEN;
      sendMsg.broom = LEFT;
      esp_now_send(macAddressOne, (uint8_t *) &sendMsg, sizeof(sendMsg));
      esp_now_send(macAddressTwo, (uint8_t *) &sendMsg, sizeof(sendMsg));

    } else {
      // Yellow
      sendMsg.state = YELLOW;
      sendMsg.broom = LEFT;
      esp_now_send(macAddressOne, (uint8_t *) &sendMsg, sizeof(sendMsg));
      esp_now_send(macAddressTwo, (uint8_t *) &sendMsg, sizeof(sendMsg));
    }
  } else {
    if (yOn == 1) {
      // Yellow
      sendMsg.state = YELLOW;
      sendMsg.broom = LEFT;
      esp_now_send(macAddressOne, (uint8_t *) &sendMsg, sizeof(sendMsg));
      esp_now_send(macAddressTwo, (uint8_t *) &sendMsg, sizeof(sendMsg));
    }
  }

  if (digitalRead(R_BUTTON)) {
    yOnB = 1;
    delay(500);
    if (digitalRead(R_BUTTON)) {
      // Green
      sendMsg.state = GREEN;
      sendMsg.broom = RIGHT;
      esp_now_send(macAddressOne, (uint8_t *) &sendMsg, sizeof(sendMsg));
      esp_now_send(macAddressTwo, (uint8_t *) &sendMsg, sizeof(sendMsg));

    } else {
      // Yellow
      sendMsg.state = YELLOW;
      sendMsg.broom = RIGHT;
      esp_now_send(macAddressOne, (uint8_t *) &sendMsg, sizeof(sendMsg));
      esp_now_send(macAddressTwo, (uint8_t *) &sendMsg, sizeof(sendMsg));
    }
  } else {
    if (yOnB == 1) {
      // Yellow
      sendMsg.state = YELLOW;
      sendMsg.broom = RIGHT;
      esp_now_send(macAddressOne, (uint8_t *) &sendMsg, sizeof(sendMsg));
      esp_now_send(macAddressTwo, (uint8_t *) &sendMsg, sizeof(sendMsg));
    }
  }
  
  if (digitalRead(S_BUTTON)) {
    yOn = 0;
    yOnB = 0;
    // Red
    sendMsg.state = RED;
    sendMsg.broom = LEFT;
    esp_now_send(macAddressOne, (uint8_t *) &sendMsg, sizeof(sendMsg));
    esp_now_send(macAddressTwo, (uint8_t *) &sendMsg, sizeof(sendMsg));
  }
  
}
