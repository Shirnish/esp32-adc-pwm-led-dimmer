#define PIN_LED 2        // GPIO connected to the LED.
#define FRQ 1000         // PWM frequency in Hz.
#define PWM_BIT 8        // 8-bit duty value: 0-255.
#define PIN_ANALOG_IN 1  // ADC-capable GPIO connected to potentiometer wiper.

void setup() {
  Serial.begin(115200);
  ledcAttach(PIN_LED, FRQ, PWM_BIT);
}

void loop() {
  // Assumes the default 12-bit ADC reading: 0-4095.
  int adcVal = analogRead(PIN_ANALOG_IN);
  int pwmValue = adcVal / 16;  // Reduce 12-bit input to 8-bit output.

  // Approximate voltage assuming a 3.3 V full scale; not calibrated.
  double voltage = adcVal / 4095.0 * 3.3;

  ledcWrite(PIN_LED, pwmValue);
  Serial.printf("ADC: %d\tVoltage: %.2f V\tPWM: %d\n", adcVal, voltage, pwmValue);
  delay(200);
}
