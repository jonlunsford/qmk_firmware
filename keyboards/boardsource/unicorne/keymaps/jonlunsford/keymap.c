#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#include "music-bars.c"
#endif

enum unicorne_layers { _QWERTY, _VIMUX, _UTIL, _LOWER, _RAISE, _ADJUST };

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
#define UTIL MO(_UTIL)
/* _VIMUX layer when held, space when tapped */
#define VIMUX LT(_VIMUX, KC_SPC)
/* Homerow mods left */
#define HOME_ESC LCTL_T(KC_ESC)
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)
/* Homerow mods right */
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L RALT_T(KC_L)
#define HOME_SCLN RCTL_T(KC_SCLN)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_split_3x6_3(
	KC_TAB,   KC_Q,   KC_W,   KC_E,    KC_R,   KC_T,      KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,      KC_BSPC,
	HOME_ESC, HOME_A, HOME_S, HOME_D,  HOME_F, KC_G,      KC_H,   HOME_J, HOME_K,  HOME_L, HOME_SCLN, KC_QUOT,
	KC_LSFT,  KC_Z,   KC_X,   KC_C,    KC_V,   KC_B,      KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,   RSFT_T(KC_ENT),
	                          LOWER,   UTIL,   KC_TAB,    KC_ENT, VIMUX,  RAISE
),

[_LOWER] = LAYOUT_split_3x6_3(
	KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
	KC_DEL,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,     _______, KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
	_______, _______, _______, _______, _______, _______,     _______, S(KC_NUHS), S(KC_NUBS), KC_VOLD, KC_VOLU, KC_MPLY,
	                           _______, _______, _______,     _______, _______, _______
),

[_RAISE] = LAYOUT_split_3x6_3(
	KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
	KC_DEL,  KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, _______,     _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
	_______, _______, _______, _______, _______, _______,     _______, KC_NUHS, KC_NUBS, KC_VOLD, KC_VOLU, KC_MPLY,
	                           _______, _______, _______,     _______, _______, _______
),

[_ADJUST] = LAYOUT_split_3x6_3(
	QK_BOOT, _______, _______, _______, _______, _______,    RGB_VAI, RGB_HUI, RGB_SAI, RGB_MOD,  RGB_TOG, _______,
	EE_CLR,  _______, _______, _______, _______, _______,    RGB_VAD, RGB_HUD, RGB_SAD, RGB_RMOD, CK_TOGG, _______,
	_______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______,  _______,
	                           _______, _______, _______,    _______, _______, _______
),

[_VIMUX] = LAYOUT_split_3x6_3(
    _______, V_Q, V_W,     _______, _______, _______,    _______, _______, _______, _______, _______, _______,
    _______, T_P, _______, V_BD,    _______, _______,    _______, T_SH,    _______, V_PU,    V_PD,    T_SV,
    _______, T_Z, T_C,     _______, _______, _______,    _______, _______, _______, _______, _______, _______,
	                       _______, _______, _______,    _______, _______, _______
),

[_UTIL] = LAYOUT_split_3x6_3(
     _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______,  _______, _______,
    KC_F1,    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_F6,      KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,
    KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     _______, _______, _______, _______,  _______, _______,
	                           _______, _______, _______,     KC_BSPC, _______, _______
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

#ifdef OLED_ENABLE
static void render_layer_state(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _VIMUX:
            oled_write_P(PSTR("VIMUX\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJUST\n"), false);
            break;
        case _UTIL:
            oled_write_P(PSTR("UTIL\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_state();
    } else {
        oled_render_anim();
    }

    return false;
}
#endif
