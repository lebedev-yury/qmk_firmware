/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _SYMB,
  _NUMB
};

enum planck_keycodes {
  QWERTY,
  SYMB,
  NUMB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Hyper| Numb | Alt  | Cmd  | Symb | Space| Enter| Symb | Cmd  | Alt  |  Numb| Tmux |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,      KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,      KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSPO,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,      KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC},
  {ALL_T(KC_NO),  NUMB,    KC_LALT, KC_LGUI, SYMB,    KC_SPC,  KC_ENTER,  SYMB,    KC_LGUI, KC_LALT, NUMB,    LCTL(KC_B)}
},

/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   -  |   =  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   `  |   (  |   {  |   }  |   )  | Left | Down |  Up  | Right|   _  |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   ~  |   |  |   [  |   ]  |      |      | Home |PgDown| PgUp |  End |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = {
  {_______, KC_EXLM,  KC_AT,   KC_HASH,     KC_DLR,      KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINUS, KC_EQUAL, KC_BSLASH},
  {_______, KC_GRAVE, KC_LPRN, KC_LCBR,     KC_RCBR,     KC_RPRN, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_UNDS,  KC_PLUS},
  {_______, KC_TILD,  KC_PIPE, KC_LBRACKET, KC_RBRACKET, _______, _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,   _______},
  {_______, _______,  _______, _______,     _______,     _______, _______, _______, _______, _______,  _______,  _______}
},

/* Numbers
 * ,-----------------------------------------------------------------------------------.
 * | RESET|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   |  |   &  |   *  |   /  |   %  |   ^  |   +  |   -  |   =  |   !  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMB] = {
  {RESET,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,    KC_BSLASH},
  {_______, KC_PIPE, KC_AMPR, KC_ASTR, KC_SLSH, KC_PERC, KC_CIRC, KC_PLUS, KC_MINUS, KC_EQUAL, KC_EXLM, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______}
}

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SYMB:
      if (record->event.pressed) {
        layer_on(_SYMB);
      } else {
        layer_off(_SYMB);
      }
      return false;
      break;
    case NUMB:
      if (record->event.pressed) {
        layer_on(_NUMB);
      } else {
        layer_off(_NUMB);
      }
      return false;
      break;
  }
  return true;
}
