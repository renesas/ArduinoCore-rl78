/*
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

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
 
  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}

#include "Wire.h"

/* Initialize Class Variables *************************************************/

/* Constructors ***************************************************************/

/**********************************************************************************************************************
 * Function Name: TwoWire::TwoWire
 * Description  : Constructor
 * Arguments    : ch - I2C channel no.
 * Return Value : -
 *********************************************************************************************************************/
TwoWire::TwoWire(uint8_t ch) :
  iica   (ch)
, channel(ch)
{
  initializeProps();
}

/* Private Methods ************************************************************/

/**********************************************************************************************************************
 * Function Name: TwoWire::initializeProps
 * Description  : Initialize instance properties.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::initializeProps(void) {
  rxBufferIndex = 0;
  rxBufferLength = 0;

  txAddress = 0;
  txBufferIndex = 0;
  txBufferLength = 0;

  transmitting = 0;

  clearWriteError();
}

/* Public Methods *************************************************************/

/**********************************************************************************************************************
 * Function Name: TwoWire::begin
 * Description  : Initiate the Wire library and join the I2C bus as master.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::begin(void)
{
  initializeProps();

  iica.Master_Create();
}

#if !defined(I2C_SLAVE_MODE_UNSUPPORTED)
/**********************************************************************************************************************
 * Function Name: TwoWire::begin
 * Description  : Initiate the Wire library and join the I2C bus as slave.
 * Arguments    : address - the 7-bit slave address
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::begin(uint8_t address)
{
  #warning TODO: Slave: twi_setAddress(address);
  #warning TODO: Slave: twi_attachSlaveTxEvent(onRequestService);
  #warning TODO: Slave: twi_attachSlaveRxEvent(onReceiveService);
  begin();
}

/**********************************************************************************************************************
 * Function Name: TwoWire::begin
 * Description  : Initiate the Wire library and join the I2C bus as slave.
 * Arguments    : address - the 7-bit slave address
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::begin(int address)
{
  begin((uint8_t)address);
}
#endif  /* !defined(I2C_SLAVE_MODE_UNSUPPORTED) */

/**********************************************************************************************************************
 * Function Name: TwoWire::setClock
 * Description  : Modify the clock frequency for I2C communication.
 * Arguments    : clock - desired communication clock
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::setClock(uint32_t clock)
{
  iica.Master_SetClock(clock);
}

/**********************************************************************************************************************
 * Function Name: TwoWire::requestFrom
 * Description  : Request bytes from a slave device (for master mode).
 * Arguments    : address  - the 7-bit address of the device to request bytes from
 *              : quantity - the number of bytes to request
 *              : sendStop - flag to send a stop message after the request or not
 * Return Value : the number of bytes returned from the slave device
 *********************************************************************************************************************/
uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
  /* clamp to buffer length */
  if(quantity > BUFFER_LENGTH){
    quantity = BUFFER_LENGTH;
  }

  /* perform blocking read into buffer */
  uint8_t read = iica.Master_Receive(address, rxBuffer, quantity, static_cast<bool>(sendStop));

  /* set rx buffer iterator vars */
  rxBufferIndex = 0;
  rxBufferLength = read;

  return read;
}

/**********************************************************************************************************************
 * Function Name: TwoWire::requestFrom
 * Description  : Request bytes from a slave device (for master mode).
 * Arguments    : address  - the 7-bit address of the device to request bytes from
 *              : quantity - the number of bytes to request
 * Return Value : the number of bytes returned from the slave device
 *********************************************************************************************************************/
uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

/**********************************************************************************************************************
 * Function Name: TwoWire::requestFrom
 * Description  : Request bytes from a slave device (for master mode).
 * Arguments    : address  - the 7-bit address of the device to request bytes from
 *              : quantity - the number of bytes to request
 * Return Value : the number of bytes returned from the slave device
 *********************************************************************************************************************/
uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

/**********************************************************************************************************************
 * Function Name: TwoWire::requestFrom
 * Description  : Request bytes from a slave device (for master mode).
 * Arguments    : address  - the 7-bit address of the device to request bytes from
 *              : quantity - the number of bytes to request
 *              : sendStop - flag to send a stop message after the request or not
 * Return Value : the number of bytes returned from the slave device
 *********************************************************************************************************************/
uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

/**********************************************************************************************************************
 * Function Name: TwoWire::beginTransmission
 * Description  : Begin a transmission to the I2C slave device with the given address.
 * Arguments    : address - the 7-bit address of the device to transmit to
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::beginTransmission(uint8_t address)
{
  /* indicate that we are transmitting */
  transmitting = 1;

  /* set address of targeted slave */
  txAddress = address;

  /* reset tx buffer iterator vars */
  txBufferIndex = 0;
  txBufferLength = 0;

  clearWriteError();
}

/**********************************************************************************************************************
 * Function Name: TwoWire::beginTransmission
 * Description  : Begin a transmission to the I2C slave device with the given address.
 * Arguments    : address - the 7-bit address of the device to transmit to
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::beginTransmission(int address)
{
  beginTransmission((uint8_t)address);
}

/*
 * Originally, 'endTransmission' was an f(void) function.
 * It has been modified to take one parameter indicating
 * whether or not a STOP should be performed on the bus.
 * Calling endTransmission(false) allows a sketch to 
 * perform a repeated start. 
 * 
 * WARNING: Nothing in the library keeps track of whether
 * the bus tenure has been properly ended with a STOP. It
 * is very possible to leave the bus in a hung state if
 * no call to endTransmission(true) is made. Some I2C
 * devices will behave oddly if they do not see a STOP.
 */
/**********************************************************************************************************************
 * Function Name: TwoWire::endTransmission
 * Description  : Ends a transmission to a slave device that was begun by beginTransmission() and
 *              : transmits the bytes that were queued by write().
 * Arguments    : sendStop - flag to send a stop message after the request or not
 * Return Value : error status
 *              :   0 : success
 *              :   1 : data too long to fit in transmit buffer
 *              :   2 : received NACK on transmit of address
 *              :   3 : received NACK on transmit of data
 *              :   4 : other error
 *********************************************************************************************************************/
uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  /* transmit buffer (blocking) */

  int8_t ret;

  if (getWriteError() != 0) {
    ret = 1;
  } else {
    ret = iica.Master_Send(txAddress, txBuffer, txBufferLength, static_cast<bool>(sendStop));
  }

  /* reset tx buffer iterator vars */
  txBufferIndex = 0;
  txBufferLength = 0;

  /* indicate that we are done transmitting */
  transmitting = 0;

  clearWriteError();

  return ret;
}

/*
 * This provides backwards compatibility with the original
 * definition, and expected behaviour, of endTransmission
 */
/**********************************************************************************************************************
 * Function Name: TwoWire::endTransmission
 * Description  : Ends a transmission to a slave device that was begun by beginTransmission() and
 *              : transmits the bytes that were queued by write().
 * Arguments    : -
 * Return Value : error status
 *              :   0 : success
 *              :   1 : data too long to fit in transmit buffer
 *              :   2 : received NACK on transmit of address
 *              :   3 : received NACK on transmit of data
 *              :   4 : other error
 *********************************************************************************************************************/
uint8_t TwoWire::endTransmission(void)
{
  return endTransmission(true);
}

/*
 * must be called in:
 * slave tx event callback
 * or after beginTransmission(address)
 */
/**********************************************************************************************************************
 * Function Name: TwoWire::write
 * Description  : Writes data from a slave device in response to a request from a master, or
 *              : queues bytes for transmission from a master to slave device.
 * Arguments    : data - a value to send as a single byte
 * Return Value : the number of bytes written
 *********************************************************************************************************************/
size_t TwoWire::write(uint8_t data)
{
  if(transmitting){
    /*
     * in master transmitter mode
     * don't bother if buffer is full
     */
    if(txBufferLength >= BUFFER_LENGTH){
      setWriteError();
      return 0;
    }

    /* put byte in tx buffer */
    txBuffer[txBufferIndex] = data;
    ++txBufferIndex;

    /* update amount in buffer */
    txBufferLength = txBufferIndex;
  }else{
    /*
     * in slave send mode
     * reply to master
     */
#if defined(I2C_SLAVE_MODE_UNSUPPORTED)
    return 0;
#else /* defined(I2C_SLAVE_MODE_UNSUPPORTED) */
    #warning TODO: Slave: twi_transmit(&data, 1);
#endif /* defined(I2C_SLAVE_MODE_UNSUPPORTED) */
  }
  return 1;
}

/*
 * must be called in:
 * slave tx event callback
 * or after beginTransmission(address)
 */
/**********************************************************************************************************************
 * Function Name: TwoWire::write
 * Description  : Writes data from a slave device in response to a request from a master, or
 *              : queues bytes for transmission from a master to slave device.
 * Arguments    : data   - an array of data to send as bytes
 *              : length - the number of bytes to transmit
 * Return Value : the number of bytes written
 *********************************************************************************************************************/
size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
  if(transmitting){
    /* in master transmitter mode */
    for(size_t i = 0; i < quantity; ++i){
      write(data[i]);
    }
  }else{
    /*
     * in slave send mode
     * reply to master
     */
#if defined(I2C_SLAVE_MODE_UNSUPPORTED)
    return 0;
#else /* defined(I2C_SLAVE_MODE_UNSUPPORTED) */
    #warning TODO: Slave: twi_transmit(data, quantity);
#endif /* defined(I2C_SLAVE_MODE_UNSUPPORTED) */
  }
  return quantity;
}

/*
 * must be called in:
 * slave rx event callback
 * or after requestFrom(address, numBytes)
 */
/**********************************************************************************************************************
 * Function Name: TwoWire::available
 * Description  : Returns the number of bytes available for retrieval with read().
 * Arguments    : -
 * Return Value : the number of bytes available for reading
 *********************************************************************************************************************/
int TwoWire::available(void)
{
  return rxBufferLength - rxBufferIndex;
}

/*
 * must be called in:
 * slave rx event callback
 * or after requestFrom(address, numBytes)
 */
/**********************************************************************************************************************
 * Function Name: TwoWire::read
 * Description  : Reads a byte that
 *              : was transmitted from a slave device to a master after a call to requestFrom() or
 *              : was transmitted from a master       to a slave.
 * Arguments    : -
 * Return Value : the next byte received; or -1 if no data is available
 *********************************************************************************************************************/
int TwoWire::read(void)
{
  int value = -1;

  /* get each successive byte on each call */
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
    ++rxBufferIndex;
  }

  return value;
}

/*
 * must be called in:
 * slave rx event callback
 * or after requestFrom(address, numBytes)
 */
/**********************************************************************************************************************
 * Function Name: TwoWire::peek
 * Description  : Reads a bytes from the communicating device without advancing to the next one.
 * Arguments    : -
 * Return Value : the next byte received; or -1 if no data is available
 *********************************************************************************************************************/
int TwoWire::peek(void)
{
  int value = -1;
  
  if(rxBufferIndex < rxBufferLength){
    value = rxBuffer[rxBufferIndex];
  }

  return value;
}

/**********************************************************************************************************************
 * Function Name: TwoWire::flush
 * Description  : Clears the buffer once all outgoing characters have been sent.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::flush(void)
{
  /* XXX: to be implemented. */
}

/* behind the scenes function that is called when data is received */
/**********************************************************************************************************************
 * Function Name: TwoWire::onReceiveService
 * Description  : Handler to be called when a slave device receives a transmission from a master.
 * Arguments    : inBytes  - the data            read from the master
 *              : numBytes - the number of bytes read from the master
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::onReceiveService(uint8_t* inBytes, int numBytes)
{
  /* don't bother if user hasn't registered a callback */
  if(!user_onReceive){
    return;
  }

  /*
   * don't bother if rx buffer is in use by a master requestFrom() op
   * i know this drops data, but it allows for slight stupidity
   * meaning, they may not have read all the master requestFrom() data yet
   */
  if(rxBufferIndex < rxBufferLength){
    return;
  }

  /*
   * copy twi rx buffer into local read buffer
   * this enables new reads to happen in parallel
   */
  for(uint8_t i = 0; i < numBytes; ++i){
    rxBuffer[i] = inBytes[i];
  }

  /* set rx iterator vars */
  rxBufferIndex = 0;
  rxBufferLength = numBytes;

  /* alert user program */
  user_onReceive(numBytes);
}

/* behind the scenes function that is called when data is requested */
/**********************************************************************************************************************
 * Function Name: TwoWire::onRequestService
 * Description  : Handler to be called when a master requests data from this slave device.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::onRequestService(void)
{
  /* don't bother if user hasn't registered a callback */
  if(!user_onRequest){
    return;
  }

  /*
   * reset tx buffer iterator vars
   * !!! this will kill any pending pre-master sendTo() activity
   */
  txBufferIndex = 0;
  txBufferLength = 0;

  /* alert user program */
  user_onRequest();
  clearWriteError();
}

/* sets function called on slave write */
/**********************************************************************************************************************
 * Function Name: TwoWire::onReceive
 * Description  : Registers a function to be called when a slave device receives a transmission from a master.
 * Arguments    : function - the function to be called when the slave receives data
 *              :   Arguments   : numBytes - the number of bytes read from the master
 *              :   Return Value: -
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::onReceive( void (*function)(int) )
{
  user_onReceive = function;
}

/* sets function called on slave read */
/**********************************************************************************************************************
 * Function Name: TwoWire::onRequest
 * Description  : Registers a function to be called when a master requests data from this slave device.
 * Arguments    : function - the function to be called when the slave is requested data
 *              :   Arguments   : -
 *              :   Return Value: -
 * Return Value : -
 *********************************************************************************************************************/
void TwoWire::onRequest( void (*function)(void) )
{
  user_onRequest = function;
}

/**********************************************************************************************************************
 * Function Name: TwoWire::availableForWrite
 * Description  : Get the number of available transmit buffer space for write.
 * Arguments    : -
 * Return Value : size of transmit buffer free space
 *********************************************************************************************************************/
int TwoWire::availableForWrite()
{
  return sizeof(txBuffer) / sizeof(txBuffer[0]) - txBufferLength;
}

/* Preinstantiate Objects *****************************************************/

#if     defined(IIC_CHANNEL0) && IIC_CHANNEL0 == 0
TwoWire Wire = TwoWire(0);
#endif  /* defined(IIC_CHANNEL0) && IIC_CHANNEL0 == 0 */

#if     defined(IIC_CHANNEL1) && IIC_CHANNEL1 == 1
TwoWire Wire1 = TwoWire(1);
#endif  /* defined(IIC_CHANNEL1) && IIC_CHANNEL1 == 1 */
