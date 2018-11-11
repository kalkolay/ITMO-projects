cc = gcc

main.o: libmylib.dylib main.cpp
	cc -c -fpic main.cpp

main: main.o libmylib.dylib
	g++ -o main main.o libmylib.dylib

libmylib.dylib: hello.o here.o bye.o
	g++ --verbose -dynamiclib -install_name libmylib.dylib.1.5.10 -o libmylib.dylib $^

%.o: %.cpp mylib.h
	cc -c -fPIC $<

clean:
	rm -rf *.o