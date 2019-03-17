#include "log.h"
#include "usb_log.h"
#include "usbd_cdc_if.h"

static const LogApi_t api =
{
    .write_string = usb_log_write,
};



LogResult_t usb_log_init(Log_t *log)
{
    if(!log)
    {
        return LOG_ERR_INSTANCE;
    }

    LogConfig_t *config = log->logConfig ;
    
    log->logApi = &api;


    CDC_Transmit_FS("Log init\n", 10);
    
    return LOG_OK;
}


LogResult_t usb_log_write(Log_t * log, const char *string, uint8_t len)
{

   
   CDC_Transmit_FS(string, len);
}

