#ifndef OUTPUT_PIN_TOGGLER_H
#define OUTPUT_PIN_TOGGLER_H

#include "driver/gpio.h"

enum output_pin_state { OUTPUT_PIN_STATE_OFF = 0, OUTPUT_PIN_STATE_ON = 1 };

typedef enum output_pin_state output_pin_state_e;

struct output_pin {
    gpio_num_t pin;
    output_pin_state_e state;
};

typedef struct output_pin output_pin_s;

void output_pin_init(output_pin_s *output_pin, gpio_num_t pin);

output_pin_state_e output_pin_get_state(output_pin_s *output_pin);

void output_pin_toggle(output_pin_s *output_pin);

#endif  // OUTPUT_PIN_TOGGLER_H
