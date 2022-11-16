CC=cc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -c -fPIC
LIB_NAME=containers
SO_NAME=lib$(LIB_NAME).so

all: $(SO_NAME) install

string.o:
	$(CC) $(CFLAGS) src/string.c

dict.o:
	$(CC) $(CFLAGS) src/dict.c

$(SO_NAME): string.o dict.o
	$(CC) -shared -o $@ $^

install:
	cp $(SO_NAME) /usr/lib
	chmod 0755 /usr/lib/$(SO_NAME)
	mkdir /usr/include/$(LIB_NAME)
	cp src/*.h /usr/include/$(LIB_NAME)
	ldconfig

clean:
	rm -f *.o
	rm -f $(SO_NAME)

uninstall:
	rm -r -f /usr/include/$(LIB_NAME)
	rm -f /usr/lib/$(SO_NAME)
