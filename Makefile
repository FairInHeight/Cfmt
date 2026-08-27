CC = gcc
AR = ar

CFLAGS = -Wall -Wextra -std=c23
CPPFLAGS = -Iinclude -Iinternal -MMD -MP

LIB = build/cfmt.a
TEST = ../build/test

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,build/%.o,$(SRCS))
DEPS = $(patsubst src/%.c,deps/%.d,$(SRCS))


# Build the static library.
all: $(LIB)


$(LIB): $(OBJS)
	@mkdir -p build
	$(AR) rcs $@ $^


# Compile source files into build/.
# Generate dependency files into deps/.
build/%.o: src/%.c
	@mkdir -p build deps
	$(CC) $(CFLAGS) $(CPPFLAGS) -MF deps/$*.d -c $< -o $@


# Build the external test program using the static library.
test: $(LIB)
	@mkdir -p ../build
	$(CC) $(CFLAGS) -Iinclude ../main.c ../commands.c  $(LIB) -o $(TEST)


# Clean, build, and run tests.
automake:
	$(MAKE) clean
	$(MAKE)
	$(MAKE) test


# Remove generated files.
clean:
	rm -f build/*.o
	rm -f build/*.a
	rm -f deps/*.d
	rm -f $(TEST)


# Load generated dependency files.
-include $(DEPS)


.PHONY: all test clean automake