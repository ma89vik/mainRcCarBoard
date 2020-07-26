#include "log.h"
#include "usb_log.h"
#include "usbd_cdc_if.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "ring_buffer.h"

static char buf[256];
static RingBuffer_t outbox;

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

    
    log->logApi = &api;

    xLogMutex = xSemaphoreCreateMutex();

    ring_buffer_init(&outbox, buf, 256);
    
    return LOG_OK;
}


LogResult_t usb_log_write(Log_t * log, const char *string, uint8_t len)
{
    if (xLogMutex != NULL)
    {
        const TickType_t xWaitPeriodMs = 0;
        if(xSemaphoreTake(xLogMutex, xWaitPeriodMs) == pdTRUE)
        {
            for(int i = 0;i<len;i++)
            {
                ring_buffer_put(&outbox, string[i]);
            }
            
        }
        xSemaphoreGive(xLogMutex);
        
        return LOG_OK;
    }


   
}


void v_log_task(void *pvParameters)
{

    portTickType xLastExecutionTime;
    volatile unsigned portBASE_TYPE uxLine = 0;


    char outData[100];

   
    while(1)
    {
        xLastExecutionTime = xTaskGetTickCount();
      
        
        int i = 0;
        char c;
        while( !ring_buffer_empty(&outbox) && i<100)
        {
                if (xLogMutex != NULL)
                {
                    const TickType_t xWaitPeriodMs = 500;
                    if(xSemaphoreTake(xLogMutex, xWaitPeriodMs) == pdTRUE)
                    {
                        ring_buffer_get(&outbox, &c); 
                    }
                    xSemaphoreGive(xLogMutex);      
        
                }       
            
            outData[i] = c;

            i++;
        }

        CDC_Transmit_FS(outData, i);

        
        vTaskDelayUntil( &xLastExecutionTime, 300 );
    }

}