# Makefile for FOOS utility tools
CC=gcc

all:	mkdisk tartest symtable

mkdisk:	mkdisk.c ../include/dev/ramdisk.h
	$(CC) -o $@ $<

symtable:	symtable.c ../include/foos/debug.h
	$(CC) -o $@ $<

tartest:	tartest.c
	$(CC) -o $@ $<

clean:
	rm -f mkdisk tartest symtable
