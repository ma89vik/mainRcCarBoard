#ifndef BLE_LOG_
#define BLE_LOG_

#include "log.h"
#include "log_cus.h"
#include <stdarg.h>

void on_logs_evt(ble_logs_evt_t *p_evt);
LogResult_t ble_log_init(Log_t *log);
LogResult_t ble_log_write(Log_t *log, const char *sFormat, va_list *pParamList);
#endif