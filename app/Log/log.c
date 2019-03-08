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

void log_log(int level, const char *fmt, ...)
{

    va_list args;
    uint8_t ret;
    char buf[21];
    va_start(args, fmt);
    // Add log level to the message
    log.outbox[0] = level;

    strncpy(&log.outbox[1], fmt, LOG_MSG_MAX_LEN - 1);
    if (log.logApi)
    {
        log.logApi->write(&log, fmt, &args);
    }

    va_end(args);
}