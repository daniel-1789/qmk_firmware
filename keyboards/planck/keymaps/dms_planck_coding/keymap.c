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
 * qmk compile -kb planck/rev6 -km dms_planck_coding
 * qmk compile -kb planck/ez -km dms_ez_planck_coding
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "debug.h"
#include "action_layer.h"
#include "process_tap_dance.h"
#include "quantum.h"

#define KC_SPOT XXXXXXX
#define KC_DICT XXXXXXX
#define KC_SLEEP KC_SLEP


enum planck_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMNUM
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  MACRO_LOCK,
  MACRO_SCREENCAP,
  MACRO_SCREENCAP5,
  MACRO_CTRL_ALT_DEL,
  EN_DASH,
  EM_DASH,
  MACRO_SPOTLIGHT,
  MACRO_DICTATION


};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define NUMNUM MO(_NUMNUM)

enum {
    TD_DASHES
};

void dash_dance(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_DASHES] = ACTION_TAP_DANCE_FN(dash_dance)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |  F*  |   G  |   H  |  J*  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |NumNum| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,             KC_T,    KC_Y,    KC_U,            KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,             KC_G,    KC_H,    KC_J,            KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,             KC_B,    KC_N,    KC_M,            KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    NUMNUM,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,            KC_SPC,  KC_SPC,  RAISE,           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   [  |   ]  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |   { |    }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PGDN | PGUP | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LBRC, KC_RBRC, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_LCBR, KC_RCBR,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_HOME,    KC_PGDN, KC_PGUP, KC_END
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | ScCp5| Lock |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,          KC_8,    KC_9,            KC_0,       KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   TD(TD_DASHES), KC_EQL,  KC_LBRC,         KC_RBRC,    KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS,       KC_NUBS, MACRO_SCREENCAP5,MACRO_LOCK, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,       KC_MNXT, KC_VOLD,         KC_VOLU,    KC_MPLY
),



/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|C A D |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      | PrSc |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | ScCp |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI,        RGB_VAD, MACRO_CTRL_ALT_DEL ,
    _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,  _______,        KC_PSCR, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, MACRO_SCREENCAP, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,        _______, _______
),

/* Extra Stuff
* ,-----------------------------------------------------------------------------------.
* |  Br- |  Br+ |  MC  | Spot | Dict |Sleep | Prev | Play | Next | Mute | Vol- | Vol+ |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |C A D |      |      |      |      |      |  -   |  –   |  —   |      |Enter |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |    Space    |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/
[_NUMNUM] = LAYOUT_planck_grid(
    KC_BRID, KC_BRIU,            KC_MCTL, MACRO_SPOTLIGHT, MACRO_DICTATION, KC_SLEEP, KC_MRWD,KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU,
    KC_F1,   KC_F2,              KC_F3,   KC_F4,           KC_F5,           KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, MACRO_CTRL_ALT_DEL, XXXXXXX, XXXXXXX,         XXXXXXX,         XXXXXXX, XXXXXXX, KC_MINS, EN_DASH, EM_DASH, XXXXXXX, KC_ENT,
    _______, _______,            _______, _______,         _______,         KC_SPC,   KC_SPC, _______, _______, _______, _______, _______
)
};



#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;

        case BACKLIT:
            if (record->event.pressed) {
                register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
                backlight_step();
#endif
#ifdef KEYBOARD_planck_rev5
                writePinLow(E6);
#endif
            } else {
                unregister_code(KC_RSFT);
#ifdef KEYBOARD_planck_rev5
                writePinHigh(E6);
#endif
            }
            return false;

        case MACRO_LOCK:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_Q))));
            }
            return false;

        case MACRO_SCREENCAP:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_3))));
            }
            return false;

        case MACRO_SCREENCAP5:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_5))));
            }
            return false;

        case MACRO_CTRL_ALT_DEL:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DELETE))));
            }
            return false;

        case EN_DASH:
            if (record->event.pressed) {
                SEND_STRING("–");  // U+2013
            }
            return false;

        case EM_DASH:
            if (record->event.pressed) {
                SEND_STRING("—");  // U+2014
            }
            return false;

        case MACRO_SPOTLIGHT:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(" "));
            }
            return false;

        case MACRO_DICTATION:
            if (record->event.pressed) {
                // Dictation may need to be remapped in macOS System Settings to use Cmd+D
                SEND_STRING(SS_LGUI("D"));
            }
            return false;

    }

    return true;
}


bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

void dash_dance(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("-");
    } else if (state->count == 2) {
        SEND_STRING(SS_LALT("-")); // Option + - → en dash
    } else if (state->count == 3) {
        SEND_STRING(SS_LSFT(SS_LALT("-"))); // Shift + Option + - → em dash
    }
}

