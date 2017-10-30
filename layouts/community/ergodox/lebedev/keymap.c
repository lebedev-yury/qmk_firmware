#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define NUMB 2 // media keys

// Tap Dance keys
enum {
  TD_VIM_MACRO = 0,
  TD_LAYERS_MACRO = 1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_ergodox(
    TD(TD_VIM_MACRO), KC_1,     KC_2,    KC_3,    KC_4,    KC_5, TD(TD_LAYERS_MACRO),
    KC_TAB,           KC_Q,     KC_W,    KC_E,    KC_R,    KC_T, KC_F12,
    CTL_T(KC_ESCAPE), KC_A,     KC_S,    KC_D,    KC_F,    KC_G,
    KC_LSPO,          KC_Z,     KC_X,    KC_C,    KC_V,    KC_B, KC_LBRACKET,
    ALL_T(KC_NO),     MO(NUMB), KC_LALT, KC_LGUI, MO(SYMB),

                                         KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK,
                                                              KC_MEDIA_PLAY_PAUSE,
                                         KC_SPACE, KC_BSPACE, KC_0,


    KC_CAPS,     KC_6, KC_7,     KC_8,     KC_9,    KC_0,      KC_MINUS,
    KC_F12,      KC_Y, KC_U,     KC_I,     KC_O,    KC_P,      KC_BSLASH,
                 KC_H, KC_J,     KC_K,     KC_L,    KC_SCOLON, CTL_T(KC_QUOTE),
    KC_RBRACKET, KC_N, KC_M,     KC_COMMA, KC_DOT,  KC_SLASH,  KC_RSPC,
                       MO(SYMB), KC_LGUI,  KC_LALT, MO(NUMB),  ALL_T(KC_NO),

    KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
    KC_AUDIO_MUTE,
    KC_DLR,            CTL_T(KC_ESCAPE), KC_ENTER
  ),

  [SYMB] = LAYOUT_ergodox(
    M(0),    KC_F1,    KC_F2,   KC_F3,       KC_F4,       KC_F5,    KC_F6,
    KC_TRNS, KC_EXLM,  KC_AT,   KC_HASH,     KC_DLR,      KC_PERC,  KC_TRNS,
    KC_TRNS, KC_GRAVE, KC_LPRN, KC_LCBR,     KC_RCBR,     KC_RPRN,
    KC_TRNS, KC_TILD,  KC_PIPE, KC_LBRACKET, KC_RBRACKET, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS,

                                                                  KC_TRNS, KC_TRNS,
                                                                           KC_TRNS,
                                                         KC_TRNS, KC_TRNS, KC_TRNS,


    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,    KC_F13,
    KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINUS, KC_EQUAL,  KC_TRNS,
             KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_UNDS,   KC_PLUS,
    KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_TRNS,   KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,

    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [NUMB] = LAYOUT_ergodox(
    KC_TRNS, KC_F14,  KC_F15,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_TRNS,
    KC_TRNS, KC_PIPE, KC_AMPR, KC_ASTR, KC_SLASH, KC_PERC,
    KC_TRNS, M(1),    M(2),    M(3),    KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

                                                           KC_TRNS, KC_TRNS,
                                                                    KC_TRNS,
                                                  KC_TRNS, KC_TRNS, KC_TRNS,


    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
    KC_TRNS, KC_6,    KC_7,    KC_8,     KC_9,     KC_0,    KC_TRNS,
             KC_CIRC, KC_PLUS, KC_MINUS, KC_EQUAL, KC_EXLM, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
                      KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,

    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
  case 0:
    if (record->event.pressed) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    break;
  case 1:
    if (record->event.pressed) {
      SEND_STRING("lebedev.yurii@gmail.com");
    }
    break;
  case 2:
    if (record->event.pressed) {
      SEND_STRING("yury.lebedev@td-berlin.com");
    }
    break;
  case 3:
    if (record->event.pressed) {
      SEND_STRING("y.lebedev@reply.de");
    }
    break;
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
  case 1:
    ergodox_right_led_2_on();
    break;
  case 2:
    ergodox_right_led_3_on();
    break;
  default:
    break;
  }
};

void led_set_kb(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    ergodox_right_led_1_on();
  } else{
    ergodox_right_led_1_off();
  }
};

// Record macro to register X on a double press, stop recording, when pressed 3 times.
// Replay macro on a single press
void vim_macro_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    register_code(KC_LSHIFT);
    register_code(KC_2);
    unregister_code(KC_2);
    unregister_code(KC_LSHIFT);

    register_code(KC_X);
    unregister_code(KC_X);
    break;
  case 2:
    register_code(KC_Q);
    unregister_code(KC_Q);

    register_code(KC_X);
    unregister_code(KC_X);
    break;
  case 3:
    register_code(KC_Q);
    unregister_code(KC_Q);
    break;
  }
  reset_tap_dance(state);
}

void layers_macro_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
  case 1:
    layer_off(SYMB);
    layer_off(NUMB);
    break;
  case 2:
    layer_on(SYMB);
    layer_off(NUMB);
    break;
  case 3:
    layer_off(SYMB);
    layer_on(NUMB);
    break;
  }
  reset_tap_dance(state);
}

// Tap Dance Definitions

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_VIM_MACRO] = ACTION_TAP_DANCE_FN(vim_macro_dance_finished),
  [TD_LAYERS_MACRO] = ACTION_TAP_DANCE_FN(layers_macro_dance_finished)
};
