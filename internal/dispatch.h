#ifndef CFMT_DISPATCH_H
#define CFMT_DISPATCH_H

#include <stddef.h>

typedef struct
{
    const char *input;
    size_t *index;
} DispatchContext;

typedef char *(*DispatchHandler)(DispatchContext *ctx);

DispatchHandler dispatch(char spec);

char *dispatch_style(DispatchContext *ctx);
char *dispatch_foreground(DispatchContext *ctx);
char *dispatch_background(DispatchContext *ctx);
char *dispatch_bright_foreground(DispatchContext *ctx);
char *dispatch_bright_background(DispatchContext *ctx);
char *dispatch_rgb(DispatchContext *ctx);

#endif
