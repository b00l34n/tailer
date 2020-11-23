# --------------------------------------------- #
# Makefile	                                    #
# building file                                 #
# A.C.P.I. - monday                             #
#                                               #
# Makefile                                      #
# version: 1                                    #
# --------------------------------------------- #

.PHONY: buid clean
.SUFFIXES: .c
.SECONDARY:

SOURCE     = main.c
LIB_SOURCE =

CC         = gcc
CF         = -Wall -o
PPF		     =

TRGT       = tailer

default: build

build:
	${CC} ${PPF} ${CF} ${TRGT} ${SOURCE} ${LIB_SOURCE}

clean:
	rm ${TRGT}
