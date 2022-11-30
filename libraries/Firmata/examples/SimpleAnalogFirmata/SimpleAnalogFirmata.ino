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

/* Supports as many analog inputs and analog PWM outputs as possible.
 *
 * This example code is in the public domain.
 */
#include <Firmata.h>

byte analogPin = A0;
int pin = 0;


void analogWriteCallback(byte pin, int value)
{
  if ((pin) == 5 || (pin) == 6 || (pin) == 10) {
    pinMode(pin, OUTPUT);
    analogWrite(pin, value);

  }
}

void setup()
{
  Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.begin(57600);
}

void loop()
{
  while (Firmata.available()) {
    Firmata.processInput();
  }
  // do one analogRead per loop, so if PC is sending a lot of
  // analog write messages, we will only delay 1 analogRead
  Firmata.sendAnalog(pin, analogRead(analogPin));
  analogPin = analogPin + 1;
  pin = pin + 1;
  if (analogPin >= TOTAL_ANALOG_PINS+A0)
  {
	analogPin = A0;
  	pin = 0;
  }
}
