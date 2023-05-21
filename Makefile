
CFLAGS= -Wall -Wextra -g




#-I/usr/local/include/raymath.h -I/usr/local/lib/libraylib.a

main: main.o
	clang++ $(CLFLAGs) -o main main.cpp -lraylib -lGL -lpthread -ldl -lrt -lX11


run: main
	./main

debug: main
	lldb main

dasher:
	clang++ $(CLFLAGs) -o dasher dasher.cpp -lraylib -lGL -lpthread -ldl -lrt -lX11

clean:
	rm ./main ./main.o
	rm ./dasher ./dasher.o

