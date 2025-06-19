
#include <Arduino.h>
#include <MyEncoder.h>


Encoder* Encoder::instances[3] = {nullptr};

Encoder::Encoder(uint8_t pinA, uint8_t pinB)
  : _pinA(pinA), _pinB(pinB), _position(0) {
  for (uint8_t i = 0; i < 3; i++) {
    if (!instances[i]) {
      instances[i] = this;
      instanceIndex = i;
      break;
    }
  }
}

void Encoder::begin() {
  pinMode(_pinA, INPUT);
  pinMode(_pinB, INPUT);

  switch (instanceIndex) {
    case 0: attachInterrupt(digitalPinToInterrupt(_pinA), isrA_wrapper0, RISING); break;
    case 1: attachInterrupt(digitalPinToInterrupt(_pinA), isrA_wrapper1, RISING); break;
    case 2: attachInterrupt(digitalPinToInterrupt(_pinA), isrA_wrapper2, RISING); break;
  }
}

long Encoder::getPosition() {
  noInterrupts();
  long pos = _position;
  interrupts();
  return pos;
}

void Encoder::reset() {
  noInterrupts();
  _position = 0;
  interrupts();
}

void IRAM_ATTR Encoder::handleInterrupt() {
  int b = digitalRead(_pinB);
  _position += (b == HIGH) ? 1 : -1;
}

// static wrappers
void IRAM_ATTR Encoder::isrA_wrapper0() { if (instances[0]) instances[0]->handleInterrupt(); }
void IRAM_ATTR Encoder::isrA_wrapper1() { if (instances[1]) instances[1]->handleInterrupt(); }
void IRAM_ATTR Encoder::isrA_wrapper2() { if (instances[2]) instances[2]->handleInterrupt(); }