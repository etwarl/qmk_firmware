#include QMK_KEYBOARD_H

#include "keymap_jis2us.h"
#include "action_pseudo_lut.h"
#include "keymap_jp.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum my_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _PSEUDO_US,
  _PSEUDO_US_LOWER,
  _PSEUDO_US_RAISE,
  _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  JIS2US,
  P_LOWER,
  P_RAISE,
  ADJUST,
};

// Layer related keycodes
#define QWERTY DF(_QWERTY)
#define PSEU_US DF(_PSEUDO_US)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define WINLOCK LGUI(KC_L)

// Special keycodes
#define KC_CAD LCTL(LALT(KC_DEL))
#define KC_SENT SFT_T(KC_ENT)

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,  \
                    KC_LGUI, KC_LALT, LOWER,   KC_LCTL, KC_SPC,  KC_BSPC, KC_SENT, RAISE,   KC_RALT, KC_APP\
),

[_LOWER] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,\
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,\
  KC_LCTL, _______, _______, _______, KC_WH_U, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, _______,\
  _______, KC_CAD,  WINLOCK,  KC_WH_L, KC_WH_D, KC_WH_R, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END,\
                    _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______\
),

[_RAISE] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     _______, _______, _______, _______, _______, _______,\
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    _______, _______, _______, _______, _______, _______,\
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  _______,                   _______, KC_MINS, KC_EQL,  KC_BSLS, _______, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
),

[_PSEUDO_US] = LAYOUT( \
  JIS2US,  KC_1,    JIS2US,  KC_3,    KC_4,    KC_5,                      JIS2US,  JIS2US,  JIS2US,  JIS2US,  JIS2US,  JIS2US, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    JIS2US, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    JIS2US,  JIS2US, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    JIS2US,  JIS2US,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, JIS2US,  \
                    KC_LGUI, KC_LALT, P_LOWER, KC_LCTL, KC_SPC,  KC_BSPC, KC_SENT, P_RAISE, KC_RALT, KC_APP\
),

[_PSEUDO_US_LOWER] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,\
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,\
  KC_LCTL, _______, _______, _______, KC_WH_U, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGUP, _______,\
  _______, KC_CAD,  WINLOCK, KC_WH_L, KC_WH_D, KC_WH_R, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END,\
                    _______, _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______\
),

[_PSEUDO_US_RAISE] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     _______, _______, _______, _______, _______, _______,\
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    _______, _______, _______, _______, _______, _______,\
  _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  _______,                   _______, JIS2US,  JIS2US,  JIS2US,  _______, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,\
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
),

[_ADJUST] =  LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, RESET  , _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_PSCR, _______, _______, QWERTY,                    _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, PSEU_US, _______, _______, _______, _______, _______, _______, _______, _______, \
                    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______\
)
};

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed) {
          register_code(KC_LANG2); // for macOS
          register_code(KC_F13);
          unregister_code(KC_F13);
          unregister_code(KC_LANG2);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed) {
          register_code(KC_LANG1); // for macOS
          register_code(KC_F14);
          unregister_code(KC_F14);
          unregister_code(KC_LANG1);
        }
        raise_pressed = false;
      }
      return false;
      break;
    case P_LOWER:
      if (record->event.pressed) {
        lower_pressed = true;

        layer_on(_PSEUDO_US_LOWER);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);
      } else {
        layer_off(_PSEUDO_US_LOWER);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);

        if (lower_pressed) {
          register_code(KC_LANG2); // for macOS
          register_code(KC_F13);
          unregister_code(KC_F13);
          unregister_code(KC_LANG2);
        }
        lower_pressed = false;
      }
      return false;
      break;
    case P_RAISE:
      if (record->event.pressed) {
        raise_pressed = true;

        layer_on(_PSEUDO_US_RAISE);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);
      } else {
        layer_off(_PSEUDO_US_RAISE);
        update_tri_layer(_PSEUDO_US_LOWER, _PSEUDO_US_RAISE, _ADJUST);

        if (raise_pressed) {
          register_code(KC_LANG1); // for macOS
          register_code(KC_F14);
          unregister_code(KC_F14);
          unregister_code(KC_LANG1);
        }
        raise_pressed = false;
      }
      return false;
      break;
    case JIS2US:
      action_pseudo_lut(record, _QWERTY, keymap_jis2us);
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    default:
      if (record->event.pressed) {
        // reset the flags
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }
  return true;
}
