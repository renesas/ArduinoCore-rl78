#include "r_cg_macrodriver.h"
#include <string.h>
#include "r_stdint.h"
#include "r_mtl_com.h"
#include "r_mmc.h"

/************************************************************************************
Macro definitions
************************************************************************************/
#define MMC_INS_CHAT   20      /* counter value of chattering detection  */

static uint16_t        gDetChatCnt[MMC_SLOT_NUM];  /* Counter of chattering detection    */
static uint16_t        gDetSts_Old[MMC_SLOT_NUM];  /* Previous status of detection     */

/******************************************************************************
* Declaration  : int16_t R_card_insertion_chk(gSlotNo)
* Function Name: R_card_insertion_chk
* Description  : Check whether a card is inserted.
               : After insertion confirmation, sample program initialize it for MMC
* Argument     : uint8_t gSlotNo: Slot No.
* Return Value : Library return value
******************************************************************************/
int16_t R_card_insertion_chk(uint8_t slot_num)
{
    uint8_t    DetSts;                           /* Detection status        */
    int16_t    api_ret;

    /* Check MMC insertion. */
    api_ret = R_mmc_Chk_Detect(slot_num, &DetSts); /* Get status of MMC insertion.     */
    if (api_ret < MMC_OK)
    {
        return api_ret;
    }
    if (DetSts != gDetSts_Old[slot_num])         /* Status Changed!        */
    {
        if (DetSts == MMC_TRUE)                  /* Removal -> Insertion       */
        {
            gDetChatCnt[slot_num]--;             /* Chattering counter decrement     */
            if (gDetChatCnt[slot_num] == 0)      /* counter =0          */
            {
                gDetChatCnt[slot_num] = MMC_INS_CHAT;
                gDetSts_Old[slot_num] = DetSts;
                /* Initialize MMC slot. */
            }
        }
        else
        {
            /* Insertion -> Removal       */
            /* Do not care chattering. */
            gDetChatCnt[slot_num] = MMC_INS_CHAT;
            gDetSts_Old[slot_num] = DetSts;
        }
    }
    else
    {
        /* No change         */
        gDetChatCnt[slot_num] = MMC_INS_CHAT;
    }
    return gDetSts_Old[slot_num];
}

/******************************************************************************
* Declaration  : void R_init_card_detect_chat(void)
* Function Name: R_init_card_detect_chat
* Description  : clear of the chattering counter
* Argument     : None
* Return Value : None
******************************************************************************/
void R_init_card_detect_chat(void)               /* Initial process                 */
{
    uint8_t    slot_num;                         /* Slot number         */

    for (slot_num = MMC_SLOT0; slot_num < MMC_SLOT_NUM; slot_num++)
    {
        gDetChatCnt[slot_num] = MMC_INS_CHAT;    /* Reset the counter of chattering detection. */
        gDetSts_Old[slot_num] = MMC_FALSE;       /* Set the previous status of detection to "removal". */
    }
}

