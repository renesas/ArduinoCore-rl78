/*""FILE COMMENT""*******************************************************************
* File Name     : r_mtl_com2.h
* Version       : 4.05R00B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description  : Common header file
*************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 28.01.2003 1.00R01 First Release
*              : 02.12.2003 2.00R01
*              : 03.03.2004 2.00R02
*              : 02.12.2004 3.00R01
*              : 20.06.2006 3.10R01
*              : 15.09.2006 4.00R01
*              : 19.01.2007 4.01R00
*              : 06.02.2007 4.02R00
*              : 31.10.2007 4.03R00
*              : 22.06.2010 4.05R00
*              : 25.06.2010 4.05R00A
*              : 02.03.2012 4.05R00B
*""FILE COMMENT END""***************************************************************/
#ifndef __MTL_COM2_H__
#define __MTL_COM2_H__
/*----------------------------------------------------------------------------------------------*
 Definitions
 *----------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
#define STATIC   static         /* For release      */
/* #define STATIC     */        /* For debug      */

#ifndef NULL
#define NULL 0
#endif

/*----------------------------------------------------------------------------------------------*
 Macros
 *----------------------------------------------------------------------------------------------*/
#define ARRAYSIZE(n) (sizeof(n)/sizeof(*n))

#define R_mtl_memcmp(s1, s2, n)      ( R_mtl_memcmp2((void *)(s1), (void *)(s2), (natural_uint_t)(n)) )
#define R_mtl_memmove(s1, s2, n)     ( R_mtl_memmove2((void *)(s1), (void *)(s2), (natural_uint_t)(n)) )
#define R_mtl_memcpy(s1, s2, n)      ( R_mtl_memcpy2((void *)(s1), (void *)(s2), (natural_uint_t)(n)) )
#define R_mtl_memcpy_w(s1, s2, n)    ( R_mtl_memcpy_w2((void *)(s1), (void *)(s2), (natural_uint_t)(n)) )
#define R_mtl_memset(s, c, n)        ( R_mtl_memset2((void *)(s), (natural_int_t )(c), (natural_uint_t)(n)) )
#define R_mtl_strcat(s1, s2)         ( R_mtl_strcat2((char *)(s1), (char *)(s2)) )
#define R_mtl_strcmp(s1, s2)         ( R_mtl_strcmp2((char *)(s1), (char *)(s2)) )
#define R_mtl_strcpy(s1, s2)         ( R_mtl_strcpy2((char *)(s1), (char *)(s2)) )
#define R_mtl_strlen(s)              ( R_mtl_strlen2((char *)(s)) )

#define R_mtl_ShortPeek(adr)         ( R_mtl_ShortPeek2((void *)(adr)) )
#define R_mtl_LongPeek(adr)          ( R_mtl_LongPeek2((void *)(adr)) )
#define R_mtl_ShortPoke(adr, dat)    ( R_mtl_ShortPoke2((void *)(adr), (uint16_t)(dat)) )
#define R_mtl_LongPoke(adr, dat)     ( R_mtl_LongPoke2((void *)(adr), (uint32_t)(dat)) )

#define R_mtl_wait_lp(time)          ( R_mtl_wait_lp2((natural_uint_t)(time)) )

/*----------------------------------------------------------------------------------------------*
 Prototypes
 *----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/* Replace standard functions.                 */
natural_int_t  R_mtl_memcmp2(void *s1, void *s2, natural_uint_t n);
void           *R_mtl_memmove2(void *s1, void *s2, natural_uint_t n);
void           *R_mtl_memcpy2(void *s1, void *s2, natural_uint_t n);
void           *R_mtl_memcpy_w2(void *s1, void *s2, natural_uint_t n);/* memcpy2() for word unit  */
void           *R_mtl_memset2(void *s, natural_int_t c, natural_uint_t n);
char           *R_mtl_strcat2(char *s1, char *s2);
int32_t        R_mtl_strcmp2(char *s1, char *s2);
char           *R_mtl_strcpy2(char *s1, char *s2);
uint16_t       R_mtl_strlen2(char *s);

/*----------------------------------------------------------------------------------------------*/
/* Routine for each system.                  */
uint16_t R_mtl_ShortPeek2(void *adr);
uint32_t R_mtl_LongPeek2(void *adr);
void     R_mtl_ShortPoke2(void *adr, uint16_t dat);
void     R_mtl_LongPoke2(void *adr, uint32_t dat);

/*----------------------------------------------------------------------------------------------*/
/* loop timer  */
void     R_mtl_wait_lp2(natural_uint_t time);

/************************************************************************************************
 * Sub-module for debugging
 ************************************************************************************************/
/* Definition of LOG buffer size value */

#define MTL_LOG_MAX  8        /* LOG buffer size      */

#define R_mtl_Log(FLG, VAL, FID, LINE)  R_mtl_Log2((((uint32_t )(FLG))     << (4 + 6 + 13 + 8)) \
        | (((uint32_t )(FID))  << (        13 + 8)) \
        | (((uint32_t )(LINE)) <<               8)  \
        | ( (uint8_t  )(VAL)))
uint32_t R_mtl_Log2(uint32_t data);
void R_mtl_LogClear(void);

#endif /* #ifndef __MTL_COM2_H__ */