#ifndef OAPI_LOG_H
#define OAPI_LOG_H 1

#include <stdarg.h>
#include "om_inttypes.h"

#define OAPI_PRINTF(s) \
	oapi_printf_ext(__FILE__, __LINE__, s)
#define OAPI_PRINTF_1(s, p1) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1)
#define OAPI_PRINTF_2(s, p1, p2) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2)
#define OAPI_PRINTF_3(s, p1, p2, p3) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3)
#define OAPI_PRINTF_4(s, p1, p2, p3, p4) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4)
#define OAPI_PRINTF_5(s, p1, p2, p3, p4, p5) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5)
#define OAPI_PRINTF_6(s, p1, p2, p3, p4, p5, p6) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6)
#define OAPI_PRINTF_7(s, p1, p2, p3, p4, p5, p6, p7) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7)
#define OAPI_PRINTF_8(s, p1, p2, p3, p4, p5, p6, p7, p8) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8)
#define OAPI_PRINTF_9(s, p1, p2, p3, p4, p5, p6, p7, p8, p9) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9)
#define OAPI_PRINTF_10(s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#define OAPI_PRINTF_11(s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)
#define OAPI_PRINTF_12(s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) \
	oapi_printf_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)

#define OAPI_LOG(s) \
        oapi_log_ext(__FILE__, __LINE__, s)
#define OAPI_LOG_1(s, p1) \
        oapi_log_ext(__FILE__, __LINE__, s, p1)
#define OAPI_LOG_2(s, p1, p2) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2)
#define OAPI_LOG_3(s, p1, p2, p3) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3)
#define OAPI_LOG_4(s, p1, p2, p3, p4) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4)
#define OAPI_LOG_5(s, p1, p2, p3, p4, p5) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5)
#define OAPI_LOG_6(s, p1, p2, p3, p4, p5, p6) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6)
#define OAPI_LOG_7(s, p1, p2, p3, p4, p5, p6, p7) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7)
#define OAPI_LOG_8(s, p1, p2, p3, p4, p5, p6, p7, p8) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8)
#define OAPI_LOG_9(s, p1, p2, p3, p4, p5, p6, p7, p8, p9) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9)
#define OAPI_LOG_10(s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10)
#define OAPI_LOG_11(s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11)
#define OAPI_LOG_12(s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12) \
        oapi_log_ext(__FILE__, __LINE__, s, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12)

#define OAPI_LOG_BUFFER_SIZE 256

/**
 * Writes the file name without path (and generation if it is run on OpenVMS).
 *
 *
 *
 * Parameters:
 *
 *      name      This string will only contain the name after the call.
 *                Access: Write only.
 *
 *      tot_name  The file name including the path.
 *                Access: Read only.
 *
 *
 *
 * Return:
 *
 *      None.
 *
 */
void oapi_log_get_name(char * name, const char* tot_name);

/**
 * Writes to stdout but adds date, time, filename and line.
 *
 * IMPORTANT: Do not call this function directly.
 *            Use the macro OAPI_PRINTF, OAPI_PRINTF_1, OAPI_PRINTF_2 etc. instead.
 *
 * Parameters:
 *
 *      f_name  The filename.
 *              Access: Read only.
 *
 *      line    The code line.
 *              Access: Read only.
 *
 *      msg     The message to be written. Uses the same format as am_log.
 *
 *
 *
 * Example:
 *      double x=0.67;
 *      OAPI_PRINTF_1('I', 0, "x = %f", x);
 *
 */
void oapi_printf_ext(const char* f_name, int32_t line, const char* msg, ...);

/**
 * Writes to log file but adds date, time, filename and line.
 *
 * IMPORTANT: Do not call this function directly.
 *            Use the macro OAPI_LOG, OAPI_LOG_1, OAPI_LOG_2 etc. instead.
 *
 * Parameters:
 *
 *      f_name  The filename.
 *              Access: Read only.
 *
 *      line    The code line.
 *              Access: Read only.
 *
 *      msg     The message to be written. Uses the same format as am_log.
 *
 *
 *
 * Example:
 *      double x=0.67;
 *      OAPI_LOG_1('I', 0, "x = %f", x);
 *
 */
void oapi_log_ext(const char* f_name, int32_t line, const char* msg, ...);

#endif /* OAPI_LOG_H */
