/*
 Servo.cpp - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
 Copyright (c) 2009 Michael Margolis.  All right reserved.
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 1 March 2013 by masahiko.nagata.cj@renesas.com
 */

/* 
 
 A servo is activated by creating an instance of the Servo class passing the desired pin to the attach() method.
 The servos are pulsed in the background using the value most recently written using the write() method
 
 Note that analogWrite of PWM on pins associated with the timer are disabled when the first servo is attached.
 Timers are seized as needed in groups of 12 servos - 24 servos use two timers, 48 servos will use four.
 
 The methods are:
 
 Servo - Class for manipulating servo motors connected to Arduino pins.
 
 attach(pin )  - Attaches a servo motor to an i/o pin.
 attach(pin, min, max  ) - Attaches to a pin setting min and max values in microseconds
 default min is 544, max is 2400  
 
 write()     - Sets the servo angle in degrees.  (invalid angle that is valid as pulse in microseconds is treated as microseconds)
 writeMicroseconds() - Sets the servo pulse width in microseconds 
 read()      - Gets the last written servo pulse width as an angle between 0 and 180. 
 readMicroseconds()   - Gets the last written servo pulse width in microseconds. (was read_us() in first release)
 attached()  - Returns true if there is a servo attached. 
 detach()    - Stops an attached servos from pulsing its i/o pin. 
 
*/

#include "Arduino.h"
#include "Servo.h"

extern "C" {
	#include "servo_smc.h"
}


#define usToTicks(_us)    (( clockCyclesPerMicrosecond()* _us) / 32)     // converts microseconds to tick (assumes prescale of 8)  // 12 Aug 2009
#define ticksToUs(_ticks) (( (unsigned long)_ticks * 32)/ clockCyclesPerMicrosecond() ) // converts from ticks back to microseconds


#define TRIM_DURATION       2                               // compensation ticks to trim adjust for digitalWrite delays // 12 August 2009

//#define NBR_TIMERS        (MAX_SERVOS / SERVOS_PER_TIMER)

static servo_t servos[MAX_SERVOS];                          // static array of servo structures
static volatile int8_t Channel[_Nbr_16timers ];             // counter for the servo being pulsed for each timer (or -1 if refresh interval)


uint8_t ServoCount = 0;                              // the total number of attached servos
uint16_t totalTicks;
uint16_t g_servo_refresh_interval = 20000;


// convenience macros
#define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER)) // returns the timer controlling this servo
#define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)       // returns the index of the servo on this timer
#define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)     // macro to access servo index by timer and channel
#define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])            // macro to access servo class by timer and channel

#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)  // minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)  // maximum value in uS for this servo

/************ static functions common to all instances ***********************/

static boolean isTimerActive(timer16_Sequence_t timer)
{
  // returns true if any servo is active on this timer
    for(uint8_t channel=0; channel < SERVOS_PER_TIMER; channel++){
        if(SERVO(timer,channel).Pin.isActive == true)
            return true;
    }
    return false;
}

/****************** end of static functions ******************************/

Servo::Servo()
{
    if( ServoCount < MAX_SERVOS){
        this->servoIndex = ServoCount++;                    // assign a servo index to this instance
        servos[this->servoIndex].ticks = usToTicks(DEFAULT_PULSE_WIDTH);   // store default values  - 12 Aug 2009
    }
    else
        this->servoIndex = INVALID_SERVO ;  // too many servos
}

uint8_t Servo::attach(int pin)
{
    return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t Servo::attach(int pin, int min, int max)
{
	uint16_t minmax;
	uint16_t maxmin;
	uint16_t maxmax;
	uint16_t minmin;
    if(this->servoIndex < MAX_SERVOS ){
        servos[this->servoIndex].Pin.nbr = pin;
        // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128 
//        this->min = (MIN_PULSE_WIDTH - min)/4;         // resolution of min/max is 4 uS
//        this->max = (MAX_PULSE_WIDTH - max)/4;
        minmax = min(max,min);
        maxmin = max(min, max);
        maxmax = min(MAX_PULSE_WIDTH,maxmin);
        minmin = max(MIN_PULSE_WIDTH,minmax);

        this->min = minmin;
        this->max = maxmax;
        // initialize the timer if it has not already been initialized 
        timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
        if(isTimerActive(timer) == false)
//            initISR(timer);
        	/* Timer Open */
        servos[this->servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
    } 
    return this->servoIndex;
}

void Servo::detach()
{
    servos[this->servoIndex].Pin.isActive = false;
    timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
    if(isTimerActive(timer) == false) {
//        finISR(timer);
    	/* Timer Close */
    }
}

void Servo::write(int value)
{  
    if(value < MIN_PULSE_WIDTH)  
    {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
        if(value < 0) value = 0;
        if(value > 180) value = 180;
//        value = map(value, 0, 180, SERVO_MIN(), SERVO_MAX());
        value = map(value, 0, 180, this->min, this->max);
    }
    this->writeMicroseconds(value);
}

void Servo::writeMicroseconds(int value)
{
	int current_value = this->readMicroseconds();
	int val;
	if (value <this->min) {
		value = this->min;
	}
	if (value > this->max) {
		value = this->max;
	}
	servos[this->servoIndex].ticks = value;
	if (current_value == value) {
		return;
	} else if (current_value < value) {
		for (val = current_value;val <= value ; val +=20) {
			smc_ServoWrite(servos[this->servoIndex].Pin.nbr,val);
		}
		if (val > value) {
			smc_ServoWrite(servos[this->servoIndex].Pin.nbr,value);
		}
	} else {
		for (val = current_value;val >= value ; val -=20) {
			smc_ServoWrite(servos[this->servoIndex].Pin.nbr,val);
		}
		if (val < value) {
			smc_ServoWrite(servos[this->servoIndex].Pin.nbr,value);
		}
	}

	delayMicroseconds(20000-value);
}

int Servo::read() // return the value as degrees
{
//    return map( this->readMicroseconds()+1, SERVO_MIN(), SERVO_MAX(), 0, 180);
    return map( this->readMicroseconds()+1, this->min, this->max, 0, 180);
}

int Servo::readMicroseconds()
{
    unsigned int pulsewidth;
    if( this->servoIndex != INVALID_SERVO )
        pulsewidth = ticksToUs(servos[this->servoIndex].ticks)  + TRIM_DURATION;   // 12 aug 2009
    else
        pulsewidth  = 0;
    return pulsewidth;
}

bool Servo::attached()
{
    return servos[this->servoIndex].Pin.isActive;
}
