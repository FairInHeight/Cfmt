#include "dispatch.h"

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