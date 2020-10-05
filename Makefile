# See LICENSE file for copyright and license details.

PREFIX = /usr/local

CFLAGS = -std=c99 -Wall
CC = cc

SRC = main.c

all: options alpha_dict

options:
	@echo alpha_dict build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "CC       = ${CC}"

alpha_dict:
	@${CC} -o alpha_dict ${CFLAGS} ${SRC}

clean:
	@rm -f alpha_dict
