CFLAGS=-Wall -Wextra -O2
LFLAGS=-lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Blast: libBlast.so

./obj/BlastCore.o: ./src/BlastCore.c
	cc ./src/BlastCore.c -O -o ./obj/BlastCore.o -c $(CFLAGS) $(LFLAGS)

libBlast.so: ./obj/BlastCore.o
	cc ./obj/*.o -shared -o libBlast.so $(CFLAGS)

main: main.c libBlast.so
	cc main.c $(CFLAGS) $(LFLAGS) -L. -lBlast

clean:
	rm -rf *.so ./obj/*.o

install:
	sudo mv libBlast.so /usr/lib