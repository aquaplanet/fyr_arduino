const int LED_PIN = 13;
const int BTN_PIN = 2;
const int CMD_LENGTH = 33;

int isOn = false;
int btnState = HIGH;
int oldBtnState = HIGH;

unsigned long time;
String command = "off";

void toggleBtn() {
  oldBtnState = btnState;
  btnState = digitalRead(BTN_PIN);

  if (btnState == HIGH && oldBtnState == LOW) {
    isOn = ! isOn;
    delay(10);
  }

}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);

  Serial.begin(9600);
}

// See http://sv.wikipedia.org/wiki/Fyrkarakt%C3%A4r
// http://fyr.org/ehfyrvst.htm
void vinga_ostra_nedre() {
  int modTime = time % 4000;

  if (modTime < 500) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
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
  } else {
    digitalWrite(LED_PIN, LOW);
  }

}
