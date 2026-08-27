#ifndef CFMT_DISPATCH_H
#define CFMT_DISPATCH_H

#include <stddef.h>

typedef struct
{
    const char *input;
    size_t *index;
} DispatchContext;

typedef enum
{
    DISPATCH_INVALID,
    DISPATCH_STYLE,
    DISPATCH_FOREGROUND,
    DISPATCH_BACKGROUND,
    DISPATCH_BRIGHT_FOREGROUND,
    DISPATCH_BRIGHT_BACKGROUND,
    DISPATCH_RGB
} DispatchType;

DispatchType dispatch(char spec);

char *dispatch_style(char spec);
char *dispatch_foreground(char spec);
char *dispatch_background(DispatchContext *ctx);
char *dispatch_bright_foreground(DispatchContext *ctx);
char *dispatch_bright_background(DispatchContext *ctx);
char *dispatch_rgb(DispatchContext *ctx);

#endif
