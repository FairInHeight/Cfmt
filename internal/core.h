#ifndef CORE_H
#define CORE_H

#include <stdarg.h>

typedef enum
{
    FMT_OK,
    FMT_INVALID,
    FMT_ERROR
} FmtStatus;

typedef struct
{
    char *output;
    FmtStatus status;
} FmtResult;

char *fmtstr(const char *input);
FmtResult fmtspec(char spec, va_list *args);
char *fmtin(const char *input, va_list *args);

#endif