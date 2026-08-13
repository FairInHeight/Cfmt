#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "cfmt.h"
#include "flags.h"
#include "style.h"
#include "color.h"
#include "codec.h"


// Converts cfmt codes such as \&1 and \&h2 to ANSI.
char *fmtstr(const char *input)
{
    if (input == NULL)
    {
        return NULL;
    }

    size_t output_size = strlen(input) + 1;
    char *output = malloc(output_size);

    if (output == NULL)
    {
        return NULL;
    }

    size_t out_index = 0;

    for (size_t index = 0; input[index] != '\0'; index++)
    {
        // Handle the character following \&.
        if (is_(parsing))
        {
            char fspec = input[index];
            char fspec2 = input[index + 1];

            // Cancel formatting if the string ends after the specifier.
            if (fspec2 == '\0')
            {
                output[out_index++] = '&';
                output[out_index++] = fspec;

                clr_(parsing);
                continue;
            }

            // Validate foreground and background color codes.
            if (fspec == 'h')
            {
                // Background colors require a second numeric color code.
                if ((fspec2 < '0' || fspec2 > '7') && fspec2 != '9')
                {
                    // Preserve the invalid format literally.
                    output[out_index++] = '&';
                    output[out_index++] = fspec;

                    clr_(parsing);
                    continue;
                }
            }
            else if ((fspec < '0' || fspec > '7') && fspec != '9')
            {
                // Invalid foreground color code. Preserve it literally.
                output[out_index++] = '&';
                output[out_index++] = fspec;

                clr_(parsing);
                continue;
            }
            

            // The '&' was never copied to the output. The backslash was
            // consumed by the \& detection block below, so the current
            // output index already points to the correct insertion point.

            char *ansi;

            // Generate the ANSI sequence for the requested format.
            if (fspec == 'h')
            {
                // Background color: use the second character as the color code.
                color = decode(fspec2);
                ansi = encode(color, 'b');

                // Consume the second character of the format specifier.
                index++;
            }
            else
            {
                // Foreground color: use the first character as the color code.
                color = decode(fspec);
                ansi = encode(color, 'f');
            }

            if (ansi == NULL)
            {
                free(output);
                return NULL;
            }

            size_t ansi_size = strlen(ansi);

            // Expand the output buffer to make room for the ANSI sequence.
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

            // Insert the ANSI sequence where the cfmt code was located.
            memcpy(output + out_index, ansi, ansi_size);
            out_index += ansi_size;

            free(ansi);

            // A valid format is now active.
            // This lets newline handling reset the format automatically.
            set_(formatting);

            // The format specifier has been fully processed.
            clr_(parsing);

            continue;
        }

        // Detect \& and consume the escape backslash.
        if (index > 0 &&
            input[index] == '&' &&
            input[index - 1] == '\\')
        {
            // The backslash was copied during the previous iteration.
            // Remove it because it belongs to cfmt syntax.
            out_index--;

            // The next character is the formatting specifier.
            set_(parsing);

            continue;
        }

        // Reset active formatting before copying a newline.
        // The newline already exists in the input string, normally because
        // fgets() stored the Enter key as '\n'. We insert the ANSI reset
        // immediately before that existing newline.
        if (input[index] == '\n' && is_(formatting))
        {
            const char reset[] = "\033[0m";
            size_t reset_size = sizeof(reset) - 1;

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

            // The format is no longer active after the reset.
            clr_(formatting);
        }

        // Copy the current normal character.
        output[out_index++] = input[index];
    }

    // Null-terminate the final formatted string.
    output[out_index] = '\0';

    return output;
}


// Converts a printf-style format specifier into a string.
char *fmtspec(char spec, va_list *args)
{
    if (args == NULL)
    {
        return NULL;
    }

    // %s
    if (spec == 's')
    {
        char *string = va_arg(*args, char *);

        if (string == NULL)
        {
            string = "(null)";
        }

        // CHANGED:
        // Copy the raw string here. Do not call fmtstr().
        //
        // fmtin() assembles the complete string first and then sends
        // the entire result through fmtstr() exactly once.
        size_t size = strlen(string) + 1;
        char *output = malloc(size);

        if (output == NULL)
        {
            return NULL;
        }

        memcpy(output, string, size);

        return output;
    }

    // %c
    else if (spec == 'c')
    {
        int character = va_arg(*args, int);

        char *output = malloc(2);

        if (output == NULL)
        {
            return NULL;
        }

        output[0] = (char)character;
        output[1] = '\0';

        return output;
    }

    // %i
    else if (spec == 'i')
    {
        int number = va_arg(*args, int);

        int size = snprintf(NULL, 0, "%i", number);

        if (size < 0)
        {
            return NULL;
        }

        char *output = malloc((size_t)size + 1);

        if (output == NULL)
        {
            return NULL;
        }

        snprintf(output, (size_t)size + 1, "%i", number);

        return output;
    }

    // %f
    else if (spec == 'f')
    {
        double number = va_arg(*args, double);

        int size = snprintf(NULL, 0, "%f", number);

        if (size < 0)
        {
            return NULL;
        }

        char *output = malloc((size_t)size + 1);

        if (output == NULL)
        {
            return NULL;
        }

        snprintf(output, (size_t)size + 1, "%f", number);

        return output;
    }

    return NULL;
}


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
    {
        return -1;
    }

    size_t string_size = strlen(string);

    char *new_output =
        realloc(*output, *output_size + string_size);

    if (new_output == NULL)
    {
        return -1;
    }

    *output = new_output;

    memcpy(*output + *out_index, string, string_size);

    *out_index += string_size;
    *output_size += string_size;

    return 0;
}


// Processes the input string and printf-style arguments.
char *fmtin(const char *input, va_list *args)
{
    if (input == NULL || args == NULL)
    {
        return NULL;
    }

    // Start with enough space for the input string.
    size_t output_size = strlen(input) + 1;
    char *output = malloc(output_size);

    if (output == NULL)
    {
        return NULL;
    }

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
    {
        return -1;
    }

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