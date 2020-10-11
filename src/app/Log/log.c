/**
 * Copyright 2020 Marius
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include "log.h"
#include "string.h"
#include "app_uart.h"
#include "printf.h"

#include <stdarg.h>

static const char *s_log_level_strings[] =
{
    "NO LOG",
    "CRITICAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
};

// Only one logger is active in the system
static app_uart_handle_t s_uart_handle;

void log_init(log_config_t *log_config)
{
    app_uart_init(&s_uart_handle, log_config->uart_handle);    

}

void log_string(uint8_t level, const char *format, ...)
{
    char buf[100] = {'\0'};

    size_t level_string_len = strlen(s_log_level_strings[level]);
    memcpy(buf, s_log_level_strings[level], level_string_len);
    memcpy(buf + level_string_len, ": ", 2);

    va_list args;
    va_start(args, format);
    vsnprintf_(buf + level_string_len + 2, sizeof(buf) - 1, format, args);
    va_end (args);
    
    app_uart_write(&s_uart_handle, buf, strlen(buf));
}