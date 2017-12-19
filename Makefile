CFLAGS=-Wall -Wextra -Werror -pedantic-errors -std=c99 -fPIC
LDFLAGS=-shared

src=$(wildcard src/*.c)
obj=$(src:.c=.o)

STATIC_LIB=dist/libmemchunk.a
DYNAMIC_LIB=dist/libmemchunk.so

.PHONY: all
all: $(STATIC_LIB) $(DYNAMIC_LIB)

debug: CFLAGS+=-g
debug: all

release: CFLAGS+=-O3 -DNDEBUG
release: all

$(STATIC_LIB): $(obj)
	ar vrcs $@ $^

$(DYNAMIC_LIB): $(obj)
	$(CC) $(LDFLAGS) -o $@ $^

docs:
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -f $(STATIC_LIB) $(DYNAMIC_LIB) $(obj)
