/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : iodefine_ext.h
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 08.03.2021 1.00     First Release

***********************************************************************************************************************/
#ifndef __INTRINSIC_FUNCTIONS
#define __INTRINSIC_FUNCTIONS

#define DI() asm("di")
#define EI() asm("ei")
#define HALT() asm("halt")
#define NOP() asm("nop")
#define STOP() asm("stop")

#endif

#ifndef __IOREG_BIT_STRUCTURES
#define __IOREG_BIT_STRUCTURES
typedef struct {
	unsigned char no0 :1;
	unsigned char no1 :1;
	unsigned char no2 :1;
	unsigned char no3 :1;
	unsigned char no4 :1;
	unsigned char no5 :1;
	unsigned char no6 :1;
	unsigned char no7 :1;
} __BITS8;

typedef struct {
	unsigned short no0 :1;
	unsigned short no1 :1;
	unsigned short no2 :1;
	unsigned short no3 :1;
	unsigned short no4 :1;
	unsigned short no5 :1;
	unsigned short no6 :1;
	unsigned short no7 :1;
	unsigned short no8 :1;
	unsigned short no9 :1;
	unsigned short no10 :1;
	unsigned short no11 :1;
	unsigned short no12 :1;
	unsigned short no13 :1;
	unsigned short no14 :1;
	unsigned short no15 :1;
} __BITS16;

#endif

#ifndef IODEFINE_EXT_H
#define IODEFINE_EXT_H

/*
 IO Registers
 */
union un_adm2 {
	unsigned char adm2;
	__BITS8 BIT;
};
union un_pu0 {
	unsigned char pu0;
	__BITS8 BIT;
};
union un_pu1 {
	unsigned char pu1;
	__BITS8 BIT;
};
union un_pu3 {
	unsigned char pu3;
	__BITS8 BIT;
};
union un_pu4 {
	unsigned char pu4;
	__BITS8 BIT;
};
union un_pu5 {
	unsigned char pu5;
	__BITS8 BIT;
};
union un_pu6 {
	unsigned char pu6;
	__BITS8 BIT;
};
union un_pu7 {
	unsigned char pu7;
	__BITS8 BIT;
};
union un_pu8 {
	unsigned char pu8;
	__BITS8 BIT;
};
union un_pu9 {
	unsigned char pu9;
	__BITS8 BIT;
};
union un_pu10 {
	unsigned char pu10;
	__BITS8 BIT;
};
union un_pu11 {
	unsigned char pu11;
	__BITS8 BIT;
};
union un_pu12 {
	unsigned char pu12;
	__BITS8 BIT;
};
union un_pu14 {
	unsigned char pu14;
	__BITS8 BIT;
};
union un_pim0 {
	unsigned char pim0;
	__BITS8 BIT;
};
union un_pim1 {
	unsigned char pim1;
	__BITS8 BIT;
};
union un_pim3 {
	unsigned char pim3;
	__BITS8 BIT;
};
union un_pim4 {
	unsigned char pim4;
	__BITS8 BIT;
};
union un_pim5 {
	unsigned char pim5;
	__BITS8 BIT;
};
union un_pim7 {
	unsigned char pim7;
	__BITS8 BIT;
};
union un_pim8 {
	unsigned char pim8;
	__BITS8 BIT;
};
union un_pim14 {
	unsigned char pim14;
	__BITS8 BIT;
};
union un_pom0 {
	unsigned char pom0;
	__BITS8 BIT;
};
union un_pom1 {
	unsigned char pom1;
	__BITS8 BIT;
};
union un_pom3 {
	unsigned char pom3;
	__BITS8 BIT;
};
union un_pom4 {
	unsigned char pom4;
	__BITS8 BIT;
};
union un_pom5 {
	unsigned char pom5;
	__BITS8 BIT;
};
union un_pom7 {
	unsigned char pom7;
	__BITS8 BIT;
};
union un_pom8 {
	unsigned char pom8;
	__BITS8 BIT;
};
union un_pom9 {
	unsigned char pom9;
	__BITS8 BIT;
};
union un_pom12 {
	unsigned char pom12;
	__BITS8 BIT;
};
union un_pom14 {
	unsigned char pom14;
	__BITS8 BIT;
};
union un_pmca0 {
	unsigned char pmca0;
	__BITS8 BIT;
};
union un_pmca1 {
	unsigned char pmca1;
	__BITS8 BIT;
};
union un_pmca2 {
	unsigned char pmca2;
	__BITS8 BIT;
};
union un_pmca3 {
	unsigned char pmca3;
	__BITS8 BIT;
};
union un_pmca10 {
	unsigned char pmca10;
	__BITS8 BIT;
};
union un_pmca11 {
	unsigned char pmca11;
	__BITS8 BIT;
};
union un_pmca12 {
	unsigned char pmca12;
	__BITS8 BIT;
};
union un_pmca14 {
	unsigned char pmca14;
	__BITS8 BIT;
};
union un_pmca15 {
	unsigned char pmca15;
	__BITS8 BIT;
};
union un_nfen0 {
	unsigned char nfen0;
	__BITS8 BIT;
};
union un_nfen1 {
	unsigned char nfen1;
	__BITS8 BIT;
};
union un_nfen2 {
	unsigned char nfen2;
	__BITS8 BIT;
};
union un_isc {
	unsigned char isc;
	__BITS8 BIT;
};
union un_ulbs {
	unsigned char ulbs;
	__BITS8 BIT;
};
union un_pms {
	unsigned char pms;
	__BITS8 BIT;
};
union un_gdidis {
	unsigned char gdidis;
	__BITS8 BIT;
};
union un_dflctl {
	unsigned char dflctl;
	__BITS8 BIT;
};
union un_flmode {
	unsigned char flmode;
	__BITS8 BIT;
};
union un_flmwrp {
	unsigned char flmwrp;
	__BITS8 BIT;
};
union un_fsse {
	unsigned char fsse;
	__BITS8 BIT;
};
union un_pfs {
	unsigned char pfs;
	__BITS8 BIT;
};
union un_per0 {
	unsigned char per0;
	__BITS8 BIT;
};
union un_prr0 {
	unsigned char prr0;
	__BITS8 BIT;
};
union un_osmc {
	unsigned char osmc;
	__BITS8 BIT;
};
union un_rpectl {
	unsigned char rpectl;
	__BITS8 BIT;
};
union un_porsr {
	unsigned char porsr;
	__BITS8 BIT;
};
union un_per1 {
	unsigned char per1;
	__BITS8 BIT;
};
union un_prr1 {
	unsigned char prr1;
	__BITS8 BIT;
};
union un_se0l {
	unsigned char se0l;
	__BITS8 BIT;
};
union un_ss0l {
	unsigned char ss0l;
	__BITS8 BIT;
};
union un_st0l {
	unsigned char st0l;
	__BITS8 BIT;
};
union un_soe0l {
	unsigned char soe0l;
	__BITS8 BIT;
};
union un_se1l {
	unsigned char se1l;
	__BITS8 BIT;
};
union un_ss1l {
	unsigned char ss1l;
	__BITS8 BIT;
};
union un_st1l {
	unsigned char st1l;
	__BITS8 BIT;
};
union un_soe1l {
	unsigned char soe1l;
	__BITS8 BIT;
};
union un_te0l {
	unsigned char te0l;
	__BITS8 BIT;
};
union un_ts0l {
	unsigned char ts0l;
	__BITS8 BIT;
};
union un_tt0l {
	unsigned char tt0l;
	__BITS8 BIT;
};
union un_toe0l {
	unsigned char toe0l;
	__BITS8 BIT;
};
union un_te1l {
	unsigned char te1l;
	__BITS8 BIT;
};
union un_ts1l {
	unsigned char ts1l;
	__BITS8 BIT;
};
union un_tt1l {
	unsigned char tt1l;
	__BITS8 BIT;
};
union un_toe1l {
	unsigned char toe1l;
	__BITS8 BIT;
};
union un_wkupmd {
	unsigned char wkupmd;
	__BITS8 BIT;
};
union un_psmcr {
	unsigned char psmcr;
	__BITS8 BIT;
};
union un_lvdfclr {
	unsigned char lvdfclr;
	__BITS8 BIT;
};
union un_rtcc0 {
	unsigned char rtcc0;
	__BITS8 BIT;
};
union un_rtcc1 {
	unsigned char rtcc1;
	__BITS8 BIT;
};
union un_iicctl00 {
	unsigned char iicctl00;
	__BITS8 BIT;
};
union un_iicctl01 {
	unsigned char iicctl01;
	__BITS8 BIT;
};
union un_iicctl10 {
	unsigned char iicctl10;
	__BITS8 BIT;
};
union un_iicctl11 {
	unsigned char iicctl11;
	__BITS8 BIT;
};
union un_pmct0 {
	unsigned char pmct0;
	__BITS8 BIT;
};
union un_pmct2 {
	unsigned char pmct2;
	__BITS8 BIT;
};
union un_pmct3 {
	unsigned char pmct3;
	__BITS8 BIT;
};
union un_pmct5 {
	unsigned char pmct5;
	__BITS8 BIT;
};
union un_pmct6 {
	unsigned char pmct6;
	__BITS8 BIT;
};
union un_pmct7 {
	unsigned char pmct7;
	__BITS8 BIT;
};
union un_pmct15 {
	unsigned char pmct15;
	__BITS8 BIT;
};
union un_pmce0 {
	unsigned char pmce0;
	__BITS8 BIT;
};
union un_pmce1 {
	unsigned char pmce1;
	__BITS8 BIT;
};
union un_pmce5 {
	unsigned char pmce5;
	__BITS8 BIT;
};
union un_pmce6 {
	unsigned char pmce6;
	__BITS8 BIT;
};
union un_ccde {
	unsigned char ccde;
	__BITS8 BIT;
};
union un_ptdc {
	unsigned char ptdc;
	__BITS8 BIT;
};
union un_pfoe0 {
	unsigned char pfoe0;
	__BITS8 BIT;
};
union un_pfoe1 {
	unsigned char pfoe1;
	__BITS8 BIT;
};
union un_pdidis0 {
	unsigned char pdidis0;
	__BITS8 BIT;
};
union un_pdidis1 {
	unsigned char pdidis1;
	__BITS8 BIT;
};
union un_pdidis3 {
	unsigned char pdidis3;
	__BITS8 BIT;
};
union un_pdidis4 {
	unsigned char pdidis4;
	__BITS8 BIT;
};
union un_pdidis5 {
	unsigned char pdidis5;
	__BITS8 BIT;
};
union un_pdidis7 {
	unsigned char pdidis7;
	__BITS8 BIT;
};
union un_pdidis8 {
	unsigned char pdidis8;
	__BITS8 BIT;
};
union un_pdidis9 {
	unsigned char pdidis9;
	__BITS8 BIT;
};
union un_pdidis12 {
	unsigned char pdidis12;
	__BITS8 BIT;
};
union un_pdidis13 {
	unsigned char pdidis13;
	__BITS8 BIT;
};
union un_pdidis14 {
	unsigned char pdidis14;
	__BITS8 BIT;
};
union un_flars {
	unsigned char flars;
	__BITS8 BIT;
};
union un_fssq {
	unsigned char fssq;
	__BITS8 BIT;
};
union un_flrst {
	unsigned char flrst;
	__BITS8 BIT;
};
union un_fsastl {
	unsigned char fsastl;
	__BITS8 BIT;
};
union un_fsasth {
	unsigned char fsasth;
	__BITS8 BIT;
};
union un_dtcen0 {
	unsigned char dtcen0;
	__BITS8 BIT;
};
union un_dtcen1 {
	unsigned char dtcen1;
	__BITS8 BIT;
};
union un_dtcen2 {
	unsigned char dtcen2;
	__BITS8 BIT;
};
union un_dtcen3 {
	unsigned char dtcen3;
	__BITS8 BIT;
};
union un_dtcen4 {
	unsigned char dtcen4;
	__BITS8 BIT;
};
union un_crc0ctl {
	unsigned char crc0ctl;
	__BITS8 BIT;
};
union un_asima00 {
	unsigned char asima00;
	__BITS8 BIT;
};
union un_asima01 {
	unsigned char asima01;
	__BITS8 BIT;
};
union un_ascta0 {
	unsigned char ascta0;
	__BITS8 BIT;
};
union un_asima10 {
	unsigned char asima10;
	__BITS8 BIT;
};
union un_asima11 {
	unsigned char asima11;
	__BITS8 BIT;
};
union un_ascta1 {
	unsigned char ascta1;
	__BITS8 BIT;
};
union un_uta0ck {
	unsigned char uta0ck;
	__BITS8 BIT;
};
union un_uta1ck {
	unsigned char uta1ck;
	__BITS8 BIT;
};
union un_dam {
	unsigned char dam;
	__BITS8 BIT;
};
union un_compmdr {
	unsigned char compmdr;
	__BITS8 BIT;
};
union un_compfir {
	unsigned char compfir;
	__BITS8 BIT;
};
union un_compocr {
	unsigned char compocr;
	__BITS8 BIT;
};
union un_itlctl0 {
	unsigned char itlctl0;
	__BITS8 BIT;
};
union un_itlcc0 {
	unsigned char itlcc0;
	__BITS8 BIT;
};
union un_smsc {
	unsigned char smsc;
	__BITS8 BIT;
};
union un_smss {
	unsigned char smss;
	__BITS8 BIT;
};
union un_remcon0 {
	unsigned char remcon0;
	__BITS8 BIT;
};
union un_remcon1 {
	unsigned char remcon1;
	__BITS8 BIT;
};
union un_remsts {
	unsigned char remsts;
	__BITS8 BIT;
};
union un_remint {
	unsigned char remint;
	__BITS8 BIT;
};
union un_remstc {
	unsigned char remstc;
	__BITS8 BIT;
};
union un_remrbit {
	unsigned char remrbit;
	__BITS8 BIT;
};
union un_remdat0 {
	unsigned char remdat0;
	__BITS8 BIT;
};

#define ADM2 (*(volatile union un_adm2 *)0xF0010).adm2
#define ADM2_bit (*(volatile union un_adm2 *)0xF0010).BIT
#define ADUL (*(volatile unsigned char *)0xF0011)
#define ADLL (*(volatile unsigned char *)0xF0012)
#define ADTES (*(volatile unsigned char *)0xF0013)
#define ADCR0 (*(volatile unsigned short *)0xF0020)
#define ADCR0H (*(volatile unsigned char *)0xF0021)
#define ADCR1 (*(volatile unsigned short *)0xF0022)
#define ADCR1H (*(volatile unsigned char *)0xF0023)
#define ADCR2 (*(volatile unsigned short *)0xF0024)
#define ADCR2H (*(volatile unsigned char *)0xF0025)
#define ADCR3 (*(volatile unsigned short *)0xF0026)
#define ADCR3H (*(volatile unsigned char *)0xF0027)
#define PU0 (*(volatile union un_pu0 *)0xF0030).pu0
#define PU0_bit (*(volatile union un_pu0 *)0xF0030).BIT
#define PU1 (*(volatile union un_pu1 *)0xF0031).pu1
#define PU1_bit (*(volatile union un_pu1 *)0xF0031).BIT
#define PU3 (*(volatile union un_pu3 *)0xF0033).pu3
#define PU3_bit (*(volatile union un_pu3 *)0xF0033).BIT
#define PU4 (*(volatile union un_pu4 *)0xF0034).pu4
#define PU4_bit (*(volatile union un_pu4 *)0xF0034).BIT
#define PU5 (*(volatile union un_pu5 *)0xF0035).pu5
#define PU5_bit (*(volatile union un_pu5 *)0xF0035).BIT
#define PU6 (*(volatile union un_pu6 *)0xF0036).pu6
#define PU6_bit (*(volatile union un_pu6 *)0xF0036).BIT
#define PU7 (*(volatile union un_pu7 *)0xF0037).pu7
#define PU7_bit (*(volatile union un_pu7 *)0xF0037).BIT
#define PU8 (*(volatile union un_pu8 *)0xF0038).pu8
#define PU8_bit (*(volatile union un_pu8 *)0xF0038).BIT
#define PU9 (*(volatile union un_pu9 *)0xF0039).pu9
#define PU9_bit (*(volatile union un_pu9 *)0xF0039).BIT
#define PU10 (*(volatile union un_pu10 *)0xF003A).pu10
#define PU10_bit (*(volatile union un_pu10 *)0xF003A).BIT
#define PU11 (*(volatile union un_pu11 *)0xF003B).pu11
#define PU11_bit (*(volatile union un_pu11 *)0xF003B).BIT
#define PU12 (*(volatile union un_pu12 *)0xF003C).pu12
#define PU12_bit (*(volatile union un_pu12 *)0xF003C).BIT
#define PU14 (*(volatile union un_pu14 *)0xF003E).pu14
#define PU14_bit (*(volatile union un_pu14 *)0xF003E).BIT
#define PIM0 (*(volatile union un_pim0 *)0xF0040).pim0
#define PIM0_bit (*(volatile union un_pim0 *)0xF0040).BIT
#define PIM1 (*(volatile union un_pim1 *)0xF0041).pim1
#define PIM1_bit (*(volatile union un_pim1 *)0xF0041).BIT
#define PIM3 (*(volatile union un_pim3 *)0xF0043).pim3
#define PIM3_bit (*(volatile union un_pim3 *)0xF0043).BIT
#define PIM4 (*(volatile union un_pim4 *)0xF0044).pim4
#define PIM4_bit (*(volatile union un_pim4 *)0xF0044).BIT
#define PIM5 (*(volatile union un_pim5 *)0xF0045).pim5
#define PIM5_bit (*(volatile union un_pim5 *)0xF0045).BIT
#define PIM7 (*(volatile union un_pim7 *)0xF0047).pim7
#define PIM7_bit (*(volatile union un_pim7 *)0xF0047).BIT
#define PIM8 (*(volatile union un_pim8 *)0xF0048).pim8
#define PIM8_bit (*(volatile union un_pim8 *)0xF0048).BIT
#define PIM14 (*(volatile union un_pim14 *)0xF004E).pim14
#define PIM14_bit (*(volatile union un_pim14 *)0xF004E).BIT
#define POM0 (*(volatile union un_pom0 *)0xF0050).pom0
#define POM0_bit (*(volatile union un_pom0 *)0xF0050).BIT
#define POM1 (*(volatile union un_pom1 *)0xF0051).pom1
#define POM1_bit (*(volatile union un_pom1 *)0xF0051).BIT
#define POM3 (*(volatile union un_pom3 *)0xF0053).pom3
#define POM3_bit (*(volatile union un_pom3 *)0xF0053).BIT
#define POM4 (*(volatile union un_pom4 *)0xF0054).pom4
#define POM4_bit (*(volatile union un_pom4 *)0xF0054).BIT
#define POM5 (*(volatile union un_pom5 *)0xF0055).pom5
#define POM5_bit (*(volatile union un_pom5 *)0xF0055).BIT
#define POM7 (*(volatile union un_pom7 *)0xF0057).pom7
#define POM7_bit (*(volatile union un_pom7 *)0xF0057).BIT
#define POM8 (*(volatile union un_pom8 *)0xF0058).pom8
#define POM8_bit (*(volatile union un_pom8 *)0xF0058).BIT
#define POM9 (*(volatile union un_pom9 *)0xF0059).pom9
#define POM9_bit (*(volatile union un_pom9 *)0xF0059).BIT
#define POM12 (*(volatile union un_pom12 *)0xF005C).pom12
#define POM12_bit (*(volatile union un_pom12 *)0xF005C).BIT
#define POM14 (*(volatile union un_pom14 *)0xF005E).pom14
#define POM14_bit (*(volatile union un_pom14 *)0xF005E).BIT
#define PMCA0 (*(volatile union un_pmca0 *)0xF0060).pmca0
#define PMCA0_bit (*(volatile union un_pmca0 *)0xF0060).BIT
#define PMCA1 (*(volatile union un_pmca1 *)0xF0061).pmca1
#define PMCA1_bit (*(volatile union un_pmca1 *)0xF0061).BIT
#define PMCA2 (*(volatile union un_pmca2 *)0xF0062).pmca2
#define PMCA2_bit (*(volatile union un_pmca2 *)0xF0062).BIT
#define PMCA3 (*(volatile union un_pmca3 *)0xF0063).pmca3
#define PMCA3_bit (*(volatile union un_pmca3 *)0xF0063).BIT
#define PMCA10 (*(volatile union un_pmca10 *)0xF006A).pmca10
#define PMCA10_bit (*(volatile union un_pmca10 *)0xF006A).BIT
#define PMCA11 (*(volatile union un_pmca11 *)0xF006B).pmca11
#define PMCA11_bit (*(volatile union un_pmca11 *)0xF006B).BIT
#define PMCA12 (*(volatile union un_pmca12 *)0xF006C).pmca12
#define PMCA12_bit (*(volatile union un_pmca12 *)0xF006C).BIT
#define PMCA14 (*(volatile union un_pmca14 *)0xF006E).pmca14
#define PMCA14_bit (*(volatile union un_pmca14 *)0xF006E).BIT
#define PMCA15 (*(volatile union un_pmca15 *)0xF006F).pmca15
#define PMCA15_bit (*(volatile union un_pmca15 *)0xF006F).BIT
#define NFEN0 (*(volatile union un_nfen0 *)0xF0070).nfen0
#define NFEN0_bit (*(volatile union un_nfen0 *)0xF0070).BIT
#define NFEN1 (*(volatile union un_nfen1 *)0xF0071).nfen1
#define NFEN1_bit (*(volatile union un_nfen1 *)0xF0071).BIT
#define NFEN2 (*(volatile union un_nfen2 *)0xF0072).nfen2
#define NFEN2_bit (*(volatile union un_nfen2 *)0xF0072).BIT
#define ISC (*(volatile union un_isc *)0xF0073).isc
#define ISC_bit (*(volatile union un_isc *)0xF0073).BIT
#define TIS0 (*(volatile unsigned char *)0xF0074)
#define TIS1 (*(volatile unsigned char *)0xF0075)
#define PIOR (*(volatile unsigned char *)0xF0077)
#define IAWCTL (*(volatile unsigned char *)0xF0078)
#define ULBS (*(volatile union un_ulbs *)0xF0079).ulbs
#define ULBS_bit (*(volatile union un_ulbs *)0xF0079).BIT
#define PMS (*(volatile union un_pms *)0xF007B).pms
#define PMS_bit (*(volatile union un_pms *)0xF007B).BIT
#define GDIDIS (*(volatile union un_gdidis *)0xF007D).gdidis
#define GDIDIS_bit (*(volatile union un_gdidis *)0xF007D).BIT
#define DFLCTL (*(volatile union un_dflctl *)0xF0090).dflctl
#define DFLCTL_bit (*(volatile union un_dflctl *)0xF0090).BIT
#define HIOTRM (*(volatile unsigned char *)0xF00A0)
#define HOCODIV (*(volatile unsigned char *)0xF00A8)
#define FLMODE (*(volatile union un_flmode *)0xF00AA).flmode
#define FLMODE_bit (*(volatile union un_flmode *)0xF00AA).BIT
#define FLMWRP (*(volatile union un_flmwrp *)0xF00AB).flmwrp
#define FLMWRP_bit (*(volatile union un_flmwrp *)0xF00AB).BIT
#define FLSEC (*(volatile unsigned short *)0xF00B0)
#define FLFSWS (*(volatile unsigned short *)0xF00B2)
#define FLFSWE (*(volatile unsigned short *)0xF00B4)
#define FSSET (*(volatile unsigned char *)0xF00B6)
#define FSSE (*(volatile union un_fsse *)0xF00B7).fsse
#define FSSE_bit (*(volatile union un_fsse *)0xF00B7).BIT
#define FLFADL (*(volatile unsigned short *)0xF00B8)
#define FLFADH (*(volatile unsigned char *)0xF00BA)
#define PFCMD (*(volatile unsigned char *)0xF00C0)
#define PFS (*(volatile union un_pfs *)0xF00C1).pfs
#define PFS_bit (*(volatile union un_pfs *)0xF00C1).BIT
#define FLWE (*(volatile unsigned char *)0xF00C6)
#define PER0 (*(volatile union un_per0 *)0xF00F0).per0
#define PER0_bit (*(volatile union un_per0 *)0xF00F0).BIT
#define PRR0 (*(volatile union un_prr0 *)0xF00F1).prr0
#define PRR0_bit (*(volatile union un_prr0 *)0xF00F1).BIT
#define MOCODIV (*(volatile unsigned char *)0xF00F2)
#define OSMC (*(volatile union un_osmc *)0xF00F3).osmc
#define OSMC_bit (*(volatile union un_osmc *)0xF00F3).BIT
#define RPECTL (*(volatile union un_rpectl *)0xF00F5).rpectl
#define RPECTL_bit (*(volatile union un_rpectl *)0xF00F5).BIT
#define PORSR (*(volatile union un_porsr *)0xF00F9).porsr
#define PORSR_bit (*(volatile union un_porsr *)0xF00F9).BIT
#define PER1 (*(volatile union un_per1 *)0xF00FA).per1
#define PER1_bit (*(volatile union un_per1 *)0xF00FA).BIT
#define PRR1 (*(volatile union un_prr1 *)0xF00FB).prr1
#define PRR1_bit (*(volatile union un_prr1 *)0xF00FB).BIT
#define BCDADJ (*(volatile unsigned char *)0xF00FE)
#define VECTCTRL (*(volatile unsigned char *)0xF00FF)
#define SSR00 (*(volatile unsigned short *)0xF0100)
#define SSR00L (*(volatile unsigned char *)0xF0100)
#define SSR01 (*(volatile unsigned short *)0xF0102)
#define SSR01L (*(volatile unsigned char *)0xF0102)
#define SSR02 (*(volatile unsigned short *)0xF0104)
#define SSR02L (*(volatile unsigned char *)0xF0104)
#define SSR03 (*(volatile unsigned short *)0xF0106)
#define SSR03L (*(volatile unsigned char *)0xF0106)
#define SIR00 (*(volatile unsigned short *)0xF0108)
#define SIR00L (*(volatile unsigned char *)0xF0108)
#define SIR01 (*(volatile unsigned short *)0xF010A)
#define SIR01L (*(volatile unsigned char *)0xF010A)
#define SIR02 (*(volatile unsigned short *)0xF010C)
#define SIR02L (*(volatile unsigned char *)0xF010C)
#define SIR03 (*(volatile unsigned short *)0xF010E)
#define SIR03L (*(volatile unsigned char *)0xF010E)
#define SMR00 (*(volatile unsigned short *)0xF0110)
#define SMR01 (*(volatile unsigned short *)0xF0112)
#define SMR02 (*(volatile unsigned short *)0xF0114)
#define SMR03 (*(volatile unsigned short *)0xF0116)
#define SCR00 (*(volatile unsigned short *)0xF0118)
#define SCR01 (*(volatile unsigned short *)0xF011A)
#define SCR02 (*(volatile unsigned short *)0xF011C)
#define SCR03 (*(volatile unsigned short *)0xF011E)
#define SE0 (*(volatile unsigned short *)0xF0120)
#define SE0L (*(volatile union un_se0l *)0xF0120).se0l
#define SE0L_bit (*(volatile union un_se0l *)0xF0120).BIT
#define SS0 (*(volatile unsigned short *)0xF0122)
#define SS0L (*(volatile union un_ss0l *)0xF0122).ss0l
#define SS0L_bit (*(volatile union un_ss0l *)0xF0122).BIT
#define ST0 (*(volatile unsigned short *)0xF0124)
#define ST0L (*(volatile union un_st0l *)0xF0124).st0l
#define ST0L_bit (*(volatile union un_st0l *)0xF0124).BIT
#define SPS0 (*(volatile unsigned short *)0xF0126)
#define SPS0L (*(volatile unsigned char *)0xF0126)
#define SO0 (*(volatile unsigned short *)0xF0128)
#define SOE0 (*(volatile unsigned short *)0xF012A)
#define SOE0L (*(volatile union un_soe0l *)0xF012A).soe0l
#define SOE0L_bit (*(volatile union un_soe0l *)0xF012A).BIT
#define SOL0 (*(volatile unsigned short *)0xF0134)
#define SOL0L (*(volatile unsigned char *)0xF0134)
#define SSC0 (*(volatile unsigned short *)0xF0138)
#define SSC0L (*(volatile unsigned char *)0xF0138)
#define SSR10 (*(volatile unsigned short *)0xF0140)
#define SSR10L (*(volatile unsigned char *)0xF0140)
#define SSR11 (*(volatile unsigned short *)0xF0142)
#define SSR11L (*(volatile unsigned char *)0xF0142)
#define SSR12 (*(volatile unsigned short *)0xF0144)
#define SSR12L (*(volatile unsigned char *)0xF0144)
#define SSR13 (*(volatile unsigned short *)0xF0146)
#define SSR13L (*(volatile unsigned char *)0xF0146)
#define SIR10 (*(volatile unsigned short *)0xF0148)
#define SIR10L (*(volatile unsigned char *)0xF0148)
#define SIR11 (*(volatile unsigned short *)0xF014A)
#define SIR11L (*(volatile unsigned char *)0xF014A)
#define SIR12 (*(volatile unsigned short *)0xF014C)
#define SIR12L (*(volatile unsigned char *)0xF014C)
#define SIR13 (*(volatile unsigned short *)0xF014E)
#define SIR13L (*(volatile unsigned char *)0xF014E)
#define SMR10 (*(volatile unsigned short *)0xF0150)
#define SMR11 (*(volatile unsigned short *)0xF0152)
#define SMR12 (*(volatile unsigned short *)0xF0154)
#define SMR13 (*(volatile unsigned short *)0xF0156)
#define SCR10 (*(volatile unsigned short *)0xF0158)
#define SCR11 (*(volatile unsigned short *)0xF015A)
#define SCR12 (*(volatile unsigned short *)0xF015C)
#define SCR13 (*(volatile unsigned short *)0xF015E)
#define SE1 (*(volatile unsigned short *)0xF0160)
#define SE1L (*(volatile union un_se1l *)0xF0160).se1l
#define SE1L_bit (*(volatile union un_se1l *)0xF0160).BIT
#define SS1 (*(volatile unsigned short *)0xF0162)
#define SS1L (*(volatile union un_ss1l *)0xF0162).ss1l
#define SS1L_bit (*(volatile union un_ss1l *)0xF0162).BIT
#define ST1 (*(volatile unsigned short *)0xF0164)
#define ST1L (*(volatile union un_st1l *)0xF0164).st1l
#define ST1L_bit (*(volatile union un_st1l *)0xF0164).BIT
#define SPS1 (*(volatile unsigned short *)0xF0166)
#define SPS1L (*(volatile unsigned char *)0xF0166)
#define SO1 (*(volatile unsigned short *)0xF0168)
#define SOE1 (*(volatile unsigned short *)0xF016A)
#define SOE1L (*(volatile union un_soe1l *)0xF016A).soe1l
#define SOE1L_bit (*(volatile union un_soe1l *)0xF016A).BIT
#define SOL1 (*(volatile unsigned short *)0xF0174)
#define SOL1L (*(volatile unsigned char *)0xF0174)
#define SSC1 (*(volatile unsigned short *)0xF0178)
#define SSC1L (*(volatile unsigned char *)0xF0178)
#define TCR00 (*(volatile unsigned short *)0xF0180)
#define TCR01 (*(volatile unsigned short *)0xF0182)
#define TCR02 (*(volatile unsigned short *)0xF0184)
#define TCR03 (*(volatile unsigned short *)0xF0186)
#define TCR04 (*(volatile unsigned short *)0xF0188)
#define TCR05 (*(volatile unsigned short *)0xF018A)
#define TCR06 (*(volatile unsigned short *)0xF018C)
#define TCR07 (*(volatile unsigned short *)0xF018E)
#define TMR00 (*(volatile unsigned short *)0xF0190)
#define TMR01 (*(volatile unsigned short *)0xF0192)
#define TMR02 (*(volatile unsigned short *)0xF0194)
#define TMR03 (*(volatile unsigned short *)0xF0196)
#define TMR04 (*(volatile unsigned short *)0xF0198)
#define TMR05 (*(volatile unsigned short *)0xF019A)
#define TMR06 (*(volatile unsigned short *)0xF019C)
#define TMR07 (*(volatile unsigned short *)0xF019E)
#define TSR00 (*(volatile unsigned short *)0xF01A0)
#define TSR00L (*(volatile unsigned char *)0xF01A0)
#define TSR01 (*(volatile unsigned short *)0xF01A2)
#define TSR01L (*(volatile unsigned char *)0xF01A2)
#define TSR02 (*(volatile unsigned short *)0xF01A4)
#define TSR02L (*(volatile unsigned char *)0xF01A4)
#define TSR03 (*(volatile unsigned short *)0xF01A6)
#define TSR03L (*(volatile unsigned char *)0xF01A6)
#define TSR04 (*(volatile unsigned short *)0xF01A8)
#define TSR04L (*(volatile unsigned char *)0xF01A8)
#define TSR05 (*(volatile unsigned short *)0xF01AA)
#define TSR05L (*(volatile unsigned char *)0xF01AA)
#define TSR06 (*(volatile unsigned short *)0xF01AC)
#define TSR06L (*(volatile unsigned char *)0xF01AC)
#define TSR07 (*(volatile unsigned short *)0xF01AE)
#define TSR07L (*(volatile unsigned char *)0xF01AE)
#define TE0 (*(volatile unsigned short *)0xF01B0)
#define TE0L (*(volatile union un_te0l *)0xF01B0).te0l
#define TE0L_bit (*(volatile union un_te0l *)0xF01B0).BIT
#define TS0 (*(volatile unsigned short *)0xF01B2)
#define TS0L (*(volatile union un_ts0l *)0xF01B2).ts0l
#define TS0L_bit (*(volatile union un_ts0l *)0xF01B2).BIT
#define TT0 (*(volatile unsigned short *)0xF01B4)
#define TT0L (*(volatile union un_tt0l *)0xF01B4).tt0l
#define TT0L_bit (*(volatile union un_tt0l *)0xF01B4).BIT
#define TPS0 (*(volatile unsigned short *)0xF01B6)
#define TO0 (*(volatile unsigned short *)0xF01B8)
#define TO0L (*(volatile unsigned char *)0xF01B8)
#define TOE0 (*(volatile unsigned short *)0xF01BA)
#define TOE0L (*(volatile union un_toe0l *)0xF01BA).toe0l
#define TOE0L_bit (*(volatile union un_toe0l *)0xF01BA).BIT
#define TOL0 (*(volatile unsigned short *)0xF01BC)
#define TOL0L (*(volatile unsigned char *)0xF01BC)
#define TOM0 (*(volatile unsigned short *)0xF01BE)
#define TOM0L (*(volatile unsigned char *)0xF01BE)
#define TCR10 (*(volatile unsigned short *)0xF01C0)
#define TCR11 (*(volatile unsigned short *)0xF01C2)
#define TCR12 (*(volatile unsigned short *)0xF01C4)
#define TCR13 (*(volatile unsigned short *)0xF01C6)
#define TCR14 (*(volatile unsigned short *)0xF01C8)
#define TCR15 (*(volatile unsigned short *)0xF01CA)
#define TCR16 (*(volatile unsigned short *)0xF01CC)
#define TCR17 (*(volatile unsigned short *)0xF01CE)
#define TMR10 (*(volatile unsigned short *)0xF01D0)
#define TMR11 (*(volatile unsigned short *)0xF01D2)
#define TMR12 (*(volatile unsigned short *)0xF01D4)
#define TMR13 (*(volatile unsigned short *)0xF01D6)
#define TMR14 (*(volatile unsigned short *)0xF01D8)
#define TMR15 (*(volatile unsigned short *)0xF01DA)
#define TMR16 (*(volatile unsigned short *)0xF01DC)
#define TMR17 (*(volatile unsigned short *)0xF01DE)
#define TSR10 (*(volatile unsigned short *)0xF01E0)
#define TSR10L (*(volatile unsigned char *)0xF01E0)
#define TSR11 (*(volatile unsigned short *)0xF01E2)
#define TSR11L (*(volatile unsigned char *)0xF01E2)
#define TSR12 (*(volatile unsigned short *)0xF01E4)
#define TSR12L (*(volatile unsigned char *)0xF01E4)
#define TSR13 (*(volatile unsigned short *)0xF01E6)
#define TSR13L (*(volatile unsigned char *)0xF01E6)
#define TSR14 (*(volatile unsigned short *)0xF01E8)
#define TSR14L (*(volatile unsigned char *)0xF01E8)
#define TSR15 (*(volatile unsigned short *)0xF01EA)
#define TSR15L (*(volatile unsigned char *)0xF01EA)
#define TSR16 (*(volatile unsigned short *)0xF01EC)
#define TSR16L (*(volatile unsigned char *)0xF01EC)
#define TSR17 (*(volatile unsigned short *)0xF01EE)
#define TSR17L (*(volatile unsigned char *)0xF01EE)
#define TE1 (*(volatile unsigned short *)0xF01F0)
#define TE1L (*(volatile union un_te1l *)0xF01F0).te1l
#define TE1L_bit (*(volatile union un_te1l *)0xF01F0).BIT
#define TS1 (*(volatile unsigned short *)0xF01F2)
#define TS1L (*(volatile union un_ts1l *)0xF01F2).ts1l
#define TS1L_bit (*(volatile union un_ts1l *)0xF01F2).BIT
#define TT1 (*(volatile unsigned short *)0xF01F4)
#define TT1L (*(volatile union un_tt1l *)0xF01F4).tt1l
#define TT1L_bit (*(volatile union un_tt1l *)0xF01F4).BIT
#define TPS1 (*(volatile unsigned short *)0xF01F6)
#define TO1 (*(volatile unsigned short *)0xF01F8)
#define TO1L (*(volatile unsigned char *)0xF01F8)
#define TOE1 (*(volatile unsigned short *)0xF01FA)
#define TOE1L (*(volatile union un_toe1l *)0xF01FA).toe1l
#define TOE1L_bit (*(volatile union un_toe1l *)0xF01FA).BIT
#define TOL1 (*(volatile unsigned short *)0xF01FC)
#define TOL1L (*(volatile unsigned char *)0xF01FC)
#define TOM1 (*(volatile unsigned short *)0xF01FE)
#define TOM1L (*(volatile unsigned char *)0xF01FE)
#define MIOTRM (*(volatile unsigned char *)0xF0212)
#define LIOTRM (*(volatile unsigned char *)0xF0213)
#define MOSCDIV (*(volatile unsigned char *)0xF0214)
#define WKUPMD (*(volatile union un_wkupmd *)0xF0215).wkupmd
#define WKUPMD_bit (*(volatile union un_wkupmd *)0xF0215).BIT
#define PSMCR (*(volatile union un_psmcr *)0xF0216).psmcr
#define PSMCR_bit (*(volatile union un_psmcr *)0xF0216).BIT
#define LVDFCLR (*(volatile union un_lvdfclr *)0xF0218).lvdfclr
#define LVDFCLR_bit (*(volatile union un_lvdfclr *)0xF0218).BIT
#define SEC (*(volatile unsigned char *)0xF0220)
#define MIN (*(volatile unsigned char *)0xF0221)
#define HOUR (*(volatile unsigned char *)0xF0222)
#define WEEK (*(volatile unsigned char *)0xF0223)
#define DAY (*(volatile unsigned char *)0xF0224)
#define MONTH (*(volatile unsigned char *)0xF0225)
#define YEAR (*(volatile unsigned char *)0xF0226)
#define SUBCUD (*(volatile unsigned char *)0xF0227)
#define ALARMWM (*(volatile unsigned char *)0xF0228)
#define ALARMWH (*(volatile unsigned char *)0xF0229)
#define ALARMWW (*(volatile unsigned char *)0xF022A)
#define RTCC0 (*(volatile union un_rtcc0 *)0xF022B).rtcc0
#define RTCC0_bit (*(volatile union un_rtcc0 *)0xF022B).BIT
#define RTCC1 (*(volatile union un_rtcc1 *)0xF022C).rtcc1
#define RTCC1_bit (*(volatile union un_rtcc1 *)0xF022C).BIT
#define IICCTL00 (*(volatile union un_iicctl00 *)0xF0230).iicctl00
#define IICCTL00_bit (*(volatile union un_iicctl00 *)0xF0230).BIT
#define IICCTL01 (*(volatile union un_iicctl01 *)0xF0231).iicctl01
#define IICCTL01_bit (*(volatile union un_iicctl01 *)0xF0231).BIT
#define IICWL0 (*(volatile unsigned char *)0xF0232)
#define IICWH0 (*(volatile unsigned char *)0xF0233)
#define SVA0 (*(volatile unsigned char *)0xF0234)
#define IICCTL10 (*(volatile union un_iicctl10 *)0xF0238).iicctl10
#define IICCTL10_bit (*(volatile union un_iicctl10 *)0xF0238).BIT
#define IICCTL11 (*(volatile union un_iicctl11 *)0xF0239).iicctl11
#define IICCTL11_bit (*(volatile union un_iicctl11 *)0xF0239).BIT
#define IICWL1 (*(volatile unsigned char *)0xF023A)
#define IICWH1 (*(volatile unsigned char *)0xF023B)
#define SVA1 (*(volatile unsigned char *)0xF023C)
#define PMCT0 (*(volatile union un_pmct0 *)0xF0260).pmct0
#define PMCT0_bit (*(volatile union un_pmct0 *)0xF0260).BIT
#define PMCT2 (*(volatile union un_pmct2 *)0xF0262).pmct2
#define PMCT2_bit (*(volatile union un_pmct2 *)0xF0262).BIT
#define PMCT3 (*(volatile union un_pmct3 *)0xF0263).pmct3
#define PMCT3_bit (*(volatile union un_pmct3 *)0xF0263).BIT
#define PMCT5 (*(volatile union un_pmct5 *)0xF0265).pmct5
#define PMCT5_bit (*(volatile union un_pmct5 *)0xF0265).BIT
#define PMCT6 (*(volatile union un_pmct6 *)0xF0266).pmct6
#define PMCT6_bit (*(volatile union un_pmct6 *)0xF0266).BIT
#define PMCT7 (*(volatile union un_pmct7 *)0xF0267).pmct7
#define PMCT7_bit (*(volatile union un_pmct7 *)0xF0267).BIT
#define PMCT15 (*(volatile union un_pmct15 *)0xF026F).pmct15
#define PMCT15_bit (*(volatile union un_pmct15 *)0xF026F).BIT
#define PMCE0 (*(volatile union un_pmce0 *)0xF0280).pmce0
#define PMCE0_bit (*(volatile union un_pmce0 *)0xF0280).BIT
#define PMCE1 (*(volatile union un_pmce1 *)0xF0281).pmce1
#define PMCE1_bit (*(volatile union un_pmce1 *)0xF0281).BIT
#define PMCE5 (*(volatile union un_pmce5 *)0xF0285).pmce5
#define PMCE5_bit (*(volatile union un_pmce5 *)0xF0285).BIT
#define PMCE6 (*(volatile union un_pmce6 *)0xF0286).pmce6
#define PMCE6_bit (*(volatile union un_pmce6 *)0xF0286).BIT
#define CCS0 (*(volatile unsigned char *)0xF02A0)
#define CCS4 (*(volatile unsigned char *)0xF02A4)
#define CCS5 (*(volatile unsigned char *)0xF02A5)
#define CCS6 (*(volatile unsigned char *)0xF02A6)
#define CCS7 (*(volatile unsigned char *)0xF02A7)
#define CCDE (*(volatile union un_ccde *)0xF02A8).ccde
#define CCDE_bit (*(volatile union un_ccde *)0xF02A8).BIT
#define PTDC (*(volatile union un_ptdc *)0xF02A9).ptdc
#define PTDC_bit (*(volatile union un_ptdc *)0xF02A9).BIT
#define PFOE0 (*(volatile union un_pfoe0 *)0xF02AA).pfoe0
#define PFOE0_bit (*(volatile union un_pfoe0 *)0xF02AA).BIT
#define PFOE1 (*(volatile union un_pfoe1 *)0xF02AB).pfoe1
#define PFOE1_bit (*(volatile union un_pfoe1 *)0xF02AB).BIT
#define PDIDIS0 (*(volatile union un_pdidis0 *)0xF02B0).pdidis0
#define PDIDIS0_bit (*(volatile union un_pdidis0 *)0xF02B0).BIT
#define PDIDIS1 (*(volatile union un_pdidis1 *)0xF02B1).pdidis1
#define PDIDIS1_bit (*(volatile union un_pdidis1 *)0xF02B1).BIT
#define PDIDIS3 (*(volatile union un_pdidis3 *)0xF02B3).pdidis3
#define PDIDIS3_bit (*(volatile union un_pdidis3 *)0xF02B3).BIT
#define PDIDIS4 (*(volatile union un_pdidis4 *)0xF02B4).pdidis4
#define PDIDIS4_bit (*(volatile union un_pdidis4 *)0xF02B4).BIT
#define PDIDIS5 (*(volatile union un_pdidis5 *)0xF02B5).pdidis5
#define PDIDIS5_bit (*(volatile union un_pdidis5 *)0xF02B5).BIT
#define PDIDIS7 (*(volatile union un_pdidis7 *)0xF02B7).pdidis7
#define PDIDIS7_bit (*(volatile union un_pdidis7 *)0xF02B7).BIT
#define PDIDIS8 (*(volatile union un_pdidis8 *)0xF02B8).pdidis8
#define PDIDIS8_bit (*(volatile union un_pdidis8 *)0xF02B8).BIT
#define PDIDIS9 (*(volatile union un_pdidis9 *)0xF02B9).pdidis9
#define PDIDIS9_bit (*(volatile union un_pdidis9 *)0xF02B9).BIT
#define PDIDIS12 (*(volatile union un_pdidis12 *)0xF02BC).pdidis12
#define PDIDIS12_bit (*(volatile union un_pdidis12 *)0xF02BC).BIT
#define PDIDIS13 (*(volatile union un_pdidis13 *)0xF02BD).pdidis13
#define PDIDIS13_bit (*(volatile union un_pdidis13 *)0xF02BD).BIT
#define PDIDIS14 (*(volatile union un_pdidis14 *)0xF02BE).pdidis14
#define PDIDIS14_bit (*(volatile union un_pdidis14 *)0xF02BE).BIT
#define FLPMC (*(volatile unsigned char *)0xF02C0)
#define FLARS (*(volatile union un_flars *)0xF02C1).flars
#define FLARS_bit (*(volatile union un_flars *)0xF02C1).BIT
#define FLAPL (*(volatile unsigned short *)0xF02C2)
#define FLAPH (*(volatile unsigned char *)0xF02C4)
#define FSSQ (*(volatile union un_fssq *)0xF02C5).fssq
#define FSSQ_bit (*(volatile union un_fssq *)0xF02C5).BIT
#define FLSEDL (*(volatile unsigned short *)0xF02C6)
#define FLSEDH (*(volatile unsigned char *)0xF02C8)
#define FLRST (*(volatile union un_flrst *)0xF02C9).flrst
#define FLRST_bit (*(volatile union un_flrst *)0xF02C9).BIT
#define FSASTL (*(volatile union un_fsastl *)0xF02CA).fsastl
#define FSASTL_bit (*(volatile union un_fsastl *)0xF02CA).BIT
#define FSASTH (*(volatile union un_fsasth *)0xF02CB).fsasth
#define FSASTH_bit (*(volatile union un_fsasth *)0xF02CB).BIT
#define FLWL (*(volatile unsigned short *)0xF02CC)
#define FLWH (*(volatile unsigned short *)0xF02CE)
#define DTCBAR (*(volatile unsigned char *)0xF02E0)
#define DTCEN0 (*(volatile union un_dtcen0 *)0xF02E8).dtcen0
#define DTCEN0_bit (*(volatile union un_dtcen0 *)0xF02E8).BIT
#define DTCEN1 (*(volatile union un_dtcen1 *)0xF02E9).dtcen1
#define DTCEN1_bit (*(volatile union un_dtcen1 *)0xF02E9).BIT
#define DTCEN2 (*(volatile union un_dtcen2 *)0xF02EA).dtcen2
#define DTCEN2_bit (*(volatile union un_dtcen2 *)0xF02EA).BIT
#define DTCEN3 (*(volatile union un_dtcen3 *)0xF02EB).dtcen3
#define DTCEN3_bit (*(volatile union un_dtcen3 *)0xF02EB).BIT
#define DTCEN4 (*(volatile union un_dtcen4 *)0xF02EC).dtcen4
#define DTCEN4_bit (*(volatile union un_dtcen4 *)0xF02EC).BIT
#define CRC0CTL (*(volatile union un_crc0ctl *)0xF02F0).crc0ctl
#define CRC0CTL_bit (*(volatile union un_crc0ctl *)0xF02F0).BIT
#define PGCRCL (*(volatile unsigned short *)0xF02F2)
#define CRCD (*(volatile unsigned short *)0xF02FA)
#define TXBA0 (*(volatile unsigned char *)0xF0300)
#define RXBA0 (*(volatile unsigned char *)0xF0301)
#define ASIMA00 (*(volatile union un_asima00 *)0xF0302).asima00
#define ASIMA00_bit (*(volatile union un_asima00 *)0xF0302).BIT
#define ASIMA01 (*(volatile union un_asima01 *)0xF0303).asima01
#define ASIMA01_bit (*(volatile union un_asima01 *)0xF0303).BIT
#define BRGCA0 (*(volatile unsigned char *)0xF0304)
#define ASISA0 (*(volatile unsigned char *)0xF0305)
#define ASCTA0 (*(volatile union un_ascta0 *)0xF0306).ascta0
#define ASCTA0_bit (*(volatile union un_ascta0 *)0xF0306).BIT
#define TXBA1 (*(volatile unsigned char *)0xF0308)
#define RXBA1 (*(volatile unsigned char *)0xF0309)
#define ASIMA10 (*(volatile union un_asima10 *)0xF030A).asima10
#define ASIMA10_bit (*(volatile union un_asima10 *)0xF030A).BIT
#define ASIMA11 (*(volatile union un_asima11 *)0xF030B).asima11
#define ASIMA11_bit (*(volatile union un_asima11 *)0xF030B).BIT
#define BRGCA1 (*(volatile unsigned char *)0xF030C)
#define ASISA1 (*(volatile unsigned char *)0xF030D)
#define ASCTA1 (*(volatile union un_ascta1 *)0xF030E).ascta1
#define ASCTA1_bit (*(volatile union un_ascta1 *)0xF030E).BIT
#define UTA0CK (*(volatile union un_uta0ck *)0xF0310).uta0ck
#define UTA0CK_bit (*(volatile union un_uta0ck *)0xF0310).BIT
#define UTA1CK (*(volatile union un_uta1ck *)0xF0311).uta1ck
#define UTA1CK_bit (*(volatile union un_uta1ck *)0xF0311).BIT
#define DACS0 (*(volatile unsigned char *)0xF0330)
#define DACS1 (*(volatile unsigned char *)0xF0331)
#define DAM (*(volatile union un_dam *)0xF0332).dam
#define DAM_bit (*(volatile union un_dam *)0xF0332).BIT
#define COMPMDR (*(volatile union un_compmdr *)0xF0340).compmdr
#define COMPMDR_bit (*(volatile union un_compmdr *)0xF0340).BIT
#define COMPFIR (*(volatile union un_compfir *)0xF0341).compfir
#define COMPFIR_bit (*(volatile union un_compfir *)0xF0341).BIT
#define COMPOCR (*(volatile union un_compocr *)0xF0342).compocr
#define COMPOCR_bit (*(volatile union un_compocr *)0xF0342).BIT
#define ITLCMP00 (*(volatile unsigned short *)0xF0360)
#define ITLCMP000 (*(volatile unsigned char *)0xF0360)
#define ITLCMP001 (*(volatile unsigned char *)0xF0361)
#define ITLCMP01 (*(volatile unsigned short *)0xF0362)
#define ITLCMP012 (*(volatile unsigned char *)0xF0362)
#define ITLCMP013 (*(volatile unsigned char *)0xF0363)
#define ITLCAP00 (*(volatile unsigned short *)0xF0364)
#define ITLCTL0 (*(volatile union un_itlctl0 *)0xF0366).itlctl0
#define ITLCTL0_bit (*(volatile union un_itlctl0 *)0xF0366).BIT
#define ITLCSEL0 (*(volatile unsigned char *)0xF0367)
#define ITLFDIV00 (*(volatile unsigned char *)0xF0368)
#define ITLFDIV01 (*(volatile unsigned char *)0xF0369)
#define ITLCC0 (*(volatile union un_itlcc0 *)0xF036A).itlcc0
#define ITLCC0_bit (*(volatile union un_itlcc0 *)0xF036A).BIT
#define ITLS0 (*(volatile unsigned char *)0xF036B)
#define ITLMKF0 (*(volatile unsigned char *)0xF036C)
#define SMSI0 (*(volatile unsigned short *)0xF0380)
#define SMSI1 (*(volatile unsigned short *)0xF0382)
#define SMSI2 (*(volatile unsigned short *)0xF0384)
#define SMSI3 (*(volatile unsigned short *)0xF0386)
#define SMSI4 (*(volatile unsigned short *)0xF0388)
#define SMSI5 (*(volatile unsigned short *)0xF038A)
#define SMSI6 (*(volatile unsigned short *)0xF038C)
#define SMSI7 (*(volatile unsigned short *)0xF038E)
#define SMSI8 (*(volatile unsigned short *)0xF0390)
#define SMSI9 (*(volatile unsigned short *)0xF0392)
#define SMSI10 (*(volatile unsigned short *)0xF0394)
#define SMSI11 (*(volatile unsigned short *)0xF0396)
#define SMSI12 (*(volatile unsigned short *)0xF0398)
#define SMSI13 (*(volatile unsigned short *)0xF039A)
#define SMSI14 (*(volatile unsigned short *)0xF039C)
#define SMSI15 (*(volatile unsigned short *)0xF039E)
#define SMSI16 (*(volatile unsigned short *)0xF03A0)
#define SMSI17 (*(volatile unsigned short *)0xF03A2)
#define SMSI18 (*(volatile unsigned short *)0xF03A4)
#define SMSI19 (*(volatile unsigned short *)0xF03A6)
#define SMSI20 (*(volatile unsigned short *)0xF03A8)
#define SMSI21 (*(volatile unsigned short *)0xF03AA)
#define SMSI22 (*(volatile unsigned short *)0xF03AC)
#define SMSI23 (*(volatile unsigned short *)0xF03AE)
#define SMSI24 (*(volatile unsigned short *)0xF03B0)
#define SMSI25 (*(volatile unsigned short *)0xF03B2)
#define SMSI26 (*(volatile unsigned short *)0xF03B4)
#define SMSI27 (*(volatile unsigned short *)0xF03B6)
#define SMSI28 (*(volatile unsigned short *)0xF03B8)
#define SMSI29 (*(volatile unsigned short *)0xF03BA)
#define SMSI30 (*(volatile unsigned short *)0xF03BC)
#define SMSI31 (*(volatile unsigned short *)0xF03BE)
#define SMSG0 (*(volatile unsigned short *)0xF03C0)
#define SMSG1 (*(volatile unsigned short *)0xF03C2)
#define SMSG2 (*(volatile unsigned short *)0xF03C4)
#define SMSG3 (*(volatile unsigned short *)0xF03C6)
#define SMSG4 (*(volatile unsigned short *)0xF03C8)
#define SMSG5 (*(volatile unsigned short *)0xF03CA)
#define SMSG6 (*(volatile unsigned short *)0xF03CC)
#define SMSG7 (*(volatile unsigned short *)0xF03CE)
#define SMSG8 (*(volatile unsigned short *)0xF03D0)
#define SMSG9 (*(volatile unsigned short *)0xF03D2)
#define SMSG10 (*(volatile unsigned short *)0xF03D4)
#define SMSG11 (*(volatile unsigned short *)0xF03D6)
#define SMSG12 (*(volatile unsigned short *)0xF03D8)
#define SMSG13 (*(volatile unsigned short *)0xF03DA)
#define SMSG14 (*(volatile unsigned short *)0xF03DC)
#define SMSG15 (*(volatile unsigned short *)0xF03DE)
#define SMSC (*(volatile union un_smsc *)0xF03E0).smsc
#define SMSC_bit (*(volatile union un_smsc *)0xF03E0).BIT
#define SMSS (*(volatile union un_smss *)0xF03E1).smss
#define SMSS_bit (*(volatile union un_smss *)0xF03E1).BIT
#define FLSIVC0 (*(volatile unsigned short *)0xF0480)
#define FLSIVC1 (*(volatile unsigned short *)0xF0482)
#define GFLASH0 (*(volatile unsigned short *)0xF0488)
#define GFLASH1 (*(volatile unsigned short *)0xF048A)
#define GFLASH2 (*(volatile unsigned short *)0xF048C)
#define GIAWCTL (*(volatile unsigned short *)0xF048E)
#define CTSUCRAL (*(volatile unsigned short *)0xF0500)
#define CTSUCR0 (*(volatile unsigned char *)0xF0500)
#define CTSUCR1 (*(volatile unsigned char *)0xF0501)
#define CTSUCRAH (*(volatile unsigned short *)0xF0502)
#define CTSUCR2 (*(volatile unsigned char *)0xF0502)
#define CTSUCR3 (*(volatile unsigned char *)0xF0503)
#define CTSUCRBL (*(volatile unsigned short *)0xF0504)
#define CTSUSDPRS (*(volatile unsigned char *)0xF0504)
#define CTSUSST (*(volatile unsigned char *)0xF0505)
#define CTSUCRBH (*(volatile unsigned short *)0xF0506)
#define CTSUDCLKC (*(volatile unsigned char *)0xF0507)
#define CTSUMCHL (*(volatile unsigned short *)0xF0508)
#define CTSUMCH0 (*(volatile unsigned char *)0xF0508)
#define CTSUMCH1 (*(volatile unsigned char *)0xF0509)
#define CTSUMCHH (*(volatile unsigned short *)0xF050A)
#define CTSUMFAF (*(volatile unsigned char *)0xF050A)
#define CTSUCHACAL (*(volatile unsigned short *)0xF050C)
#define CTSUCHAC0 (*(volatile unsigned char *)0xF050C)
#define CTSUCHAC1 (*(volatile unsigned char *)0xF050D)
#define CTSUCHACAH (*(volatile unsigned short *)0xF050E)
#define CTSUCHAC2 (*(volatile unsigned char *)0xF050E)
#define CTSUCHAC3 (*(volatile unsigned char *)0xF050F)
#define CTSUCHACBL (*(volatile unsigned short *)0xF0510)
#define CTSUCHAC4 (*(volatile unsigned char *)0xF0510)
#define CTSUCHAC5 (*(volatile unsigned char *)0xF0511)
#define CTSUCHACBH (*(volatile unsigned short *)0xF0512)
#define CTSUCHAC6 (*(volatile unsigned char *)0xF0512)
#define CTSUCHAC7 (*(volatile unsigned char *)0xF0513)
#define CTSUCHTRCAL (*(volatile unsigned short *)0xF0514)
#define CTSUCHTRC0 (*(volatile unsigned char *)0xF0514)
#define CTSUCHTRC1 (*(volatile unsigned char *)0xF0515)
#define CTSUCHTRCAH (*(volatile unsigned short *)0xF0516)
#define CTSUCHTRC2 (*(volatile unsigned char *)0xF0516)
#define CTSUCHTRC3 (*(volatile unsigned char *)0xF0517)
#define CTSUCHTRCBL (*(volatile unsigned short *)0xF0518)
#define CTSUCHTRC4 (*(volatile unsigned char *)0xF0518)
#define CTSUCHTRC5 (*(volatile unsigned char *)0xF0519)
#define CTSUCHTRCBH (*(volatile unsigned short *)0xF051A)
#define CTSUCHTRC6 (*(volatile unsigned char *)0xF051A)
#define CTSUCHTRC7 (*(volatile unsigned char *)0xF051B)
#define CTSUSRL (*(volatile unsigned short *)0xF051C)
#define CTSUST1 (*(volatile unsigned char *)0xF051C)
#define CTSUST (*(volatile unsigned char *)0xF051D)
#define CTSUSRH (*(volatile unsigned short *)0xF051E)
#define CTSUST2 (*(volatile unsigned char *)0xF051E)
#define CTSUSO0 (*(volatile unsigned short *)0xF0520)
#define CTSUSO1 (*(volatile unsigned short *)0xF0522)
#define CTSUSC (*(volatile unsigned short *)0xF0524)
#define CTSUUC (*(volatile unsigned short *)0xF0526)
#define CTSUDBGR0 (*(volatile unsigned short *)0xF0528)
#define CTSUDBGR1 (*(volatile unsigned short *)0xF052A)
#define CTSUSUCLK0 (*(volatile unsigned short *)0xF052C)
#define CTSUSUCLK1 (*(volatile unsigned short *)0xF052E)
#define CTSUSUCLK2 (*(volatile unsigned short *)0xF0530)
#define CTSUSUCLK3 (*(volatile unsigned short *)0xF0532)
#define TRNGSDR (*(volatile unsigned char *)0xF0540)
#define TRNGSCR0 (*(volatile unsigned char *)0xF0542)
#define CTSUTRIM0 (*(volatile unsigned short *)0xF0600)
#define RTRIM (*(volatile unsigned char *)0xF0600)
#define DACTRIM (*(volatile unsigned char *)0xF0601)
#define CTSUTRIM1 (*(volatile unsigned short *)0xF0602)
#define SUADJD (*(volatile unsigned char *)0xF0602)
#define TRESULT4 (*(volatile unsigned char *)0xF0603)
#define CTSUTRIM2 (*(volatile unsigned short *)0xF0604)
#define TRESULT0 (*(volatile unsigned char *)0xF0604)
#define TRESULT1 (*(volatile unsigned char *)0xF0605)
#define CTSUTRIM3 (*(volatile unsigned short *)0xF0606)
#define TRESULT2 (*(volatile unsigned char *)0xF0606)
#define TRESULT3 (*(volatile unsigned char *)0xF0607)
#define REMCON0 (*(volatile union un_remcon0 *)0xF0640).remcon0
#define REMCON0_bit (*(volatile union un_remcon0 *)0xF0640).BIT
#define REMCON1 (*(volatile union un_remcon1 *)0xF0641).remcon1
#define REMCON1_bit (*(volatile union un_remcon1 *)0xF0641).BIT
#define REMSTS (*(volatile union un_remsts *)0xF0642).remsts
#define REMSTS_bit (*(volatile union un_remsts *)0xF0642).BIT
#define REMINT (*(volatile union un_remint *)0xF0643).remint
#define REMINT_bit (*(volatile union un_remint *)0xF0643).BIT
#define REMCPC (*(volatile unsigned char *)0xF0645)
#define REMCPD (*(volatile unsigned short *)0xF0646)
#define HDPMIN (*(volatile unsigned short *)0xF0648)
#define HDPMAX (*(volatile unsigned short *)0xF064A)
#define D0PMIN (*(volatile unsigned char *)0xF064C)
#define D0PMAX (*(volatile unsigned char *)0xF064D)
#define D1PMIN (*(volatile unsigned char *)0xF064E)
#define D1PMAX (*(volatile unsigned char *)0xF064F)
#define SDPMIN (*(volatile unsigned short *)0xF0650)
#define SDPMAX (*(volatile unsigned short *)0xF0652)
#define REMPE (*(volatile unsigned short *)0xF0654)
#define REMSTC (*(volatile union un_remstc *)0xF0656).remstc
#define REMSTC_bit (*(volatile union un_remstc *)0xF0656).BIT
#define REMRBIT (*(volatile union un_remrbit *)0xF0657).remrbit
#define REMRBIT_bit (*(volatile union un_remrbit *)0xF0657).BIT
#define REMDAT0 (*(volatile union un_remdat0 *)0xF0658).remdat0
#define REMDAT0_bit (*(volatile union un_remdat0 *)0xF0658).BIT
#define REMDAT1 (*(volatile unsigned char *)0xF0659)
#define REMDAT2 (*(volatile unsigned char *)0xF065A)
#define REMDAT3 (*(volatile unsigned char *)0xF065B)
#define REMDAT4 (*(volatile unsigned char *)0xF065C)
#define REMDAT5 (*(volatile unsigned char *)0xF065D)
#define REMDAT6 (*(volatile unsigned char *)0xF065E)
#define REMDAT7 (*(volatile unsigned char *)0xF065F)
#define REMTIM (*(volatile unsigned short *)0xF0660)
#define ELISEL0 (*(volatile unsigned char *)0xF0680)
#define ELISEL1 (*(volatile unsigned char *)0xF0681)
#define ELISEL2 (*(volatile unsigned char *)0xF0682)
#define ELISEL3 (*(volatile unsigned char *)0xF0683)
#define ELISEL4 (*(volatile unsigned char *)0xF0684)
#define ELISEL5 (*(volatile unsigned char *)0xF0685)
#define ELISEL6 (*(volatile unsigned char *)0xF0686)
#define ELISEL7 (*(volatile unsigned char *)0xF0687)
#define ELISEL8 (*(volatile unsigned char *)0xF0688)
#define ELISEL9 (*(volatile unsigned char *)0xF0689)
#define ELISEL10 (*(volatile unsigned char *)0xF068A)
#define ELISEL11 (*(volatile unsigned char *)0xF068B)
#define ELL1SEL0 (*(volatile unsigned char *)0xF0690)
#define ELL1SEL1 (*(volatile unsigned char *)0xF0691)
#define ELL1SEL2 (*(volatile unsigned char *)0xF0692)
#define ELL1SEL3 (*(volatile unsigned char *)0xF0693)
#define ELL1SEL4 (*(volatile unsigned char *)0xF0694)
#define ELL1SEL5 (*(volatile unsigned char *)0xF0695)
#define ELL1SEL6 (*(volatile unsigned char *)0xF0696)
#define ELL1CTL (*(volatile unsigned char *)0xF0697)
#define ELL1LNK0 (*(volatile unsigned char *)0xF0698)
#define ELL1LNK1 (*(volatile unsigned char *)0xF0699)
#define ELL1LNK2 (*(volatile unsigned char *)0xF069A)
#define ELL1LNK3 (*(volatile unsigned char *)0xF069B)
#define ELL1LNK4 (*(volatile unsigned char *)0xF069C)
#define ELL1LNK5 (*(volatile unsigned char *)0xF069D)
#define ELL1LNK6 (*(volatile unsigned char *)0xF069E)
#define ELL2SEL0 (*(volatile unsigned char *)0xF06A0)
#define ELL2SEL1 (*(volatile unsigned char *)0xF06A1)
#define ELL2SEL2 (*(volatile unsigned char *)0xF06A2)
#define ELL2SEL3 (*(volatile unsigned char *)0xF06A3)
#define ELL2SEL4 (*(volatile unsigned char *)0xF06A4)
#define ELL2SEL5 (*(volatile unsigned char *)0xF06A5)
#define ELL2SEL6 (*(volatile unsigned char *)0xF06A6)
#define ELL2CTL (*(volatile unsigned char *)0xF06A7)
#define ELL2LNK0 (*(volatile unsigned char *)0xF06A8)
#define ELL2LNK1 (*(volatile unsigned char *)0xF06A9)
#define ELL2LNK2 (*(volatile unsigned char *)0xF06AA)
#define ELL2LNK3 (*(volatile unsigned char *)0xF06AB)
#define ELL2LNK4 (*(volatile unsigned char *)0xF06AC)
#define ELL2LNK5 (*(volatile unsigned char *)0xF06AD)
#define ELL2LNK6 (*(volatile unsigned char *)0xF06AE)
#define ELL3SEL0 (*(volatile unsigned char *)0xF06B0)
#define ELL3SEL1 (*(volatile unsigned char *)0xF06B1)
#define ELL3SEL2 (*(volatile unsigned char *)0xF06B2)
#define ELL3SEL3 (*(volatile unsigned char *)0xF06B3)
#define ELL3SEL4 (*(volatile unsigned char *)0xF06B4)
#define ELL3SEL5 (*(volatile unsigned char *)0xF06B5)
#define ELL3SEL6 (*(volatile unsigned char *)0xF06B6)
#define ELL3CTL (*(volatile unsigned char *)0xF06B7)
#define ELL3LNK0 (*(volatile unsigned char *)0xF06B8)
#define ELL3LNK1 (*(volatile unsigned char *)0xF06B9)
#define ELL3LNK2 (*(volatile unsigned char *)0xF06BA)
#define ELL3LNK3 (*(volatile unsigned char *)0xF06BB)
#define ELL3LNK4 (*(volatile unsigned char *)0xF06BC)
#define ELL3LNK5 (*(volatile unsigned char *)0xF06BD)
#define ELL3LNK6 (*(volatile unsigned char *)0xF06BE)
#define ELOSEL0 (*(volatile unsigned char *)0xF06C0)
#define ELOSEL1 (*(volatile unsigned char *)0xF06C1)
#define ELOSEL2 (*(volatile unsigned char *)0xF06C2)
#define ELOSEL3 (*(volatile unsigned char *)0xF06C3)
#define ELOSEL4 (*(volatile unsigned char *)0xF06C4)
#define ELOSEL5 (*(volatile unsigned char *)0xF06C5)
#define ELOSEL6 (*(volatile unsigned char *)0xF06C6)
#define ELOSEL7 (*(volatile unsigned char *)0xF06C7)
#define ELOENCTL (*(volatile unsigned char *)0xF06C8)
#define ELOMONI (*(volatile unsigned char *)0xF06C9)

/*
 Sfr bits
 */
#define ADTYP0 ADM2_bit.no0
#define ADTYP1 ADM2_bit.no1
#define AWC ADM2_bit.no2
#define ADRCK ADM2_bit.no3
#define ULBS0 ULBS_bit.no0
#define ULBS1 ULBS_bit.no1
#define ULBS2 ULBS_bit.no2
#define ULBS3 ULBS_bit.no3
#define ULBS4 ULBS_bit.no4
#define ULBS5 ULBS_bit.no5
#define DFLEN DFLCTL_bit.no0
#define MODE0 FLMODE_bit.no6
#define MODE1 FLMODE_bit.no7
#define FLMWEN FLMWRP_bit.no0
#define ESQST FSSE_bit.no7
#define TAU0EN PER0_bit.no0
#define TAU1EN PER0_bit.no1
#define SAU0EN PER0_bit.no2
#define SAU1EN PER0_bit.no3
#define IICA0EN PER0_bit.no4
#define ADCEN PER0_bit.no5
#define IICA1EN PER0_bit.no6
#define RTCWEN PER0_bit.no7
#define TAU0RES PRR0_bit.no0
#define TAU1RES PRR0_bit.no1
#define SAU0RES PRR0_bit.no2
#define SAU1RES PRR0_bit.no3
#define IICA0RES PRR0_bit.no4
#define ADCRES PRR0_bit.no5
#define IICA1RES PRR0_bit.no6
#define HIPREC OSMC_bit.no0
#define WUTMMCK0 OSMC_bit.no4
#define RTCLPC OSMC_bit.no7
#define RPEF RPECTL_bit.no0
#define RPERDIS RPECTL_bit.no7
#define PORF PORSR_bit.no0
#define CTSUEN PER1_bit.no0
#define REMCEN PER1_bit.no1
#define UTAEN PER1_bit.no2
#define DTCEN PER1_bit.no3
#define TML32EN PER1_bit.no4
#define CMPEN PER1_bit.no5
#define SMSEN PER1_bit.no6
#define DACEN PER1_bit.no7
#define CTSURES PRR1_bit.no0
#define REMCRES PRR1_bit.no1
#define TML32RES PRR1_bit.no4
#define CMPRES PRR1_bit.no5
#define SMSRES PRR1_bit.no6
#define DACRES PRR1_bit.no7
#define FWKUP WKUPMD_bit.no0
#define RAMSDS PSMCR_bit.no0
#define RAMSDMD PSMCR_bit.no1
#define DLVD0FCLR LVDFCLR_bit.no2
#define DLVD1FCLR LVDFCLR_bit.no3
#define RTC128EN RTCC0_bit.no4
#define RCLOE1 RTCC0_bit.no5
#define RTCE RTCC0_bit.no7
#define RWAIT RTCC1_bit.no0
#define RWST RTCC1_bit.no1
#define RIFG RTCC1_bit.no3
#define WAFG RTCC1_bit.no4
#define WALIE RTCC1_bit.no6
#define WALE RTCC1_bit.no7
#define SPT0 IICCTL00_bit.no0
#define STT0 IICCTL00_bit.no1
#define ACKE0 IICCTL00_bit.no2
#define WTIM0 IICCTL00_bit.no3
#define SPIE0 IICCTL00_bit.no4
#define WREL0 IICCTL00_bit.no5
#define LREL0 IICCTL00_bit.no6
#define IICE0 IICCTL00_bit.no7
#define PRS0 IICCTL01_bit.no0
#define DFC0 IICCTL01_bit.no2
#define SMC0 IICCTL01_bit.no3
#define DAD0 IICCTL01_bit.no4
#define CLD0 IICCTL01_bit.no5
#define SVADIS0 IICCTL01_bit.no6
#define WUP0 IICCTL01_bit.no7
#define SPT1 IICCTL10_bit.no0
#define STT1 IICCTL10_bit.no1
#define ACKE1 IICCTL10_bit.no2
#define WTIM1 IICCTL10_bit.no3
#define SPIE1 IICCTL10_bit.no4
#define WREL1 IICCTL10_bit.no5
#define LREL1 IICCTL10_bit.no6
#define IICE1 IICCTL10_bit.no7
#define PRS1 IICCTL11_bit.no0
#define DFC1 IICCTL11_bit.no2
#define SMC1 IICCTL11_bit.no3
#define DAD1 IICCTL11_bit.no4
#define CLD1 IICCTL11_bit.no5
#define SVADIS1 IICCTL11_bit.no6
#define WUP1 IICCTL11_bit.no7
#define FSSTP FSSQ_bit.no6
#define SQST FSSQ_bit.no7
#define CRC0EN CRC0CTL_bit.no7
#define ISRMA0 ASIMA00_bit.no0
#define ISSMA0 ASIMA00_bit.no1
#define RXEA0 ASIMA00_bit.no5
#define TXEA0 ASIMA00_bit.no6
#define UARTAEN0 ASIMA00_bit.no7
#define OVECTA0 ASCTA0_bit.no0
#define FECTA0 ASCTA0_bit.no1
#define PECTA0 ASCTA0_bit.no2
#define ISRMA1 ASIMA10_bit.no0
#define ISSMA1 ASIMA10_bit.no1
#define RXEA1 ASIMA10_bit.no5
#define TXEA1 ASIMA10_bit.no6
#define UARTAEN1 ASIMA10_bit.no7
#define OVECTA1 ASCTA1_bit.no0
#define FECTA1 ASCTA1_bit.no1
#define PECTA1 ASCTA1_bit.no2
#define DACE0 DAM_bit.no4
#define DACE1 DAM_bit.no5
#define C0ENB COMPMDR_bit.no0
#define C1ENB COMPMDR_bit.no4
#define C0IE COMPOCR_bit.no0
#define C0OE COMPOCR_bit.no1
#define C1IE COMPOCR_bit.no4
#define C1OE COMPOCR_bit.no5
#define ITLEN00 ITLCTL0_bit.no0
#define ITLEN01 ITLCTL0_bit.no1
#define ITLEN02 ITLCTL0_bit.no2
#define ITLEN03 ITLCTL0_bit.no3
#define CAPR0 ITLCC0_bit.no4
#define CAPF0CR ITLCC0_bit.no6
#define LONGWAIT SMSC_bit.no4
#define SMSTRGWAIT SMSC_bit.no5
#define SMSSTOP SMSC_bit.no6
#define SMSSTART SMSC_bit.no7
#define SMSSTAT SMSS_bit.no7
#define ENFLG REMCON0_bit.no0
#define INFLG REMCON0_bit.no3
#define EN REMCON1_bit.no2
#define INTMD REMCON1_bit.no3
#define CPFLG REMSTS_bit.no0
#define REFLG REMSTS_bit.no1
#define DRFLG REMSTS_bit.no2
#define BFULFLG REMSTS_bit.no3
#define HDFLG REMSTS_bit.no4
#define D0FLG REMSTS_bit.no5
#define D1FLG REMSTS_bit.no6
#define SDFLG REMSTS_bit.no7
#define CPINT REMINT_bit.no0
#define REINT REMINT_bit.no1
#define DRINT REMINT_bit.no2
#define BFULINT REMINT_bit.no3
#define HDINT REMINT_bit.no4
#define DINT REMINT_bit.no5
#define SDINT REMINT_bit.no7
#define SNZON REMSTC_bit.no0
#define RBIT0 REMRBIT_bit.no0
#define DAT00 REMDAT0_bit.no0

/*
 Interrupt vector addresses
 */
#endif
