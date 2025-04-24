#include "error.h"

void setLastErr(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(last_error, ERRBUF_SIZE, fmt, ap);
    va_end(ap);
}