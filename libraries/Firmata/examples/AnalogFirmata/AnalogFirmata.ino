/*
 * Firmata is a generic protocol for communicating with microcontrollers
 * from software on a host computer. It is intended to work with
 * any host computer software package.
 *
 * To download a host software package, please click on the following link
 * to open the list of Firmata client libraries in your default browser.
 *
 * https://github.com/firmata/arduino#firmata-client-libraries
 */

/* This firmware supports as many analog ports as possible, all analog inputs,
 * three PWM outputs support.
 *
 * This example code is in the public domain.
 */
#include <Firmata.h>

/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/

/* analog inputs */
int analogInputsToReport = 0; // bitwise array to store pin reporting
int analogPin = 0; // counter for reading analog pins
/* timer variables */
unsigned long currentMillis;     // store the current value from millis()
unsigned long previousMillis;    // for comparison with currentMillis


/*==============================================================================
 * FUNCTIONS
 *============================================================================*/

void analogWriteCallback(byte pin, int value)
{
  switch (pin) {
    case 5:
    case 6:
    case 10: // PWM pins
      analogWrite(pin, value);
      break;
  }
}
// -----------------------------------------------------------------------------
// sets bits in a bit array (int) to toggle the reporting of the analogIns
void reportAnalogCallback(byte pin, int value)
{
  if (value == 0) {
    analogInputsToReport = analogInputsToReport & ~ (1 << pin);
  }
  else { // everything but 0 enables reporting of that pin
    analogInputsToReport = analogInputsToReport | (1 << pin);
  }
  // TODO: save status to EEPROM here, if changed
}

/*==============================================================================
 * SETUP()
 *============================================================================*/
void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.attach(REPORT_ANALOG, reportAnalogCallback);

  Firmata.begin(57600);
}

/*==============================================================================
 * LOOP()
 *============================================================================*/
void loop()
{
  while (Firmata.available())
    Firmata.processInput();
  currentMillis = millis();
  if (currentMillis - previousMillis > 20) {
    previousMillis += 20;                   // run this every 20ms
    for (int i = 0, analogPin = A0; analogPin < TOTAL_ANALOG_PINS+A0; i++, analogPin++) {
      if ( analogInputsToReport & (1 << i) )
        Firmata.sendAnalog(i, analogRead(analogPin));
    }
  }
}

