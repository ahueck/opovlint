/*
 * Logger.h
 *
 *  Created on: May 9, 2014
 *      Author: ahueck
 */

#ifndef CORE_LOGGING_LOGGER_H
#define CORE_LOGGING_LOGGER_H

#include <llvm/Support/raw_ostream.h>

#ifndef LOG_LEVEL
/*
 * Usually set at compile time: -DLOG_LEVEL=<N>, N in [0, 3] for output
 * 3 being most verbose
 */
#define LOG_LEVEL 1
#endif

// clang-format off
#define _OO_LOG_LEVEL_MSG(LEVEL_NUM, LEVEL, MSG) \
  if (LEVEL_NUM <= LOG_LEVEL) \
    llvm::errs() << LEVEL << ": " << __FILE__ << "@'" << __func__ << "' (" << __LINE__ << "): " << MSG << "\n"

#define _OO_LOG_LEVEL_MSG_S(LEVEL_NUM, LEVEL, STMT) \
  if (LEVEL_NUM <= LOG_LEVEL) \
    llvm::errs() << LEVEL << ": " << __FILE__ << "@'" << __func__ << "' (" << __LINE__ << "): " << #STMT << "=" << STMT << "\n"

#define LOG_DEBUG_S(STMT) _OO_LOG_LEVEL_MSG_S(3, "Debug", MSG)
#define LOG_INFO_S(STMT) _OO_LOG_LEVEL_MSG_S(2, "Info", MSG)
#define LOG_ERROR_S(STMT) _OO_LOG_LEVEL_MSG_S(1, "Error", MSG)
#define LOG_FATAL_S(STMT) _OO_LOG_LEVEL_MSG_S(0, "Fatal", MSG)

#define LOG_DEBUG(MSG) _OO_LOG_LEVEL_MSG(3, "Debug", MSG)
#define LOG_INFO(MSG) _OO_LOG_LEVEL_MSG(2, "Info", MSG)
#define LOG_ERROR(MSG) _OO_LOG_LEVEL_MSG(1, "Error", MSG)
#define LOG_FATAL(MSG) _OO_LOG_LEVEL_MSG(0, "Fatal", MSG)
#define LOG_MSG(MSG) llvm::outs() << MSG << "\n"
// clang-format on
#endif  // CORE_LOGGING_LOGGER_H
