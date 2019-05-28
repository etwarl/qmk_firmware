/*
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "app_ble_func.h"

enum custom_keycodes {
    AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
    BLE_DIS,              /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    DELBNDS,              /* Delete all bonding                   */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    BATT_LV,              /* Display battery level in milli volts */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    ENT_DFU,              /* Start bootloader                     */
    ENT_SLP,              /* Deep sleep mode                      */
    QWERTY,
    EUCALYN,
    LOWER,
    RAISE,
    ADJUST,
    BACKLIT,
    EISU,
    KANA,
    RGBRST
};


extern keymap_config_t keymap_config;

enum layer_number {
    _QWERTY = 0,
    _EUCALYN,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum { //tapdance_keycodes
  LBR = 0,
  RBR
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

//win-MODE
#define WN_LGUI KC_LALT
#define WN_LALT KC_LGUI

//alias
#define KC_UNDO LCTL(KC_Z)
#define KC_CUT  LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PST  LCTL(KC_V)
#define KC_CAD  LCTL(LALT(KC_DEL))
#define KC_CTSP LCTL_T(KC_SPC)
#define KC_ZNHN LALT(KC_GRV)

#if HELIX_ROWS == 5
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |  1!  |  2@  |  3#  |  4$  |  5%  |             |  6^  |  7&  |  8*  |  9(  |  0)  |  -_  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \|  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |  ;:  |  '"  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Sft  |   Z  |   X  |   C  |   V  |   B  | ([{  | )]}  |   N  |   M  |  ,<  |  .>  |  /?  |  =+  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  `~  | GUI  | Alt  | KANA |Lower |CtrSp |Space |  BS  |Enter |Raise | Left |  Up  | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */ 
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,\
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,\
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,\
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TD(LBR), TD(RBR), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_EQL,\
      KC_GRV,  KC_LGUI, KC_LALT, KC_ZNHN, LOWER,   KC_CTSP, KC_SPC,  KC_BSPC, KC_ENT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT\
      ),

  /* Eucalyn
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |  1!  |  2@  |  3#  |  4$  |  5%  |             |  6^  |  7&  |  8*  |  9(  |  0)  |  -_  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |  ;:  |  ,<  |  .>  |   P  |   Q  |             |   Y  |   G  |   D  |   M  |   F  |  \|  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   I  |   U  |             |   B  |   N  |   T  |   R  |   S  |  '"  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Sft  |   Z  |   X  |   C  |   V  |   W  | ([{  | )]}  |   H  |   J  |   K  |   L  |  /?  |  =+  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  `~  |C+A+D | GUI  | Alt  |Lower |CtrSp |Space |  BS  |Enter |Raise | Left |  Up  | Down |Right |
   * `-------------------------------------------------------------------------------------------------'
   */ 
  [_EUCALYN] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,\
      KC_TAB,  KC_SCLN, KC_COMM, KC_DOT,  KC_P,   KC_Q,                      KC_Y,    KC_G,    KC_D,    KC_M,    KC_F,    KC_BSLS,\
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_I,   KC_U,                      KC_B,    KC_N,    KC_T,    KC_R,    KC_S,    KC_QUOT,\
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_W,    TD(LBR), TD(RBR), KC_H,    KC_J,    KC_K,    KC_L,    KC_SLSH, KC_EQL,\
      KC_GRV,  KC_LGUI, KC_LALT, KC_ZNHN, LOWER,  KC_CTSP, KC_SPC,  KC_BSPC, KC_ENT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT\
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | ESC  | 1!   |  2@  |  3#  |  4$  |  5%  |             |  6^  |  7&  |  8*  |  9(  |  0)  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             | Left | Down |  Up  |Right |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      | PGUP |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | CAD  |      |      |      |      |      | DEL  |      |      |      | HOME | PGDN | End  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
      _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
      _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_WH_L, KC_WH_R, _______, _______, _______, _______, _______, KC_PGUP, _______, \
      _______, KC_CAD,  _______, _______, _______, _______, _______, KC_DEL,  _______, _______, KC_APP,  KC_HOME, KC_PGDN, KC_END \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  `~  |  F1  |  F2  |  F3  |  F4  |  F5  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F6  |  F7  |  F8  |  F9  |  F10 |             | Left | Down |  Up  |Right |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |  F11 |  F12 |      |      |      |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     _______, _______, _______, _______, _______, _______, \
      KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     _______, _______, _______, _______, _______, _______, \
      _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
      _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ADV  | ADV_1| ADV_2|      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | BATT | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             | Win  |Qwerty|Eucaly|      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      AD_WO_L, ADV_ID1, ADV_ID2, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      BATT_LV, RESET,   RGBRST,  _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, AG_NORM,                   AG_SWAP, QWERTY,  EUCALYN, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )

};
#else
#error "undefined keymaps"
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;
#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  layer_state_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  char str[16];
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case EUCALYN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_EUCALYN);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(16);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  if (record->event.pressed) {
    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      sprintf(str, "%4dmV", get_vcc());
      send_string(str);
      return false;
    case ENT_DFU:
      bootloader_jump();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }
  }
  return true;
}

//Tap Dance Settings
void l_brc_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LSFT);
    register_code (KC_9);
  } else if (state->count == 2) {
    register_code (KC_LBRC);
  } else {
    register_code (KC_LSFT);
    register_code (KC_LBRC);
  }
}

void l_brc_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LSFT);
    unregister_code (KC_9);
  } else if (state->count == 2) {
    unregister_code (KC_LBRC);
  } else {
    unregister_code (KC_LSFT);
    unregister_code (KC_LBRC);
  }
}


void r_brc_dance_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LSFT);
    register_code (KC_0);
  } else if (state->count == 2) {
    register_code (KC_RBRC);
  } else {
    register_code (KC_LSFT);
    register_code (KC_RBRC);
  }
}

void r_brc_dance_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LSFT);
    unregister_code (KC_0);
  } else if (state->count == 2) {
    unregister_code (KC_RBRC);
  } else {
    unregister_code (KC_LSFT);
    unregister_code (KC_RBRC);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [LBR] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, l_brc_dance_finished, l_brc_dance_reset)
 ,[RBR] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, r_brc_dance_finished, r_brc_dance_reset)
};
;
