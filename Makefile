CC=gcc
CFLAGS=--std=c99

all: project1

project1:process_sche.c process_sche.h project1.c
	$(CC) $(CFLAGS) project1.c process_sche.c -o $@
