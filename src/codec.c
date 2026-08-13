#include <stdlib.h>
#include <stdio.h>

#include "codec.h"
#include "color.h"

Color decode(char code)
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

char recode(Color input) //inverse of decode.
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

char *encode(Color colcode, char mode)
{
    char *output = malloc(6);

    if (mode != 'b' && mode != 'f')
    {
        printf("Invalid encode mode. Use 'b' for background or 'f' for foreground.\n");
        return NULL;
    }


    output[0] = '\033';
    output[1] = '[';
    output[2] = (mode == 'b') ? '4' : '3';
    output[3] = recode(colcode);
    output[4] = 'm';
    output[5] = '\0';

    return output;
}

Color uncode(char *input)
{
    return decode(input[3]);
}