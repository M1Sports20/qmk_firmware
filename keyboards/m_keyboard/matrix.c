/* Copyright 2021 Michael Spradling <mike@mspradling.com>
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

#include "matrix.h"
#include "quantum/quantum.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static void select_col(uint8_t col) { setPinOutput_writeLow(col_pins[col]); }

static void unselect_col(uint8_t col) { setPinInputHigh_atomic(col_pins[col]); }

static void unselect_cols(void) {
    for (uint8_t x = 0; x < (MATRIX_COLS - 1); x++) {
        setPinInputHigh_atomic(col_pins[x]);
    }
}

void matrix_init_custom(void) {
    // Initialize 3 keys outside of standard matrix
    setPinInputHigh(C13);
    setPinInputHigh(C14);
    setPinInputHigh(C15);

    // Initialize regular matrix data structures and row/col pins
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
	setPinInputHigh_atomic(row_pins[x]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    matrix_io_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin HI, clear col bit
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_row_value)) {
            matrix_changed |= true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}

static bool read_direct_pins(matrix_row_t current_matrix[], int row, pin_t pin) {
    matrix_row_t last_row_value = current_matrix[row];
    if (readPin(pin) == 0) {
	current_matrix[row] |= (MATRIX_ROW_SHIFTER << (MATRIX_COLS - 1));
    } else {
	current_matrix[row] &= ~(MATRIX_ROW_SHIFTER << (MATRIX_COLS - 1));
    }

    if (last_row_value != current_matrix[row]) {
	return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set col, read rows
    for (uint8_t current_col = 0; current_col < (MATRIX_COLS - 1); current_col++) {
	changed |= read_rows_on_col(current_matrix, current_col);
    }

    changed |= read_direct_pins(current_matrix, 1, C14);
    changed |= read_direct_pins(current_matrix, 2, C15);
    changed |= read_direct_pins(current_matrix, 4, C13);

    return changed;
}
