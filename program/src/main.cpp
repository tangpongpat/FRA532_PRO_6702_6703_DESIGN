#include <Arduino.h>

// Pin definitions
const int COIL_PIN_1 = 25;
const int COIL_PIN_2 = 26;

// PWM settings
const int PWM_CH1      = 0;
const int PWM_CH2      = 1;
const int PWM_FREQ     = 2000;  // 20 kHz (above audible)
const int PWM_RES      = 8;      // 8-bit
const int DUTY_TARGET  = 255;    // 100% duty = full brake

// -----------------------------------------------------------------------------
// คลาสควบคุมคอยล์ 1 ตัว (ไม่มี delay, แค่ hold)
class CoilController {
public:
  CoilController(int pin, int ch)
    : _pin(pin), _ch(ch) {}

  void init() {
    ledcSetup(_ch, PWM_FREQ, PWM_RES);
    ledcAttachPin(_pin, _ch);
  }

  // เข้าเต็มทันที และค้างไว้
  void hold() {
    ledcWrite(_ch, DUTY_TARGET);
  }

private:
  int _pin, _ch;
};

CoilController coil1(COIL_PIN_1, PWM_CH1);
CoilController coil2(COIL_PIN_2, PWM_CH2);

void setup() {
  coil1.init();
  coil2.init();

  // ดูดค้างไว้เลย (ไม่มี delay ใน loop)
  coil1.hold();
  coil2.hold();
}

void loop() {
  // ปล่อยว่างไว้ ไม่ต้องสั่งอะไรอีก
}
