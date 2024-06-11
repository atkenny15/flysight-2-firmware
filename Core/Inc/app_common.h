/* USER CODE BEGIN Header */
/***************************************************************************
**                                                                        **
**  FlySight 2 firmware                                                   **
**  Copyright 2023 Bionic Avionics Inc.                                   **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see <http://www.gnu.org/licenses/>. **
**                                                                        **
****************************************************************************
**  Contact: Bionic Avionics Inc.                                         **
**  Website: http://flysight.ca/                                          **
****************************************************************************/
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_COMMON_H
#define APP_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "app_conf.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------- *
 *  Basic definitions               *
 * -------------------------------- */
#undef NULL
#define NULL 0

#undef FALSE
#define FALSE 0

#undef TRUE
#define TRUE (!0)

/* -------------------------------- *
 *  Critical Section definition     *
 * -------------------------------- */
#define BACKUP_PRIMASK() uint32_t primask_bit = __get_PRIMASK()
#define DISABLE_IRQ() __disable_irq()
#define RESTORE_PRIMASK() __set_PRIMASK(primask_bit)

/* -------------------------------- *
 *  Macro delimiters                *
 * -------------------------------- */
#define M_BEGIN do {

#define M_END \
    }         \
    while (0)

/* -------------------------------- *
 *  Some useful macro definitions   *
 * -------------------------------- */
#ifndef MAX
#    define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
#    define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#define MODINC(a, m) \
    M_BEGIN(a)++;    \
    if ((a) >= (m))  \
        (a) = 0;     \
    M_END

#define MODDEC(a, m)                \
    M_BEGIN if ((a) == 0)(a) = (m); \
    (a)--;                          \
    M_END

#define MODADD(a, b, m) \
    M_BEGIN(a) += (b);  \
    if ((a) >= (m))     \
        (a) -= (m);     \
    M_END

#define MODSUB(a, b, m) MODADD(a, (m) - (b), m)

#define PAUSE(t)               \
    M_BEGIN                    \
    __IO int _i;               \
    for (_i = t; _i > 0; _i--) \
        ;                      \
    M_END

#define DIVF(x, y) ((x) / (y))

#define DIVC(x, y) (((x) + (y)-1) / (y))

#define DIVR(x, y) (((x) + ((y) / 2)) / (y))

#define SHRR(x, n) ((((x) >> ((n)-1)) + 1) >> 1)

#define BITN(w, n) (((w)[(n) / 32] >> ((n) % 32)) & 1)

#define BITNSET(w, n, b)                              \
    M_BEGIN(w)[(n) / 32] |= ((U32)(b)) << ((n) % 32); \
    M_END

/* -------------------------------- *
 *  Compiler                         *
 * -------------------------------- */
#define PLACE_IN_SECTION(__x__) __attribute__((section(__x__)))

#ifdef WIN32
#    define ALIGN(n)
#else
#    define ALIGN(n) __attribute__((aligned(n)))
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*APP_COMMON_H */
