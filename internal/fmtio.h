#ifndef FMTIO_H
#define FMTIO_H

#include <stdio.h>

int printfx(const char *input, ...);
int snprintfx(char *str, size_t size, const char *input, ...);
int fprintfx(FILE *stream, const char *input, ...);

#endif