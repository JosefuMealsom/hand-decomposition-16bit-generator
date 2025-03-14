#include "logger.h"
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>

static std::shared_ptr<spdlog::logger> m_logger;

void Log::init() {
  m_logger = spdlog::stdout_color_mt("Debug");
  m_logger->set_level(spdlog::level::trace);
}
