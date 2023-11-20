OBJS = main.o history.o tokenizer.o
CFLAGS = -g -O3 -Wall -Wextra

all: main

main: $(OBJS)
	gcc -o main $(CFLAGS) $(OBJS)

main.o: main.c history.h tokenizer.h
	gcc -c $(CFLAGS) main.c

history.o: history.c history.h
	gcc -c $(CFLAGS) history.c

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c $(CFLAGS) tokenizer.c

clean:
	rm -f *.o tokenizer main history


run: main
	./main
