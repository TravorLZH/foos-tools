# Makefile for FOOS utility tools
CC=gcc

all:	mkdisk tartest

mkdisk:	mkdisk.c ../include/dev/ramdisk.h
	$(CC) -g -o $@ $<

tartest:	tartest.c
	$(CC) -g -o $@ $<

clean:
	rm -f mkdisk tartest
