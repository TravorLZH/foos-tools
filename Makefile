# Makefile for FOOS utility tools
CC=gcc

all:	mkdisk tartest

mkdisk:	mkdisk.c ../include/dev/ramdisk.h
	$(CC) -o $@ $<

tartest:	tartest.c
	$(CC) -o $@ $<

clean:
	rm -f mkdisk tartest
