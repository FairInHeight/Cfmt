#include "dispatch.h"
#include "codec.h"
#include "style.h"

static const DispatchHandler dispatch_table[256] =
{
    /* Styles */
    ['b'] = dispatch_style,
    ['d'] = dispatch_style,
    ['i'] = dispatch_style,
    ['u'] = dispatch_style,
    ['k'] = dispatch_style,
    ['v'] = dispatch_style,
    ['n'] = dispatch_style,
    ['t'] = dispatch_style,
    ['r'] = dispatch_style,

    /* Standard foreground colors */
    ['0'] = dispatch_foreground,
    ['1'] = dispatch_foreground,
    ['2'] = dispatch_foreground,
    ['3'] = dispatch_foreground,
    ['4'] = dispatch_foreground,
    ['5'] = dispatch_foreground,
    ['6'] = dispatch_foreground,
    ['7'] = dispatch_foreground,
    ['9'] = dispatch_foreground,

    /* Standard background colors */
    ['h'] = dispatch_background,

    /* Bright foreground colors */
    ['*'] = dispatch_bright_foreground,

    /* Bright background colors */
    ['H'] = dispatch_bright_background,

    /* RGB color */
    ['c'] = dispatch_rgb
};

DispatchHandler dispatch(char spec)
{
    return dispatch_table[(unsigned char)spec];
}

DispatchResult dispatch_style(DispatchContext *ctx)
{
    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    style = decode_style(ctx->input[*ctx->index]);

    char *ansi = encode_style(style);

    if (ansi == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    return (DispatchResult){ .ansi = ansi, .status = DISPATCH_OK };
}

DispatchResult dispatch_foreground(DispatchContext *ctx)
{
    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    color = decode_color(ctx->input[*ctx->index]);

    char *ansi = encode_color(color, 'f');

    if (ansi == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    return (DispatchResult){ .ansi = ansi, .status = DISPATCH_OK };
}

DispatchResult dispatch_background(DispatchContext *ctx)
{
    char spec;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_INVALID };

    color = decode_color(spec);

    char *ansi = encode_color(color, 'b');

    if (ansi == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    (*ctx->index)++;

    return (DispatchResult){ .ansi = ansi, .status = DISPATCH_OK };
}

DispatchResult dispatch_bright_foreground(DispatchContext *ctx)
{
    char spec;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_INVALID };

    color = decode_color(spec);

    char *ansi = encode_color(color, '*');

    if (ansi == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    (*ctx->index)++;

    return (DispatchResult){ .ansi = ansi, .status = DISPATCH_OK };
}

DispatchResult dispatch_bright_background(DispatchContext *ctx)
{
    char spec;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    spec = ctx->input[*ctx->index + 1];

    if (!((spec >= '0' && spec <= '7') || spec == '9'))
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_INVALID };

    color = decode_color(spec);

    char *ansi = encode_color(color, 'H');

    if (ansi == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    (*ctx->index)++;

    return (DispatchResult){ .ansi = ansi, .status = DISPATCH_OK };
}

DispatchResult dispatch_rgb(DispatchContext *ctx)
{
    char r;
    char g;
    char b;

    if (ctx == NULL || ctx->input == NULL || ctx->index == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    r = ctx->input[*ctx->index + 1];
    g = ctx->input[*ctx->index + 2];
    b = ctx->input[*ctx->index + 3];

    if (r == '\0' || r == '\n' ||
        g == '\0' || g == '\n' ||
        b == '\0' || b == '\n')
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_INVALID };

    if (r < '0' || r > '5' ||
        g < '0' || g > '5' ||
        b < '0' || b > '5')
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_INVALID };

    color = 16
            + (36 * (r - '0'))
            + (6  * (g - '0'))
            + (b - '0');

    char *ansi = encode_color256(color, 'f');

    if (ansi == NULL)
        return (DispatchResult){ .ansi = NULL, .status = DISPATCH_ERROR };

    (*ctx->index) += 3;

    return (DispatchResult){ .ansi = ansi, .status = DISPATCH_OK };
}
