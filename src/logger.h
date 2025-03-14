#pragma once

#include "pch/pch.h"
#include <spdlog/logger.h>

class Log {
private:
  static inline std::shared_ptr<spdlog::logger> m_logger;

public:
  static void init();
  // why inline static?
  inline static std::shared_ptr<spdlog::logger> &get_logger() {
    return m_logger;
  };
};

#define LOG_INFO(...) Log::get_logger()->info(__VA_ARGS__)
#define LOG_ERROR(...) Log::get_logger()->error(__VA_ARGS__)
#define LOG_WARN(...) Log::get_logger()->warn(__VA_ARGS__)
#define LOG_TRACE(...) Log::get_logger()->trace(__VA_ARGS__)
#define LOG_FATAL(...) Log::get_logger()->fatal(__VA_ARGS__)
