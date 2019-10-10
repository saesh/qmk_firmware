#include "saesh.h"
#include "rgb.h"
extern uint8_t is_master;
void rgb_matrix_update_pwm_buffers(void);

void rgb_matrix_indicators_user(void) {
    switch (biton32(layer_state)) {
        case _LOWER:
            // left side
            if (is_master) rgb_matrix_set_color(17,  0x00, 0xFF, 0x00); // e green
            if (is_master) rgb_matrix_set_color(10,  0xFF, 0x00, 0xFF); // r violet
            if (is_master) rgb_matrix_set_color( 9,  0xFF, 0x80, 0x00); // t orange
            
            // right side
            if (!is_master) rgb_matrix_set_color(17,  0x00, 0xFF, 0x00); // i green
            if (!is_master) rgb_matrix_set_color(10,  0xFF, 0x00, 0xFF); // u violet
            if (!is_master) rgb_matrix_set_color( 9,  0xFF, 0x80, 0x00); // y orange

            if (!is_master) rgb_matrix_set_color(8,  0xFF, 0xFF, 0x00); // h yellow
            if (!is_master) rgb_matrix_set_color(11, 0xFF, 0x00, 0x00); // j red
            if (!is_master) rgb_matrix_set_color(16, 0x00, 0xFF, 0x00); // k green
            if (!is_master) rgb_matrix_set_color(19, 0x00, 0x00, 0xFF); // l blue

            if (!is_master) rgb_matrix_set_color(24, 0xFF, 0x00, 0x00); // del red
            if (!is_master) rgb_matrix_set_color(25, 0x00, 0xFF, 0x00); // ' green
            break;
        case _RAISE:
            if (is_master) rgb_matrix_set_color(22, 0xFF, 0x00, 0x51); // a white
            if (is_master) rgb_matrix_set_color(19, 0xFF, 0xFF, 0xFF); // s white
            if (is_master) rgb_matrix_set_color(16, 0xFF, 0x00, 0x51); // d white
            if (is_master) rgb_matrix_set_color(11, 0xFF, 0xFF, 0xFF); // f white
            if (is_master) rgb_matrix_set_color( 8, 0xFF, 0x00, 0x51); // g white

            if (!is_master) rgb_matrix_set_color( 8, 0xFF, 0xFF, 0xFF); // h white
            if (!is_master) rgb_matrix_set_color(11, 0xFF, 0x00, 0x51); // j white
            if (!is_master) rgb_matrix_set_color(16, 0xFF, 0xFF, 0xFF); // k white
            if (!is_master) rgb_matrix_set_color(19, 0xFF, 0x00, 0x51); // l white
            if (!is_master) rgb_matrix_set_color(22, 0xFF, 0xFF, 0xFF); // ; white
            break;
    }
}

layer_state_t rgb_layer_state_set(layer_state_t state) {
    return state;
}

void rgb_on_power_down(void) {
    rgb_matrix_set_suspend_state(true);
}

void rgb_on_wakeup(void) {
    rgb_matrix_set_suspend_state(false);
}

void set_background_red(void) {
    rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
    rgb_matrix_update_pwm_buffers();
}

void rgb_on_shutdown(void) {
    set_background_red();
}
