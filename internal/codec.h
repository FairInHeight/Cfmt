#ifndef CODEC_H
#define CODEC_H

#include "color.h"
#include "style.h"

Color decode_color(char code);
char recode_color(Color input);
char *encode_color(Color color, char mode);
Color uncode_color(const char *input);

Style decode_style(char code);
char recode_style(Style input);
char *encode_style(Style style);
Style uncode_style(const char *input);

char *encode_color256(Color color, char mode);

#endif