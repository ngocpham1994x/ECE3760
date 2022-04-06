
int GREEN = 32;
int YELLOW = 33;
int RED = 25;
int BUTTON = 22;
int RED_BUTTON = 23;

int yOn = 0;

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(RED_BUTTON, INPUT);
}

void loop() {
  if (digitalRead(BUTTON)) {
    yOn = 1;
    if (digitalRead(BUTTON)) {
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(RED, LOW);
    } else {
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(RED, LOW);
    }
  } else {
    if (yOn == 1) {
      digitalWrite(GREEN, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(RED, LOW);
    }
  }
  
  if (digitalRead(RED_BUTTON)) {
    yOn = 0;
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, HIGH);
  }
  
}
