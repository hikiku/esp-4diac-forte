#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



#include "esp_log.h"



#include "forteinit.h"
#include "forte_Init.h"


static const char *const TAG = "MAIN";

extern "C" {
void forte_main(void);
void wifi_init_sta(void);
}



static uint8_t ucParameterToPass;
TaskHandle_t xHandle = NULL;

void MyForteTask(void *pvParameters)
{

    ESP_LOGI(TAG, "Executing forte...");

    forteGlobalInitialize();
    TForteInstance forteInstance = 0;
    int resultForte = forteStartInstanceGeneric(0, 0, &forteInstance);
    if (FORTE_OK == resultForte)
    {
        ESP_LOGI(TAG,"OK %d , Could start forte\n", resultForte);
        forteJoinInstance(forteInstance);
    }
    else
    {
         ESP_LOGE(TAG,"Error %d: Couldn't start forte\n", resultForte);
    }
    forteGlobalDeinitialize();
    vTaskDelete(NULL);
}


void forte_main(void)
{

    xTaskCreate( MyForteTask, "MY_FORTE", 10000, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle );
     
    configASSERT(xHandle);
}

void vApplicationMallocFailedHook____()
{
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_LOGE(TAG, "vApplicationMallocFailedHook");
    }
}

void vApplicationStackOverflowHook____(TaskHandle_t xTask, char *pcTaskName)
{
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        ESP_LOGE(TAG, "vApplicationStackOverflowHook");
    }
}


enum E_MsgLevel {
  E_INFO,
  E_WARNING,
  E_ERROR,
  E_DEBUG,
  E_TRACE
};

static const char *const FTAG = "forte";


//TODO !!!
// if Forte is to DEBUG and ESP-IDF to Info,
// DEBUG Information gets lost.

/*! \brief print the given log message with the error level and a time stamp
 *
 * @param pa_ecLevel the message's log level
 * @param pa_acMessage the message to log
 */
void printLogMessage(E_MsgLevel paLevel, char * const paMessage)
{
	size_t strlen0 = strlen(paMessage);
	size_t strlen1 = strlen0 - 1;

	if (paMessage[strlen1] == '\n') {
		paMessage[strlen1]  = '\0';
	}



	switch (paLevel)
	{
	case E_INFO:
	    ESP_LOGI(FTAG, "%s", paMessage);
		break;
	case E_WARNING:
	    ESP_LOGW(FTAG, "%s", paMessage);
		break;
	case E_ERROR:
	    ESP_LOGE(FTAG, "%s", paMessage);
		break;
	case E_DEBUG:
	    ESP_LOGI(FTAG, "%s", paMessage); //TODO find a better way.
		break;
	case E_TRACE:
	    ESP_LOGI(FTAG, "%s", paMessage); //TODO find a better way.
		break;
	}





}

