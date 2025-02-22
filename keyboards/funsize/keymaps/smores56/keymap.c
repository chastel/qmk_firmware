/* Copyright 2021 Sam Mohr <sam@mohr.codes>
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

#include QMK_KEYBOARD_H
#include "quantum.h"

enum layers {
    _MAIN = 0,
    _SYM_LMOD,
    _NUM_RMOD,
    _NAV,
    _FN
};

// layer controls
#define LMOD    OSL(_SYM_LMOD)
#define RMOD    OSL(_NUM_RMOD)
#define FN      OSL(_FN)
#define SPC_NAV LT(_NAV, KC_SPC)

// one-shot mods
#define LSFT_ OSM(MOD_LSFT)
#define RSFT_ OSM(MOD_RSFT)
#define LALT_ OSM(MOD_LALT)
#define RALT_ OSM(MOD_RALT)
#define LCTL_ OSM(MOD_LCTL)
#define RCTL_ OSM(MOD_RCTL)
#define LGUI_ OSM(MOD_LGUI)
#define RGUI_ OSM(MOD_RGUI)
#define RSG_  OSM(MOD_RSFT | MOD_RGUI)
#define RAG_  OSM(MOD_RALT | MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAIN] = LAYOUT_split_3x5_3(
        KC_Y, KC_C, KC_L,   KC_M,    KC_K,     KC_Z,  KC_F,  KC_U,    KC_COMM, KC_SLSH,
        KC_I, KC_S, KC_R,   KC_T,    KC_G,     KC_P,  KC_N,  KC_E,    KC_A,    KC_O,
        KC_Q, KC_V, KC_W,   KC_D,    KC_J,     KC_B,  KC_H,  KC_QUOT, KC_DOT,  KC_X,
                      LMOD, SPC_NAV, KC_NO,    KC_NO, RSFT_, RMOD
    ),

    [_SYM_LMOD] = LAYOUT_split_3x5_3(
        A(KC_LEFT),  C(KC_W),      C(KC_Q),   C(KC_T), G(KC_L),    KC_LBRC,    KC_DEL,   KC_RBRC,    S(KC_3),    S(KC_GRV),
        LSFT_,       LALT_,        LCTL_,     LGUI_,   KC_PSCR,    S(KC_9),    KC_BSPC,  S(KC_0),    S(KC_COMM), S(KC_BSLS),
        A(KC_RIGHT), C(S(KC_TAB)), C(KC_TAB), KC_NO,   KC_CAPS,    S(KC_LBRC), KC_ENTER, S(KC_RBRC), S(KC_DOT),  S(KC_2),
                                   KC_NO,     KC_NO,   KC_NO,      KC_NO,      KC_TRNS,  FN
    ),

    [_NUM_RMOD] = LAYOUT_split_3x5_3(
        S(KC_4), KC_7, KC_8,   KC_9,  S(KC_8),      KC_NO, RSG_,  C(KC_D), C(KC_D), C(KC_V),
        S(KC_7), KC_1, KC_2,   KC_3,  KC_EQL,       KC_NO, RGUI_, RCTL_,   RALT_,   RSFT_,
        S(KC_6), KC_4, KC_5,   KC_6,  S(KC_EQL),    KC_NO, KC_NO, S(KC_5), KC_NO,   KC_NO,
                       KC_DOT, KC_0, KC_NO,         KC_NO, KC_NO, KC_NO
    ),

    [_NAV] = LAYOUT_split_3x5_3(
        KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,  KC_MUTE,    KC_NO, G(KC_D),     S(G(KC_D)), G(KC_Q),  KC_NO,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_MPLY,    RAG_,  G(KC_LEFT),  G(KC_DOWN), G(KC_UP), G(KC_RIGHT), 
        KC_HOME, KC_PGDN, KC_PGUP, KC_END,   KC_MSTP,    KC_NO, G(KC_ENTER), G(KC_O),    G(KC_N),  KC_NO,
                          KC_NO,    KC_NO,   KC_NO,      KC_NO, KC_TRNS,     KC_NO
    ),

    [_FN] = LAYOUT_split_3x5_3(
        KC_NO, KC_F7, KC_F8, KC_F9, KC_F10,    KC_NO, KC_BRIU, KC_BRID, KC_NO,   KC_NO,
        KC_NO, KC_F1, KC_F2, KC_F3, KC_F11,    KC_NO, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
        KC_NO, KC_F4, KC_F5, KC_F6, KC_F12,    KC_NO, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                      KC_NO, KC_NO, KC_NO,     KC_NO, KC_TRNS, KC_NO                           
    ),
};

enum combos {
    WD_TAB,
    VW_ESC,
    HQ_MINS,
    HD_UNDER,
    FD_GRAVE,
    DS_BSLH,
    UC_COLON,
    CL_SCLN,
};

const uint16_t PROGMEM tab_combo[] = {KC_W, KC_D, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_V, KC_W, COMBO_END};
const uint16_t PROGMEM minus_combo[] = {KC_H, KC_QUOT, COMBO_END};
const uint16_t PROGMEM underscore_combo[] = {KC_H, KC_DOT, COMBO_END};
const uint16_t PROGMEM grave_combo[] = {KC_QUOT, KC_DOT, COMBO_END};
const uint16_t PROGMEM backslash_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM colon_combo[] = {KC_U, KC_COMM, COMBO_END};
const uint16_t PROGMEM semicolon_combo[] = {KC_C, KC_L, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [WD_TAB]    = COMBO(tab_combo, KC_TAB),
    [VW_ESC]    = COMBO(escape_combo, KC_ESC),
    [HQ_MINS]   = COMBO(minus_combo, KC_MINS),
    [HD_UNDER]  = COMBO(underscore_combo, S(KC_MINS)),
    [FD_GRAVE]  = COMBO(grave_combo, KC_GRAVE),
    [DS_BSLH]   = COMBO(backslash_combo, KC_BSLS),
    [UC_COLON]  = COMBO(colon_combo, S(KC_SCLN)),
    [CL_SCLN]   = COMBO(semicolon_combo, KC_SCLN),
};

const key_override_t question_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, S(KC_SLSH));
const key_override_t exclamation_mark_override = ko_make_basic(MOD_MASK_SHIFT, KC_COMM, S(KC_1));

const key_override_t **key_overrides = (const key_override_t *[]){
    &question_mark_override,
    &exclamation_mark_override,
    NULL
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 2) {
        // Mouse Scrolling
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
    return true;
}
#endif
