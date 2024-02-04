#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "esp_err.h"

//extern int isobus_main(void);
extern void Network_softAP_main(void);
extern void forte_main(void);
//extern void file_server_main1(void);
//extern void file_server_main2(void);

void app_main(void)
{
    printf("sample without isobus!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

    printf("CONFIG_FREERTOS_HZ: %d must be 1000 !!!! (200Hz at least for 5ms )\n", CONFIG_FREERTOS_HZ);

    assert(CONFIG_FREERTOS_HZ == 1000);

    printf("app_main starting \n");


    Network_softAP_main();

    //file_server_main1();
    //file_server_main2();
    forte_main();
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    printf("forte_main done \n");
}
