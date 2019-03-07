#include "ble_log.h"
#include "ble_handler.h"
#include "log.h"
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

static bool rdyForWrite = false;

void on_logs_evt(ble_logs_evt_t *p_evt)
{
}

static const LogApi_t api = {
    .write = ble_log_write,
};

LogResult_t ble_log_init(Log_t *log)
{
    if (!log)
    {
        return LOG_ERR_INSTANCE;
    }

    LogConfig_t *config = log->logConfig;

    log->logApi = &api;

    return LOG_OK;
}

LogResult_t ble_log_write(Log_t *log, const char *sFormat, va_list *pParamList)
{

    // BLE notificatiosn are limited to 20 bytes
    uint8_t ret;

    ret = vsnprintf(log->outbox, 20, sFormat, *pParamList);

    ble_logs_err_msg_send(log->outbox, 20);
}