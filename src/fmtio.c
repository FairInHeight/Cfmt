#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "core.h"

// printf wrapper with cfmt support.
int printfx(const char *input, ...)
{
    if (input == NULL)
        return -1;

    va_list args;
    va_start(args, input);

    // fmtin handles printf-style arguments and builds the final string.
    char *output = fmtin(input, &args);

    if (output == NULL)
    {
        va_end(args);
        return -1;
    }

    // printfx only prints the completed string.
    int result = printf("%s", output);

    free(output);
    va_end(args);

    return result;
}

int snprintfx(char *str, size_t size, const char *input, ...)
{
    if (str == NULL || input == NULL)
        return -1;

    va_list args;
    va_start(args, input);

    // fmtin handles printf-style arguments and builds the final string.
    char *output = fmtin(input, &args);

    if (output == NULL)
    {
        va_end(args);
        return -1;
    }

    // snprintf handles the destination buffer and size limit.
    int result = snprintf(str, size, "%s", output);

    free(output);
    va_end(args);

    return result;
}

int fprintfx(FILE *stream, const char *input, ...)
{
    if (stream == NULL || input == NULL)
        return -1;

    va_list args;
    va_start(args, input);

    char *output = fmtin(input, &args);

    va_end(args);

    if (output == NULL)
        return -1;

    int result = fprintf(stream, "%s", output);

    free(output);

    return result;
}