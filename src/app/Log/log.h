// Copyright 2020 Marius
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <stdarg.h>
#include <stdint.h>

#include "usart.h"

// Less severe errors have higher values
typedef enum {
    LOG_LEVEL_NO_LOG = 0,
    LOG_LEVEL_CRIT_LEVEL,
    LOG_LEVEL_ERROR_LEVEL,
    LOG_LEVEL_WARN_LEVEL,
    LOG_LEVEL_INFO_LEVEL,
    LOG_LEVEL_DEBUG_LEVEL,
} log_level_t;

#define LOG_LEVEL DEBUG_LEVEL

typedef struct {
    UART_HandleTypeDef *uart_handle;
} log_config_t;

void log_init(log_config_t *log_config);

#if LOG_LEVEL >= LOG_LEVEL_DEBUG_LEVEL
#define LOG_DEBUG(...) log_string(LOG_LEVEL_DEBUG_LEVEL, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_INFO_LEVEL
#define LOG_INFO(...) log_string(LOG_LEVEL_INFO_LEVEL, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_WARN_LEVEL
#define LOG_WARN(...) log_string(LOG_LEVEL_WARN_LEVEL, __VA_ARGS__)
#else
#define LOG_WARN(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_ERROR_LEVEL
#define LOG_ERROR(...) log_string(LOG_LEVEL_ERROR_LEVEL, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOG_LEVEL >= LOG_LEVEL_CRIT_LEVEL
#define LOG_CRIT(...) log_string(CRIT_LEVEL, __VA_ARGS__)
#else
#define LOG_CRIT(...)
#endif

void log_string(log_level_t level, const char *format, ...);
