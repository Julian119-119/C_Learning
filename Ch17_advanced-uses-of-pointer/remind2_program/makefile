remind2: remind2.o read_line.o
	gcc -o remind2 remind2.o read_line.o

remind2.o: remind2.c read_line.h
	gcc -c remind2.c

read_line.o: read_line.c read_line.h
	gcc -c read_line.c

clean: 
	rm -f remind2 remind2.o read_line.o
