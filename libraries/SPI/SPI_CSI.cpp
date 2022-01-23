#include "SPI_CSI.h"

#include "r_cg_macrodriver.h"

extern "C" {

#if defined(CSI_CHANNEL3) && CSI_CHANNEL3 == 3
  #include "Config_CSI11.h"
  extern volatile uint16_t g_csi11_tx_count;
  extern volatile uint16_t g_csi11_status_flag;
#endif

}

#define DELAY_MS(x)    delay(x)

// Constructors ////////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: CSI_Impl::CSI_Impl
 * Description  : Constructor
 * Arguments    : ch - SPI channel no.
 * Return Value : -
 *********************************************************************************************************************/
CSI_Impl::CSI_Impl(uint8_t ch) {
  switch (ch) {

#if     defined(CSI_CHANNEL3) && CSI_CHANNEL3 == 3
  case 3:
    Master_Create_          = R_Config_CSI11_Create;
    Master_Start_           = R_Config_CSI11_Start;
    Master_Stop_            = R_Config_CSI11_Stop;
    Master_Create_UserInit_ = R_Config_CSI11_Create_UserInit;
    Master_ClearStatus_     = R_Config_CSI11_ClearStatus;
    Master_Send_Receive_    = R_Config_CSI11_Send_Receive;
    Master_SetBitOrder_     = R_Config_CSI11_SetBitOrder;
    Master_SetDataMode_     = R_Config_CSI11_SetDataMode;
    Master_SetClockDivider_ = R_Config_CSI11_SetClockDivider;
    Master_SetClock_        = R_Config_CSI11_SetClock;
    Master_GetBitOrder_     = R_Config_CSI11_GetBitOrder;
    master_tx_count         = &g_csi11_tx_count;
    master_status_flag      = &g_csi11_status_flag;
    break;
#endif /* defined(CSI_CHANNEL3) && CSI_CHANNEL3 == 3 */

  default:
    Master_Create_          =
    Master_Start_           =
    Master_Stop_            =
    Master_Create_UserInit_ =
    Master_ClearStatus_     = nullptr;
    Master_Send_Receive_    = nullptr;
    Master_SetBitOrder_     =
    Master_SetDataMode_     = nullptr;
    Master_SetClockDivider_ = nullptr;
    Master_SetClock_        = nullptr;
    Master_GetBitOrder_     = nullptr;
    master_tx_count         =
    master_status_flag      = nullptr;
    break;

  }
}

// Private Methods /////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_ClearStatus
 * Description  : Clear the CSI module's status.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_ClearStatus(void) const {
  if (Master_ClearStatus_ != nullptr) {
    Master_ClearStatus_();
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_StatusFlagWait
 * Description  : Wait for CSI interruption to know the operation exit status or error.
 * Arguments    : -
 * Return Value : status of the operation
 *              :   Upper 8 bits (0xFF00U) is assigned to CSI status bits (e.g. operation completion)
 *              :   Lower 8 bits (0x00FFU) is assigned to CSI errors
 *********************************************************************************************************************/
uint16_t  CSI_Impl::Master_StatusFlagWait(void) const {
  uint16_t ret = 0x0000U;

  unsigned long wait = 0;
  while (true) {
    auto stat   = getMasterStatusFlag();
    if ((stat & _00FF_SPI_STATUS_ERROR_MASK) != 0x0000U) {
      ret = stat;
      break;
    }

    if (
        (stat & _8000_SPI_STATUS_SENDEND   ) != 0x0000U
    &&  (stat & _4000_SPI_STATUS_RECEIVEEND) != 0x0000U
    ) {
      ret = stat;
      break;
    }

    if (wait > STATUS_WAIT_INTERVAL) {
      ret = (stat                           & ~_00FF_SPI_STATUS_ERROR_MASK)
          | (_0080_SPI_STATUS_ERROR_TIMEOUT &  _00FF_SPI_STATUS_ERROR_MASK);
      break;
    }

    /* XXX: Need Timer module enabled */
    DELAY_MS(STATUS_WAIT_INTERVAL);
    wait += STATUS_WAIT_INTERVAL;
  }

  return ret;
}

// Public Methods //////////////////////////////////////////////////////////////

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_Create
 * Description  : Initialize the CSI module.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_Create         (void) const {
  if (Master_Create_ != nullptr) {
    Master_Create_();
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_Start
 * Description  : Start the CSI module operation.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_Start          (void) const {
  if (Master_Start_ != nullptr) {
    Master_Start_();
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_Stop
 * Description  : Stop the CSI module operation.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_Stop           (void) const {
  if (Master_Stop_ != nullptr) {
    Master_Stop_();
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_Send_Receive
 * Description  : send and receive CSI data.
 * Arguments    : tx_buf - transfer buffer pointer
 *                tx_num - buffer size
 *                rx_buf - receive buffer pointer
 * Return Value : error status
 *              :   MD_OK
 *              :   MD_ARGERROR
 *              :   MD_ERROR
 *********************************************************************************************************************/
MD_STATUS CSI_Impl::Master_Send_Receive   (uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf) const {
  MD_STATUS ret;
  uint16_t  status = 0x0000U;

  if (Master_Send_Receive_ == nullptr) {
    ret = MD_ERROR;
  } else {
    Master_ClearStatus();
    ret = Master_Send_Receive_(tx_buf, tx_num, rx_buf);
    if (ret == MD_OK) {
      status = Master_StatusFlagWait();
      if ((status & _00FF_SPI_STATUS_ERROR_MASK) != 0x0000u) {
        ret = (status & _0080_SPI_STATUS_ERROR_TIMEOUT) != 0x0000u ? MD_BUSY2
            : (status & _0001_SPI_STATUS_ERROR_OVERRUN) != 0x0000u ? MD_OVERRUN
            :                                                        MD_ERROR;
      }
    }
  }

  return ret;
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_Create_UserInit
 * Description  : Call the user code for the CSI initialization.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_Create_UserInit(void) const {
  if (Master_Create_UserInit_ != nullptr) {
    Master_Create_UserInit_();
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_GetBitOrder
 * Description  : Get the order of the bits shifted out of and into the SPI bus.
 * Arguments    : -
 * Return Value : Current bit order setting
 *              :   LSBFIRST
 *              :   MSBFIRST
 *********************************************************************************************************************/
uint8_t   CSI_Impl::Master_GetBitOrder    (void) const {
  if (Master_GetBitOrder_ != nullptr) {
    return Master_GetBitOrder_();
  } else {
    /* XXX: If SMC function is not set, return device endian by default. */
    const uint16_t TESTVAL = 0x1234U;
    return reinterpret_cast<const uint8_t *>(&TESTVAL)[0] == 0x12U ? MSBFIRST : LSBFIRST;
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_SetBitOrder
 * Description  : Set the order of the bits shifted out of and into the SPI bus.
 * Arguments    : bitOrder - Bit order setting
 *              :   LSBFIRST
 *              :   MSBFIRST
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_SetBitOrder    (uint8_t bitOrder) const {
  if (Master_SetBitOrder_ != nullptr) {
    Master_SetBitOrder_(bitOrder);
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_SetDataMode
 * Description  : Set the SPI data mode (clock polarity and phase).
 * Arguments    : dataMode - SPI data mode
 *              :   SPI_MODE0
 *              :   SPI_MODE1
 *              :   SPI_MODE2
 *              :   SPI_MODE3
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_SetDataMode    (uint8_t dataMode) const {
  if (Master_SetDataMode_ != nullptr) {
    Master_SetDataMode_(dataMode);
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_SetClockDivider
 * Description  : Set the SPI clock divider relative to the system clock.
 * Arguments    : clockDiv - SPI clock divider
 *              :   SPI_CLOCK_DIV2
 *              :   SPI_CLOCK_DIV4
 *              :   SPI_CLOCK_DIV8
 *              :   SPI_CLOCK_DIV16
 *              :   SPI_CLOCK_DIV32
 *              :   SPI_CLOCK_DIV64
 *              :   SPI_CLOCK_DIV128
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_SetClockDivider(uint16_t clockDiv) const {
  if (Master_SetClockDivider_ != nullptr) {
    Master_SetClockDivider_(clockDiv);
  }
}

/**********************************************************************************************************************
 * Function Name: CSI_Impl::Master_SetClock
 * Description  : Set the SPI maximum speed of communication.
 * Arguments    : clock - SPI clock speed
 * Return Value : -
 *********************************************************************************************************************/
void      CSI_Impl::Master_SetClock       (uint32_t clock) const {
  if (Master_SetClock_ != nullptr) {
    Master_SetClock_(clock);
  }
}
