#ifndef RTT_LOG_H_
#define RTT_LOG_H_

#include "log.h"
#include <stdarg.h>

LogResult_t rtt_log_init(Log_t *log);
LogResult_t rtt_log_write(Log_t *log, const char *sFormat, va_list *pParamList);

#endif