#include "Wire_IICA.h"

#include "r_cg_macrodriver.h"

extern "C" {

#if     defined(IIC_CHANNEL0) && IIC_CHANNEL0 == 0
  #include "Config_IICA0.h"
  extern volatile uint16_t g_iica0_rx_len;
  extern volatile uint16_t g_iica0_rx_cnt;
  extern volatile uint16_t g_iica0_tx_cnt;
  extern volatile uint8_t  g_iica0_master_status_flag;
#endif  /* defined(IIC_CHANNEL0) && IIC_CHANNEL0 == 0 */

#if     defined(IIC_CHANNEL1) && IIC_CHANNEL1 == 1
  #include "Config_IICA1.h"
  extern volatile uint16_t g_iica1_rx_len;
  extern volatile uint16_t g_iica1_rx_cnt;
  extern volatile uint16_t g_iica1_tx_cnt;
  extern volatile uint8_t  g_iica1_master_status_flag;
#endif  /* defined(IIC_CHANNEL1) && IIC_CHANNEL1 == 1 */

}

/* Constructors ***************************************************************/

/**********************************************************************************************************************
 * Function Name: IICA_Impl::IICA_Impl
 * Description  : Constructor
 * Arguments    : ch - I2C channel no.
 * Return Value : -
 *********************************************************************************************************************/
IICA_Impl::IICA_Impl(uint8_t ch) {
  switch (ch) {

#if     defined(IIC_CHANNEL1) && IIC_CHANNEL1 == 1
  case 1:
    Master_Create_          = R_Config_IICA1_Create;
    Master_Stop_            = R_Config_IICA1_Stop;
    Master_StopCondition_   = R_Config_IICA1_StopCondition;
    Master_Create_UserInit_ = R_Config_IICA1_Create_UserInit;
    Master_Send_            = R_Config_IICA1_Master_Send;
    Master_Receive_         = R_Config_IICA1_Master_Receive;
    Master_SetClock_        = R_Config_IICA1_Master_SetClock;
    rx_len                  = &g_iica1_rx_len;
    rx_cnt                  = &g_iica1_rx_cnt;
    tx_cnt                  = &g_iica1_tx_cnt;
    master_status_flag      = &g_iica1_master_status_flag;
    break;
#endif  /* defined(IIC_CHANNEL1) && IIC_CHANNEL1 == 1 */

#if     defined(IIC_CHANNEL0) && IIC_CHANNEL0 == 0
  case 0:
    Master_Create_          = R_Config_IICA0_Create;
    Master_Stop_            = R_Config_IICA0_Stop;
    Master_StopCondition_   = R_Config_IICA0_StopCondition;
    Master_Create_UserInit_ = R_Config_IICA0_Create_UserInit;
    Master_Send_            = R_Config_IICA0_Master_Send;
    Master_Receive_         = R_Config_IICA0_Master_Receive;
    Master_SetClock_        = R_Config_IICA0_Master_SetClock;
    rx_len                  = &g_iica0_rx_len;
    rx_cnt                  = &g_iica0_rx_cnt;
    tx_cnt                  = &g_iica0_tx_cnt;
    master_status_flag      = &g_iica0_master_status_flag;
    break;
#endif  /* defined(IIC_CHANNEL0) && IIC_CHANNEL0 == 0 */

  default:
    Master_Create_          =
    Master_Stop_            =
    Master_StopCondition_   =
    Master_Create_UserInit_ = nullptr;
    Master_Send_            =
    Master_Receive_         = nullptr;
    Master_SetClock_        = nullptr;
    rx_len                  =
    rx_cnt                  =
    tx_cnt                  = nullptr;
    break;

  }
}

/* Private Methods ************************************************************/

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_StatusFlagWait
 * Description  : [Master] Wait for IICA interruption to know the operation exit status or error.
 * Arguments    : -
 * Return Value : status of the operation
 *              :   Upper 4 bits (0xF0U) is assigned to IICA status bits (e.g. operation completion)
 *              :   Lower 4 bits (0x0FU) is assigned to IICA errors (MD_STATUS)
 *********************************************************************************************************************/
MD_STATUS IICA_Impl::Master_StatusFlagWait(void) const {
  MD_STATUS ret = MD_OK;

  unsigned long wait = 0;
  while (true) {
    auto stat   = getMasterStatusFlag();
    if ((stat & 0x0FU) != 0x00U) {
      ret = stat;
      break;
    }

    if ((stat & _40_IICA_DATA_COMPLETE) != 0x00U) {
      ret = stat;
      break;
    }

    if (wait > STATUS_WAIT_INTERVAL) {
      ret = (stat & ~0x0FU) | MD_BUSY2;
      break;
    }

    /* XXX: Need Timer module enabled */
    delay(STATUS_WAIT_INTERVAL);
    wait += STATUS_WAIT_INTERVAL;
  }

  return ret;
}

/* Public Methods *************************************************************/

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_Create
 * Description  : [Master] Initialize the IICA module.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      IICA_Impl::Master_Create         (void) const {
  if (Master_Create_ != nullptr) {
     Master_Create_();
  }
}

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_Stop
 * Description  : [Master] Terminate the IICA module.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      IICA_Impl::Master_Stop           (void) const {
  if (Master_Stop_ != nullptr) {
     Master_Stop_();
  }
}

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_StopCondition
 * Description  : [Master] Send stop message.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      IICA_Impl::Master_StopCondition  (void) const {
#if     !defined(IGNORE_SEND_STOP_FLAG)
  if (Master_StopCondition_ != nullptr) {
     Master_StopCondition_();
  }
#endif  /* !defined(IGNORE_SEND_STOP_FLAG) */
}

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_Send
 * Description  : [Master] Transfer data to a slave device.
 * Arguments    : adr      - the 7-bit address of the device to transmit to
 *              : tx_buf   - transmit data buffer
 *              : tx_num   - the number of bytes to transmit
 *              : sendStop - flag to send a stop message after the request or not
 * Return Value : error status (converted for `Wire.endTransmission()`)
 *              :   0 : success
 *              :   1 : data too long to fit in transmit buffer
 *              :   2 : received NACK on transmit of address
 *              :   3 : received NACK on transmit of data
 *              :   4 : other error
 *********************************************************************************************************************/
uint8_t   IICA_Impl::Master_Send           (uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num, bool sendStop) const {
  uint8_t ret = 0;
  MD_STATUS ret_;
  MD_STATUS status = MD_OK;
  if (Master_Send_ == nullptr) {
    ret_ = MD_ERROR;
  } else {
    ret_ = Master_Send_((adr << 1) & ~0x01U, tx_buf, tx_num, 0xFFU);
    if (ret_ == MD_OK) {
      status = Master_StatusFlagWait();
    }
  }

  if (sendStop) {
    Master_StopCondition();
  }

  if (ret_ == MD_OK) {
    switch (status & 0x0FU) {
    case MD_OK:   ret = 0; break;
    case MD_NACK: ret = (status & _80_IICA_ADDRESS_COMPLETE) == 0x00U ? 2 : 3; break;
    default:      ret = 4; break;
    }
  } else {
    ret = 4;
  }

  return ret;
}

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_Receive
 * Description  : [Master] Request and receive data from a slave device.
 * Arguments    : adr      - the 7-bit address of the device to request bytes from
 *              : rx_buf   - receive data buffer
 *              : rx_num   - the number of bytes to request
 *              : sendStop - flag to send a stop message after the request or not
 * Return Value : the number of bytes returned from the slave device;
 *              : or 0 if some error happens
 *********************************************************************************************************************/
uint8_t   IICA_Impl::Master_Receive        (uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num, bool sendStop) const {
  MD_STATUS ret;
  MD_STATUS status = MD_OK;
  if (Master_Receive_ == nullptr) {
    ret = MD_ERROR;
  } else {
    ret = Master_Receive_((adr << 1) | 0x01U, rx_buf, rx_num, 0xFFU);
    if (ret == MD_OK) {
      status = Master_StatusFlagWait();
    }
  }

  if (sendStop) {
    Master_StopCondition();
  }

  return ret == MD_OK && (status & 0x0FU) == 0x00U ? getRxLen() : 0;
}

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_Create_UserInit
 * Description  : [Master] Call the user code for the IICA initialization.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      IICA_Impl::Master_Create_UserInit(void) const {
  if (Master_Create_UserInit_ != nullptr) {
     Master_Create_UserInit_();
  }
}

/**********************************************************************************************************************
 * Function Name: IICA_Impl::Master_SetClock
 * Description  : [Master] Set I2C clock frequency.
 * Arguments    : clock - clock frequency to set
 * Return Value : -
 *********************************************************************************************************************/
void      IICA_Impl::Master_SetClock       (uint32_t clock) {
  if (Master_SetClock_ != nullptr) {
     Master_SetClock_(clock);
  }
}
