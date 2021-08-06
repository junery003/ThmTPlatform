#ifndef OAPI_LOG_C
#define OAPI_LOG_C 1

#if defined(WIN32) || defined(_WIN64)
#pragma warning(disable: 4711) // function selected for automatic inline expansion
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "oapi_log.h"

/**
 * -1 = Undefined
 *  0 = No
 *  1 = Yes
 */
static int do_oapi_log = -1;
static FILE* oapi_log_fp = NULL;

int is_oapi_log() {
  char *env_p;
  if (do_oapi_log < 0) {
    env_p = getenv("OAPI_LOG");
    do_oapi_log = env_p != NULL && strcmp(env_p, "0") != 0;
    if (do_oapi_log) {
      oapi_log_fp = fopen("oapi.log", "w");
      if (oapi_log_fp == NULL) {
	fprintf(stderr, "Unable to open oapi.log for writing. No logs will be written.");
      }
    }
  }
  return do_oapi_log;
}

/**
 * Returns the position for the last occurance of c in s.
 * A negative number is returned if c isn't found.
 *
 * Parameters:
 *      s     The string to be search.
 *      c     The character that shall be found.
 *
 */
int oapi_log_find_char(const char* s, char* t) {
  int i, j, n;
  n = strlen(t);
  for (i=(int)strlen(s)-1; i>=0; i--) {
    for (j=0; j<n; ++j) {
      if (s[i] == t[j]) {
	return i;
      }
    }
  }
  return -1;
}

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
void oapi_log_get_name(char * name, const char* tot_name) {
  int start = -1, stop = -1;
#if defined(__VMS)
  start = oapi_log_find_char(tot_name, "]>");
  stop  = oapi_log_find_char(tot_name, ";");
#elif defined(__linux__)
  start = oapi_log_find_char(tot_name, "/");
#elif defined(_WIN32) || defined(_WIN64)
  start = oapi_log_find_char(tot_name, "\\");
#else
  // Unknown OS. Write the whole name.
#endif
  if (start >= 0) {
    (void)strcpy(name, tot_name+start+1);
    stop -= start+1;
  }
  else {
    (void)strcpy(name, tot_name);
  }
  if (stop >= 0) {
    name[stop] = '\0';
  }
}

void oapi_log_file_ext(FILE* fp, const char* f_name, int32_t line, const char* msg) {
  char name_part[OAPI_LOG_BUFFER_SIZE];
  time_t rawtime;
  struct tm *tm_p;
  memset(name_part, 0, OAPI_LOG_BUFFER_SIZE);
  oapi_log_get_name(name_part, f_name);
  time(&rawtime);
  tm_p = localtime(&rawtime);
  fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d %15s %5d %s\n", 1900+tm_p->tm_year, 1 + tm_p->tm_mon, tm_p->tm_mday, tm_p->tm_hour, tm_p->tm_min, tm_p->tm_sec, name_part, line, msg);
  fflush(fp);
}


/**
* Writes to stdout but adds date, time, filename and line.
*
* IMPORTANT: Do not call this function directly.
*            Use the macro OAPI_PRINTF provided by oapi_log.h instead.
*
* Parameters:
*
*      f_name  The filename.
*              Access: Read only.
*
*      line    The code line.
*              Access: Read only.
*
*      msg     The message to be written.
*
*
*
* Example:
*      double x=0.67;
*      OMN_LOG_1('I', 0, "x = %f", x);
*
*/
void oapi_printf_ext(const char* f_name, int32_t line, const char* msg, ...) {
  char msg_part[OAPI_LOG_BUFFER_SIZE];
  va_list ap;
  memset(msg_part, 0, OAPI_LOG_BUFFER_SIZE);
  va_start(ap, msg);
  (void)vsprintf(msg_part, msg, ap);
  va_end(ap);
  oapi_log_file_ext(stdout, f_name, line, msg_part);
  if (is_oapi_log()) {
    oapi_log_file_ext(oapi_log_fp, f_name, line, msg_part);
  }
}

/**
 * Writes to log-file but adds date, time, filename and line.
 *
 * IMPORTANT: Do not call this function directly.
 *            Use the macro OAPI_LOG provided by oapi_log.h instead.
 *
 *
 *
 * Parameters:
 *
 *      f_name  The filename.
 *              Access: Read only.
 *
 *      line    The code line.
 *              Access: Read only.
 *
 *      msg     The message to be written.
 *
 *
 *
 * Example:
 *      double x=0.67;
 *      OMN_LOG_1('I', 0, "x = %f", x);
 *
 */
void oapi_log_ext(const char* f_name, int line, const char* msg, ...) {
  char msg_part[OAPI_LOG_BUFFER_SIZE];
  va_list ap;
  memset(msg_part, 0, OAPI_LOG_BUFFER_SIZE);
  if (is_oapi_log()) {
    va_start(ap, msg);
    (void)vsprintf(msg_part, msg, ap);
    va_end(ap);
    oapi_log_file_ext(oapi_log_fp, f_name, line, msg_part);
  }
}

#endif /* OAPI_LOG_C */
