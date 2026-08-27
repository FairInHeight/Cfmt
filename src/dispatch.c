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

char *dispatch_background(DispatchContext *ctx)
{
    char spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return NULL;

    (*ctx->index)++;

    color = decode_color(spec);

    return encode_color(color, 'b');
}

char *dispatch_bright_foreground(DispatchContext *ctx)
{
    char spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return NULL;

    (*ctx->index)++;

    color = decode_color(spec);

    return encode_color(color, 'B');
}

char *dispatch_bright_background(DispatchContext *ctx)
{
    char spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return NULL;

    (*ctx->index)++;

    color = decode_color(spec);

    return encode_color(color, 'H');
}

char *dispatch_rgb(DispatchContext *ctx)
{
    char r = ctx->input[*ctx->index + 1];
    char g = ctx->input[*ctx->index + 2];
    char b = ctx->input[*ctx->index + 3];

    if (r == '\0' || r == '\n' ||
        g == '\0' || g == '\n' ||
        b == '\0' || b == '\n')
        return NULL;

    if (r < '0' || r > '5' ||
        g < '0' || g > '5' ||
        b < '0' || b > '5')
        return NULL;

    color = 16
            + (36 * (r - '0'))
            + (6  * (g - '0'))
            + (b - '0');

    (*ctx->index) += 3;

    return encode_color256(color, 'f');
}
