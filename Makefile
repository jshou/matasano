export CC = gcc
export CFLAGS = `pkg-config --cflags glib-2.0`
export LDFLAGS = `pkg-config --libs glib-2.0`

all: round1-build

round1-build:
	cd round1 && $(MAKE)

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@
