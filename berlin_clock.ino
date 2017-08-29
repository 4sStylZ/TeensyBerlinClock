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

    // Initialize the digitals pin as an outputs
    initLedsOutput();

    // Blink some flash just for see if the device is started even
    // if the serial monitoring is not set-up.
    startWithSomeFlash();

    // set time to Saturday 8:29:00am Jan 1 2011.
    setTime(8,29,0,1,1,11);

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

        displaySecond();
        displayHours();
        // displayHour();
        // displayMinuteFirstRow();

    }
}

void displayHours() {
    for (int i = 1; i <= 4; i++) {
        if (hour()%5) {
            digitalWrite(i, HIGH);
        } else {
            digitalWrite(i, LOW);
        }
    }
}

void displayHour() {
    for (int i = 1; i <= 4; i++) {
        if (hour()%5) {
            digitalWrite(i + 4, HIGH);
        } else {
            digitalWrite(i + 4, LOW);
        }
    }
}



void displaySecond() {
    if (second()%2) {
        digitalWrite(0, HIGH);
    } else {
        digitalWrite(0, LOW);
    }
}

void displayMinuteFirstRow() {
    for (int i = 1; i <= 4; i++) {
        if (minute()%5) {
            digitalWrite(i + 1, HIGH);
        } else {
            digitalWrite(i + 1, LOW);
        }
    }
}

/**
 * Print some flash when the device start.
 *
 * @return {[type]} [description]
 */
void startWithSomeFlash() {

    Serial.println("Start Berlin clock");
    for (int i = 0; i <= 3; i++) {
        powerAllLights(true);
        delay(100);
        powerAllLights(false);
        delay(100);
    }
}

/**
 * Initialize all the leds output.
 *
 * @return {void}
 */
void initLedsOutput() {
    for (int i = 0; i <= 24; i++) {
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
    for (i = 1; i <= 24; i++) {
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
    }
    Serial.print(digits);
}
