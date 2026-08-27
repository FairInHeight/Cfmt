#include "dispatch.h"
#include "codec.h"
#include "style.h"

static const DispatchType dispatch_table[256] =
{
    /*
     * Styles
     */
    ['b'] = DISPATCH_STYLE,              // Bold
    ['d'] = DISPATCH_STYLE,              // Dim
    ['i'] = DISPATCH_STYLE,              // Italic
    ['u'] = DISPATCH_STYLE,              // Underline
    ['k'] = DISPATCH_STYLE,              // Blink
    ['v'] = DISPATCH_STYLE,              // Inverse
    ['n'] = DISPATCH_STYLE,              // Hidden
    ['t'] = DISPATCH_STYLE,              // Strikethrough
    ['r'] = DISPATCH_STYLE,              // Reset

    /*
     * Standard foreground colors
     */
    ['0'] = DISPATCH_FOREGROUND,
    ['1'] = DISPATCH_FOREGROUND,
    ['2'] = DISPATCH_FOREGROUND,
    ['3'] = DISPATCH_FOREGROUND,
    ['4'] = DISPATCH_FOREGROUND,
    ['5'] = DISPATCH_FOREGROUND,
    ['6'] = DISPATCH_FOREGROUND,
    ['7'] = DISPATCH_FOREGROUND,
    ['9'] = DISPATCH_FOREGROUND,

    /*
     * Standard background colors
     */
    ['h'] = DISPATCH_BACKGROUND,

    /*
     * Bright foreground colors
     */
    ['*'] = DISPATCH_BRIGHT_FOREGROUND,

    /*
     * Bright background colors
     */
    ['H'] = DISPATCH_BRIGHT_BACKGROUND,

    /*
     * RGB color
     */
    ['c'] = DISPATCH_RGB
};

DispatchType dispatch(char spec)
{
    return dispatch_table[(unsigned char)spec];
}

char *dispatch_style(char spec)
{
    style = decode_style(spec);

    return encode_style(style);
}

char *dispatch_foreground(char spec)
{
    color = decode_color(spec);

    return encode_color(color, 'f');
}

char *dispatch_background(char spec)
{
    color = decode_color(spec);

    return encode_color(color, 'b');
}

char *dispatch_bright_foreground(char spec)
{
    color = decode_color(spec);

    return encode_color(color, 'B');
}

char *dispatch_bright_background(char spec)
{
    color = decode_color(spec);

    return encode_color(color, 'H');
}

char *dispatch_rgb(char spec)
{
    (void)spec;

    return NULL;
}
