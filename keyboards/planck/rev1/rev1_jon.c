// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "planck.h"
#include "backlight.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QW 0
#define _LW 1
#define _RS 2
#define _VI 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QW] = { /* Qwerty */
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,             KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC },
  {KC_FN2,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,             KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT },
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,             KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_FN1  },
  {M(0),    KC_LALT, KC_LCTL, KC_LGUI, MO(_LW), LT(_VI, KC_SPC),  LT(_VI, KC_SPC),  MO(_RS), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
},
[_RS] = { /* RAISE */
  {KC_GRV,  KC_1,    KC_2,    KC_3,     KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_WREF, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_LW] = { /* LOWER */
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},
[_VI] = { /* VI + Tmux Macros */
  {KC_TRNS, M(9),    M(8),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
  {KC_TRNS, M(2),    KC_TRNS, M(1),    KC_TRNS, KC_TRNS, KC_TRNS, M(4),    KC_TRNS, M(7),    M(6),    M(5)   },
  {KC_TRNS, M(10),   M(3),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
  {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS}
},
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_ENT), // Right shift when held, enter when tapped
  [2] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC), // Left Ctrl when held, esc when tapped
  [3] = ACTION_LAYER_TAP_KEY(_RS, KC_BSPC), // Hold for upper layer tap for back space
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          // LED brightness
          if (record->event.pressed) {
            register_code(KC_RSFT);
            backlight_step();
          } else {
            unregister_code(KC_RSFT);
          }

          break;
        case 1:
          // vi close buffer
          if(record->event.pressed) {
            return MACRO( T(ESC), D(LSFT), T(SCLN), U(LSFT), T(B), T(D), T(ENT), END );
          }
          break;
        case 2:
          // Tmux prev window
          if(record->event.pressed) {
            return MACRO( D(LCTL), T(A), T(A), U(LCTL), END );
          }
          break;
        case 3:
          // Tmux close pane
          if(record->event.pressed) {
            return MACRO( D(LCTL), T(A), U(LCTL), T(X), END );
          }
          break;
        case 4:
          // Tmux split horizontally
          if(record->event.pressed) {
            return MACRO( D(LCTL), T(A), U(LCTL), T(MINS), END );
          }
          break;
        case 5:
          // Tmux split vertically
          if(record->event.pressed) {
            return MACRO( D(LCTL), T(A), U(LCTL), D(LSFT), T(BSLASH), U(LSFT), END );
          }
          break;
        case 6:
          // VI move down by paragraph
          if(record->event.pressed) {
            return MACRO( D(LSFT), T(RCBR), U(LSFT), END );
          }
          break;
        case 7:
          // VI move up by paragraph
          if(record->event.pressed) {
            return MACRO( D(LSFT), T(LCBR), U(LSFT), END );
          }
          break;
        case 8:
          // VI save
          if(record->event.pressed) {
            return MACRO( T(ESC), D(LSFT), T(SCLN), U(LSFT), T(W), T(ENT), END );
          }
          break;
        case 9:
          // VI quit
          if(record->event.pressed) {
            return MACRO( T(ESC), D(LSFT), T(SCLN), U(LSFT), T(Q), T(ENT), END );
          }
          break;
        case 10:
          // Tmux zoom
          if(record->event.pressed) {
            return MACRO( D(LCTL), T(A), U(LCTL), T(Z), END );
          }
          break;
      }
    return MACRO_NONE;
};

