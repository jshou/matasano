all: 1 2 3

1: 1.o converter.o
	$(CC) -o 1 1.o converter.o $(LDFLAGS)

2: 2.o converter.o
	$(CC) -o 2 2.o converter.o $(LDFLAGS)

3: 3.o converter.o xor.o eval.o
	$(CC) -o 3 3.o converter.o xor.o eval.o $(LDFLAGS)
