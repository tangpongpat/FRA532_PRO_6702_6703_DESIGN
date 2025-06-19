  #include <Arduino.h>

const int COIL_PIN    = 25;
const int PWM_CHANNEL = 0;
const int PWM_FREQ    = 1000;
const int PWM_RES     = 8;

void setup() {
  Serial.begin(115200);
  // configure PWM
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(COIL_PIN, PWM_CHANNEL);
}

void loop() {
  // 1) Enable full-on PWM
  ledcWrite(PWM_CHANNEL, 255);
  Serial.println("PWM ON");
  delay(5000);

  // 2) Disable by duty=0
  ledcWrite(PWM_CHANNEL, 0);
  Serial.println("PWM OFF (duty=0)");
  delay(5000);

  // 3) Re-enable PWM
  ledcWrite(PWM_CHANNEL, 255);
  Serial.println("PWM ON again");
  delay(5000);

  // 4) Detach PWM completely
  ledcDetachPin(COIL_PIN);
  Serial.println("PWM Detached");
  delay(5000);

  // 5) Re-attach and continue
  ledcAttachPin(COIL_PIN, PWM_CHANNEL);
  ledcWrite(PWM_CHANNEL, 255);
  Serial.println("PWM Re-Attached and ON");
  delay(5000);
}
