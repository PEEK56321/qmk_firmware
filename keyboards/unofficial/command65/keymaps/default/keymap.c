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

#include QMK_KEYBOARD_H

#include "print.h"
#include "../../ble.h"
#include "quantum.h"

ble_led_stat ble_led;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    // 0: Base Layer
    [0] = LAYOUT(
                                                                                                                                MO(1), MO(2), \
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,  KC_DEL, KC_HOME, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,           KC_BSLS,  KC_PGUP, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NONUS_HASH, KC_ENT,   KC_PGDN, \
        KC_LSFT, KC_NUBS,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, KC_UP,    KC_END, \
        KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                          KC_RALT, KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RIGHT),

    // 1: Function Layer
    [1] = LAYOUT(
                                                                                                                                    _______, _______, \
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, RGB_TOG, RGB_MOD, BL_TOGG, BL_STEP, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, _______, _______, \
        _______,  _______,  _______,                          _______,                                     _______, _______, _______, _______, _______),

    [2] = LAYOUT(
                                                                                                                                    _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______,  _______,  _______,                          _______,                                     _______, _______, _______, _______, _______),

    [3] = LAYOUT(
                                                                                                                                    _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______,  _______,  _______,                          _______,                                     _______, _______, _______, _______, _______),
    // clang-format on
};

void led_set_user(uint8_t usb_led) {
    if (!ble_on) {
        if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
            writePinHigh(F0);
            ble_led.caplck = true;
        } else {
            writePinLow(F0);
            ble_led.caplck = false;
        }
    }
}

void keyboard_pre_init_user(void) {
    setPinOutput(F0);
    writePinLow(F0);

    setPinOutput(F5);
    writePinLow(F5);

    setPinOutput(E2);
    writePinLow(E2);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_F21:
            if (record->event.pressed) {
                module_reset();
            } else {
            }
            break;
        case KC_F19:
            if (record->event.pressed) {
                reset_ble_batt();
            } else {
            }
            break;
        case KC_F20:
            if (record->event.pressed) {
                update_ble_batt();
                wait_ms(100);
            } else {
            }
            break;
        case KC_CAPS:
            if (record->event.pressed) {
                if (ble_on) {
                    ble_led.caplck = !ble_led.caplck;
                    if (ble_led.caplck) {
                        writePinLow(F0);
                    } else {
                        writePinLow(F0);
                    }
                }
            }
            break;
        default:
            return true;
    }
    return true;
}

void matrix_scan_user(void) {
    if (ble_led.caplck) {
        writePinHigh(F0);
    } else {
        writePinLow(F0);
    }
}
