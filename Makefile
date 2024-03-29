export CC=gcc -g -std=c99
export CFLAGS=`pkg-config --cflags glib-2.0`
export LDFLAGS=-I"*.h" `pkg-config --libs glib-2.0` -lm `pkg-config --libs openssl`

all: round1-build

round1-build:
	cd round1 && $(MAKE)
