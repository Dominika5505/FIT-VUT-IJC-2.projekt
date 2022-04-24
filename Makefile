# -*- Makefile -*-
CC = gcc
CXX = g++
CFLAGS = -std=c99 -pedantic -Wall -Wextra -g
CXXFLAGS = -std=c++11 -O2

TARGETS = tail wordcount wordcount-dynamic wordcount_cc

LIB_HEADER_FILES = htab.h htab_private.h

# Library objects as c files
SRCS = $(wildcard htab_*.c)
# Library objects as o files
LIB_OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(TARGETS)

valgrind:
	valgrind --main-stacksize=67108864 --max-stackframe=67108864 --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt  ./wordcount-dynamic < /usr/share/dict/words

zip:
	zip xsedil00.zip *.c *.cc *.h Makefile

# Tail -------------------

tail: tail.o
	$(CC) $(CFLAGS) $^ -o $@

tail.o: tail.c
	$(CC) $(CFLAGS) -c $< -o $@

# Worcount ---------------

wordcount: wordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) $^ -static -o $@ -L. -lhtab

wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c $< -o $@

# Wordcount-dynamic ------

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) -Wl,-rpath . $^ -o $@

# Wordcount C++

wordcount_cc: wordcount_cc.o
	$(CXX) $(CXXFLAGS) $^ -o $@

wordcount_cc.o: wordcount-.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# IO ---------------------

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< -o $@

# Static Library ---------

%.a: $(LIB_OBJS)
	ar rcs $@ $^

# Dynamic Library --------
%.so: $(LIB_OBJS)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@


# Library objects --------

htab_print.o: htab_print.c $(LIB_HEADER_FILES) htab_print.h
	$(CC) -fPIC -c $< -o $@

%.o: %.c $(LIB_HEADER_FILES)
	$(CC) -fPIC -c $< -o $@

clean:
	rm -f *.o