CC = gcc
CFLAGS = -ansi -Wall -pedantic

a3 : main.o binary.o common.o name.o principals.o title.o
	$(CC) $(CFLAGS) -o $@ main.o binary.o common.o name.o principals.o title.o

main.o : main.c binary.h common.h name.h principals.h title.h
	$(CC) $(CFLAGS) -o $@ -c main.c

binary.o : binary.c binary.h
	$(CC) $(CFLAGS) -o $@ -c binary.c

common.o : common.c common.h
	$(CC) $(CFLAGS) -o $@ -c common.c

name.o : name.c name.h
	$(CC) $(CFLAGS) -o $@ -c name.c

principals.o : principals.c principals.h
	$(CC) $(CFLAGS) -o $@ -c principals.c

title.o : title.c title.h 
	$(CC) $(CFLAGS) -o $@ -c title.c

clean : 
	rm main.o binary.o common.o name.o principals.o title.o
