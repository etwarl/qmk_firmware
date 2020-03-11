#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _EUCALYN,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  EUCALYN,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
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
#define KC_LWBS LT(_LOWER,KC_BSPC) //
#define KC_UNDO LCTL(KC_Z)
#define KC_CUT  LCTL(KC_X)
#define KC_COPY LCTL(KC_C)
#define KC_PST  LCTL(KC_V)
#define KC_CAD  LCTL(LALT(KC_DEL))
#define KC_CTSP LCTL_T(KC_SPC)
#define KC_ZNHN LALT(KC_GRV)

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

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
      KC_GRV,  WN_LGUI, WN_LALT, KC_ZNHN, KC_LSFT, KC_LSFT, KC_SPC,  KC_BSPC, KC_RSFT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT\
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
      KC_GRV,  WN_LGUI, WN_LALT, KC_ZNHN, LOWER,  KC_CTSP, KC_SPC,  KC_BSPC, KC_ENT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT\
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |  F7  |  F8  |  F9  |  F10 |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |  Up  |      |      |  F11 |             |  F12 |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Left | Down |Right |      |      |             | Left | Down |  Up  |Right |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | Undo | Cut  | Copy |Paste |      |      |      |      |      |      |      | PGUP |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      | CAD  |      |      |      |      |      | DEL  |      |      |      | HOME | PGDN | End  |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
      _______, _______, KC_UP,   _______, _______, KC_F11,                    KC_F12,  _______, _______, _______, _______, _______, \
      _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
      _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PST,  _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______, \
      _______, KC_CAD,  _______, _______, _______, _______, _______, KC_DEL,  _______, _______, KC_APP,  KC_HOME, KC_PGDN, KC_END \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             | Bksp |  P7  |  P8  |  P9  |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |             |  Tab |  P4  |  P5  |  P6  |   -  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |Numlk |PrtScr|      |      |      |             |      |  P1  |  P2  |  P3  |   +  |  Ent |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |  P0  |  ,   |  .   |      |  Ent |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_BSPC, KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX, \
      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                    KC_TAB,  KC_4,    KC_5,    KC_6,    KC_MINS, XXXXXXX, \
      _______, KC_NLCK, KC_PSCR, _______, _______, _______,                   XXXXXXX, KC_1,    KC_2,    KC_3,    KC_PLUS, KC_ENT, \
      _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_0,    KC_COMM, KC_DOT,  XXXXXXX, KC_ENT, \
      _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             | Win  |Qwerty|Eucaly|      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      _______, RESET,   RGBRST,  _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL, \
      _______, _______, _______, _______, _______, AG_NORM,                   AG_SWAP, QWERTY,  EUCALYN, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      )
};


#ifdef AUDIO_ENABLE
  float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
  float tone_plover[][2]     = SONG(PLOVER_SOUND);
  float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
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
          PLAY_SONG(tone_qwerty);
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
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

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
