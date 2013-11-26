# Makefile for gqic
CC=gplc
CFLAGS=-I.

gqicwt: gqicwt_d.pl gqicwt_d.c
	$(CC) --c-compiler gcc -L '-lpthread' -o gqicwt_d gqicwt_d.pl gqicwt_d.c

clean:
	rm -rf gqicwt_d

