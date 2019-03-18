#include "log.h"
#include "usb_log.h"
#include "usbd_cdc_if.h"
#include "FreeRTOS.h"
#include "semphr.h"

static const LogApi_t api =
{
    .write_string = usb_log_write,
};

static SemaphoreHandle_t xLogMutex;

LogResult_t usb_log_init(Log_t *log)
{
    if(!log)
    {
        return LOG_ERR_INSTANCE;
    }

    LogConfig_t *config = log->logConfig ;
    
    log->logApi = &api;

    xLogMutex = xSemaphoreCreateMutex();

    CDC_Transmit_FS("Log init\n", 10);
    
    return LOG_OK;
}


LogResult_t usb_log_write(Log_t * log, const char *string, uint8_t len)
{
    if (xLogMutex != NULL)
    {
        const TickType_t xWaitPeriodMs = 10/portTICK_PERIOD_MS;
        if(xSemaphoreTake(xLogMutex, xWaitPeriodMs) == pdTRUE)
        {
            CDC_Transmit_FS(string, len);
        }
        xSemaphoreGive(xLogMutex);
        
        return LOG_OK;
    }


   
}

