# Makefile
# Brandon Steege
# COSC 3750 Spring 2021
# Homework 7
# April 6, 2021
#
# This is a makefile used to generate the wytalkD and WytalkC executable.

CFLAGS=-ggdb -Wall
CC=gcc

.PHONY: clean

#creates executable wytalkC and wytalkD
wytalk: wytalkC.c wytalkD.c socketfun.c
		${CC} ${CFLAGS} wytalkC.c socketfun.c -o wytalkC
		${CC} ${CFLAGS} wytalkD.c socketfun.c -o wytalkD

#Deletes all object files and executable
clean: 
		/bin/rm -f wytalkC wytalkD core.*