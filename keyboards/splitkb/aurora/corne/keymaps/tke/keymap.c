#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "sendstring_german.h"
#include "action_util.h"
#include "keycode.h"
#include "keycodes.h"
#include "process_caps_word.h"
#include "process_combo.h"
#include "progmem.h"
#include "quantum_keycodes.h"

enum layers {
    LAYER_BASE = 0,
    LAYER_NAV,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_FUN,
    LAYER_MOUSE,
    // LAYER_EXTRA,
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
    C_DQ,
    C_SQ,
    C_CAPSWORD,
};

// keys
#define NAV LT(LAYER_NAV, KC_SPC)
#define SYM LT(LAYER_SYM, KC_DEL)
#define NUM LT(LAYER_NUM, KC_BSPC)
#define FUN LT(LAYER_FUN, KC_ENT)
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
const uint16_t PROGMEM nei_combo[] = {MY_N, MY_E, MY_I, COMBO_END};
const uint16_t PROGMEM rst_combo[] = {MY_R, MY_S, MY_T, COMBO_END};
const uint16_t PROGMEM dh_combo[]  = {KC_D, KC_H, COMBO_END};

// clang-format off
combo_t key_combos[] = {
    [C_AE] = COMBO(ars_combo, DE_ADIA), // ä
    [C_UE] = COMBO(luy_combo, DE_UDIA), // ü
    [C_OE] = COMBO(eio_combo, DE_ODIA), // ö
    [C_SQ] = COMBO(nei_combo, MY_SQUO), // '
    [C_DQ] = COMBO(rst_combo, DE_DQUO), // "
    [C_CAPSWORD] = COMBO(dh_combo, QK_CAPS_WORD_TOGGLE)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    DE_Y, CONF_SS, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,    MY_A,    MY_R,    MY_S,    MY_T,    KC_G,       KC_M,    MY_N,    MY_E,    MY_I,    MY_O, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, MOUSE_X,    MY_X,    KC_C,    KC_D,    KC_V,       KC_K,    KC_H, KC_COMM,  MY_DOT, DE_MINS, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_ESC,     NAV,  KC_TAB,        FUN,     NUM,     SYM
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
    [LAYER_NAV] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,     CUT,    COPY,   PASTE, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, XXXXXXX, XXXXXXX,     KC_ENT, KC_BSPC, KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_SYM] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX,   CARET, DE_SLSH, DE_LCBR, DE_RCBR, DE_PIPE,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, DE_TILD, DE_HASH, DE_LABK, DE_RABK,   G_ACC,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, DE_CIRC, DE_BSLS, DE_LBRC, DE_RBRC, DE_ACUT,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_DOT,  DE_EQL, KC_COMM,    XXXXXXX, XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NUM] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX,  DE_DEG,    KC_7,    KC_8,    KC_9, DE_EURO,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, DE_PIPE,    KC_4,    KC_5,    KC_6, DE_PLUS,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, DE_BSLS,    KC_1,    KC_2,    KC_3, DE_MINS,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_DOT,    KC_0, KC_COMM,    XXXXXXX, XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_FUN] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX,  KC_APP, KC_CAPS,    XXXXXXX, XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_MOUSE] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_R, KC_WH_U,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT, KC_WH_D,    XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX,     CUT,    COPY,   PASTE, XXXXXXX,    XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN3, KC_BTN1, KC_BTN2,    XXXXXXX, KC_BSPC,  KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  /* [LAYER_EXTRA] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX,   G_ACC, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                   KC_ESC,  KC_SPC,  KC_TAB,     KC_ENT, KC_BSPC,  KC_DEL
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ), */

  [LAYER_CONFIG] = LAYOUT_split_3x6_3(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       XXXXXXX, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, RGB_SPI,    XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_MSTP, KC_MPLY, KC_MUTE,    XXXXXXX, XXXXXXX, XXXXXXX
  //                            ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on
//
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

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NAV:
        case NUM:
        case SYM:
        case FUN:
        case MOUSE_X:
        // case EXT_MIN:
        case CONF_SS:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
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

void keyboard_pre_init_user(void) {
    // Set our LED pin as output
    setPinOutput(24);
    // Turn the LED off
    // (Due to technical reasons, high is off and low is on)
    writePinHigh(24);
}
