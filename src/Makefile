#StringArt by Arthur Péraud

CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm `sdl2-config --cflags --libs` #-lSDL2_image
OBJ = main.o rendering.o thread.o image.o

#.out
StringArt : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

#Image processing
image.o : Images/image.h Images/image.c
	$(CC) -c Images/image.c $(CFLAGS)

#Thread Calculations
thread.o : Threads/thread.h Threads/thread.c Images/image.h 
	$(CC) -c Threads/thread.c $(CFLAGS)

#Graphic render
rendering.o : Graphics/rendering.h Graphics/rendering.c Threads/thread.h 
	$(CC) -c Graphics/rendering.c $(CFLAGS) 

#Main file
main.o : main.c Graphics/rendering.h Threads/thread.h 
	$(CC) -c main.c $(CFLAGS)

#Cleaning objects
clean :
	rm -f $(OBJ)