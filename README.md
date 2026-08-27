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

cfmt formatting begins with `\&`.

### Styles


\b  Bold
\d  Dim
\i  Italic
\u  U̲n̲d̲e̲r̲l̲i̲n̲e̲
\k  Blink
\v  Inverse
\n  Hidden
\t  Strikethrough
\r  Reset


### Foreground Colors

```text
\&0  Black
\&1  Red
\&2  Green
\&3  Yellow
\&4  Blue
\&5  Magenta
\&6  Cyan
\&7  White
\&9  Default
```

### Background Colors

Prefix the color with `h`:

```text
\&h1  Red background
\&h2  Green background
\&h7  White background
```

### Bright Colors

Use `B` for a bright foreground:

```text
\&B1  Bright red
\&B2  Bright green
```

Use `H` for a bright background:

```text
\&H1  Bright red background
\&H2  Bright green background
```

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

## printf-style Formatting

cfmt also supports common `printf` conversions:

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

`fmtstr()` returns a newly allocated formatted string. The caller owns the returned memory and must `free()` it.

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

cfmt is intentionally small and dependency-light, with the parser, codecs, state flags, and public interface separated into focused components.

------------------------------------------------------------------------------------------------------------------------------------------------

This project is actively in development. Changes to the source and readme could happen at any time. If you intend to use this library, please make sure you are keeping up to date with the changes until development is finished. Expect to see the full 256 color table, gretyscale ramp, hex RGB support and specific resets for each style in the near future. I will consider this project complete once all those features are implemented, but I may decide to add more after 1.0 if there is demand or reason for it. I use this library in my own C testing right now and I am orienting this to be a standard library for C Prime (check my gh profile).


$${\\color{red}This text is red!}$$
$${\\color{#9370DB}This text is custom purple!}$$
