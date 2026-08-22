#ifndef CFMT_H
#define CFMT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

char *fmtstr(const char *input);
char *fmtspec(char spec, va_list *args);

int printfx(const char *input, ...);
int snprintfx(char *str, size_t size, const char *input, ...);
int fprintfx(FILE *stream, const char *input, ...);

#endif