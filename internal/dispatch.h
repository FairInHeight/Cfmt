#ifndef CFMT_DISPATCH_H
#define CFMT_DISPATCH_H

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
char *dispatch_background(char spec);
char *dispatch_bright_foreground(char spec);
char *dispatch_bright_background(char spec);
char *dispatch_rgb(char spec);

#endif
