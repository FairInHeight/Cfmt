#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "dispatch.h"
#include "../internal/flags.h"
#include "core.h"

// Converts cfmt codes such as \&1 and \&h2 to ANSI.
char *fmtstr(const char *input)
{
    if (input == NULL || strlen(input) == SIZE_MAX)
        return NULL;

    // Start with enough space for the original input plus '\0'.
    size_t output_size = strlen(input) + 1;
    char *output = malloc(output_size);

    if (output == NULL)
        return NULL;

    size_t out_index = 0;

    for (size_t index = 0; input[index] != '\0'; index++)
    {
        // Detect the complete \& sequence before copying either character.
        // This consumes both '\\' and '&' as cfmt syntax.
        if (input[index] == '\\' && input[index + 1] == '&')
        {
            // The next character will be processed as the format specifier.
            set_(parsing);

            // Skip the '&'. The for-loop will advance to the specifier.
            index++;

            continue;
        }

        // Handle the character following \&.
        if (is_(parsing))
        {
            char fspec = input[index];

            // Incomplete format at end of string.
            if (fspec == '\0')
            {
                output[out_index++] = '&';

                clr_(parsing);
                continue;
            }

            DispatchContext ctx = {
                .input = input,
                .index = &index
            };

            DispatchHandler handler = dispatch(fspec);
            char *ansi = NULL;

            if (handler != NULL)
                ansi = handler(&ctx);

            // Invalid formatting is emitted literally.
            if (ansi == NULL)
            {
                output[out_index++] = '&';
                output[out_index++] = fspec;
                clr_(parsing);
                continue;
            }

            size_t ansi_size = strlen(ansi);

            if (ansi_size > SIZE_MAX - output_size)
            {
                free(ansi);
                free(output);
                return NULL;
            }

            char *new_output =
                realloc(output, output_size + ansi_size);

            if (new_output == NULL)
            {
                free(ansi);
                free(output);
                return NULL;
            }

            output = new_output;
            output_size += ansi_size;

            memcpy(output + out_index, ansi, ansi_size);
            out_index += ansi_size;

            free(ansi);

            // A format is now active.
            set_(formatting);

            // Parsing is complete.
            clr_(parsing);

            continue;
        }

        // Reset active formatting before copying a newline.
        if (input[index] == '\n' && is_(formatting))
        {
            const char reset[] = "\033[0m";
            size_t reset_size = sizeof(reset) - 1;

            if (reset_size > SIZE_MAX - output_size)
            {
                free(output);
                return NULL;
            }

            // Expand the output buffer for the ANSI reset sequence.
            char *new_output =
                realloc(output, output_size + reset_size);

            if (new_output == NULL)
            {
                free(output);
                return NULL;
            }

            output = new_output;
            output_size += reset_size;

            // Insert the reset immediately before the newline.
            memcpy(output + out_index, reset, reset_size);
            out_index += reset_size;

            // Formatting is no longer active after the reset.
            clr_(formatting);
        }

        // Copy a normal character.
        output[out_index++] = input[index];
    }

    // Null-terminate the final string.
    output[out_index] = '\0';

    return output;
}


// Converts a printf-style format specifier into a string.
char *fmtspec(char spec, va_list *args)
{
    if (args == NULL)
        return NULL;

    // %s
    if (spec == 's')
    {
        char *string = va_arg(*args, char *);

        if (string == NULL || strlen(string) == SIZE_MAX)
            string = "(null)";

        // fmtin() assembles the complete string first and then sends
        // the entire result through fmtstr() exactly once.
        size_t size = strlen(string) + 1;
        char *output = malloc(size);

        if (output == NULL)
            return NULL;

        memcpy(output, string, size);

        return output;
    }

    // %c
    else if (spec == 'c')
    {
        int character = va_arg(*args, int);

        char *output = malloc(2);

        if (output == NULL)
            return NULL;

        output[0] = (char)character;
        output[1] = '\0';

        return output;
    }

    // %i, %d
    else if (spec == 'i' || spec == 'd')
    {
        int number = va_arg(*args, int);

        int size = snprintf(NULL, 0, "%i", number);

        if (size < 0)
            return NULL;

        char *output = malloc((size_t)size + 1);

        if (output == NULL)
            return NULL;

        snprintf(output, (size_t)size + 1, "%i", number);

        return output;
    }

    // %f
    else if (spec == 'f')
    {
        double number = va_arg(*args, double);

        int size = snprintf(NULL, 0, "%f", number);

        if (size < 0)
            return NULL;

        char *output = malloc((size_t)size + 1);

        if (output == NULL)
            return NULL;

        snprintf(output, (size_t)size + 1, "%f", number);

        return output;
    }

    return NULL;
}