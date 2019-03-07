#include "rtt_log.h"
#include "SEGGER_RTT.h"
#include "log.h"

static const LogApi_t api = {
    .write = rtt_log_write,
};

LogResult_t rtt_log_init(Log_t *log)
{
    if (!log)
    {
        return LOG_ERR_INSTANCE;
    }

    LogConfig_t *config = log->logConfig;

    log->logApi = &api;

    SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_TRIM);

    SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Initialized\r\n\r\n");

    return LOG_OK;
}

LogResult_t rtt_log_write(Log_t *log, const char *sFormat, va_list *pParamList)
{
    SEGGER_RTT_vprintf(0, sFormat, pParamList);
}
