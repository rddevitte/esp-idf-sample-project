#ifndef MAIN_H
#define MAIN_H

#include "sdkconfig.h"

#define BLINK_LED_GPIO_PIN CONFIG_BLINK_LED_GPIO_PIN
#define WAIT_PERIOD_MS CONFIG_WAIT_PERIOD_MS

static const char *TAG = "esp-idf-sample-project";

static void display_system_info(void);

static void led_blinker_task(void *pvParameters);

static void fake_sensors_value_printer_task(void *pvParameters);

#endif  // MAIN_H
