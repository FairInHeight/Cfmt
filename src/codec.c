#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    size_t out_size = 6;

    if (mode == 'h')
        out_size = 7;

    char *output = malloc(out_size);

    if (output == NULL)
    {
        return NULL;
    }

    output[0] = '\033';
    output[1] = '[';

    if (mode == 'f')
        output[2] = '3';
    else if (mode == 'b')
        output[2] = '4';
    else if (mode == 'B')
        output[2] = '9';
    else if (mode == 'H')
    {
        output[2] = '1';
        output[3] = '0';
        output[4] = recode_color(color);
        output[5] = 'm';
        output[6] = '\0';

        return output;
    }
    else
    {
        free(output);
        return NULL;
    }

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







char *encode_color256(Color color, char mode)
{
    char *buffer;
    size_t buffer_size;

    if (color > 99)
    {
        buffer_size = 4;
    }
    else if (color > 9)
    {
        buffer_size = 3;
    }
    else
    {
        buffer_size = 2;
    }
    
    buffer = malloc(buffer_size);

    snprintf(buffer, buffer_size, "%d", color);

    size_t output_size = buffer_size + 9;
    char *output = malloc(output_size);

    output[0] = '\033';
    output[1] = '[';
    output[2] = mode == 'h' ? '4' : '3';
    output[3] = '8';
    output[4] = ';';
    output[5] = '5';
    output[6] = ';';
    
    memcpy(output + 7, buffer, buffer_size - 1);

    output[7 + buffer_size - 1] = 'm';
    output[7 + buffer_size] = '\0';

    free(buffer);
    return output;
}