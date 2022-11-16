PKG_NAME="Sandvich"
PKG_AUTHOR="Andy Frank Schoknecht <afschoknecht@gmail.com>"
PKG_REPOSITORY = "https://github.com/SchokiCoder/sandvich"
PKG_LICENSE="GPLv3"
PKG_VERSION_MAJOR=0
PKG_VERSION_MINOR=0
PKG_VERSION_PATCH=0


CC=cc
CFLAGS="-ansi -pedantic -Wall -Wextra"

snvp:
	$(CC) $(CFLAGS) -c -fPIC "$@/src/*.c"
	$(CC) -o $@ -shared "$@/src/*.o"

#snvc:

#snvi:

#snv:

#build: snvp snvc snvi snv

#install: build

#remove:

