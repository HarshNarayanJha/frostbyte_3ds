#pragma once

#include <3ds.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

struct Logger {
  enum class LogLevel : u8 { TRACE, DEBUG, INFO, ERROR };

  static constexpr const char *LOG_PREFIX = "FROSTBYTE_APP";

  static void setLevel(LogLevel level) {
    getCurrentLevel() = level;
  }

  static void trace(const char *format, ...) __attribute__((format(printf, 1, 2))) {
    if (getCurrentLevel() > LogLevel::TRACE)
      return;
    va_list args;
    va_start(args, format);
    logInternal("TRACE", format, args);
    va_end(args);
  }

  static void debug(const char *format, ...) __attribute__((format(printf, 1, 2))) {
    if (getCurrentLevel() > LogLevel::DEBUG)
      return;
    va_list args;
    va_start(args, format);
    logInternal("DEBUG", format, args);
    va_end(args);
  }

  static void info(const char *format, ...) __attribute__((format(printf, 1, 2))) {
    if (getCurrentLevel() > LogLevel::INFO)
      return;
    va_list args;
    va_start(args, format);
    logInternal("INFO", format, args);
    va_end(args);
  }

  static void error(const char *format, ...) __attribute__((format(printf, 1, 2))) {
    if (getCurrentLevel() > LogLevel::ERROR)
      return;
    va_list args;
    va_start(args, format);
    logInternal("ERROR", format, args);
    va_end(args);
  }

private:
  static LogLevel &getCurrentLevel() {
    static LogLevel level = LogLevel::DEBUG;
    return level;
  }

  static void logInternal(const char *prefix, const char *format, va_list args) {
    char buffer[512];

    int headerLen = snprintf(buffer, sizeof(buffer), "[%s] %s: ", LOG_PREFIX, prefix);

    if (headerLen > 0 && headerLen < (int)sizeof(buffer)) {
      vsnprintf(buffer + headerLen, sizeof(buffer) - headerLen, format, args);
    }

    int len = strnlen(buffer, sizeof(buffer));
    if (len >= (int)sizeof(buffer) - 1) {
      len = sizeof(buffer) - 2;
    }

    buffer[len]     = '\n';
    buffer[len + 1] = '\0';
    len++;

    // Send directly to hardware debugging interface (Emulators / 3dslink)
    svcOutputDebugString(buffer, len);
  }
};
