CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -I../

all: dynarrx_tests.out hashtabx_tests.out

dynarrx_tests.out: dynarrx_tests.c
	$(CC) $(CFLAGS) -o $@ $^

hashtabx_tests.out: hashtabx_tests.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f dynarrx_tests.out hashtabx_tests.out
