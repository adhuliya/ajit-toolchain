
#ifndef CORTOS_LOGGING_H
#define CORTOS_LOGGING_H

////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_logging_declarations
////////////////////////////////////////////////////////////////////////////////

// The programmer can log messages in CoRTOS using logging macros.
// These macros pass the arguments to printf function internally.
// For example, to log a TRACE message
//      CORTOS_TRACE("Current count: %d", count);
// When the user disables all logging or some log levels,
// all the macros of disabled log levels expand to a blank space,
// which removes the logging message entirely.

#define LOG_LEVEL_ALL       10
#define LOG_LEVEL_TRACE     20
#define LOG_LEVEL_DEBUG     30
#define LOG_LEVEL_INFO      40
#define LOG_LEVEL_ERROR     50
#define LOG_LEVEL_CRITICAL  60
#define LOG_LEVEL_NONE      100

// The log level the project is built with:
#define CORTOS_LOG_LEVEL {{confObj.software.build.logLevel.value}}
#define CORTOS_LOG_LEVEL_NAME "{{ confObj.software.build.logLevel.name }}"

% for level in consts.LEVEL_ORDER:
% if level.value >= confObj.software.build.logLevel.value:
#define CORTOS_{{ level.name }}(...) \
__cortos_log_printf("{{ level.name }}", __FILE__, __func__, __LINE__, __VA_ARGS__);

% else:
#define CORTOS_{{ level.name }}(...)     /*blank*/

% end
% end

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_logging_declarations
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// BLOCK START: cortos_logging_routines_internal
////////////////////////////////////////////////////////////////////////////////

// specially defined for logging purposes
int __cortos_log_printf(const char *level, const char *fileName,
  const char *funcName, int lineNum, const char *fmt, ...);

////////////////////////////////////////////////////////////////////////////////
// BLOCK END  : cortos_logging_routines_internal
////////////////////////////////////////////////////////////////////////////////

#endif // CORTOS_LOGGING_H

