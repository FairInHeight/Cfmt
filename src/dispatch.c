#include "dispatch.h"
#include "codec.h"
#include "style.h"

static char *dispatch_style_handler(DispatchContext *ctx)
{
    return dispatch_style(ctx);
}

static char *dispatch_foreground_handler(DispatchContext *ctx)
{
    return dispatch_foreground(ctx);
}

static char *dispatch_background_handler(DispatchContext *ctx)
{
    return dispatch_background(ctx);
}

static char *dispatch_bright_foreground_handler(DispatchContext *ctx)
{
    return dispatch_bright_foreground(ctx);
}

static char *dispatch_bright_background_handler(DispatchContext *ctx)
{
    return dispatch_bright_background(ctx);
}

static char *dispatch_rgb_handler(DispatchContext *ctx)
{
    return dispatch_rgb(ctx);
}

static DispatchHandler dispatch_table[256] =
{
    /* Styles */
    ['b'] = dispatch_style_handler,
    ['d'] = dispatch_style_handler,
    ['i'] = dispatch_style_handler,
    ['u'] = dispatch_style_handler,
    ['k'] = dispatch_style_handler,
    ['v'] = dispatch_style_handler,
    ['n'] = dispatch_style_handler,
    ['t'] = dispatch_style_handler,
    ['r'] = dispatch_style_handler,

    /* Standard foreground colors */
    ['0'] = dispatch_foreground_handler,
    ['1'] = dispatch_foreground_handler,
    ['2'] = dispatch_foreground_handler,
    ['3'] = dispatch_foreground_handler,
    ['4'] = dispatch_foreground_handler,
    ['5'] = dispatch_foreground_handler,
    ['6'] = dispatch_foreground_handler,
    ['7'] = dispatch_foreground_handler,
    ['9'] = dispatch_foreground_handler,

    /* Standard background colors */
    ['h'] = dispatch_background_handler,

    /* Bright foreground colors */
    ['*'] = dispatch_bright_foreground_handler,

    /* Bright background colors */
    ['H'] = dispatch_bright_background_handler,

    /* RGB color */
    ['c'] = dispatch_rgb_handler
};

DispatchHandler dispatch(char spec)
{
    return dispatch_table[(unsigned char)spec];
}

char *dispatch_style(DispatchContext *ctx)
{
    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return NULL;

    style = decode_style(ctx->input[*ctx->index]);

    return encode_style(style);
}

char *dispatch_foreground(DispatchContext *ctx)
{
    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return NULL;

    color = decode_color(ctx->input[*ctx->index]);

    return encode_color(color, 'f');
}

char *dispatch_background(DispatchContext *ctx)
{
    char spec;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return NULL;

    spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return NULL;

    (*ctx->index)++;

    color = decode_color(spec);

    return encode_color(color, 'b');
}

char *dispatch_bright_foreground(DispatchContext *ctx)
{
    char spec;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return NULL;

    spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return NULL;

    (*ctx->index)++;

    color = decode_color(spec);

    return encode_color(color, 'B');
}

char *dispatch_bright_background(DispatchContext *ctx)
{
    char spec;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return NULL;

    spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return NULL;

    (*ctx->index)++;

    color = decode_color(spec);

    return encode_color(color, 'H');
}

char *dispatch_rgb(DispatchContext *ctx)
{
    char r;
    char g;
    char b;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return NULL;

    r = ctx->input[*ctx->index + 1];
    g = ctx->input[*ctx->index + 2];
    b = ctx->input[*ctx->index + 3];

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
