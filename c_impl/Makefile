PKG_NAME = "Sandvich"
PKG_AUTHOR = "Andy Frank Schoknecht <afschoknecht@gmail.com>"
PKG_REPOSITORY = "https://github.com/SchokiCoder/sandvich"
PKG_LICENSE = "GPLv3"
PKG_VERSION_MAJOR = 0
PKG_VERSION_MINOR = 0
PKG_VERSION_PATCH = 0

MAKE = make
CC = cc
CFLAGS = -ansi -pedantic -Wall -Wextra

OUTDIR = ./bin

info:
	@echo "Hi :)"
	@echo "pls define a target"

#snvp: snvp/src/*.c
#	$(CC) $(CFLAGS) -c -fPIC $^
#	$(CC) -o $@ -shared lib$@.so

#snvc:

#snvi:

#snv:

#build: snvp snvc snvi snv

#install: build

#remove:

snv_test_bco.o: ./snv_test/snv_test_bco.c ./snv_test/snv_test_bco.h ./snv_test/snv_test_bool.h
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ -g -c ./snv_test/snv_test_bco.c

snv_test: snv_test_bco.o ./snv_test/snv_test.c ./snv_test/snv_test_bool.h
	$(CC) $(CFLAGS) -o $(OUTDIR)/$@ -g ./snv_test/snv_test.c ./bin/snv_test_bco.o

clear:
	rm ./bin/*
