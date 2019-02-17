/*
tap danc eis turned on in the rules now...
*/
#include QMK_KEYBOARD_H

#define _EMOJI 0
#define _TAPLAND 1
#define _LEDCNTL 2

enum custom_keycodes {
    SHRUG,
    DISFACE,
    FU,
    TFLIP,
    TFLIP2,
    SAD_EYES,
    TPUT,
    HAPPYFACE,
    HEARTFACE,
    CLOUD,
    CHANFACE,
    CMDCLEAR
};
//Tap Dance Declarations
enum {
  TD_EXAMPLE1 = 0,
  TD_EXAMPLE2,
  TD_EXAMPLE3,
  TD_EXAMPLE4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* EMOJI Pad
    * ,-------------------------------.
    * |TFLIP | TFlIP2|DISFACE|   FU   |
    * |------+-------+-------+--------|
    * | CLOUD|       |       | CLEAR  |
    * |------+-------+-------+--------|
    * |SHRUG |DISFACE| HRTFAC| HAPPYF |
    * |------+-------+-------+--------|
    * | ENTER|       |LEDCNTR| tapland| 
    * `-------------------------------'
    */
      //purple
    [_EMOJI] = LAYOUT_ortho_4x4(
       TFLIP,   TFLIP2,   KC_NO,      FU , 
       CLOUD,   KC_NO,  KC_NO,      CMDCLEAR, 
       SHRUG,   DISFACE,  HEARTFACE,    HAPPYFACE, 
       KC_ENT,  RGB_TOG,  MO(_LEDCNTL), MO(_TAPLAND)
    ),
 
    /* TapLand //
    * ,-------------------------------.
    * | str1 | str2  |  str3 |   str4 |
    * |------+-------+-------+--------|
    * |      |       |       |        |
    * |------+-------+-------+--------|
    * |      |       |       |        |
    * |------+-------+-------+--------|
    * |      |       |       |        | 
    * `-------------------------------'
    */
    //blue
    [_TAPLAND] = LAYOUT_ortho_4x4(
       TD(TD_EXAMPLE1), TD(TD_EXAMPLE2),  TD(TD_EXAMPLE3), TD(TD_EXAMPLE4), 
       KC_NO,         KC_NO,          KC_NO,         KC_NO, 
       KC_NO,         KC_NO,          KC_NO,         KC_NO, 
       KC_NO,         KC_NO,          KC_NO,         KC_NO
    ),
    /* LEDControl Pad
    * ,-------------------------------.
    * | snake|breathe|rainbow|gradient|
    * |------+-------+-------+--------|
    * | xmas |  Val+ | Sat+  |   HUE+ |
    * |------+-------+-------+--------|
    * |kngrdr|  Val- | Sat-  |   HUE- |
    * |------+-------+-------+--------|
    * | swirl| PLAIN |       | ON/OFF | 
    * `-------------------------------'
    */
    //blue
    [_LEDCNTL] = LAYOUT_ortho_4x4(
        RGB_M_SN, RGB_M_B,    RGB_M_R,     RGB_M_G, 
        RGB_M_X,  RGB_VAI,    RGB_SAI,     RGB_HUI, 
        RGB_M_K,  RGB_VAD,    RGB_SAD,     RGB_HUD, 
        RGB_M_SW, RGB_M_P,    KC_NO,     RGB_TOG
     ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case CLOUD:       // (っ◕‿◕)っ
                if(record->event.pressed){
                    send_unicode_hex_string("0028 3063 25D5 203F 25D5 0029 3063");
                }
                return false;
                break;
            case FU:       // t(-_-t)
                if(record->event.pressed){
                    SEND_STRING("t(-_-t)");
                }
                return false;
                break;  
            case HAPPYFACE:       // ʘ‿ʘ 
                if(record->event.pressed){
                     send_unicode_hex_string("0298 203F 0298");
                }
                return false;
                break; 
            case CMDCLEAR:
                if (record->event.pressed) {
                    register_code(KC_LGUI);
                    tap_code(KC_A);                 
                    unregister_code(KC_LGUI);
                    tap_code(KC_DEL);                 
                }
                return false;
                break;  
            case SHRUG: // ¯\_(ツ)_/¯
                if (record->event.pressed) {
                    send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
                }
                return false; 
                break;
            case HEARTFACE:       // ♥‿♥
                if(record->event.pressed){
                    send_unicode_hex_string("2665 203F 2665");
                }
                return false;
                break;  
            case DISFACE:       // ಠ_ಠ 
                if(record->event.pressed){
                    send_unicode_hex_string("0CA0 005F 0CA0");
                }
                return false;
                break;
            case TFLIP:         // (╯°□°)╯ ︵ ┻━┻ 
                if(record->event.pressed){
                    send_unicode_hex_string("0028 256F 00B0 25A1 00B0 0029 256F 0020 FE35 0020 253B 2501 253B");
                }
                return false;
                break;
            case TFLIP2:         // ┻━┻︵ \(°□°)/ ︵ ┻━┻  
                if(record->event.pressed){
                    send_unicode_hex_string("253B 2501 253B FE35 0020 005C 0028 00B0 25A1 00B0 0029 002F 0020 FE35 0020 253B 2501 253B");
                }
                return false;
                break;
                } 
    }
    return true;
}


/* tap dance time */
void tdexample1(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING1);
    reset_tap_dance (state);
  }
}
void tdexample2(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING2);
    reset_tap_dance (state);
  }
}
void tdexample3(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING3);
    reset_tap_dance (state);
  }
}
void tdexample4(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    SEND_STRING(EXAMPLESTRING4);
    reset_tap_dance (state);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_EXAMPLE1] = ACTION_TAP_DANCE_FN(tdexample1),
    [TD_EXAMPLE2] = ACTION_TAP_DANCE_FN(tdexample2),
    [TD_EXAMPLE3] = ACTION_TAP_DANCE_FN(tdexample3),
    [TD_EXAMPLE4] = ACTION_TAP_DANCE_FN(tdexample4)
};

// Runs just one time when the keyboard initializes.
void matrix_scan_user(void) {
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
        rgblight_setrgb (16, 0, 16);
  }
}
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _TAPLAND:
        rgblight_setrgb(0, 16, 0); //green
        break;
    case _LEDCNTL:
        rgblight_setrgb(0, 0, 16); //blue
        break;
    case _EMOJI:
        rgblight_setrgb (16, 0, 16); //purple
        break;

    default: //  for any other layers, or the default layer
        rgblight_setrgb (16, 0, 16); //purple
        break;
    }
  return state;
}