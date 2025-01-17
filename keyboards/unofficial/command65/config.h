/* Copyright 2022 Basic I/O Instruments (@scottywei)
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

#define USB_POLLING_INTERVAL_MS 1

#define BLE_NAME "BIOI COMMAND65 BLE"
#define BIOI_CMD65
#define NO_BAT_LEVEL

#define MATRIX_ROW_PINS { B0, E6, F1, F6, F4 }
#define MATRIX_COL_PINS { F7, C7, C6, B6, B5, B4, D7, D6, D4, D5, B3, B1, D1, D0, B2 }

#define DIP_SWITCH_MATRIX_GRID { {4,7}, {4,8} }

#define AUDIO_PIN B7
#define AUDIO_CLICKY
#define STARTUP_SONG SONG(MUSIC_ON_SOUND)

#define DIODE_DIRECTION COL2ROW

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define KEYBOARD_LOCK_ENABLE
#define MAGIC_KEY_LOCK L
#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))
