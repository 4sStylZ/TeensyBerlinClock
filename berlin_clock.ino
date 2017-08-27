#include <Metro.h> // Include the Metro library

void setup()   {

    // Start the serial monitoring for debug purpose.
    Serial.begin(38400);

    // Blink some flash just for see if the device is started even
    // if the serial monitoring is not set-up.
    startWithSomeFlash();

    // initialize the digitals pin as an outputs
    initLedsOutput();
}

// the loop() method runs over and over again,
void loop()
{
    powerAllLights(true);
    delay(1000);
    powerAllLights(false);
    delay(1000);
    Serial.println("Iteration…");
}

void startWithSomeFlash() {

    Serial.println("Start Berlin clock");

    // 3 flash with the Teensy led.
    pinMode(13, OUTPUT);
    for (int i = 0; i <= 3; i++) {
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
    }
}

void initLedsOutput() {
    for (int i = 0; i <= 9; i++) {
        pinMode(i, OUTPUT);
    }
}

/**
 * Blink off or blink on all the leds.
 *
 * @param boolean power HIGH or LOW
 *
 * @return void
 */
void powerAllLights(boolean power) {
    int i;
    for (i = 0; i <= 9; i++) {
        if (power == true) {
            digitalWrite(i, HIGH);
        } else {
            digitalWrite(i, LOW);
        }

    }
}
