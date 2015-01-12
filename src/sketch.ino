const int RED_PIN = 14;
const int GREEN_PIN = 15;
const int BLUE_PIN = 16;
const int BTN_PIN = 2;

const int RED = 0;
const int GREEN = 1;
const int WHITE = 2;
const int BLACK = 3;


int btnState = HIGH;
int oldBtnState = HIGH;

unsigned long time;
String command = "off";

void toggleBtn() {
  oldBtnState = btnState;
  btnState = digitalRead(BTN_PIN);

  if (btnState == HIGH && oldBtnState == LOW) {
    command = "off";
    delay(10);
  }

}

void writeColor(unsigned int red, unsigned int green, unsigned blue) {
  analogWrite(RED_PIN, red);
  analogWrite(BLUE_PIN, green);
  analogWrite(GREEN_PIN, blue);
}

void writeFixedColor(unsigned int color) {
  if (color == RED) {
    writeColor(255,0,0);
  } else if (color == GREEN) {
    writeColor(0,255,0);
  } else if (color == WHITE) {
    writeColor(255,255,255);
  } else {
    writeColor(0,0,0);
  }
}


void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);

  Serial.begin(9600);
}

// See http://sv.wikipedia.org/wiki/Fyrkarakt%C3%A4r
// http://fyr.org/ehfyrvst.htm
void vinga_ostra_nedre() {
  int modTime = time % 4000;

  if (modTime < 500) {
    writeFixedColor(BLACK);
  } else {
    writeFixedColor(WHITE);
  }
}

void tistlarna() {
  int modTime = time % 15000;

  if (modTime < 2000) {
    writeFixedColor(WHITE);
  } else if (modTime < 8000) {
    writeFixedColor(BLACK);
  } else if (modTime < 10000) {
    writeFixedColor(WHITE);
  } else {
    writeFixedColor(BLACK);
  }
}

void loop()
{
  toggleBtn();

  if (Serial.available() > 0) {
    command = Serial.readString();
    command.trim();
  }

  time = millis();

  if (command == "VINGA_OSTRA_NEDRE") {
    vinga_ostra_nedre();
  } else if (command == "TISTLARNA") {
    tistlarna();
  } else {
    writeColor(0,0,0);
  }

}
