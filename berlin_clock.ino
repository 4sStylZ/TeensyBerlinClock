#include <Metro.h> // Include the Metro library

void setup()   {

    Serial.begin(38400);
    startWithSomeFlash();

    // initialize the digitals pin as an outputs
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
}


// the loop() method runs over and over again,
void loop()
{
    allHigh();
    delay(1000);
    allLow();
    delay(1000);
    Serial.println("Iteration…");
}

/**
 * Blink off or blink on all the leds.
 *
 * @return {[type]} [description]
 */
void allHigh() {
    int i;
    for (i = 0; i <= 9; i++) {
       digitalWrite(i, HIGH);
    }
}


void allLow() {
    int i;
    for (i = 0; i <= 9; i++) {
        digitalWrite(i, LOW);
    }
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
