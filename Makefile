CC = gcc
CFLAGS += -w -Wall -Wextra -Werror -pedantic-errors -O3 -std=c99 -fPIC
LDFLAGS = -shared

src = $(wildcard src/*.c)
obj = $(src:.c=.o)

STATIC_LIB = dist/libmemchunk.a
DYNAMIC_LIB = dist/libmemchunk.so

.PHONY: all
all: $(STATIC_LIB) $(DYNAMIC_LIB)

$(STATIC_LIB): $(obj)
	ar vrcs $@ $^

$(DYNAMIC_LIB): $(obj)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(STATIC_LIB) $(DYNAMIC_LIB) $(obj)
