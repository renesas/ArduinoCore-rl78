#include <Arduino.h>
#include <pintable.h>

#define pinTable_userled1 pinTable_16
#define pinTable_userled2 pinTable_15
#define pinTable_usersw   pinTable_26

const PinTableType pinTable_0 =
{
        DIGITAL_PIN_MASK_0, //uint8_t mask;
        DIGITAL_PIN_BIT_0, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_0,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_0,//uint8_t pmct;
        DIGITAL_PIN_PMCE_0,//uint8_t pmce;
        DIGITAL_PIN_CCDE_0,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_0, //uint8_t pdidis;
        DIGITAL_PIN_PM_0,//uint8_t pm;
        DIGITAL_PIN_PU_0,//uint8_t pu;
        DIGITAL_PIN_PIM_0,//uint8_t pim;
        DIGITAL_PIN_POM_0,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_0),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_1 =
{
        DIGITAL_PIN_MASK_1, //uint8_t mask;
        DIGITAL_PIN_BIT_1, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_1,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_1,//uint8_t pmct;
        DIGITAL_PIN_PMCE_1,//uint8_t pmce;
        DIGITAL_PIN_CCDE_1,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_1, //uint8_t pdidis;
        DIGITAL_PIN_PM_1,//uint8_t pm;
        DIGITAL_PIN_PU_1,//uint8_t pu;
        DIGITAL_PIN_PIM_1,//uint8_t pim;
        DIGITAL_PIN_POM_1,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_1),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};
const PinTableType pinTable_2 =
{
        DIGITAL_PIN_MASK_2, //uint8_t mask;
        DIGITAL_PIN_BIT_2, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_2,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_2,//uint8_t pmct;
        DIGITAL_PIN_PMCE_2,//uint8_t pmce;
        DIGITAL_PIN_CCDE_2,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_2, //uint8_t pdidis;
        DIGITAL_PIN_PM_2,//uint8_t pm;
        DIGITAL_PIN_PU_2,//uint8_t pu;
        DIGITAL_PIN_PIM_2,//uint8_t pim;
        DIGITAL_PIN_POM_2,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_2),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_3 =
{
        DIGITAL_PIN_MASK_3, //uint8_t mask;
        DIGITAL_PIN_BIT_3, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_3,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_3,//uint8_t pmct;
        DIGITAL_PIN_PMCE_3,//uint8_t pmce;
        DIGITAL_PIN_CCDE_3,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_3, //uint8_t pdidis;
        DIGITAL_PIN_PM_3,//uint8_t pm;
        DIGITAL_PIN_PU_3,//uint8_t pu;
        DIGITAL_PIN_PIM_3,//uint8_t pim;
        DIGITAL_PIN_POM_3,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_3),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_4 =
{
        DIGITAL_PIN_MASK_4, //uint8_t mask;
        DIGITAL_PIN_BIT_4, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_4,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_4,//uint8_t pmct;
        DIGITAL_PIN_PMCE_4,//uint8_t pmce;
        DIGITAL_PIN_CCDE_4,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_4, //uint8_t pdidis;
        DIGITAL_PIN_PM_4,//uint8_t pm;
        DIGITAL_PIN_PU_4,//uint8_t pu;
        DIGITAL_PIN_PIM_4,//uint8_t pim;
        DIGITAL_PIN_POM_4,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_4),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_5 =
{
        DIGITAL_PIN_MASK_5, //uint8_t mask;
        DIGITAL_PIN_BIT_5, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_5,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_5,//uint8_t pmct;
        DIGITAL_PIN_PMCE_5,//uint8_t pmce;
        DIGITAL_PIN_CCDE_5,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_5, //uint8_t pdidis;
        DIGITAL_PIN_PM_5,//uint8_t pm;
        DIGITAL_PIN_PU_5,//uint8_t pu;
        DIGITAL_PIN_PIM_5,//uint8_t pim;
        DIGITAL_PIN_POM_5,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_5),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_6 =
{
        DIGITAL_PIN_MASK_6, //uint8_t mask;
        DIGITAL_PIN_BIT_6, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_6,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_6,//uint8_t pmct;
        DIGITAL_PIN_PMCE_6,//uint8_t pmce;
        DIGITAL_PIN_CCDE_6,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_6, //uint8_t pdidis;
        DIGITAL_PIN_PM_6,//uint8_t pm;
        DIGITAL_PIN_PU_6,//uint8_t pu;
        DIGITAL_PIN_PIM_6,//uint8_t pim;
        DIGITAL_PIN_POM_6,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_6),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_7 =
{
        DIGITAL_PIN_MASK_7, //uint8_t mask;
        DIGITAL_PIN_BIT_7, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_7,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_7,//uint8_t pmct;
        DIGITAL_PIN_PMCE_7,//uint8_t pmce;
        DIGITAL_PIN_CCDE_7,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_7, //uint8_t pdidis;
        DIGITAL_PIN_PM_7,//uint8_t pm;
        DIGITAL_PIN_PU_7,//uint8_t pu;
        DIGITAL_PIN_PIM_7,//uint8_t pim;
        DIGITAL_PIN_POM_7,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_7),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_8 =
{
        DIGITAL_PIN_MASK_8, //uint8_t mask;
        DIGITAL_PIN_BIT_8, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_8,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_8,//uint8_t pmct;
        DIGITAL_PIN_PMCE_8,//uint8_t pmce;
        DIGITAL_PIN_CCDE_8,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_8, //uint8_t pdidis;
        DIGITAL_PIN_PM_8,//uint8_t pm;
        DIGITAL_PIN_PU_8,//uint8_t pu;
        DIGITAL_PIN_PIM_8,//uint8_t pim;
        DIGITAL_PIN_POM_8,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_8),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_9 =
{
        DIGITAL_PIN_MASK_9, //uint8_t mask;
        DIGITAL_PIN_BIT_9, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_9,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_9,//uint8_t pmct;
        DIGITAL_PIN_PMCE_9,//uint8_t pmce;
        DIGITAL_PIN_CCDE_9,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_9, //uint8_t pdidis;
        DIGITAL_PIN_PM_9,//uint8_t pm;
        DIGITAL_PIN_PU_9,//uint8_t pu;
        DIGITAL_PIN_PIM_9,//uint8_t pim;
        DIGITAL_PIN_POM_9,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_9),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_10 =
{
        DIGITAL_PIN_MASK_10, //uint8_t mask;
        DIGITAL_PIN_BIT_10, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_10,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_10,//uint8_t pmct;
        DIGITAL_PIN_PMCE_10,//uint8_t pmce;
        DIGITAL_PIN_CCDE_10,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_10, //uint8_t pdidis;
        DIGITAL_PIN_PM_10,//uint8_t pm;
        DIGITAL_PIN_PU_10,//uint8_t pu;
        DIGITAL_PIN_PIM_10,//uint8_t pim;
        DIGITAL_PIN_POM_10,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_10),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_11 =
{
        DIGITAL_PIN_MASK_11, //uint8_t mask;
        DIGITAL_PIN_BIT_11, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_11,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_11,//uint8_t pmct;
        DIGITAL_PIN_PMCE_11,//uint8_t pmce;
        DIGITAL_PIN_CCDE_11,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_11, //uint8_t pdidis;
        DIGITAL_PIN_PM_11,//uint8_t pm;
        DIGITAL_PIN_PU_11,//uint8_t pu;
        DIGITAL_PIN_PIM_11,//uint8_t pim;
        DIGITAL_PIN_POM_11,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_11),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_12 =
{
        DIGITAL_PIN_MASK_12, //uint8_t mask;
        DIGITAL_PIN_BIT_12, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_12,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_12,//uint8_t pmct;
        DIGITAL_PIN_PMCE_12,//uint8_t pmce;
        DIGITAL_PIN_CCDE_12,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_12, //uint8_t pdidis;
        DIGITAL_PIN_PM_12,//uint8_t pm;
        DIGITAL_PIN_PU_12,//uint8_t pu;
        DIGITAL_PIN_PIM_12,//uint8_t pim;
        DIGITAL_PIN_POM_12,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_12),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_13 =
{
        DIGITAL_PIN_MASK_13, //uint8_t mask;
        DIGITAL_PIN_BIT_13, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_13,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_13,//uint8_t pmct;
        DIGITAL_PIN_PMCE_13,//uint8_t pmce;
        DIGITAL_PIN_CCDE_13,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_13, //uint8_t pdidis;
        DIGITAL_PIN_PM_13,//uint8_t pm;
        DIGITAL_PIN_PU_13,//uint8_t pu;
        DIGITAL_PIN_PIM_13,//uint8_t pim;
        DIGITAL_PIN_POM_13,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_13),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_14 =
{
        DIGITAL_PIN_MASK_14, //uint8_t mask;
        DIGITAL_PIN_BIT_14, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_14,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_14,//uint8_t pmct;
        DIGITAL_PIN_PMCE_14,//uint8_t pmce;
        DIGITAL_PIN_CCDE_14,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_14, //uint8_t pdidis;
        DIGITAL_PIN_PM_14,//uint8_t pm;
        DIGITAL_PIN_PU_14,//uint8_t pu;
        DIGITAL_PIN_PIM_14,//uint8_t pim;
        DIGITAL_PIN_POM_14,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_14),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_15 =
{
        DIGITAL_PIN_MASK_15, //uint8_t mask;
        DIGITAL_PIN_BIT_15, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_15,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_15,//uint8_t pmct;
        DIGITAL_PIN_PMCE_15,//uint8_t pmce;
        DIGITAL_PIN_CCDE_15,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_15, //uint8_t pdidis;
        DIGITAL_PIN_PM_15,//uint8_t pm;
        DIGITAL_PIN_PU_15,//uint8_t pu;
        DIGITAL_PIN_PIM_15,//uint8_t pim;
        DIGITAL_PIN_POM_15,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_15),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_16 =
{
        DIGITAL_PIN_MASK_16, //uint8_t mask;
        DIGITAL_PIN_BIT_16, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_16,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_16,//uint8_t pmct;
        DIGITAL_PIN_PMCE_16,//uint8_t pmce;
        DIGITAL_PIN_CCDE_16,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_16, //uint8_t pdidis;
        DIGITAL_PIN_PM_16,//uint8_t pm;
        DIGITAL_PIN_PU_16,//uint8_t pu;
        DIGITAL_PIN_PIM_16,//uint8_t pim;
        DIGITAL_PIN_POM_16,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_16),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_17 =
{
        DIGITAL_PIN_MASK_17, //uint8_t mask;
        DIGITAL_PIN_BIT_17, //uint8_t bit;
        17,//uint8_t timer;
        DIGITAL_PIN_PMCA_17,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_17,//uint8_t pmct;
        DIGITAL_PIN_PMCE_17,//uint8_t pmce;
        DIGITAL_PIN_CCDE_17,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_17, //uint8_t pdidis;
        DIGITAL_PIN_PM_17,//uint8_t pm;
        DIGITAL_PIN_PU_17,//uint8_t pu;
        DIGITAL_PIN_PIM_17,//uint8_t pim;
        DIGITAL_PIN_POM_17,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_18 =
{
        DIGITAL_PIN_MASK_18, //uint8_t mask;
        DIGITAL_PIN_BIT_18, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_18,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_18,//uint8_t pmct;
        DIGITAL_PIN_PMCE_18,//uint8_t pmce;
        DIGITAL_PIN_CCDE_18,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_18, //uint8_t pdidis;
        DIGITAL_PIN_PM_18,//uint8_t pm;
        DIGITAL_PIN_PU_18,//uint8_t pu;
        DIGITAL_PIN_PIM_18,//uint8_t pim;
        DIGITAL_PIN_POM_18,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_18),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_19 =
{
        DIGITAL_PIN_MASK_19, //uint8_t mask;
        DIGITAL_PIN_BIT_19, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_19,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_19,//uint8_t pmct;
        DIGITAL_PIN_PMCE_19,//uint8_t pmce;
        DIGITAL_PIN_CCDE_19,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_19, //uint8_t pdidis;
        DIGITAL_PIN_PM_19,//uint8_t pm;
        DIGITAL_PIN_PU_19,//uint8_t pu;
        DIGITAL_PIN_PIM_19,//uint8_t pim;
        DIGITAL_PIN_POM_19,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_19),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_20 =
{
        DIGITAL_PIN_MASK_20, //uint8_t mask;
        DIGITAL_PIN_BIT_20, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_20,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_20,//uint8_t pmct;
        DIGITAL_PIN_PMCE_20,//uint8_t pmce;
        DIGITAL_PIN_CCDE_20,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_20, //uint8_t pdidis;
        DIGITAL_PIN_PM_20,//uint8_t pm;
        DIGITAL_PIN_PU_20,//uint8_t pu;
        DIGITAL_PIN_PIM_20,//uint8_t pim;
        DIGITAL_PIN_POM_20,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_20),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_21 =
{
        DIGITAL_PIN_MASK_21, //uint8_t mask;
        DIGITAL_PIN_BIT_21, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_21,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_21,//uint8_t pmct;
        DIGITAL_PIN_PMCE_21,//uint8_t pmce;
        DIGITAL_PIN_CCDE_21,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_21, //uint8_t pdidis;
        DIGITAL_PIN_PM_21,//uint8_t pm;
        DIGITAL_PIN_PU_21,//uint8_t pu;
        DIGITAL_PIN_PIM_21,//uint8_t pim;
        DIGITAL_PIN_POM_21,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_21),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_22 =
{
        DIGITAL_PIN_MASK_22, //uint8_t mask;
        DIGITAL_PIN_BIT_22, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_22,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_22,//uint8_t pmct;
        DIGITAL_PIN_PMCE_22,//uint8_t pmce;
        DIGITAL_PIN_CCDE_22,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_22, //uint8_t pdidis;
        DIGITAL_PIN_PM_22,//uint8_t pm;
        DIGITAL_PIN_PU_22,//uint8_t pu;
        DIGITAL_PIN_PIM_22,//uint8_t pim;
        DIGITAL_PIN_POM_22,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_22),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_23 =
{
        DIGITAL_PIN_MASK_23, //uint8_t mask;
        DIGITAL_PIN_BIT_23, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_23,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_23,//uint8_t pmct;
        DIGITAL_PIN_PMCE_23,//uint8_t pmce;
        DIGITAL_PIN_CCDE_23,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_23, //uint8_t pdidis;
        DIGITAL_PIN_PM_23,//uint8_t pm;
        DIGITAL_PIN_PU_23,//uint8_t pu;
        DIGITAL_PIN_PIM_23,//uint8_t pim;
        DIGITAL_PIN_POM_23,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_23),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_24 =
{
        DIGITAL_PIN_MASK_24, //uint8_t mask;
        DIGITAL_PIN_BIT_24, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_24,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_24,//uint8_t pmct;
        DIGITAL_PIN_PMCE_24,//uint8_t pmce;
        DIGITAL_PIN_CCDE_24,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_24, //uint8_t pdidis;
        DIGITAL_PIN_PM_24,//uint8_t pm;
        DIGITAL_PIN_PU_24,//uint8_t pu;
        DIGITAL_PIN_PIM_24,//uint8_t pim;
        DIGITAL_PIN_POM_24,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_24),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_25 =
{
        DIGITAL_PIN_MASK_25, //uint8_t mask;
        DIGITAL_PIN_BIT_25, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_25,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_25,//uint8_t pmct;
        DIGITAL_PIN_PMCE_25,//uint8_t pmce;
        DIGITAL_PIN_CCDE_25,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_25, //uint8_t pdidis;
        DIGITAL_PIN_PM_25,//uint8_t pm;
        DIGITAL_PIN_PU_25,//uint8_t pu;
        DIGITAL_PIN_PIM_25,//uint8_t pim;
        DIGITAL_PIN_POM_25,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_25),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_usersw =
{
        DIGITAL_PIN_MASK_26, //uint8_t mask;
        DIGITAL_PIN_BIT_26, //uint8_t bit;
        17,//uint8_t timer;
        DIGITAL_PIN_PMCA_26,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_26,//uint8_t pmct;
        DIGITAL_PIN_PMCE_26,//uint8_t pmce;
        DIGITAL_PIN_CCDE_26,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_26, //uint8_t pdidis;
        DIGITAL_PIN_PM_26,//uint8_t pm;
        DIGITAL_PIN_PU_26,//uint8_t pu;
        DIGITAL_PIN_PIM_26,//uint8_t pim;
        DIGITAL_PIN_POM_26,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_17),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_26),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_27 =
{
        DIGITAL_PIN_MASK_27, //uint8_t mask;
        DIGITAL_PIN_BIT_27, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_27,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_27,//uint8_t pmct;
        DIGITAL_PIN_PMCE_27,//uint8_t pmce;
        DIGITAL_PIN_CCDE_27,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_27, //uint8_t pdidis;
        DIGITAL_PIN_PM_27,//uint8_t pm;
        DIGITAL_PIN_PU_27,//uint8_t pu;
        DIGITAL_PIN_PIM_27,//uint8_t pim;
        DIGITAL_PIN_POM_27,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_27),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_28 =
{
        DIGITAL_PIN_MASK_28, //uint8_t mask;
        DIGITAL_PIN_BIT_28, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_28,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_28,//uint8_t pmct;
        DIGITAL_PIN_PMCE_28,//uint8_t pmce;
        DIGITAL_PIN_CCDE_28,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_28, //uint8_t pdidis;
        DIGITAL_PIN_PM_28,//uint8_t pm;
        DIGITAL_PIN_PU_28,//uint8_t pu;
        DIGITAL_PIN_PIM_28,//uint8_t pim;
        DIGITAL_PIN_POM_28,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_28),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_29 =
{
        DIGITAL_PIN_MASK_29, //uint8_t mask;
        DIGITAL_PIN_BIT_29, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_29,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_29,//uint8_t pmct;
        DIGITAL_PIN_PMCE_29,//uint8_t pmce;
        DIGITAL_PIN_CCDE_29,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_29, //uint8_t pdidis;
        DIGITAL_PIN_PM_29,//uint8_t pm;
        DIGITAL_PIN_PU_29,//uint8_t pu;
        DIGITAL_PIN_PIM_29,//uint8_t pim;
        DIGITAL_PIN_POM_29,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_29),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_30 =
{
        DIGITAL_PIN_MASK_30, //uint8_t mask;
        DIGITAL_PIN_BIT_30, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_30,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_30,//uint8_t pmct;
        DIGITAL_PIN_PMCE_30,//uint8_t pmce;
        DIGITAL_PIN_CCDE_30,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_30, //uint8_t pdidis;
        DIGITAL_PIN_PM_30,//uint8_t pm;
        DIGITAL_PIN_PU_30,//uint8_t pu;
        DIGITAL_PIN_PIM_30,//uint8_t pim;
        DIGITAL_PIN_POM_30,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_30),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_31 =
{
        DIGITAL_PIN_MASK_31, //uint8_t mask;
        DIGITAL_PIN_BIT_31, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_31,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_31,//uint8_t pmct;
        DIGITAL_PIN_PMCE_31,//uint8_t pmce;
        DIGITAL_PIN_CCDE_31,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_31, //uint8_t pdidis;
        DIGITAL_PIN_PM_31,//uint8_t pm;
        DIGITAL_PIN_PU_31,//uint8_t pu;
        DIGITAL_PIN_PIM_31,//uint8_t pim;
        DIGITAL_PIN_POM_31,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_31),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_32 =
{
        DIGITAL_PIN_MASK_32, //uint8_t mask;
        DIGITAL_PIN_BIT_32, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_32,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_32,//uint8_t pmct;
        DIGITAL_PIN_PMCE_32,//uint8_t pmce;
        DIGITAL_PIN_CCDE_32,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_32, //uint8_t pdidis;
        DIGITAL_PIN_PM_32,//uint8_t pm;
        DIGITAL_PIN_PU_32,//uint8_t pu;
        DIGITAL_PIN_PIM_32,//uint8_t pim;
        DIGITAL_PIN_POM_32,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_32),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_33 =
{
        DIGITAL_PIN_MASK_33, //uint8_t mask;
        DIGITAL_PIN_BIT_33, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_33,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_33,//uint8_t pmct;
        DIGITAL_PIN_PMCE_33,//uint8_t pmce;
        DIGITAL_PIN_CCDE_33,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_33, //uint8_t pdidis;
        DIGITAL_PIN_PM_33,//uint8_t pm;
        DIGITAL_PIN_PU_33,//uint8_t pu;
        DIGITAL_PIN_PIM_33,//uint8_t pim;
        DIGITAL_PIN_POM_33,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_33),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_34 =
{
        DIGITAL_PIN_MASK_34, //uint8_t mask;
        DIGITAL_PIN_BIT_34, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_34,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_34,//uint8_t pmct;
        DIGITAL_PIN_PMCE_34,//uint8_t pmce;
        DIGITAL_PIN_CCDE_34,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_34, //uint8_t pdidis;
        DIGITAL_PIN_PM_34,//uint8_t pm;
        DIGITAL_PIN_PU_34,//uint8_t pu;
        DIGITAL_PIN_PIM_34,//uint8_t pim;
        DIGITAL_PIN_POM_34,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_34),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_35 =
{
        DIGITAL_PIN_MASK_35, //uint8_t mask;
        DIGITAL_PIN_BIT_35, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_35,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_35,//uint8_t pmct;
        DIGITAL_PIN_PMCE_35,//uint8_t pmce;
        DIGITAL_PIN_CCDE_35,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_35, //uint8_t pdidis;
        DIGITAL_PIN_PM_35,//uint8_t pm;
        DIGITAL_PIN_PU_35,//uint8_t pu;
        DIGITAL_PIN_PIM_35,//uint8_t pim;
        DIGITAL_PIN_POM_35,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_35),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_36 =
{
        DIGITAL_PIN_MASK_36, //uint8_t mask;
        DIGITAL_PIN_BIT_36, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_36,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_36,//uint8_t pmct;
        DIGITAL_PIN_PMCE_36,//uint8_t pmce;
        DIGITAL_PIN_CCDE_36,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_36, //uint8_t pdidis;
        DIGITAL_PIN_PM_36,//uint8_t pm;
        DIGITAL_PIN_PU_36,//uint8_t pu;
        DIGITAL_PIN_PIM_36,//uint8_t pim;
        DIGITAL_PIN_POM_36,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_36),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_37 =
{
        DIGITAL_PIN_MASK_37, //uint8_t mask;
        DIGITAL_PIN_BIT_37, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_37,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_37,//uint8_t pmct;
        DIGITAL_PIN_PMCE_37,//uint8_t pmce;
        DIGITAL_PIN_CCDE_37,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_37, //uint8_t pdidis;
        DIGITAL_PIN_PM_37,//uint8_t pm;
        DIGITAL_PIN_PU_37,//uint8_t pu;
        DIGITAL_PIN_PIM_37,//uint8_t pim;
        DIGITAL_PIN_POM_37,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_37),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_38 =
{
        DIGITAL_PIN_MASK_38, //uint8_t mask;
        DIGITAL_PIN_BIT_38, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_38,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_38,//uint8_t pmct;
        DIGITAL_PIN_PMCE_38,//uint8_t pmce;
        DIGITAL_PIN_CCDE_38,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_38, //uint8_t pdidis;
        DIGITAL_PIN_PM_38,//uint8_t pm;
        DIGITAL_PIN_PU_38,//uint8_t pu;
        DIGITAL_PIN_PIM_38,//uint8_t pim;
        DIGITAL_PIN_POM_38,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_38),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_39 =
{
        DIGITAL_PIN_MASK_39, //uint8_t mask;
        DIGITAL_PIN_BIT_39, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_39,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_39,//uint8_t pmct;
        DIGITAL_PIN_PMCE_39,//uint8_t pmce;
        DIGITAL_PIN_CCDE_39,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_39, //uint8_t pdidis;
        DIGITAL_PIN_PM_39,//uint8_t pm;
        DIGITAL_PIN_PU_39,//uint8_t pu;
        DIGITAL_PIN_PIM_39,//uint8_t pim;
        DIGITAL_PIN_POM_39,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_39),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_40 =
{
        DIGITAL_PIN_MASK_40, //uint8_t mask;
        DIGITAL_PIN_BIT_40, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_40,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_40,//uint8_t pmct;
        DIGITAL_PIN_PMCE_40,//uint8_t pmce;
        DIGITAL_PIN_CCDE_40,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_40, //uint8_t pdidis;
        DIGITAL_PIN_PM_40,//uint8_t pm;
        DIGITAL_PIN_PU_40,//uint8_t pu;
        DIGITAL_PIN_PIM_40,//uint8_t pim;
        DIGITAL_PIN_POM_40,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_40),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_41 =
{
        DIGITAL_PIN_MASK_41, //uint8_t mask;
        DIGITAL_PIN_BIT_41, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_41,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_41,//uint8_t pmct;
        DIGITAL_PIN_PMCE_41,//uint8_t pmce;
        DIGITAL_PIN_CCDE_41,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_41, //uint8_t pdidis;
        DIGITAL_PIN_PM_41,//uint8_t pm;
        DIGITAL_PIN_PU_41,//uint8_t pu;
        DIGITAL_PIN_PIM_41,//uint8_t pim;
        DIGITAL_PIN_POM_41,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_41),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_42 =
{
        DIGITAL_PIN_MASK_42, //uint8_t mask;
        DIGITAL_PIN_BIT_42, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_42,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_42,//uint8_t pmct;
        DIGITAL_PIN_PMCE_42,//uint8_t pmce;
        DIGITAL_PIN_CCDE_42,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_42, //uint8_t pdidis;
        DIGITAL_PIN_PM_42,//uint8_t pm;
        DIGITAL_PIN_PU_42,//uint8_t pu;
        DIGITAL_PIN_PIM_42,//uint8_t pim;
        DIGITAL_PIN_POM_42,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_42),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_43 =
{
        DIGITAL_PIN_MASK_43, //uint8_t mask;
        DIGITAL_PIN_BIT_43, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_43,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_43,//uint8_t pmct;
        DIGITAL_PIN_PMCE_43,//uint8_t pmce;
        DIGITAL_PIN_CCDE_43,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_43, //uint8_t pdidis;
        DIGITAL_PIN_PM_43,//uint8_t pm;
        DIGITAL_PIN_PU_43,//uint8_t pu;
        DIGITAL_PIN_PIM_43,//uint8_t pim;
        DIGITAL_PIN_POM_43,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_43),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_44 =
{
        DIGITAL_PIN_MASK_44, //uint8_t mask;
        DIGITAL_PIN_BIT_44, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_44,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_44,//uint8_t pmct;
        DIGITAL_PIN_PMCE_44,//uint8_t pmce;
        DIGITAL_PIN_CCDE_44,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_44, //uint8_t pdidis;
        DIGITAL_PIN_PM_44,//uint8_t pm;
        DIGITAL_PIN_PU_44,//uint8_t pu;
        DIGITAL_PIN_PIM_44,//uint8_t pim;
        DIGITAL_PIN_POM_44,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_44),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_45 =
{
        DIGITAL_PIN_MASK_45, //uint8_t mask;
        DIGITAL_PIN_BIT_45, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_45,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_45,//uint8_t pmct;
        DIGITAL_PIN_PMCE_45,//uint8_t pmce;
        DIGITAL_PIN_CCDE_45,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_45, //uint8_t pdidis;
        DIGITAL_PIN_PM_45,//uint8_t pm;
        DIGITAL_PIN_PU_45,//uint8_t pu;
        DIGITAL_PIN_PIM_45,//uint8_t pim;
        DIGITAL_PIN_POM_45,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_45),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_46 =
{
        DIGITAL_PIN_MASK_46, //uint8_t mask;
        DIGITAL_PIN_BIT_46, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_46,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_46,//uint8_t pmct;
        DIGITAL_PIN_PMCE_46,//uint8_t pmce;
        DIGITAL_PIN_CCDE_46,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_46, //uint8_t pdidis;
        DIGITAL_PIN_PM_46,//uint8_t pm;
        DIGITAL_PIN_PU_46,//uint8_t pu;
        DIGITAL_PIN_PIM_46,//uint8_t pim;
        DIGITAL_PIN_POM_46,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_46),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_47 =
{
        DIGITAL_PIN_MASK_47, //uint8_t mask;
        DIGITAL_PIN_BIT_47, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_47,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_47,//uint8_t pmct;
        DIGITAL_PIN_PMCE_47,//uint8_t pmce;
        DIGITAL_PIN_CCDE_47,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_47, //uint8_t pdidis;
        DIGITAL_PIN_PM_47,//uint8_t pm;
        DIGITAL_PIN_PU_47,//uint8_t pu;
        DIGITAL_PIN_PIM_47,//uint8_t pim;
        DIGITAL_PIN_POM_47,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_47),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_48 =
{
        DIGITAL_PIN_MASK_48, //uint8_t mask;
        DIGITAL_PIN_BIT_48, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_48,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_48,//uint8_t pmct;
        DIGITAL_PIN_PMCE_48,//uint8_t pmce;
        DIGITAL_PIN_CCDE_48,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_48, //uint8_t pdidis;
        DIGITAL_PIN_PM_48,//uint8_t pm;
        DIGITAL_PIN_PU_48,//uint8_t pu;
        DIGITAL_PIN_PIM_48,//uint8_t pim;
        DIGITAL_PIN_POM_48,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_48),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_49 =
{
        DIGITAL_PIN_MASK_49, //uint8_t mask;
        DIGITAL_PIN_BIT_49, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_49,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_49,//uint8_t pmct;
        DIGITAL_PIN_PMCE_49,//uint8_t pmce;
        DIGITAL_PIN_CCDE_49,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_49, //uint8_t pdidis;
        DIGITAL_PIN_PM_49,//uint8_t pm;
        DIGITAL_PIN_PU_49,//uint8_t pu;
        DIGITAL_PIN_PIM_49,//uint8_t pim;
        DIGITAL_PIN_POM_49,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_49),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_50 =
{
        DIGITAL_PIN_MASK_50, //uint8_t mask;
        DIGITAL_PIN_BIT_50, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_50,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_50,//uint8_t pmct;
        DIGITAL_PIN_PMCE_50,//uint8_t pmce;
        DIGITAL_PIN_CCDE_50,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_50, //uint8_t pdidis;
        DIGITAL_PIN_PM_50,//uint8_t pm;
        DIGITAL_PIN_PU_50,//uint8_t pu;
        DIGITAL_PIN_PIM_50,//uint8_t pim;
        DIGITAL_PIN_POM_50,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_50),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_51 =
{
        DIGITAL_PIN_MASK_51, //uint8_t mask;
        DIGITAL_PIN_BIT_51, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_51,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_51,//uint8_t pmct;
        DIGITAL_PIN_PMCE_51,//uint8_t pmce;
        DIGITAL_PIN_CCDE_51,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_51, //uint8_t pdidis;
        DIGITAL_PIN_PM_51,//uint8_t pm;
        DIGITAL_PIN_PU_51,//uint8_t pu;
        DIGITAL_PIN_PIM_51,//uint8_t pim;
        DIGITAL_PIN_POM_51,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_51),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_52 =
{
        DIGITAL_PIN_MASK_52, //uint8_t mask;
        DIGITAL_PIN_BIT_52, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_52,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_52,//uint8_t pmct;
        DIGITAL_PIN_PMCE_52,//uint8_t pmce;
        DIGITAL_PIN_CCDE_52,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_52, //uint8_t pdidis;
        DIGITAL_PIN_PM_52,//uint8_t pm;
        DIGITAL_PIN_PU_52,//uint8_t pu;
        DIGITAL_PIN_PIM_52,//uint8_t pim;
        DIGITAL_PIN_POM_52,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_52),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_53 =
{
        DIGITAL_PIN_MASK_53, //uint8_t mask;
        DIGITAL_PIN_BIT_53, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_53,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_53,//uint8_t pmct;
        DIGITAL_PIN_PMCE_53,//uint8_t pmce;
        DIGITAL_PIN_CCDE_53,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_53, //uint8_t pdidis;
        DIGITAL_PIN_PM_53,//uint8_t pm;
        DIGITAL_PIN_PU_53,//uint8_t pu;
        DIGITAL_PIN_PIM_53,//uint8_t pim;
        DIGITAL_PIN_POM_53,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_53),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_54 =
{
        DIGITAL_PIN_MASK_54, //uint8_t mask;
        DIGITAL_PIN_BIT_54, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_54,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_54,//uint8_t pmct;
        DIGITAL_PIN_PMCE_54,//uint8_t pmce;
        DIGITAL_PIN_CCDE_54,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_54, //uint8_t pdidis;
        DIGITAL_PIN_PM_54,//uint8_t pm;
        DIGITAL_PIN_PU_54,//uint8_t pu;
        DIGITAL_PIN_PIM_54,//uint8_t pim;
        DIGITAL_PIN_POM_54,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_54),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_55 =
{
        DIGITAL_PIN_MASK_55, //uint8_t mask;
        DIGITAL_PIN_BIT_55, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_55,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_55,//uint8_t pmct;
        DIGITAL_PIN_PMCE_55,//uint8_t pmce;
        DIGITAL_PIN_CCDE_55,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_55, //uint8_t pdidis;
        DIGITAL_PIN_PM_55,//uint8_t pm;
        DIGITAL_PIN_PU_55,//uint8_t pu;
        DIGITAL_PIN_PIM_55,//uint8_t pim;
        DIGITAL_PIN_POM_55,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_55),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};

const PinTableType pinTable_56 =
{
        DIGITAL_PIN_MASK_56, //uint8_t mask;
        DIGITAL_PIN_BIT_56, //uint8_t bit;
        0,//uint8_t timer;
        DIGITAL_PIN_PMCA_56,//uint8_t pmca;
        /* Add for G23 */
        DIGITAL_PIN_PMCT_56,//uint8_t pmct;
        DIGITAL_PIN_PMCE_56,//uint8_t pmce;
        DIGITAL_PIN_CCDE_56,//uint8_t ccde;
        DIGITAL_PIN_PDIDIS_56, //uint8_t pdidis;
        DIGITAL_PIN_PM_56,//uint8_t pm;
        DIGITAL_PIN_PU_56,//uint8_t pu;
        DIGITAL_PIN_PIM_56,//uint8_t pim;
        DIGITAL_PIN_POM_56,//uint8_t pom;
        /* Add for G23 */
        getPortModeRegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portModeRegisterAddr;
        getPortPullUpRegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portPullUpRegisterAddr;
        getPortInputModeRegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portInputModeRegisterAddr;
        getPortOutputModeRegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portOutputModeRegisterAddr;
        getPortRegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portRegisterAddr;
        /* Add for G23 */
        getPortModeControlARegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portModeControlARegisterAddr;
        getPortModeControlTRegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portModeControlTRegisterAddr;
        getPortModeControlERegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portModeControlERegisterAddr;
        getPortOutCurControlRegisterAddr(),//volatile uint8_t* portOutCurControlRegisterAddr;
        getPortDigInputDisRegisterAddr(DIGITAL_PIN_56),//volatile uint8_t* portDigInputDisRegisterAddr;
        /* Add for G23 */

};



const PinTableType * const pinTablelist[NUM_DIGITAL_PINS] =
{
    /* 0 ~ 9 */
    &pinTable_0,
    &pinTable_1,
    &pinTable_2,
    &pinTable_3,
    &pinTable_4,
    &pinTable_5,
    &pinTable_6,
    &pinTable_7,
    &pinTable_8,
    &pinTable_9,
    /* 10 ~ 19 */
    &pinTable_10,
    &pinTable_11,
    &pinTable_12,
    &pinTable_13,
    &pinTable_14,
    &pinTable_userled2,
    &pinTable_userled1,
    &pinTable_17,
    &pinTable_18,
    &pinTable_19,
    /* 20 ~ 29 */
    &pinTable_20,
    &pinTable_21,
    &pinTable_22,
    &pinTable_23,
    &pinTable_24,
    &pinTable_25,
    &pinTable_usersw,
    &pinTable_27,
    &pinTable_28,
    &pinTable_29,
    /* 30 ~ 39 */
    &pinTable_30,
    &pinTable_31,
    &pinTable_32,
    &pinTable_33,
    &pinTable_34,
    &pinTable_35,
    &pinTable_36,
    &pinTable_37,
    &pinTable_38,
    &pinTable_39,
    /* 40 ~ 49 */
    &pinTable_40,
    &pinTable_41,
    &pinTable_42,
    &pinTable_43,
    &pinTable_44,
    &pinTable_45,
    &pinTable_46,
    &pinTable_47,
    &pinTable_48,
    &pinTable_49,
    /* 50 ~ 56 */
    &pinTable_50,
    &pinTable_51,
    &pinTable_52,
    &pinTable_53,
    &pinTable_54,
    &pinTable_55,
    &pinTable_56,
};

