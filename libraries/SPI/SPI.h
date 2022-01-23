/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * Modified 28 February 2013 by masahiko.nagata.cj@renesas.com
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <avr/pgmspace.h>

#include "SPI_CSI.h"

// SPI_HAS_TRANSACTION means SPI has beginTransaction(), endTransaction(),
// usingInterrupt(), and SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_NOTUSINGINTERRUPT means that SPI has notUsingInterrupt() method
#define SPI_HAS_NOTUSINGINTERRUPT 1

// SPI_ATOMIC_VERSION means that SPI has atomicity fixes and what version.
// This way when there is a bug fix you can check this define to alert users
// of your code if it uses better version of this library.
// This also implies everything that SPI_HAS_TRANSACTION as documented above is
// available too.
#define SPI_ATOMIC_VERSION 1

// Uncomment this line to add detection of mismatched begin/end transactions.
// A mismatch occurs if other libraries fail to use SPI.endTransaction() for
// each SPI.beginTransaction().  Connect an LED to this pin.  The LED will turn
// on if any mismatch is ever detected.
//#define SPI_TRANSACTION_MISMATCH_LED 5

class SPISettings {
public:
  SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) :
    clock   (clock)
  , bitOrder(bitOrder)
  , dataMode(dataMode)
  { }

  SPISettings() : SPISettings(4000000, MSBFIRST, SPI_MODE0) { }

private:
  uint32_t clock;
  uint8_t  bitOrder;
  uint8_t  dataMode;

  friend class SPIClass;
};


class SPIClass {
public:
  SPIClass(uint8_t ch = 3);

  void Set_SPIPort(uint8_t sck_pin,uint8_t si_pin,uint8_t so_pin);

    // Initialize the SPI library
    void begin();

    // If SPI is used from within an interrupt, this function registers
    // that interrupt with the SPI library, so beginTransaction() can
    // prevent conflicts.  The input interruptNumber is the number used
    // with attachInterrupt.  If SPI is used from a different interrupt
    // (eg, a timer), interruptNumber should be 255.
    void usingInterrupt(uint8_t interruptNumber);
    // And this does the opposite.
    void notUsingInterrupt(uint8_t interruptNumber);
    // Note: the usingInterrupt and notUsingInterrupt functions should
    // not to be called from ISR context or inside a transaction.
    // For details see:
    // https://github.com/arduino/Arduino/pull/2381
    // https://github.com/arduino/Arduino/pull/2449

    // Before using SPI.transfer() or asserting chip select pins,
    // this function is used to gain exclusive access to the SPI bus
    // and configure the correct settings.
    void beginTransaction(SPISettings settings) {
      if (interruptMode > 0) {
        noInterrupts();
      }

      #ifdef SPI_TRANSACTION_MISMATCH_LED
      if (inTransactionFlag) {
        pinMode(SPI_TRANSACTION_MISMATCH_LED, OUTPUT);
        digitalWrite(SPI_TRANSACTION_MISMATCH_LED, HIGH);
      }
      inTransactionFlag = 1;
      #endif

      csi.Master_SetBitOrder(settings.bitOrder);
      csi.Master_SetDataMode(settings.dataMode);
      csi.Master_SetClock(settings.clock);
    }

  // Write to the SPI bus (MOSI pin) and also receive (MISO pin)
  uint8_t transfer(uint8_t data) {
    memset(rx_buf, 0x00, sizeof(rx_buf));
    memset(tx_buf, 0x00, sizeof(tx_buf));
    tx_buf[0] = data;

    /* XXX: It returns error status, though, there's no way to tell the error. */
    MD_STATUS ret = csi.Master_Send_Receive(tx_buf, sizeof(data), rx_buf);

    return rx_buf[0];
  }

  uint16_t transfer16(uint16_t data) {
    memset(rx_buf, 0x00, sizeof(rx_buf));
    memset(tx_buf, 0x00, sizeof(tx_buf));

    const uint8_t bitOrder = csi.Master_GetBitOrder();
    if (bitOrder == LSBFIRST) {
      tx_buf[0] = (data >> 0) & 0xFF;
      tx_buf[1] = (data >> 8) & 0xFF;
    } else {
      tx_buf[1] = (data >> 0) & 0xFF;
      tx_buf[0] = (data >> 8) & 0xFF;
    }

    /* XXX: It returns error status, though, there's no way to tell the error. */
    MD_STATUS ret = csi.Master_Send_Receive(tx_buf, sizeof(data), rx_buf);

    return bitOrder == LSBFIRST

            ? (static_cast<uint16_t>(rx_buf[0]) << 0)
            | (static_cast<uint16_t>(rx_buf[1]) << 8)

            : (static_cast<uint16_t>(rx_buf[1]) << 0)
            | (static_cast<uint16_t>(rx_buf[0]) << 8);
  }

  void transfer(void *buf, size_t count) {
    MD_STATUS ret;

    while (count > 0) {
      size_t sendSize = min(sizeof(tx_buf), count);

      memset(rx_buf, 0x00, sizeof(rx_buf));
      memset(tx_buf, 0x00, sizeof(tx_buf));

      /* XXX: Instead of unfound `memcpy()`, copy the buffer by hand. */
      for (size_t i = 0; i < sendSize; i++) {
        tx_buf[i] = reinterpret_cast<uint8_t *>(buf)[i];
      }

      /* XXX: It returns error status, though, there's no way to tell the error. */
      ret = csi.Master_Send_Receive(tx_buf, sendSize, rx_buf);

      /* XXX: Instead of unfound `memcpy()`, copy the buffer by hand. */
      for (size_t i = 0; i < sendSize; i++) {
        reinterpret_cast<uint8_t *>(buf)[i] = rx_buf[i];
      }

      count -= sendSize;
      buf    = reinterpret_cast<uint8_t *>(buf) + sendSize;
    }
  }

    // After performing a group of transfers and releasing the chip select
    // signal, this function allows others to access the SPI bus
    void endTransaction(void) {
      #ifdef SPI_TRANSACTION_MISMATCH_LED
      if (!inTransactionFlag) {
        pinMode(SPI_TRANSACTION_MISMATCH_LED, OUTPUT);
        digitalWrite(SPI_TRANSACTION_MISMATCH_LED, HIGH);
      }
      inTransactionFlag = 0;
      #endif

      if (interruptMode > 0) {
        noInterrupts();
        if (!interruptSave) {
          interrupts();
        }
      }
    }

    // Disable the SPI bus
    void end();

  // This function is deprecated.  New applications should use
  // beginTransaction() to configure SPI settings.
  inline void setBitOrder(uint8_t bitOrder) {
    csi.Master_SetBitOrder(bitOrder);
  }

  // This function is deprecated.  New applications should use
  // beginTransaction() to configure SPI settings.
  inline void setDataMode(uint8_t dataMode) {
    csi.Master_SetDataMode(dataMode);
  }

  // This function is deprecated.  New applications should use
  // beginTransaction() to configure SPI settings.
  // The frequency divider can only be set to the following values.
  // SPI_CLOCK_DIV{ 2, 4, 8, 16, 32, 64, 128 } 
  inline void setClockDivider(uint16_t clockDiv) {
    csi.Master_SetClockDivider(clockDiv);
  }

            // These undocumented functions should not be used.  SPI.transfer()
      // polls the hardware flag which is automatically cleared as the
      // AVR responds to SPI's interrupt

#ifndef __RL78__
inline static void attachInterrupt() {SPCR |= _BV(SPIE);}
inline static void detachInterrupt() {SPCR &= ~_BV(SPIE);}
#endif

/*
 * XXX:
 * Dummy definition.
 * Called from `main.cpp`, though,
 * SPI channel setting is already done in the constructor.
 */
inline void set_channel(uint8_t ch) { }

private:
uint8_t channel;

CSI_Impl csi;

static const size_t BUFSIZE = 32;

uint8_t tx_buf[BUFSIZE];
uint8_t rx_buf[BUFSIZE];

uint8_t initialized;
uint8_t interruptMode; // 0=none, 1=mask, 2=global
uint8_t interruptMask;// which interrupts to mask
uint8_t interruptSave;// temp storage, to restore state

#ifdef SPI_TRANSACTION_MISMATCH_LED
uint8_t inTransactionFlag;
#endif

void initializeProps(void);
};

#if defined(CSI_CHANNEL0) && CSI_CHANNEL0 == 0
extern SPIClass SPI;
#endif
#if defined(CSI_CHANNEL1) && CSI_CHANNEL1 == 1
extern SPIClass SPI1;
#endif
#if defined(CSI_CHANNEL2) && CSI_CHANNEL2 == 2
extern SPIClass SPI2;
#endif
#if defined(CSI_CHANNEL3) && CSI_CHANNEL3 == 3
extern SPIClass SPI;
#endif
#if defined(CSI_CHANNEL4) && CSI_CHANNEL4 == 4
extern SPIClass SPI4;
#endif
#if defined(CSI_CHANNEL5) && CSI_CHANNEL5 == 5
extern SPIClass SPI5;
#endif
#if defined(CSI_CHANNEL6) && CSI_CHANNEL6 == 6
extern SPIClass SPI6;
#endif
#if defined(CSI_CHANNEL7) && CSI_CHANNEL7 == 7
extern SPIClass SPI7;
#endif

#endif
