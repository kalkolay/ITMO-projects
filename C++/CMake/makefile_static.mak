ma:hello.o here.o bye.o
	ar rc libmylib.a hello.o here.o bye.o
hello.o:hello.cpp mylib.h
	gcc -c -o hello.o hello.cpp

here.o:here.cpp mylib.h
	gcc -c -o here.o here.cpp

bye.o:bye.cpp mylib.h
	gcc -c -o bye.o bye.cpp

clean:
	rm -rf *.o

all: ma