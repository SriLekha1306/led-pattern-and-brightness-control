#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int brightness = 5;

// ---------- PATTERNS ----------
byte happy[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

byte sad[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

byte heart[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000
};

byte sea[8] = {
  B00000000,
  B00111000,
  B01000100,
  B10000010,
  B00111001,
  B01000101,
  B10000010,
  B01111100
};

byte fire[8] = {
  B00010000,
  B00111000,
  B01111100,
  B11111110,
  B11111110,
  B01111100,
  B00111000,
  B00010000
};

// ---------- DRAW ----------
void show(byte p[8]) {
  mx.clear();
  for (int i = 0; i < 8; i++) {
    mx.setRow(0, i, p[i]);
  }
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);

  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, brightness);
  mx.clear();

  show(happy);
}

// ---------- LOOP ----------
void loop() {

  if (Serial.available()) {

    char cmd = Serial.read();

    if (cmd == '\n' || cmd == '\r' || cmd == ' ') return;

    // emojis
    if (cmd == 'W') show(happy);
    else if (cmd == 'X') show(fire);
    else if (cmd == 'Y') show(sad);
    else if (cmd == 'Z') show(heart);
    else if (cmd == 'Q') show(sea);

    // brightness 0–9 → map to 0–15
    else if (cmd >= '0' && cmd <= '9') {
      brightness = map(cmd - '0', 0, 9, 0, 15);
      mx.control(MD_MAX72XX::INTENSITY, brightness);
    }
  }
}