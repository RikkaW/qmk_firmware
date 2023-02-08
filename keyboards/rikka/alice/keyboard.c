#include <stdio.h>
#include <stdbool.h>
//#include "config.h"
#include "quantum.h"
#include "print.h"
#include "debug.h"

void keyboard_post_init_kb(void) {
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
}
