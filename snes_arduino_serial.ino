#include <Servo.h>

Servo myservo;
Servo myservo1;

int pan = 90;
int tilt = 90;

int devmode = 0; //set to 1 for serial outputs
//limmits
int tiltmax = 130;
int tiltmin = 22;
int panmax = 180;
int panmin = 0;

//program vars
byte incomingByte;


unsigned long buttonPressDurationMs = 150

struct buttonOutput {
  uint8_t pin
  bool buttonActive
  unsigned long buttonActiveStart
}

const uint8_t buttonA=0
const uint8_t buttonB=1
const uint8_t buttonX=2
const uint8_t buttonY=3
const uint8_t buttonSelect=4
const uint8_t buttonStart=5
const uint8_t buttonUp=6
const uint8_t buttonDown=7
const uint8_t buttonLeft=8
const uint8_t buttonRight=9
const uint8_t buttonLB=10
const uint8_t buttonRB=11

buttonOutput buttons[12] = {
  { A0, false, 0}
  { A1, false, 0}
  { A2, false, 0}
  { A3, false, 0}
  { A4, false, 0}
  { A5, false, 0}
  { 2, false, 0}
  { 3, false, 0}
  { 4, false, 0}
  { 5, false, 0}
  { 10, false, 0}
  { 11, false, 0}
}

void setup() {
  // put your setup code here, to run once:
  myservo.attach(8);
  myservo1.attach(9);
  Serial.begin(9600);
  updateservo(pan, tilt);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(A0, OUTPUT); //A - 0
  pinMode(A1, OUTPUT); //B - 1
  pinMode(A2, OUTPUT); //X - 2
  pinMode(A3, OUTPUT); //y - 3
  pinMode(A4, OUTPUT); //select -4
  pinMode(A5, OUTPUT); //start -5
  pinMode(2, OUTPUT); //up-6
  pinMode(3, OUTPUT); //down-7a
  pinMode(4, OUTPUT); //left-8
  pinMode(5, OUTPUT); //right-9
  pinMode(10, OUTPUT); //LB-q
  pinMode(11, OUTPUT); //RB-w
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void HandleSerialChar(byte serialChar){
  uint8_t button
  
  switch(serialChar){
    case 'b': button=buttonDown   break;
    case 'f': button=buttonUp     break;
    case 'r': button=buttonRight  break;
    case 'l': button=buttonLeft   break;
    case 'm': button=buttonUp     break;
    case 'n': button=buttonDown   break;
    case '0': button=buttonA      break;
    case '1': button=buttonB      break;
    case '2': button=buttonX      break;
    case '3': button=buttonY      break;
    case '4': button=buttonSelect break;
    case '5': button=buttonStart  break;
    case '6': button=buttonUp     break;
    case '7': button=buttonDown   break;
    case '8': button=buttonLeft   break;
    case '9': button=buttonRight  break;
    case 'q': button=buttonLB     break;
    case 'w': button=buttonRB     break;
    default: return;
  }
  
  buttons[button].buttonActive = true
  buttons[button].buttonActiveStart = millis()
  
  digitalWrite( buttons[button].pin, HIGH);
  
}

void loop() {
  if (Serial.available() > 0) {
    HandleSerialChar(Serial.read());
  }

  for (int i = 0; i < 12; i++){
    unsigned long now = millis();
    if(buttons[i].buttonActive == true){
        unsigned long elapsed = now - buttons[i].buttonActiveStart;
        if (elapsed >= buttonPressDurationMs){
            buttons[i].buttonActive = false
            digitalWrite( buttons[i].pin, LOW);
        }
    }
  }
}

void updateservo(int apan, int atilt)
{
  apan = constrain(apan, panmin, panmax);
  atilt = constrain(atilt, tiltmin, tiltmax);
  if (devmode == 1)
  {
    Serial.print(apan);
    Serial.print(',');
    Serial.println(atilt);
  }
  myservo.write(apan);
  myservo1.write(atilt);

}
