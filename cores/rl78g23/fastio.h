/*
  fastio.h - that provides fastDigitalWrite() and fastDigitalRead().
  Copyright (c) 2015 Nozomu Fujita. All right reserved.

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
*/
#ifndef _FASTIO_H_
#define _FASTIO_H_

#include <pintable.h>

/**
 * HIGHまたはLOWを、指定したピンに出力します。
 *
 * 指定したピンが pinMode()関数で予めOUTPUTに設定されている必要があります。
 * HIGH = 5V
 * LOW  = 0V (GND) 
 *
 * @param[in] pin   ピン番号を指定します。
 * @param[in] value HIGHかLOWを指定します。
 *
 * @return なし
 *
 * 引数には定数を使用することを想定しています。
 * 引数に変数を使用した場合にはコードサイズの肥大化が生じ、速度も遅くなるので
 * digitalWrite() のどちらを使用するかはよく検討しましょう。
 ***************************************************************************/
#define fastDigitalWrite(pin, value) \
do { \
    if (__builtin_constant_p(pin)) { \
        if ((pin) < NUM_DIGITAL_PINS) { \
            if (__builtin_constant_p((value))) { \
                if ((value)) { \
                    __asm __volatile( \
                        "\n" \
                        "        /* %%0 = %0 */                 \n" \
                        "        /* %%1 = %1 */                 \n" \
                        "        set1    0x100000+%u0.%u1       \n" \
                        : \
                        : "i"(PinTable[(pin)].portRegisterAddr), \
                          "i"(PinTable[(pin)].bit) \
                    ); \
                } else { \
                    __asm __volatile( \
                        "\n" \
                        "        /* %%0 = %0 */                 \n" \
                        "        /* %%1 = %1 */                 \n" \
                        "        clr1    0x100000+%u0.%u1       \n" \
                        : \
                        : "i"(PinTable[(pin)].portRegisterAddr), \
                          "i"(PinTable[(pin)].bit) \
                    ); \
                } \
            } else { \
                __asm __volatile( \
                    "\n" \
                    "        /* %%0 = %0 */                  \n" \
                    "        /* %%1 = %1 */                  \n" \
                    "        /* %%2 = %2 */                  \n" \
                    "        clrb    a                       \n" \
                    "        cmp     a, %0                   \n" \
                    "        mov1    0x100000+%u1.%u2, cy    \n" \
                    : \
                    : "r"((uint8_t)(value)), \
                      "i"(PinTable[(pin)].portRegisterAddr), \
                      "i"(PinTable[(pin)].bit) \
                    : "a" \
                ); \
            } \
        } \
    } else { \
        if (__builtin_constant_p((value))) { \
            if ((value)) { \
                __asm __volatile( \
                    "\n" \
                    "        /* %%0 = %0 */                 \n" \
                    "        /* %%1 = %1 */                 \n" \
                    "        /* %%2 = %2 */                 \n" \
                    "        /* %%3 = %3 */                 \n" \
                    "        /* %%4 = %4 */                 \n" \
                    "        mov     a, %0                  \n" \
                    "        cmp     a, %1                  \n" \
                    "        bnc     $8f                    \n" \
                    "        mov     x, %2                  \n" \
                    "        mulu    x                      \n" \
                    "        movw    bc, ax                 \n" \
                    "        movw    ax, %u3[bc]            \n" \
                    "        movw    hl, ax                 \n" \
                    "        mov     a, %u4[bc]             \n" \
                    "        bt      a.2, $4f               \n" \
                    "        bt      a.1, $2f               \n" \
                    "        bt      a.0, $1f               \n" \
                    "        set1    [hl].0                 \n" \
                    "        br      $8f                    \n" \
                    "1:                                     \n" \
                    "        set1    [hl].1                 \n" \
                    "        br      $8f                    \n" \
                    "2:                                     \n" \
                    "        bt      a.0, $3f               \n" \
                    "        set1    [hl].2                 \n" \
                    "        br      $8f                    \n" \
                    "3:                                     \n" \
                    "        set1    [hl].3                 \n" \
                    "        br      $8f                    \n" \
                    "4:                                     \n" \
                    "        bt      a.1, $6f               \n" \
                    "        bt      a.0, $5f               \n" \
                    "        set1    [hl].4                 \n" \
                    "        br      $8f                    \n" \
                    "5:                                     \n" \
                    "        set1    [hl].5                 \n" \
                    "        br      $8f                    \n" \
                    "6:                                     \n" \
                    "        bt      a.0, $7f               \n" \
                    "        set1    [hl].6                 \n" \
                    "        br      $8f                    \n" \
                    "7:                                     \n" \
                    "        set1    [hl].7                 \n" \
                    "8:                                     \n" \
                    : \
                    : "r"((uint8_t)pin), \
                      "i"(NUM_DIGITAL_PINS), \
                      "i"((unsigned)&PinTable[1] - (unsigned)&PinTable[0]), \
                      "i"(&PinTable->portRegisterAddr), \
                      "i"(&PinTable->bit) \
                    : "a", "x", "b", "c", "h", "l" \
                ); \
            } else { \
                __asm __volatile( \
                    "\n" \
                    "        /* %%0 = %0 */                 \n" \
                    "        /* %%1 = %1 */                 \n" \
                    "        /* %%2 = %2 */                 \n" \
                    "        /* %%3 = %3 */                 \n" \
                    "        /* %%4 = %4 */                 \n" \
                    "        mov     a, %0                  \n" \
                    "        cmp     a, %1                  \n" \
                    "        bnc     $8f                    \n" \
                    "        mov     x, %2                  \n" \
                    "        mulu    x                      \n" \
                    "        movw    bc, ax                 \n" \
                    "        movw    ax, %u3[bc]            \n" \
                    "        movw    hl, ax                 \n" \
                    "        mov     a, %u4[bc]             \n" \
                    "        bt      a.2, $4f               \n" \
                    "        bt      a.1, $2f               \n" \
                    "        bt      a.0, $1f               \n" \
                    "        clr1    [hl].0                 \n" \
                    "        br      $8f                    \n" \
                    "1:                                     \n" \
                    "        clr1    [hl].1                 \n" \
                    "        br      $8f                    \n" \
                    "2:                                     \n" \
                    "        bt      a.0, $3f               \n" \
                    "        clr1    [hl].2                 \n" \
                    "        br      $8f                    \n" \
                    "3:                                     \n" \
                    "        clr1    [hl].3                 \n" \
                    "        br      $8f                    \n" \
                    "4:                                     \n" \
                    "        bt      a.1, $6f               \n" \
                    "        bt      a.0, $5f               \n" \
                    "        clr1    [hl].4                 \n" \
                    "        br      $8f                    \n" \
                    "5:                                     \n" \
                    "        clr1    [hl].5                 \n" \
                    "        br      $8f                    \n" \
                    "6:                                     \n" \
                    "        bt      a.0, $7f               \n" \
                    "        clr1    [hl].6                 \n" \
                    "        br      $8f                    \n" \
                    "7:                                     \n" \
                    "        clr1    [hl].7                 \n" \
                    "8:                                     \n" \
                    : \
                    : "r"((uint8_t)pin), \
                      "i"(NUM_DIGITAL_PINS), \
                      "i"((unsigned)&PinTable[1] - (unsigned)&PinTable[0]), \
                      "i"(&PinTable->portRegisterAddr), \
                      "i"(&PinTable->bit) \
                    : "a", "x", "b", "c", "h", "l" \
                ); \
            } \
        } else { \
            __asm __volatile( \
                "\n" \
                "        /* %%0 = %0 */                  \n" \
                "        /* %%1 = %1 */                  \n" \
                "        /* %%2 = %2 */                  \n" \
                "        /* %%3 = %3 */                  \n" \
                "        /* %%4 = %4 */                  \n" \
                "        /* %%5 = %5 */                  \n" \
                "        mov     a, %0                   \n" \
                "        cmp     a, %1                   \n" \
                "        bnc     $8f                     \n" \
                "        mov     x, %2                   \n" \
                "        mulu    x                       \n" \
                "        movw    bc, ax                  \n" \
                "        movw    ax, %u3[bc]             \n" \
                "        movw    hl, ax                  \n" \
                "        clrb    a                       \n" \
                "        cmp     a, %5                   \n" \
                "        mov     a, %u4[bc]              \n" \
                "        bt      a.2, $4f                \n" \
                "        bt      a.1, $2f                \n" \
                "        bt      a.0, $1f                \n" \
                "        mov1    [hl].0, cy              \n" \
                "        br      $8f                     \n" \
                "1:                                      \n" \
                "        mov1    [hl].1, cy              \n" \
                "        br      $8f                     \n" \
                "2:                                      \n" \
                "        bt      a.0, $3f                \n" \
                "        mov1    [hl].2, cy              \n" \
                "        br      $8f                     \n" \
                "3:                                      \n" \
                "        mov1    [hl].3, cy              \n" \
                "        br      $8f                     \n" \
                "4:                                      \n" \
                "        bt      a.1, $6f                \n" \
                "        bt      a.0, $5f                \n" \
                "        mov1    [hl].4, cy              \n" \
                "        br      $8f                     \n" \
                "5:                                      \n" \
                "        mov1    [hl].5, cy              \n" \
                "        br      $8f                     \n" \
                "6:                                      \n" \
                "        bt      a.0, $7f                \n" \
                "        mov1    [hl].6, cy              \n" \
                "        br      $8f                     \n" \
                "7:                                      \n" \
                "        mov1    [hl].7, cy              \n" \
                "8:                                      \n" \
                : \
                : "r"((uint8_t)pin), \
                  "i"(NUM_DIGITAL_PINS), \
                  "i"((unsigned)&PinTable[1] - (unsigned)&PinTable[0]), \
                  "i"(&PinTable->portRegisterAddr), \
                  "i"(&PinTable->bit), \
                  "r"((uint8_t)value) \
                : "a", "x", "b", "c", "h", "l" \
            ); \
        } \
    } \
} while (0)

/**
 * 指定したピンの値を読み取ります。その結果はHIGHまたはLOWとなります。
 *
 * 指定したピンが pinMode()関数で予めINPUTかINPUT_PULLUPに設定されている
 * 必要があります。
 *
 * @param[in] pin ピン番号を指定します。
 *
 * @return HIGHまたはLOWを返却します。
 *
 * @attention
 * 引数には定数を使用することを想定しています。
 * 引数に変数を使用した場合にはコードサイズの肥大化が生じ、速度も遅くなるので
 * digitalRead() のどちらを使用するかはよく検討しましょう。
 ***************************************************************************/
#define fastDigitalRead(pin) \
({ \
    int s16Value = 0; \
    if (__builtin_constant_p(pin)) { \
        if ((pin) < NUM_DIGITAL_PINS) { \
            __asm __volatile( \
                "\n" \
                "        /* %%0 = %0 */                          \n" \
                "        /* %%1 = %1 */                          \n" \
                "        /* %%2 = %2 */                          \n" \
                "        /* %%3 = %3 */                          \n" \
                "        mov1    cy, 0x100000+%u2.%u3            \n" \
                "        mov1    %0.0, cy                        \n" \
                : "=r"(s16Value) \
                : "r"(s16Value), \
                  "i"(PinTable[(pin)].portRegisterAddr), \
                  "i"(PinTable[(pin)].bit) \
            ); \
        }; \
    } else { \
        __asm __volatile( \
            "\n" \
            "        /* %%0 = %0 */                 \n" \
            "        /* %%1 = %1 */                 \n" \
            "        /* %%2 = %2 */                 \n" \
            "        /* %%3 = %3 */                 \n" \
            "        /* %%4 = %4 */                 \n" \
            "        /* %%5 = %5 */                 \n" \
            "        /* %%6 = %6 */                 \n" \
            "        mov     a, %2                  \n" \
            "        cmp     a, %3                  \n" \
            "        bnc     $9f                    \n" \
            "        mov     x, %4                  \n" \
            "        mulu    x                      \n" \
            "        movw    bc, ax                 \n" \
            "        movw    ax, %u5[bc]            \n" \
            "        movw    hl, ax                 \n" \
            "        mov     a, %u6[bc]             \n" \
            "        and     a, [hl]                \n" \
            "        add     a, #0xff               \n" \
            "        mov1    %1.0, cy               \n" \
            "9:                                     \n" \
            : "=r"(s16Value) \
            : "r"(s16Value), \
              "r"((uint8_t)pin), \
              "i"(NUM_DIGITAL_PINS), \
              "i"((unsigned)&PinTable[1] - (unsigned)&PinTable[0]), \
              "i"(&PinTable->portRegisterAddr), \
              "i"(&PinTable->mask) \
            : "a", "x", "b", "c", "h", "l" \
        ); \
    }; \
    s16Value; \
})

#endif/*_FASTIO_H_*/
