#include "log.h"
#include "string.h"

#include <stdarg.h>

// Only one logger is active in the system
static Log_t log;

LogResult_t log_init(LogConfig_t *logConfig)
{
    log.logConfig = logConfig;

    if (log.logConfig->init)
    {
        return log.logConfig->init(&log);
    }

    return LOG_OK;
}

void log_string(uint8_t level, const char *string)
{

    uint8_t ret;
    char buf[21];
    // Add log level to the message
    log.outbox[0] = level;

    uint8_t len = strnlen(string, LOG_MSG_MAX_LEN - 1);

    strncpy(&log.outbox[1], string, LOG_MSG_MAX_LEN - 1);

    if (log.logApi)
    {
        log.logApi->write_string(&log, log.outbox, len);
    }

}