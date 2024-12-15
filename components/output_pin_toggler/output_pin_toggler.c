#include "output_pin_toggler.h"

void output_pin_init(output_pin_s *output_pin, gpio_num_t pin)
{
    if (output_pin == NULL) {
        return;
    }

    output_pin->pin = pin;
    output_pin->state = OUTPUT_PIN_STATE_OFF;

    ESP_ERROR_CHECK(gpio_reset_pin(output_pin->pin));
    ESP_ERROR_CHECK(gpio_set_direction(output_pin->pin, GPIO_MODE_OUTPUT));

    return;
}

output_pin_state_e output_pin_get_state(output_pin_s *output_pin)
{
    if (output_pin == NULL) {
        return OUTPUT_PIN_STATE_OFF;
    }

    return output_pin->state;
}

void output_pin_toggle(output_pin_s *output_pin)
{
    if (output_pin == NULL) {
        return;
    }

    ESP_ERROR_CHECK(gpio_set_level(output_pin->pin, (uint32_t)output_pin->state));

    output_pin->state =
        (output_pin->state == OUTPUT_PIN_STATE_ON ? OUTPUT_PIN_STATE_OFF : OUTPUT_PIN_STATE_ON);

    return;
}
