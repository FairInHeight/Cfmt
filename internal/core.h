#ifndef CORE_H
#define CORE_H

char *fmtstr(const char *input);
char *fmtspec(char spec, va_list *args);
char *fmtin(const char *input, va_list *args);

static int append_string(
    char **output,
    size_t *output_size,
    size_t *out_index,
    const char *string);

#endif