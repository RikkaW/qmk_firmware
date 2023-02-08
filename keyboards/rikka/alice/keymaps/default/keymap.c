#include QMK_KEYBOARD_H

enum layer_names { _BASE, _FN1, _FN2, _FN3 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[_BASE] = LAYOUT_all(QK_GESC, KC_1, KC_TAB, KC_Q),

                                                              [_FN1] = LAYOUT_all(KC_GRV, KC_F1, RGB_TOG, RGB_MOD),

                                                              [_FN2] = LAYOUT_all(_______, _______, _______, _______),

                                                              [_FN3] = LAYOUT_all(_______, _______, _______, _______)};
