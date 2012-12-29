GCC=gcc
X11_LIBS=-lX11
all: poorwm

poorwm: main.o
	$(GCC) -o poorwm main.o $(X11_LIBS)

main.o: main.c
	$(GCC) -c main.c

clean:
	rm poorwm *.o

