#include <stdlib.h>
#include <stdio.h>

#include "codec.h"
#include "color.h"
#include "style.h"

Color decode_color(char code)
{
    switch (code)
    {
        case '0':
            return Black;
        case '1':
            return Red;
        case '2':
            return Green;
        case '3':
            return Yellow;
        case '4':
            return Blue;
        case '5':
            return Magenta;
        case '6':
            return Cyan;
        case '7':
            return White;
        default:
            return DEFAULT;
    }
}

char recode_color(Color input) //inverse of decode.
{
    switch (input)
    {
        case Black:
            return '0';
        case Red:
            return '1';
        case Green:
            return '2';
        case Yellow:
            return '3';
        case Blue:
            return '4';
        case Magenta:
            return '5';
        case Cyan:
            return '6';
        case White:
            return '7';
        default:
            return '9'; //default color code.
    }
}

char *encode_color(Color color, char mode)
{
    if (mode != 'b' && mode != 'f')
    {
        printf("Invalid encode mode. Use 'b' for background or 'f' for foreground.\n");
        return NULL;
    }

    char *output = malloc(6);

    if (output == NULL)
    {
        return NULL;
    }

    output[0] = '\033';
    output[1] = '[';
    output[2] = (mode == 'b') ? '4' : '3';
    output[3] = recode_color(color);
    output[4] = 'm';
    output[5] = '\0';

    return output;
}
Color uncode_color(const char *input)
{
    return decode_color(input[3]);
}








Style decode_style(char code)
{
    switch (code)
    {
        case 'r':
            return Reset;
        case 'b':
            return Bold;
        case 'd':
            return Dim;
        case 'i':
            return Italic;
        case 'u':
            return Underline;
        case 'k':
            return Blink;
        case 'v':
            return Inverse;
        case 'n':
            return Hidden;
        case 't':
            return Strikethrough;
        default:
            return Reset; // Default to Reset for unrecognized codes.
    }
}

char recode_style(Style input)
{
    switch (input)
    {
        case Reset:
            return 'r';
        case Bold:
            return 'b';
        case Dim:
            return 'd';
        case Italic:
            return 'i';
        case Underline:
            return 'u';
        case Blink:
            return 'k';
        case Inverse:
            return 'v';
        case Hidden:
            return 'n';
        case Strikethrough:
            return 't';
        default:
            return 'r'; // Default to Reset for unrecognized styles.
    }
}

char *encode_style(Style style)
{
    char *output = malloc(6);

    if (output == NULL)
    {
        return NULL;
    }

    char code;

    switch (style)
    {
        case Reset:
            code = '0';
            break;
        case Bold:
            code = '1';
            break;
        case Dim:
            code = '2';
            break;
        case Italic:
            code = '3';
            break;
        case Underline:
            code = '4';
            break;
        case Blink:
            code = '5';
            break;
        case Inverse:
            code = '7';
            break;
        case Hidden:
            code = '8';
            break;
        case Strikethrough:
            code = '9';
            break;
        default:
            code = '0';
            break;
    }

    output[0] = '\033';
    output[1] = '[';
    output[2] = code;
    output[3] = 'm';
    output[4] = '\0';

    return output;
}

Style uncode_style(const char *input)
{
    return decode_style(input[2]);
}