#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfmt.h"
#include "color.h"
#include "codec.h"
#include "dispatch.h"
#include "../internal/flags.h"
#include "style.h"


// Appends a string to the output buffer.
static int append_string(
    char **output,
    size_t *output_size,
    size_t *out_index,
    const char *string)
{
    if (output == NULL ||
    output_size == NULL ||
    out_index == NULL ||
    string == NULL)
        return -1;

    size_t string_size = strlen(string);

    if (string_size > SIZE_MAX - *output_size)
        return -1;

    char *new_output =
        realloc(*output, *output_size + string_size);

    if (new_output == NULL)
        return -1;

    *output = new_output;

    memcpy(*output + *out_index, string, string_size);

    *out_index += string_size;
    *output_size += string_size;

    return 0;
}


// Processes the input string and printf-style arguments.
char *fmtin(const char *input, va_list *args)
{
    if (input == NULL || args == NULL || strlen(input) == SIZE_MAX)
        return NULL;

    // Start with enough space for the input string.
    size_t output_size = strlen(input) + 1;
    char *output = malloc(output_size);

    if (output == NULL)
        return NULL;

    size_t out_index = 0;

    for (size_t index = 0; input[index] != '\0'; index++)
    {
        // Handle printf-style format specifiers.
        if (input[index] == '%' && input[index + 1] != '\0')
        {
            char *formatted = fmtspec(input[index + 1], args);

            if (formatted != NULL)
            {
                // Append the formatted argument.
                if (append_string(
                        &output,
                        &output_size,
                        &out_index,
                        formatted) != 0)
                {
                    free(formatted);
                    free(output);
                    return NULL;
                }

                free(formatted);

                // Skip the format specifier.
                index++;

                continue;
            }
        }

        // Append normal characters.
        output[out_index++] = input[index];
    }

    // Terminate the completed printf-style string before passing it
    // to the cfmt formatting parser.
    output[out_index] = '\0';

    // Apply cfmt formatting exactly once, after all printf-style
    // substitutions have been resolved.
    char *formatted_output = fmtstr(output);

    free(output);

    return formatted_output;
}





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
