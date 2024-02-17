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
    LAYER_QWERTY,
    LAYER_MOUSE,
    LAYER_EXTRA,
    LAYER_NAV,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_FUN,
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
    C_D_QUOTE,
    C_S_QUOTE,
    C_CAPSWORD,
};

// keys
#define NAV MO(LAYER_NAV)
#define SYM MO(LAYER_SYM)
#define MOUSE_X LT(LAYER_MOUSE, DE_Z)
#define EXT_MIN LT(LAYER_EXTRA, DE_MINS)

#define MY_A LGUI_T(KC_A)
#define MY_R LALT_T(KC_R)
#define MY_S LCTL_T(KC_S)
#define MY_T LSFT_T(KC_T)

#define MY_N LSFT_T(KC_N)
#define MY_E LCTL_T(KC_E)
#define MY_I LALT_T(KC_I)
#define MY_O LGUI_T(KC_O)

#define MY_X RALT_T(KC_X)
#define MY_DOT RALT_T(KC_DOT)

#define PASTE LSFT(KC_INSERT)
#define COPY LCTL(KC_INSERT)
#define CUT LSFT(KC_DEL)

// combos
const uint16_t PROGMEM ars_combo[]         = {MY_A, MY_R, MY_S, COMBO_END};
const uint16_t PROGMEM luy_combo[]         = {KC_L, KC_U, DE_Y, COMBO_END};
const uint16_t PROGMEM eio_combo[]         = {MY_E, MY_I, MY_O, COMBO_END};
const uint16_t PROGMEM xcd_combo[]         = {MY_X, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM h_comma_dot_combo[] = {KC_H, KC_COMM, MY_DOT, COMBO_END};
const uint16_t PROGMEM dh_combo[]          = {KC_D, KC_H, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [C_AE] = COMBO(ars_combo, DE_ADIA), // ä
    [C_UE] = COMBO(luy_combo, DE_UDIA), // ü
    [C_OE] = COMBO(eio_combo, DE_ODIA), // ö
    [C_D_QUOTE] = COMBO(xcd_combo, S(KC_2)), // Double Quote
    [C_S_QUOTE] = COMBO(h_comma_dot_combo, S(DE_HASH)), // Single Quote
    [C_CAPSWORD] = COMBO(dh_combo, QK_CAPS_WORD_TOGGLE)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    DE_Y,   DE_SS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          MY_A,    MY_R,    MY_S,    MY_T,    KC_G,       KC_M,    MY_N,    MY_E,    MY_I,    MY_O,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       MOUSE_X,    MY_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  MY_DOT, EXT_MIN,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          KC_ESC,  KC_SPC,  KC_TAB,     KC_DEL, KC_BSPC, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NAV] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_TAB, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,    XXXXXXX, KC_HOME,   KC_UP,  KC_END,  KC_DEL,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LSFT, KC_LCTL, KC_LALT, KC_RGUI, KC_VOLD,    XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       QK_BOOT,  EE_CLR, KC_MPRV, KC_MNXT, KC_MPLY,    XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX,  KC_ENT,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                            KC_A, _______, KC_LSFT,     KC_SPC, _______,    KC_A
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_SYM] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        KC_ESC, KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,    KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC,  KC_GRV,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_MINS, KC_ASTR,  KC_EQL, KC_UNDS,  KC_DLR,    KC_HASH, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_PLUS, KC_PIPE,   KC_AT, KC_SLSH, KC_PERC,    _______, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                            KC_A, _______, KC_LSFT,     KC_SPC, _______,    KC_A
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NUM] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,   KC_0,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,  KC_F11,     KC_F12, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                            KC_A, _______, KC_LSFT,     KC_SPC, _______,    KC_A
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
                         KC_BTN3, KC_BTN1, KC_BTN2,    XXXXXXX, XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_EXTRA] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                         XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,  KC_ENT, XXXXXXX
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
