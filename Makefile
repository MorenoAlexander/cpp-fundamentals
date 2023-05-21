
CFLAGS= -Wall -Wextra -g




#-I/usr/local/include/raymath.h -I/usr/local/lib/libraylib.a

main: main.o
	clang++ $(CLFLAGs) -o main main.cpp -lraylib -lGL -lpthread -ldl -lrt -lX11


run: main
	./main

debug: main
	lldb main


clean:
	rm ./main ./main.o

