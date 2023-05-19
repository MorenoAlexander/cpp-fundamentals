
CFLAGS= -Wall -Wextra 

RAYLIB=



#-I/usr/local/include/raymath.h -I/usr/local/lib/libraylib.a

main: main.o
	clang++ $(CLFLAGs) main.cpp -lraylib -lGL -lpthread -ldl -lrt -lX11



