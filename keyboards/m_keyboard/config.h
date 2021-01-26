/* Copyright 2021 Michael Spradling <mike@mspradling.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x6666
#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001
#define MANUFACTURER Michael Spradling
#define PRODUCT      M-Keyboard
#define DESCRIPTION  Michael Keyboard

/* Key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18 /* Note this is one longer than MATRIX_COL_PINS to account for direct wire column */
#define MATRIX_ROW_PINS { A5, A4, A3, A2, A1, A0 }
#define MATRIX_COL_PINS { A6, A7, A8, A9, A10, B0, B1, B2, B7, B4, B6, B10, B11, B12, B13, B14, B15 }

/* Direct Pins in addition to matrix */
#define DIRECT_PINS_EXT { C13, C14, C15 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration (Mode) */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 14
