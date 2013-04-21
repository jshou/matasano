export CC = gcc
export CFLAGS =
export LDFLAGS = -I *.h

all: round1-build

round1-build:
	cd round1 && $(MAKE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) $(DEFINES) -c $< -o $@
