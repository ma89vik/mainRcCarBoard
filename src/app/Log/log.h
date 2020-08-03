#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

// Less severe errors have higher values
#define NO_LOG 0x00
#define CRIT_LEVEL 0x01
#define ERROR_LEVEL 0x02
#define WARN_LEVEL 0x03
#define INFO_LEVEL 0x04
#define DEBUG_LEVEL 0x05

#define LOG_LEVEL DEBUG_LEVEL

#define LOG_MSG_MAX_LEN 100

typedef enum
{
    LOG_NONE = -1,
    LOG_OK,
    LOG_BUSY,
    LOG_ERR_WRITE,
    LOG_ERR_INSTANCE,
} LogResult_t;

/**
 * @brief Implement this interface to log to a specific module
 *
 */

typedef struct LogConfig LogConfig_t;
typedef struct LogApi LogApi_t;

typedef struct
{
    LogConfig_t *logConfig;
    LogApi_t *logApi;
    char outbox[LOG_MSG_MAX_LEN];

} Log_t;

struct LogApi
{
    // All interface functions goes here
    LogResult_t (*write_string)(Log_t *log, const char *string, uint8_t len);    
    LogResult_t (*ready)(Log_t *log);
};

struct LogConfig
{
    LogResult_t (*init)(Log_t *log);
};

LogResult_t log_init(LogConfig_t *logConfig);

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(...) log_string(DEBUG_LEVEL, __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(...) log_string(INFO_LEVEL, __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if LOG_LEVEL >= WARN_LEVEL
#define LOG_WARN(...) log_string(WARN_LEVEL, __VA_ARGS__)
#else
#define LOG_WARN(...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(...) log_string(ERROR_LEVEL, __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOG_LEVEL >= CRIT_LEVEL
#define LOG_CRIT(...) log_string(CRIT_LEVEL, __VA_ARGS__)
#else
#define LOG_CRIT(...)
#endif

void log_string(uint8_t level, const char *string);

#endif