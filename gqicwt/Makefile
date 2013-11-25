# Makefile for gqic
CC=gplc
CFLAGS=-I.

gqicwt: gqicwt.pl gqicwt.c
	$(CC) --c-compiler gcc -L '-lpthread' -o gqicwt gqicwt.pl gqicwt.c

clean:
	rm -rf gqicwt

