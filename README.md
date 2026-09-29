# ESP32 ADC PWM LED Dimmer

An introductory embedded project that uses a potentiometer to control LED brightness. The sketch reads an analog input, converts its ADC value to an 8-bit PWM duty value, and prints the input and output values to the Serial Monitor.

## Hardware and wiring

- ESP32-family development board with an ADC-capable input and LEDC support.
- Potentiometer, breadboard, and jumper wires.
- External LED with a suitable series current-limiting resistor, or a compatible onboard LED.
- USB cable for power, programming, and serial output.

The exact board model and component values have not been recorded. Verify the board pinout before wiring: GPIO 1 is not an ADC input on the original ESP32, although some other ESP32 variants support it. Select an ADC-capable pin for your board if necessary. An onboard LED may use another GPIO or different polarity.

| Connection | Sketch setting |
| --- | --- |
| Potentiometer outer terminals | 3.3 V and GND |
| Potentiometer wiper | GPIO 1 (`PIN_ANALOG_IN`) |
| External LED anode through series resistor | GPIO 2 (`PIN_LED`) |
| External LED cathode | GND |

Keep the analog input within the board's permitted range; do not connect it to 5 V. Use a common ground. The wiring above assumes an active-high external LED.

## How it works

1. `analogRead()` obtains the potentiometer reading. The sketch assumes a 12-bit range of 0-4095.
2. Integer division by 16 maps that range to 0-255 for 8-bit PWM.
3. LEDC generates PWM at 1,000 Hz on the LED pin. Turning the potentiometer changes its duty cycle and average LED brightness.
4. The Serial Monitor receives an ADC value, estimated voltage, and PWM value every 200 ms at 115200 baud.

The displayed voltage is calculated as `adcVal / 4095.0 * 3.3`. It is an estimate, not a calibrated measurement. ADC attenuation, chip variation, and nonlinearity affect the actual relationship between input voltage and raw counts.

## Open and run

1. Install the Espressif ESP32 board package in Arduino IDE. This sketch uses the Arduino-ESP32 3.x-style `ledcAttach(pin, frequency, resolution)` and pin-based `ledcWrite(pin, duty)` API.
2. Open `_First_simple_Project/_First_simple_Project.ino` from the parent sketchbook folder, or open `_First_simple_Project.ino` if already inside this repository. Keep the sketch file in a folder with the same name.
3. Select your exact board and USB port, and confirm its ADC and LED GPIO assignments.
4. Verify and upload the sketch.
5. Open Serial Monitor at 115200 baud and turn the potentiometer.

Expected behavior: the LED becomes brighter as the raw ADC value rises. At the assumed endpoints, ADC 0 maps to PWM 0, and ADC 4095 maps to PWM 255. Actual endpoints depend on the board and ADC configuration.

## Learning outcomes

This project demonstrates analog-to-digital conversion, resolution scaling from 12 bits to 8 bits, PWM frequency versus duty cycle, serial debugging, and the difference between an estimated voltage and a calibrated measurement.

## Validation and limitations

The published formatting and comments preserve the original sketch's operations, pins, timing, and formulas. The ADC-to-PWM arithmetic was reviewed. Compilation and operation on a physical board have not been independently verified for this repository; the exact board configuration is still required. The sketch does not check the return values of LEDC setup or writes.

## References

- [Espressif Arduino-ESP32 ADC API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/adc.html)
- [Espressif Arduino-ESP32 LEDC API](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/ledc.html)
