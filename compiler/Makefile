TARGET = compiler.out
CC = gcc
CFLAGS = -w

SOURCES = $(wildcard *.c)
OBJECTS := $(SOURCES:%.c=%.o)
HEADERS = $(wildcard *.h)

.PHONY: default all clean

default: $(TARGET)

all: default 

install: 
	yacc parser.y -d
	flex scanner.l

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -w -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)

uninstall:	
	rm -f y.tab.c y.tab.h lex.yy.c