# Makefile for MyCustomShell
# Author: Ritesh Bamola and Team

CC = gcc
CFLAGS = -Wall -g

SRCS = shell.c builtins.c jobs.c parsing.c
OBJS = $(SRCS:.c=.o)
EXEC = my_shell

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean