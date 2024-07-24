CFLAGS=-Wall -Wextra -O2
LFLAGS=-lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

test: main.c
	cc main.c $(CFLAGS) $(LFLAGS)