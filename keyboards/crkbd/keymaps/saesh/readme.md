# RGB

Only RGB matrix mode is used to have better control of leds.

## Red lighting on reset

The hook `void shutdown_user(void)` is used to set the lighting before resetting the controller.

```c
__attribute__((weak))
void shutdown_keymap(void) {}
void rgb_matrix_update_pwm_buffers(void);

static void set_background_red(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all( 0xFF, 0x00, 0x00 );
    rgb_matrix_update_pwm_buffers();
#endif
}

void shutdown_user(void) {
    set_background_red();
    shutdown_keymap();
}
```

## Highlight certain keys on layer change

In `void rgb_matrix_indicators_user(void)` individual keys can be set. Using `layer_state` it is possible
to have keys light up per layer. When using `rgb_matrix_set_color()` to set a key by its matrix code take
note that the indices are mirrored, see `rev1.c`. The top right key on the left side of the board is indexed
with 9. On the right side the top left key is indexed also 9. Only execute the `rgb_matrix_set_color()`
function on the side you want the key to light up, otherwise both will light up as the code executed on both.