#ifndef SPI_CSI_h
#define SPI_CSI_h

#include "r_cg_macrodriver.h"

#include "Arduino.h"

extern "C" {

#include "r_cg_sau.h"

}

class CSI_Impl {
public:
  CSI_Impl(uint8_t ch);

  void      Master_Create         (void) const;
  void      Master_Start          (void) const;
  void      Master_Stop           (void) const;
  MD_STATUS Master_Send_Receive   (uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf) const;
  void      Master_Create_UserInit(void) const;
  uint8_t   Master_GetBitOrder    (void) const;
  void      Master_SetBitOrder    (uint8_t bitOrder) const;
  void      Master_SetDataMode    (uint8_t dataMode) const;
  void      Master_SetClockDivider(uint16_t clockDiv) const;
  void      Master_SetClock       (uint32_t clock) const;

  inline volatile uint16_t getMasterTxCount   (void) const { return master_tx_count    == nullptr ? 0U      : *master_tx_count   ; }
  inline volatile uint16_t getMasterStatusFlag(void) const { return master_status_flag == nullptr ? 0x0000U : *master_status_flag; };

private:
  void      (*Master_Create_         )(void);
  void      (*Master_Start_          )(void);
  void      (*Master_Stop_           )(void);
  MD_STATUS (*Master_Send_Receive_   )(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf);
  void      (*Master_Create_UserInit_)(void);
  void      (*Master_ClearStatus_    )(void);
  uint8_t   (*Master_GetBitOrder_    )(void);
  void      (*Master_SetBitOrder_    )(uint8_t bitOrder);
  void      (*Master_SetDataMode_    )(uint8_t dataMode);
  void      (*Master_SetClockDivider_)(uint16_t clockDiv);
  void      (*Master_SetClock_       )(uint32_t clock);

  const volatile uint16_t *master_tx_count;
  const volatile uint16_t *master_status_flag;

  const unsigned long STATUS_WAIT_TIMEOUT   = 1000;
  const unsigned long STATUS_WAIT_INTERVAL  = 10;

  void      Master_ClearStatus    (void) const;
  uint16_t  Master_StatusFlagWait (void) const;
};

#endif
