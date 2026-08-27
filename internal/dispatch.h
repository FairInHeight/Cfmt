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
    DISPATCH_OK,
    DISPATCH_INVALID,
    DISPATCH_ERROR
} DispatchStatus;

typedef struct
{
    char *ansi;
    DispatchStatus status;
} DispatchResult;

typedef DispatchResult (*DispatchHandler)(DispatchContext *ctx);

DispatchHandler dispatch(char spec);

DispatchResult dispatch_style(DispatchContext *ctx);
DispatchResult dispatch_foreground(DispatchContext *ctx);
DispatchResult dispatch_background(DispatchContext *ctx);
DispatchResult dispatch_bright_foreground(DispatchContext *ctx);
DispatchResult dispatch_bright_background(DispatchContext *ctx);
DispatchResult dispatch_rgb(DispatchContext *ctx);

#endif
