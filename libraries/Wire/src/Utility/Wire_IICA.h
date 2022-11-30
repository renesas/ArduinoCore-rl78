#ifndef TwoWire_IICA_h
#define TwoWire_IICA_h

extern "C" {
#include "r_cg_macrodriver.h"
#include "r_cg_iica.h"
}

#include "Arduino.h"

/*
 * XXX:
 * On RL78, stop bit is always to be sent in normal path
 * no matter which is specified for `sendStop`.
 *
 * In `r_Config_IICA{0,1}_callback_master_sendend()`
 * in `rl78g23/smc_gen/Config_IICA{0,1}/Config_IICA{0,1}_user.c`,
 * SPT0 = 1U is set.
 */
#define IGNORE_SEND_STOP_FLAG

class IICA_Impl {
public:
  IICA_Impl(uint8_t ch);

  void      Master_Create         (void) const;
  void      Master_Stop           (void) const;
  void      Master_StopCondition  (void) const;
  uint8_t   Master_Send           (uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num, bool sendStop) const;
  uint8_t   Master_Receive        (uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num, bool sendStop) const;
  void      Master_Create_UserInit(void) const;
  void      Master_SetClock       (uint32_t clock);

  inline volatile uint16_t getRxLen           (void) const { return rx_len             == nullptr ? 0 : *rx_len            ; }
  inline volatile uint16_t getRxCnt           (void) const { return rx_cnt             == nullptr ? 0 : *rx_cnt            ; }
  inline volatile uint16_t getTxCnt           (void) const { return tx_cnt             == nullptr ? 0 : *tx_cnt            ; }
  inline volatile uint8_t  getMasterStatusFlag(void) const { return master_status_flag == nullptr ? 0 : *master_status_flag; }

private:
  void      (*Master_Create_         )(void);
  void      (*Master_Stop_           )(void);
  void      (*Master_StopCondition_  )(void);
  MD_STATUS (*Master_Send_           )(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num, uint8_t wait);
  MD_STATUS (*Master_Receive_        )(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num, uint8_t wait);
  void      (*Master_Create_UserInit_)(void);
  void      (*Master_SetClock_       )(uint32_t clock);

  const volatile uint16_t *rx_len;
  const volatile uint16_t *rx_cnt;
  const volatile uint16_t *tx_cnt;
  const volatile uint8_t  *master_status_flag;

  const unsigned long STATUS_WAIT_TIMEOUT   = 1000;
  const unsigned long STATUS_WAIT_INTERVAL  = 10;

  MD_STATUS Master_StatusFlagWait(void) const;
};

#endif /* TwoWire_IICA_h */
