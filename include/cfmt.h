#ifndef CFMT_H
#define CFMT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

int printfx(const char *input, ...);
int snprintfx(char *str, size_t size, const char *input, ...);
int fprintfx(FILE *stream, const char *input, ...);

#endif