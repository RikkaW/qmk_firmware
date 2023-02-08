#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "quantum.h"
#include "print.h"
#include "spi_master.h"
#include <ch.h>
#include <keyboard.h>
#include <sn74x165.h>

static uint8_t result[1];

void matrix_init_custom(void) {
    sn74x165_init();
}

bool matrix_scan_custom(matrix_row_t curr_matrix[]) {
    bool changed = false;

    print("matrix_scan_custom\n");

    wait_ms(100);

    if (sn74x165_spi_receive(result)) {
        uprintf("%d\n", result[0]);
    } else {
        print("sn74x165_spi_receive failed\n");
    }

    return changed;
}
