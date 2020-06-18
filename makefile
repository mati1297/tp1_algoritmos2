CC = g++
CFLAGS  = -pedantic -Wall -g

default: imagen clean

imagen:  main.o  complejo.o shunting_yard.o leer_cmdline.o imagen.o cmdline.o
	$(CC) $(CFLAGS) -o imagen main.o complejo.o shunting_yard.o leer_cmdline.o imagen.o cmdline.o

main.o: main.cpp imagen.h leer_cmdline.h cmdline.h
	$(CC) $(CFLAGS) -c main.cpp

leer_cmdline.o:  leer_cmdline.cpp leer_cmdline.h cmdline.h imagen.h shunting_yard.h lista.h
	$(CC) $(CFLAGS) -c leer_cmdline.cpp

imagen.o:  imagen.cpp imagen.h complejo.h lista.h
	$(CC) $(CFLAGS) -c imagen.cpp

shunting_yard.o: shunting_yard.cpp shunting_yard.h lista.h
	$(CC) $(CFLAGS) -c shunting_yard.cpp

complejo.o: complejo.cpp complejo.h
	$(CC) $(CFLAGS) -c complejo.cpp

cmdline.o:  cmdline.cpp cmdline.h
	$(CC) $(CFLAGS) -c cmdline.cpp

clean: 
	$(RM) count *.o *~
