#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include "main.h"
#include "output_pin_toggler.h"
#include "random_number_getter.h"

void app_main(void)
{
    ESP_LOGI(TAG, "Begin, displaying system information");

    display_system_info();

    ESP_LOGI(TAG, "Spawning tasks");

    xTaskCreate(led_blinker_task, "led_blinker_task", 3072, NULL, 5, NULL);
    xTaskCreate(fake_sensors_value_printer_task, "random_sensors_value_printer_task", 3072, NULL, 5,
                NULL);
}

void display_system_info(void)
{
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    ESP_LOGI(TAG, "This is %s chip with %d CPU core(s), %s%s%s%s", CONFIG_IDF_TARGET,
             chip_info.cores, (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
             (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
             (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;

    ESP_LOGI(TAG, "Silicon revision v%d.%d", major_rev, minor_rev);

    uint32_t flash_size;

    if (esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        ESP_LOGE(TAG, "Failure trying to get flash size!");
        return;
    }

    ESP_LOGI(TAG, "%" PRIu32 "MB %s flash", flash_size / (uint32_t)(1024 * 1024),
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    ESP_LOGI(TAG, "Minimum free heap size: %" PRIu32 " bytes", esp_get_minimum_free_heap_size());
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
        ESP_LOGI(TAG, "Fake sensors values: { %f, %f }", get_random_number_between(0.0, 10.0),
                 get_random_number_between(-1.0, 1.0));

        vTaskDelay(pdMS_TO_TICKS(WAIT_PERIOD_MS));
    }
}
