#include <Metro.h> // Include the Metro library
#include <TimeLib.h> // Include Time library.

Metro serialMetro = Metro(1000);
time_t currentTime;

/**
 * Auto invoked setup function.
 *
 * @return {void}
 */
void setup()   {

    // Start the serial monitoring for debug purpose.
    Serial.begin(38400);

    // Blink some flash just for see if the device is started even
    // if the serial monitoring is not set-up.
    startWithSomeFlash();

    setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011

    // initialize the digitals pin as an outputs
    initLedsOutput();
}

/**
 * the loop() method runs over and over again
 *
 * @return {void}
 */
void loop()
{
    ticTac();
}

void ticTac() {

    // Check if one second is passed.
    if (serialMetro.check() == 1) {
        Serial.print(hour());
        printDigits(minute());
        printDigits(second());
        Serial.println();
        Serial.print("Iteration…");
        Serial.print("\n");
    }
}

/**
 * Print some flash when the device start.
 *
 * @return {[type]} [description]
 */
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

/**
 * Initialize all the leds output.
 *
 * @return {void}
 */
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
    for (i = 1; i <= 9; i++) {
        if (power == true) {
            digitalWrite(i, HIGH);
        } else {
            digitalWrite(i, LOW);
        }

    }
}

/**
 * Prints two digits even if the parameter have only one caractere…
 *
 * @param {[type]} int digits [description]
 *
 * @return {[type]} [description]
 */
void printDigits(int digits) {
    Serial.print(":");
    if (digits < 10) {
        Serial.print('0');
        Serial.print(digits);
    }
}
