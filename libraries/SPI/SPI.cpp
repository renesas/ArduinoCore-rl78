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

#include "pins_arduino.h"
#include "r_cg_macrodriver.h"
#include "r_cg_sau.h"
#include "SPI.h"

#if defined(CSI_CHANNEL0) && CSI_CHANNEL0 == 0
SPIClass SPI(0);
#endif
#if defined(CSI_CHANNEL1) && CSI_CHANNEL1 == 1
SPIClass SPI1(1);
#endif
#if defined(CSI_CHANNEL2) && CSI_CHANNEL2 == 2
SPIClass SPI2(2);
#endif
#if defined(CSI_CHANNEL3) && CSI_CHANNEL3 == 3
SPIClass SPI(3);
#endif
#if defined(CSI_CHANNEL4) && CSI_CHANNEL4 == 4
SPIClass SPI4(4);
#endif
#if defined(CSI_CHANNEL5) && CSI_CHANNEL5 == 5
SPIClass SPI5(5);
#endif
#if defined(CSI_CHANNEL6) && CSI_CHANNEL6 == 6
SPIClass SPI6(6);
#endif
#if defined(CSI_CHANNEL7) && CSI_CHANNEL7 == 7
SPIClass SPI7(7);
#endif

// Constructors ////////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: SPIClass::SPIClass
 * Description  : Constructor
 * Arguments    : ch - SPI channel no.
 * Return Value : -
 *********************************************************************************************************************/
SPIClass::SPIClass(uint8_t ch) :
  csi    (ch)
, channel(ch)
{
  initializeProps();
};

// Public Methods //////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: SPIClass::begin
 * Description  : Initiate the SPI bus.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void SPIClass::begin(void) {
  csi.Master_Create();
  csi.Master_Start();
}

/**********************************************************************************************************************
 * Function Name: SPIClass::end
 * Description  : Disable the SPI bus.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void SPIClass::end() {
  csi.Master_Stop();
}

// Private Methods /////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: SPIClass::initializeProps
 * Description  : Initialize instance properties.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void SPIClass::initializeProps(void) {
  initialized       = 0;
  interruptMode     = 0;
  interruptMask     = 0;
  interruptSave     = 0;
#ifdef SPI_TRANSACTION_MISMATCH_LED
  inTransactionFlag = 0;
#endif
}
