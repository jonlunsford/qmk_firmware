#include QMK_KEYBOARD_H

enum unicorne_layers { _QWERTY, _VIMUX, _LOWER, _RAISE, _ADJUST };

enum unicorne_keycodes {
    QWERTY = SAFE_RANGE,
    T_P,  /* Tmux prev */
    T_SH, /* Tmux split horizontally */
    T_SV, /* Tmux split vertically */
    T_C,  /* Tmux close */
    T_Z,  /* Tmux zoom */
    V_W,  /* Vim :w */
    V_Q,  /* Vim :q */
    V_BD, /* Vim :bd */
    V_PU, /* Vim move paragraph up */
    V_PD, /* Vim move paragraph down */
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
/* _VIMUX layer when held, space when tapped */
#define VIMUX LT(_VIMUX, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_split_3x6_3(
	KC_TAB,         KC_Q, KC_W, KC_E,    KC_R,  KC_T,    KC_Y,   KC_U,  KC_I,    KC_O,   KC_P,    KC_BSPC,
	LCTL_T(KC_ESC), KC_A, KC_S, KC_D,    KC_F,  KC_G,    KC_H,   KC_J,  KC_K,    KC_L,   KC_SCLN, KC_QUOT,
	KC_LSFT,        KC_Z, KC_X, KC_C,    KC_V,  KC_B,    KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT),
	                            KC_LGUI, LOWER, KC_SPC,  VIMUX,  RAISE, KC_RALT
),

[_LOWER] = LAYOUT_split_3x6_3(
	KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
	KC_DEL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
	_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_VOLD, KC_VOLU, KC_MPLY,
	                            _______, _______, _______,  _______, _______, _______
),

[_RAISE] = LAYOUT_split_3x6_3(
	KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,     KC_5,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
	KC_DEL,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_F5,  KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
	_______, KC_F7,   KC_F8,   KC_F9, KC_F10,   KC_F11, KC_F12,  KC_NUHS, KC_NUBS, KC_VOLD, KC_VOLU, KC_MPLY,
	                    _______, _______, _______,  _______, _______, _______
),

[_ADJUST] = LAYOUT_split_3x6_3(
	QK_BOOT, _______, _______, _______, _______, _______, RGB_VAI, RGB_HUI, RGB_SAI, RGB_MOD, RGB_TOG, _______,
	EE_CLR,  _______, _______, _______, _______, _______, RGB_VAD, RGB_HUD, RGB_SAD, RGB_RMOD, CK_TOGG, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	                    _______, _______, _______, _______, _______, _______
),

[_VIMUX] = LAYOUT_split_3x6_3(
    KC_TRNS, V_Q, V_W,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, T_P, KC_TRNS, V_BD,    KC_TRNS, KC_TRNS, KC_TRNS, T_SH,    KC_TRNS, V_PU,    V_PD,    T_SV,
    KC_TRNS, T_Z, T_C,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	                    _______, _______, _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case T_P:
            // Tmux prev window
            if(record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_A);
                tap_code(KC_A);
                unregister_code(KC_LCTL);
            }
            return false;
            break;
        case T_SH:
            // Tmux split horizontally
            if(record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_A);
                unregister_code(KC_LCTL);
                tap_code(KC_MINS);
            }
            return false;
            break;
        case T_SV:
            // Tmux split vertically
            if(record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_A);
                unregister_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_BSLS);
                unregister_code(KC_LSFT);
            }
            return false;
            break;
        case T_C:
            // Tmux close pane
            if(record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_A);
                unregister_code(KC_LCTL);
                tap_code(KC_X);
            }
            return false;
            break;
        case T_Z:
            // Tmux zoom pane
            if(record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_A);
                unregister_code(KC_LCTL);
                tap_code(KC_Z);
            }
            return false;
            break;
        case V_W:
            // Vim write
            if(record->event.pressed) {
                tap_code(KC_ESC);
                register_code(KC_LSFT);
                tap_code(KC_SCLN);
                unregister_code(KC_LSFT);
                tap_code(KC_W);
                tap_code(KC_ENT);
            }
            return false;
            break;
        case V_Q:
            // Vim quit
            if(record->event.pressed) {
                tap_code(KC_ESC);
                register_code(KC_LSFT);
                tap_code(KC_SCLN);
                unregister_code(KC_LSFT);
                tap_code(KC_Q);
                tap_code(KC_ENT);
            }
            return false;
            break;
        case V_BD:
            // Vim close buffer
            if(record->event.pressed) {
                tap_code(KC_ESC);
                register_code(KC_LSFT);
                tap_code(KC_SCLN);
                unregister_code(KC_LSFT);
                tap_code(KC_B);
                tap_code(KC_D);
                tap_code(KC_ENT);
            }
            return false;
            break;
        case V_PU:
            // Vim move paragraph UP
            if(record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LBRC);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LBRC);
            }
            return false;
            break;
        case V_PD:
            // Vim move paragraph DOWN
            if(record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_RBRC);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_RBRC);
            }
            return false;
            break;
    }
    return true;
}
