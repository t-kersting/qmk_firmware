/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "action_util.h"
#include "dilemma.h"
#include "keycode.h"
#include "keycodes.h"
#include "process_caps_word.h"
#include "process_combo.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "sendstring_german.h"

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NAV,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_FUN,
    LAYER_MOUSE,
    LAYER_EXTRA,
    LAYER_CONFIG,
};

enum custom_keycodes {
    CARET = SAFE_RANGE,
    G_ACC,
    ACUTE,
};

enum combos {
    C_AE,
    C_UE,
    C_OE,
    C_CAPSWORD,
};

// keys
#define NAV LT(LAYER_NAV, KC_SPC)
#define SYM LT(LAYER_SYM, KC_DEL)
#define NUM LT(LAYER_NUM, KC_BSPC)
#define FUN LT(LAYER_FUN, KC_ESC)
#define MOUSE_X LT(LAYER_MOUSE, DE_Z)
#define EXT_MIN LT(LAYER_EXTRA, DE_MINS)
#define CONF_SS LT(LAYER_CONFIG, DE_SS)

#define MY_A LGUI_T(KC_A)
#define MY_R LALT_T(KC_R)
#define MY_S LCTL_T(KC_S)
#define MY_T LSFT_T(KC_T)

#define MY_N LSFT_T(KC_N)
#define MY_E LCTL_T(KC_E)
#define MY_I LALT_T(KC_I)
#define MY_O LGUI_T(KC_O)
#define MY_SQUO S(DE_HASH)

#define MY_X RALT_T(KC_X)
#define MY_DOT RALT_T(KC_DOT)

#define SG_ACC S(G_ACC)

#define PASTE LSFT(KC_INSERT)
#define COPY LCTL(KC_INSERT)
#define CUT LSFT(KC_DEL)

// combos
const uint16_t PROGMEM ars_combo[] = {MY_A, MY_R, MY_S, COMBO_END};
const uint16_t PROGMEM luy_combo[] = {KC_L, KC_U, DE_Y, COMBO_END};
const uint16_t PROGMEM eio_combo[] = {MY_E, MY_I, MY_O, COMBO_END};
const uint16_t PROGMEM dh_combo[]  = {KC_D, KC_H, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [C_AE] = COMBO(ars_combo, DE_ADIA), // ä
    [C_UE] = COMBO(luy_combo, DE_UDIA), // ü
    [C_OE] = COMBO(eio_combo, DE_ODIA), // ö
    [C_CAPSWORD] = COMBO(dh_combo, QK_CAPS_WORD_TOGGLE)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    DE_Y, CONF_SS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          MY_A,    MY_R,    MY_S,    MY_T,    KC_G,       KC_M,    MY_N,    MY_E,    MY_I,    MY_O,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       MOUSE_X,    MY_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  MY_DOT, EXT_MIN,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                             FUN,     NAV,  KC_TAB,     KC_ENT,     NUM,     SYM
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NAV] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,     CUT,    COPY,   PASTE, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, XXXXXXX,     KC_ENT, KC_BSPC, KC_DEL
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_SYM] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
         CARET, DE_SLSH, DE_LCBR, DE_RCBR, DE_PIPE,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       DE_TILD, DE_HASH, DE_LABK, DE_RABK, DE_AMPR,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       DE_CIRC, DE_ACUT, DE_LBRC, DE_RBRC, DE_BSLS,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_DOT,  DE_EQL, KC_COMM,    XXXXXXX, XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NUM] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        DE_DEG,    KC_7,    KC_8,    KC_9, DE_EURO,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       DE_PIPE,    KC_4,    KC_5,    KC_6, DE_PLUS,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       DE_BSLS,    KC_1,    KC_2,    KC_3, DE_MINS,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_DOT,    KC_0, KC_COMM,    XXXXXXX, XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_FUN] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  KC_APP, KC_CAPS
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_MOUSE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, SNP_TOG, KC_WH_L, KC_WH_R, KC_WH_U,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, KC_WH_D,    XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX,     CUT,    COPY,   PASTE, DRGSCRL,    XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_BTN3, KC_BTN1, KC_BTN2,    XXXXXXX, KC_BSPC,  KC_DEL
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_EXTRA] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX,   G_ACC, DE_DQUO, MY_SQUO, XXXXXXX,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_ESC,  KC_SPC,  KC_TAB,     KC_ENT, KC_BSPC,  KC_DEL
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_CONFIG] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, RGB_SPI,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         KC_MSTP, KC_MPLY, KC_MUTE,    XXXXXXX, XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CARET:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_GRV) SS_TAP(X_SPACE));
            }
            return false;
        case G_ACC:
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_EQL) SS_UP(X_LSFT) SS_TAP(X_SPACE));
            }
            return false;
        case ACUTE:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_EQL) SS_TAP(X_SPACE));
            }
            return false;
    }
    return true;
}

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    return true;
}

bool get_combo_must_press_in_order(uint16_t index, combo_t *combo) {
    return false;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case DE_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
