all: 1 2 3 4 5 6 7

1: 1.o converter.o
	$(CC) -o 1 1.o converter.o $(LDFLAGS)

2: 2.o converter.o
	$(CC) -o 2 2.o converter.o $(LDFLAGS)

3: 3.o converter.o xor.o eval.o
	$(CC) -o 3 3.o converter.o xor.o eval.o $(LDFLAGS)

4: 4.o converter.o xor.o eval.o
	$(CC) -o 4 4.o converter.o xor.o eval.o $(LDFLAGS)

5: 5.o converter.o xor.o
	$(CC) -o 5 5.o converter.o xor.o $(LDFLAGS)

6: 6.o xor.o eval.o
	$(CC) -o 6 6.o xor.o eval.o $(LDFLAGS)

7: 7.o
	$(CC) -o 7 7.o $(LDFLAGS)
