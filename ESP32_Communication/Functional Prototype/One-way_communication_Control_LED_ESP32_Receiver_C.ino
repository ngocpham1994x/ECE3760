#include <esp_now.h>
#include <WiFi.h>

int GREEN = 22;
int YELLOW = 21;
int RED = 23;
int SWITCH = 14;
//int POWER = 13;

char LEFT = 'L';
char RIGHT = 'R';

char lookFor;

int R = 0;
int Y = 1;
int G = 2;

typedef struct msg {
  int state;
  char broom;
};

struct msg receiveMsg;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receiveMsg, incomingData, sizeof(receiveMsg));

  if (digitalRead(SWITCH) == HIGH) {
    lookFor = LEFT;
  } else {
    lookFor = RIGHT;
  }

  //note: LOW = LED ON, HIGH = LED OFF
  if (receiveMsg.state == R) {
    //red
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, HIGH);
  } else if (receiveMsg.state == Y && receiveMsg.broom == lookFor) {
    //yellow
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
  } else if (receiveMsg.state == G && receiveMsg.broom == lookFor) {
    //green
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
  }
}

void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error");
    return;
    
  }

  esp_now_register_recv_cb(OnDataRecv);
  
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
//  pinMode(POWER, OUTPUT);
  pinMode(SWITCH, INPUT);
//  digitalWrite(POWER, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

}
