#ifndef CFMT_H
#define CFMT_H

char *fmtstr(const char *input);
int printfx(const char *input, ...);
char *fmtspec(char spec, va_list *args);

#endif