# cfmt

A lightweight C23 library for readable ANSI terminal formatting.

cfmt adds a compact formatting syntax to C strings and provides `printf`-style wrappers for formatted terminal output.

## Features

* ANSI text styles
* Standard foreground colors
* Background colors
* Bright foreground and background colors
* 6×6×6 ANSI 256-color RGB cube
* Automatic formatting reset at newlines
* `printf`-style `%s`, `%c`, `%d`, `%i`, and `%f` substitutions
* `printfx`, `snprintfx`, and `fprintfx` wrappers
* Static-library build with GCC and C23

## Formatting Syntax

Cfmt formatting begins with `\&`. You must use literal backslash `\\` in strings when writing code. Single \'s in the terminal work fine, but due to how strings work in C with escape sequences, me must use literal backslash in strings to prefix our `&`.

### Styles

| Style | Cfmt Code | Ansi Sequence |
| :---: | :---: | :---: |
| Bold | \\&b | `ESC[1m` |
| Dim | \\&d | `ESC[2m` |
| Italic | \\&i | `ESC[3m` |
| Underline | \\&u | `ESC[4m` |
| Blinking | \\&k | `ESC[5m` |
| Inverted | \\&v | `ESC[7m` |
| Hidden | \\&n | `ESC[8m` |
| Strikethrough | \\&t | `ESC[9m` |
| Style Reset | \\&r | `ESC[0m` |

### Colors

Use `*` for bright colors.

| Color | Color Code | Ansi Sequence | Bright Color | Bright Color Code | Ansi Sequence |
| :---: | :---: | :---: | :---: | :---: | :---: |
| $\textcolor{black}{\text{Black}}$ | \\&0 | `ESC[30m` | $\textcolor{#7F7F7F}{\text{Bright Black}}$ | \\&*0 | `ESC[90m` |
| $\textcolor{red}{\text{Red}}$ | \\&1 | `ESC[31m` | $\textcolor{#FF5555}{\text{Bright Red}}$ | \\&*1 | `ESC[91m` |
| $\textcolor{green}{\text{Green}}$ | \\&2 | `ESC[32m` | $\textcolor{#55FF55}{\text{Bright Green}}$ | \\&*2 | `ESC[92m` |
| $\textcolor{yellow}{\text{Yellow}}$ | \\&3 | `ESC[33m` | $\textcolor{#FFFF55}{\text{Bright Yellow}}$ | \\&*3 | `ESC[93m` |
| $\textcolor{blue}{\text{Blue}}$ | \\&4 | `ESC[34m` | $\textcolor{#5555FF}{\text{Bright Blue}}$ | \\&*4 | `ESC[94m` |
| $\textcolor{magenta}{\text{Magenta}}$ | \\&5 | `ESC[35m` | $\textcolor{#FF55FF}{\text{Bright Magenta}}$ | \\&*5 | `ESC[95m` |
| $\textcolor{cyan}{\text{Cyan}}$ | \\&6 | `ESC[36m` | $\textcolor{#55FFFF}{\text{Bright Cyan}}$ | \\&*6 | `ESC[96m` |
| White | \\&7 | `ESC[37m` | $\textcolor{#FFFFFF}{\text{Bright White}}$ | \\&*7 | `ESC[97m` |
| Default Color | \\&9 | `ESC[39m` | N / A | \\&*9 | `ESC[99m` |

### Background/Highlight Colors

Prefix the color with `h` for standard colors,
or `H` for a bright colors.

| Color | Highlight/BG Code | Ansi Sequence | Bright Color | Bright BG/Highlight | Ansi Sequence |
| :---: | :---: | :---: | :---: | :---: | :---: |
| $\textcolor{black}{\text{Black}}$ | \\&h0 | `ESC[40m` | $\textcolor{#7F7F7F}{\text{Bright Black}}$ | \\&H0 | `ESC[100m` |
| $\textcolor{red}{\text{Red}}$ | \\&h1 | `ESC[41m` | $\textcolor{#FF5555}{\text{Bright Red}}$ | \\&H1 | `ESC[101m` |
| $\textcolor{green}{\text{Green}}$ | \\&h2 | `ESC[42m` | $\textcolor{#55FF55}{\text{Bright Green}}$ | \\&H2 | `ESC[102m` |
| $\textcolor{yellow}{\text{Yellow}}$ | \\&h3 | `ESC[43m` | $\textcolor{#FFFF55}{\text{Bright Yellow}}$ | \\&H3 | `ESC[103m` |
| $\textcolor{blue}{\text{Blue}}$ | \\&h4 | `ESC[44m` | $\textcolor{#5555FF}{\text{Bright Blue}}$ | \\&H4 | `ESC[104m` |
| $\textcolor{magenta}{\text{Magenta}}$ | \\&h5 | `ESC[45m` | $\textcolor{#FF55FF}{\text{Bright Magenta}}$ | \\&H5 | `ESC[105m` |
| $\textcolor{cyan}{\text{Cyan}}$ | \\&h6 | `ESC[46m` | $\textcolor{#55FFFF}{\text{Bright Cyan}}$ | \\&H6 | `ESC[106m` |
| White | \\&h7 | `ESC[47m` | $\textcolor{#FFFFFF}{\text{Bright White}}$ | \\&H7 | `ESC[107m` |
| Default BG/Highlight | \\&h9 | `ESC[49m` | N / A | \\&H9 | `ESC[109m` |

### RGB Color Cube

The ANSI 256-color palette contains a 6×6×6 RGB cube. cfmt represents each RGB component with a value from `0` through `5`:

```text
\&cRGB
```

For example:

```text
\&c500
```

represents maximum red with no green or blue.

The RGB cube is encoded into the ANSI 256-color range using:

```text
16 + (36 × R) + (6 × G) + B
```

## Print Wrappers

Cfmt wraps various standard library functions with its own functions to give the user a set of functions that behave just like the standard library counterparts, but replace our custom escape codes with ANSI sequences in the return. This is very seamless as any function you would normally use can just be followed with x to incorporate Cfmt formatting/translation. All functions behave identically to their standard library counterparts other than library exclusive escape sequences. This includes variadic arguments and % identifiers where applicable.

```c
printfx("Hello, %s!\n", name);
printfx("Value: %d\n", number);
printfx("Pi: %f\n", pi);
printfx("Character: %c\n", character);
```

Printf substitutions are resolved first, then the completed string is passed through the cfmt formatter. This allows formatting codes and runtime values to coexist in the same string.

## API

Include:

```c
#include <cfmt.h>
```

Available functions:

```c
char *fmtstr(const char *input);
char *fmtspec(char spec, va_list *args);

int printfx(const char *input, ...);
int snprintfx(char *str, size_t size, const char *input, ...);
int fprintfx(FILE *stream, const char *input, ...);
```
fmtstr will take any string and decode cfmt codes to ANSI and return a string with format codes replaces with ANSI sequences. This is the main translation layer that runs the entire library.

## Example

```c
#include <cfmt.h>

int main(void)
{
    printfx("\\&2Hello, %s!\\&r\n", "world");
    printfx("\\&B1Warning\\&r: value = %d\n", 42);

    return 0;
}
```

## Building

cfmt is built as a static library using GCC and C23:

```bash
make
```

This produces:

```text
build/cfmt.a
```

To build the project's test program:

```bash
make test
```

To remove generated files:

```bash
make clean
```

## Project Structure

```text
cfmt/
├── include/     Public headers
├── internal/    Internal headers and types
├── src/         Library implementation
├── Makefile
└── README.md
```

Cfmt is intentionally small and independent. The parser, codecs, state flags, and public interface are separated into focused components.

------------------------------------------------------------------------------------------------------------------------------------------------

This project is actively in development. Changes to the source and readme could happen at any time. If you intend to use this library, please make sure you are keeping up to date with the changes until development is finished. Expect to see the full 256 color table, gretyscale ramp, hex RGB support and specific resets for each style in the near future. I will consider this project complete once all those features are implemented, but I may decide to add more after 1.0 if there is demand or reason for it. I use this library in my own C testing right now and I am orienting this to be a standard library for C Prime (check my gh profile).
