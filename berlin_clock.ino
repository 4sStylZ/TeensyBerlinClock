// Metro is used for check the time each second.
// This is the best way for not working with delay().
#include <Metro.h>

// Time is the library wich provide some method like setTime and
// others getters like hour() / minutes().
#include <TimeLib.h>

// Time alarm call your method at a special time based on the Time
// library.
#include <TimeAlarms.h>

Metro serialMetro = Metro(1000);
time_t currentTime;
bool isAlarmOn = false;
AlarmId id;

/**
 * Auto invoked setup function.
 *
 * @return {void}
 */
void setup()   {

    // Start the serial monitoring for debug purpose.
    Serial.begin(38400);
    Serial.println("Start Berlin clock");

    // Initialize the digitals pin as an outputs
    initLedsOutput();

    // Blink some flash just for see if the device is started even
    // if the serial monitoring is not set-up.
    partyHard(3);

    initializeTime();

    // Declare the alarm each day except weekend days.
    setAlarm( 9, 30, 00);
    setAlarm(12, 30, 00);
}

/**
 * Method wich initialise the time and date.
 *
 * @return {void}
 */
void initializeTime() {

    // Initialize time.
    setTime(
        11, // Hours   (HH)
        04, // Minutes (MM)
        00, // Seconds (SS)
        31, // Days    (DD)
         8, // Months  (MM)
        17  // Years   (YY)
    );
}

/**
 * Display flash at 9:30 each day except saturday and sunday.
 *
 * @parameters int hours, minutes, seconds.
 *
 * @return {void}
 */
void setAlarm(int hours, int minutes, int seconds) {
    Alarm.alarmRepeat(dowMonday    , hours , minutes, seconds, displayAlarm);
    Alarm.alarmRepeat(dowTuesday   , hours , minutes, seconds, displayAlarm);
    Alarm.alarmRepeat(dowWednesday , hours , minutes, seconds, displayAlarm);
    Alarm.alarmRepeat(dowThursday  , hours , minutes, seconds, displayAlarm);
    Alarm.alarmRepeat(dowFriday    , hours , minutes, seconds, displayAlarm);
    Serial.println("Daily alarm setted");
}

/**
 * Display the  alarm.
 *
 * (Method coded because alarmRepeat doesn’t accept method with
 * parameters).
 *
 * @return {void}
 */
void displayAlarm() {
    Serial.println("Daily setted");
    isAlarmOn = true;
    partyHard(20);
    isAlarmOn = false;
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

/**
 * Tic, tac, tic… Et caetera !
 *
 * @return {void}
 */
void ticTac() {

    // Check if one second is passed.
    if (serialMetro.check() == 1) {

        // Display the time in serie port.
        displaySerialTime();

        // Trigger the alarm for checking if there is one.
        Alarm.delay(1000);

        // If the alarm is off then display time on leds.
        if (!isAlarmOn) {

            // Blink the led of each zone.
            displaySecond();
            displayHours();
            displayHour();
            displayMinutes();
            displayMinute();
        }
    }
}

/**
 * Display the time in serial port.
 *
 * @return {void}
 */
void displaySerialTime() {
    Serial.print(day());
    Serial.print("/");
    Serial.print(month());
    Serial.print("/");
    Serial.print(year());
    Serial.print(" ");
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.println();
}

/**
 * Display the first hour row.
 *
 * @return {[type]} [description]
 */
void displayHours() {
    for (int i = 1; i <= 4; i++) {
        if (i <= floor(hour() / 5)) {
            digitalWrite(i, HIGH);
        } else {
            digitalWrite(i, LOW);
        }
    }
}

/**
 * Display the second hour row for hour unit.
 *
 * @return {void}
 */
void displayHour() {
    for (int i = 1; i <= 4; i++) {
        if (i <= hour() % 5) {
            digitalWrite(i + 4, HIGH);
        } else {
            digitalWrite(i + 4, LOW);
        }
    }
}

/**
 * Display the first minute row.
 *
 * @return {void}
 */
void displayMinutes() {
    for (int i = 1; i <= 12; i++) {
        if (i <= floor(minute() / 5)) {
            digitalWrite(i + 8, HIGH);
        } else {
            digitalWrite(i + 8, LOW);
        }
    }
}

/**
 * Display the second minute row.
 *
 * @return {void}
 */
void displayMinute() {
    for (int i = 1; i <= 4; i++) {
        if (i <= minute() % 5) {
            digitalWrite(i + 19, HIGH);
        } else {
            digitalWrite(i + 19, LOW);
        }
    }
}

/**
 * Blink the second led at one time / second.
 *
 * @return {void}
 */
void displaySecond() {
    if (second()%2) {
        digitalWrite(0, HIGH);
    } else {
        digitalWrite(0, LOW);
    }
}

/**
 * Print some flash.
 *
 * @param {int} flashNumber
 *
 * @return {void}]
 */
void partyHard(int flashNumber) {

    for (int i = 0; i <= flashNumber; i++) {
        powerAllLights(true);
        delay(100);
        powerAllLights(false);
        delay(100);
    }
}

/**
 * Initialize all the leds in output mode.
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
 * @param boolean power, true for HIGH or false for LOW
 *
 * @return void
 */
void powerAllLights(boolean power) {
    int i;
    for (i = 0; i <= 24; i++) {
        if (power == true) {
            digitalWrite(i, HIGH);
        } else {
            digitalWrite(i, LOW);
        }
    }
}

/**
 * View-helper who print two digits even if the parameter have only
 * one caracter…
 *
 * @param {int} int digits wich are minutes or second
 *
 * @return {void}
 */
void printDigits(int digits) {
    Serial.print(":");
    if (digits < 10) {
        Serial.print('0');
    }
    Serial.print(digits);
}
