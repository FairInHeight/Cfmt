#ifndef CORE_H
#define CORE_H

#include <stdarg.h>

char *fmtstr(const char *input);
char *fmtspec(char spec, va_list *args);
char *fmtin(const char *input, va_list *args);

#endif