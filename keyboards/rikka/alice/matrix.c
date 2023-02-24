#include <stdio.h>
#include <stdbool.h>
#include <config.h>
#include <quantum.h>
#include <print.h>
#include <spi_master.h>
#include <ch.h>
#include "keyboard.h"

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_read[MATRIX_ROWS];
static matrix_row_t matrix_read_debouncing[MATRIX_ROWS];
static size_t size_matrix = MATRIX_ROWS * sizeof(matrix_row_t);

static void sn74x165_init(void) {
    setPinOutput(SN74X165_PL_PIN);
    writePinHigh(SN74X165_PL_PIN);
    spi_init();
    spi_start(SN74X165_SPI_SLAVE_SELECT_PIN, SN74X165_SPI_LSBFIRST, SN74X165_SPI_MODE, SN74X165_SPI_CLOCK_DIVISOR);
}

static bool sn74x165_spi_receive(uint8_t *out) {
    writePinLow(SN74X165_PL_PIN);
    wait_us(30);
    writePinHigh(SN74X165_PL_PIN);

    // TODO: until the right side PCB comes
    return spi_receive(out, /*SN74X165_LENGTH*/ 6) == SPI_STATUS_SUCCESS;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {

}

void matrix_init(void) {
    sn74x165_init();

    memset(matrix, 0, size_matrix);
    memset(matrix_read, 0, size_matrix);
    memset(matrix_read_debouncing, 0, size_matrix);

    // This *must* be called for correct keyboard behavior
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    bool changed = false;

    if (!sn74x165_spi_receive(matrix_read)) {
        print("74x165_spi_receive failed\n");
        goto end;
    }

    if (!sn74x165_spi_receive(matrix_read_debouncing)) {
        print("74x165_spi_receive failed\n");
        goto end;
    }

    // Low = pressed
    for (int i = 0; i < MATRIX_ROWS; ++i) {
        matrix_read[i] = ~matrix_read[i];
        matrix_read_debouncing[i] = ~matrix_read_debouncing[i];
    }

    // Low after 100us should be really pressed
    for (int i = 0; i < MATRIX_ROWS; ++i) {
        matrix_read[i] &= matrix_read_debouncing[i];
    }

    // TODO: remove until the right side PCB comes
    memset(matrix + 6, 0, size_matrix / 2);
    memset(matrix_read + 6, 0, size_matrix / 2);

    // TODO: change PCB design to make them always high
    matrix_read[0] &= 0b01111111;
    matrix_read[1] &= 0b01111111;
    matrix_read[2] &= 0b00111111;
    matrix_read[3] &= 0b00111111;
    matrix_read[4] &= 0b00111111;
    matrix_read[5] &= 0b00001111;
    matrix_read[6] &= 0b01111111;
    matrix_read[7] &= 0b01111111;
    //matrix_read[8] &= 0b11111111;
    matrix_read[9] &= 0b01111111;
    //matrix_read[10] &= 0b11111111;
    matrix_read[11] &= 0b00001111;

    for (int i = 0; i < MATRIX_ROWS; ++i) {
        if (matrix_read[i] != matrix[i]) {
            uprintf("ROW %d: %d->%d\n", i, matrix[i], matrix_read[i]);
            matrix[i] = matrix_read[i];

            changed = true;
        }
    }

end:
    // This *must* be called for correct keyboard behavior
    matrix_scan_quantum();
    return changed;
}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}