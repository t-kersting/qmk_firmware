#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "sendstring_german.h"

enum layer_names { _COLEMAK, _NAV, _MOUSE, _MEDIA, _NUM, _SYM, _FUN, _EXT };

enum custom_keycodes {
  CARET = SAFE_RANGE,
  G_ACC,
  ACUTE,
};

enum combos {
  AR_AE,
  UY_UE,
  IO_OE,
  CD_D_QUOTE,
  HCOMMA_S_QUOTE,
  DH_CAPSWORD,
};

// Combos
const uint16_t PROGMEM ars_combo[] = {LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S),
                                      COMBO_END};
const uint16_t PROGMEM luy_combo[] = {KC_L, KC_U, DE_Y, COMBO_END};
const uint16_t PROGMEM eio_combo[] = {LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O),
                                      COMBO_END};
const uint16_t PROGMEM cd_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM h_comma_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM dh_capsword[] = {KC_D, KC_H, COMBO_END};

combo_t key_combos[] = {
    [AR_AE] = COMBO(ars_combo, DE_ADIA),
    [UY_UE] = COMBO(luy_combo, DE_UDIA),
    [IO_OE] = COMBO(eio_combo, DE_ODIA),
    [CD_D_QUOTE] = COMBO(cd_combo, S(KC_2)),
    [HCOMMA_S_QUOTE] = COMBO(h_comma_combo, S(DE_HASH)),
    [DH_CAPSWORD] = COMBO(dh_capsword, QK_CAPS_WORD_TOGGLE),
};

// Keys
#define NAV LT(_NAV, KC_SPC)
#define MOUSE LT(_MOUSE, KC_TAB)
#define MEDIA LT(_MEDIA, KC_ESC)
#define NUM LT(_NUM, KC_BSPC)
#define SYM LT(_SYM, KC_DEL)
#define FUN LT(_FUN, KC_ENTER)
#define EXT_L LT(_EXT, DE_Z)

#define MY_REDO LCTL(LSFT(DE_Z))
#define MY_PASTE LSFT(KC_INSERT)
#define MY_COPY LCTL(KC_INSERT)
#define MY_CUT LCTL(KC_X)
#define MY_UNDO LCTL(DE_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Colemak
     *
     * ,----------------------------------. ,----------------------------------.
     * |   Q  |   W  |   F  |   P  |   B  |           |   J  |   L  |   U  |   Y
     * |  ß ? |
     * |------+------+------+------+------| |------+------+------+------+------|
     * |   A  |   R  |   S  |   T  |   G  |           |   M  |   N  |   E  |   I
     * |   O  |
     * |(LGUI)|(LALT)|(LCTL)|(LSFT)|      |           |
     * |(LSFT)|(LCTL)|(LALT)|(LGUI)|
     * |------+------+------+------+------| |------+------+------+------+------|
     * |   Z  |   X  |   C  |   D  |   V  |           |   K  |   H  |   ,  |   .
     * |  - _ | | Extra|(RALT)|      |      |      |           |      |      |
     * |(RALT)|      |
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  |  ESC | Space|  Tab |    | Enter| BSPC |Delete|
     *                  | Media|  Nav | Mouse|    |  Fun |  Num |  Sym |
     *                  `--------------------'    `--------------------.
     */
    [_COLEMAK] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, DE_Y, DE_SS,
        LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M,
        LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), EXT_L,
        RALT_T(KC_X), KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, RALT_T(KC_DOT),
        DE_MINS, MEDIA, NAV, MOUSE, FUN, NUM, SYM),

    /* Navigation
     *
     * ,----------------------------------. ,----------------------------------.
     * | Reset|      |      |      |      |           | Redo | Paste| Copy | Cut
     * | Undo |
     * |------+------+------+------+------| |------+------+------+------+------|
     * | LGUI | LALT | LCTL | LSFT |      |           | Caps | Left | Down |  Up
     * | Right|
     * |------+------+------+------+------| |------+------+------+------+------|
     * |      | RALT |      |      |      |           | Ins  | Home | PgDn |
     * PgUp | End  |
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  |      |      |      |    | Enter| BPSC |Delete|
     *                  `--------------------'    `--------------------.
     */
    [_NAV] = LAYOUT_split_3x5_3(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, MY_REDO, MY_PASTE, MY_COPY, MY_CUT,
        MY_UNDO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_CAPS, KC_LEFT,
        KC_DOWN, KC_UP, KC_RIGHT, KC_NO, KC_RALT, KC_NO, KC_NO, KC_NO,
        KC_INSERT, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_NO, KC_NO,
        KC_ENTER, KC_BSPC, KC_DEL),

    /* Mouse
     *
     * ,----------------------------------. ,----------------------------------.
     * | Reset|      |      |      |      |           | Redo | Paste| Copy | Cut
     * | Undo |
     * |------+------+------+------+------| |------+------+------+------+------|
     * | LGUI | LALT | LCTL | LSFT |      |           |      | Mouse| Mouse|
     * Mouse| Mouse| |      |      |      |      |      |           |      |
     * Left | Down |  Up  | Right|
     * |------+------+------+------+------| |------+------+------+------+------|
     * |      | RALT |      |      |      |           |      | Wheel| Wheel|
     * Wheel| Wheel| |      |      |      |      |      |           |      |
     * Left | Down |  Up  | Right|
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  |      |      |      |    | RCLK | LCLK | MCLK |
     *                  `--------------------'    `--------------------.
     */
    [_MOUSE] = LAYOUT_split_3x5_3(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, MY_REDO, MY_PASTE, MY_COPY, MY_CUT,
        MY_UNDO, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_MS_L,
        KC_MS_D, KC_MS_U, KC_MS_R, KC_NO, KC_RALT, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, KC_NO, KC_NO,
        KC_NO, KC_MS_BTN2, KC_MS_BTN1, KC_MS_BTN3),

    /* Media
     *
     * ,----------------------------------. ,----------------------------------.
     * | Reset|      |      |      |      |           | RGB  | RGB  | RGB  | RGB
     * | RGB  | |      |      |      |      |      |           |Toggle| Mode |
     * Hue  | Sat  | Value|
     * |------+------+------+------+------| |------+------+------+------+------|
     * | LGUI | LALT | LCTL | LSFT |      |           | RGB  | Prev
     * |Volume|Volume| Next | |      |      |      |      |      |           |
     * Speed| Track| Down |  Up  | Track|
     * |------+------+------+------+------| |------+------+------+------+------|
     * |      | RALT |      |      |      |           |      |      |      | | |
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  |      |      |      |    | Stop | Play | Mute |
     *                  `--------------------'    `--------------------.
     */
    [_MEDIA] = LAYOUT_split_3x5_3(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI,
        RGB_VAI, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, RGB_SPI,
        KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
        KC_MEDIA_NEXT_TRACK, KC_NO, KC_RALT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MEDIA_STOP,
        KC_MEDIA_PLAY_PAUSE, KC_AUDIO_MUTE),

    /* Number
     *
     * ,----------------------------------. ,----------------------------------.
     * |  °   | 7 /  | 8 (  | 9 )  |  €   |           |      |      |      | |
     * Reset|
     * |------+------+------+------+------| |------+------+------+------+------|
     * |  |   | 4 $  | 5 %  | 6 &  | +  * |           |      | LSFT | LCTL |
     * LALT | LGUI |
     * |------+------+------+------+------| |------+------+------+------+------|
     * |  \   | 1 !  | 2 "  | 3 §  | - _  |           |      |      |      |
     * RALT |      |
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  |  .   | 0 =  |  ,   |    |      |      |      |
     *                  `--------------------'    `--------------------.
     */
    [_NUM] = LAYOUT_split_3x5_3(
        DE_DEG, KC_7, KC_8, KC_9, DE_EURO, KC_NO, KC_NO, KC_NO, KC_NO, QK_BOOT,
        DE_PIPE, KC_4, KC_5, KC_6, DE_PLUS, KC_NO, KC_LSFT, KC_LCTL, KC_LALT,
        KC_LGUI, DE_BSLS, KC_1, KC_2, KC_3, DE_MINS, KC_NO, KC_NO, KC_NO,
        KC_RALT, KC_NO, KC_DOT, KC_0, KC_COMM, KC_NO, KC_NO, KC_NO),

    /* Symbol
     *
     * ,----------------------------------. ,----------------------------------.
     * |  ^   |  Ü   |  {   |  }   |  ´   |           |      |      |      | |
     * Reset|
     * |------+------+------+------+------| |------+------+------+------+------|
     * |  Ä   |  Ö   |  <   |  >   |  `   |           |      | LSFT | LCTL |
     * LALT | LGUI |
     * |------+------+------+------+------| |------+------+------+------+------|
     * | - _  | # '  |  [   |  ]   |  ~   |           |      |      |      |
     * RALT |      |
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  |   .  |  =   |  ,   |    |      |      |      |
     *                  `--------------------'    `--------------------.
     */
    [_SYM] = LAYOUT_split_3x5_3(
        CARET, DE_UDIA, DE_LCBR, DE_RCBR, ACUTE, KC_NO, KC_NO, KC_NO, KC_NO,
        QK_BOOT, DE_ADIA, DE_ODIA, DE_LABK, DE_RABK, G_ACC, KC_NO, KC_LSFT,
        KC_LCTL, KC_LALT, KC_LGUI, DE_MINS, DE_HASH, DE_LBRC, DE_RBRC, DE_TILD,
        KC_NO, KC_NO, KC_NO, KC_RALT, KC_NO, KC_DOT, DE_EQL, KC_COMM, KC_NO,
        KC_NO, KC_NO),

    /* Function
     *
     * ,----------------------------------. ,----------------------------------.
     * | F12  |  F7  |  F8  |  F9  | Print|           |      |      |      | |
     * Reset| |      |      |      |      |Screen|           |      |      | |
     * |      |
     * |------+------+------+------+------| |------+------+------+------+------|
     * | F11  |  F4  |  F5  |  F6  |Scroll|           |      | LSFT | LCTL |
     * LALT | LGUI | |      |      |      |      | Lock |           |      | |
     * |      |      |
     * |------+------+------+------+------| |------+------+------+------+------|
     * | F10  |  F1  |  F2  |  F3  | Pause|           |      |      |      |
     * RALT |      |
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  | Menu | Space| Tab  |    |      |      |      |
     *                  `--------------------'    `--------------------.
     */
    [_FUN] = LAYOUT_split_3x5_3(
        KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR, KC_NO, KC_NO,
        KC_NO, KC_NO, QK_BOOT, KC_F11, KC_F4, KC_F5, KC_F6, KC_PSCR, KC_NO,
        KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_F10, KC_F1, KC_F2, KC_F3,
        KC_PAUSE, KC_NO, KC_NO, KC_NO, KC_RALT, KC_NO, KC_APPLICATION, KC_SPACE,
        KC_TAB, KC_NO, KC_NO, KC_NO),

    /* Extra
     *
     * ,----------------------------------. ,----------------------------------.
     * |  ^D  |  ´D  |      |      |      |           |      |      |      |  ´D
     * |  ^D  |
     * |------+------+------+------+------| |------+------+------+------+------|
     * | LGUI | LALT | LCTL | LSFT |      |           |      | LSFT | LCTL |
     * LALT | LGUI |
     * |------+------+------+------+------| |------+------+------+------+------|
     * | Undo | Cut  | Copy | Paste| Redo |           | Redo | Paste| Copy | Cut
     * | Undo |
     * `-------------+--------------------' `----------------------------------'
     *                  ,--------------------.    ,--------------------.
     *                  |      |      |      |    |      |      |      |
     *                  `--------------------'    `--------------------.
     */
    [_EXT] = LAYOUT_split_3x5_3(
        DE_CIRC, DE_ACUT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DE_ACUT,
        DE_CIRC, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_NO, KC_LSFT,
        KC_LCTL, KC_LALT, KC_LGUI, MY_UNDO, MY_CUT, MY_COPY, MY_PASTE, MY_REDO,
        MY_REDO, MY_PASTE, MY_COPY, MY_CUT, MY_UNDO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO)

    // /* Template
    //  *
    //  * ,----------------------------------.
    //  ,----------------------------------.
    //  * |      |      |      |      |      |           |      |      |      |
    //  |      |
    //  * |------+------+------+------+------|
    //  |------+------+------+------+------|
    //  * |      |      |      |      |      |           |      |      |      |
    //  |      |
    //  * |------+------+------+------+------|
    //  |------+------+------+------+------|
    //  * |      |      |      |      |      |           |      |      |      |
    //  |      |
    //  * `-------------+--------------------'
    //  `----------------------------------'
    //  *                  ,--------------------.    ,--------------------.
    //  *                  |      |      |      |    |      |      |      |
    //  *                  `--------------------'    `--------------------.
    //  */
};

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

bool get_combo_must_tap(uint16_t index, combo_t *combo) { return true; }

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case NAV:
  case MOUSE:
  case MEDIA:
  case NUM:
  case SYM:
  case FUN:
    // Immediately select the hold action when another key is tapped.
    return true;
  default:
    // Do not select the hold action when another key is tapped.
    return false;
  }
}
