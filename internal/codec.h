#ifndef CODEC_H
#define CODEC_H

#include "color.h"

Color decode(char code);
char recode(Color input);
char *encode(Color color, char mode);
char recode(Color input);

#endif