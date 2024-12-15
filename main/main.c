#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "main.h"
#include "output_pin_toggler.h"
#include "random_number_getter.h"

void app_main(void)
{
    ESP_LOGI(TAG, "begin, spawning tasks");

    xTaskCreate(led_blinker_task, "led_blinker_task", 3072, NULL, 5, NULL);
    xTaskCreate(fake_sensors_value_printer_task, "random_sensors_value_printer_task", 3072, NULL, 5,
                NULL);
}

void led_blinker_task(void *pvParameters)
{
    output_pin_s led;
    output_pin_init(&led, BLINK_LED_GPIO_PIN);

    while (1) {
        ESP_LOGI(TAG, "Turning the LED %s",
                 output_pin_get_state(&led) == OUTPUT_PIN_STATE_ON ? "on" : "off");

        output_pin_toggle(&led);

        vTaskDelay(pdMS_TO_TICKS(WAIT_PERIOD_MS));
    }
}

void fake_sensors_value_printer_task(void *pvParameters)
{
    while (1) {
        ESP_LOGI(TAG, "fake sensors values: { %f, %f }", get_random_number_between(0.0, 10.0),
                 get_random_number_between(-1.0, 1.0));

        vTaskDelay(pdMS_TO_TICKS(WAIT_PERIOD_MS));
    }
}
