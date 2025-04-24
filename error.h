#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdarg.h>

#define ERRBUF_SIZE 512
extern char last_error[ERRBUF_SIZE];

void setLastErr(const char *fmt, ...);

static inline void clearLastErr()
{
    last_error[0] = '\0';
}

static inline const char *getLastErr(void)
{
    return (last_error[0] != '\0') ? last_error : "";
}

#endif // ERROR_H