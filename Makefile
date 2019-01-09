CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -Wall -std=c99 -lm -c
LFLAGS = -Wall -std=c99 -lm

OBJS = MovieLab.o FileIO.o DIPs.o Image.o ImageList.o IterativeFilter.o Movie.o MovieIO.o
DEPS = Image.h FileIO.h ImageList.h IterativeFilter.h Movie.h MovieIO.h DIPs.h 

DESIGN = MovieLab
all: $(DESIGN)
MovieLab : $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -lm -o MovieLab
MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o
FileIO.o: FileIO.c $(DEPS)
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
DIPs.o: DIPs.c $(DEPS)
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
Image.o: Image.c $(DEPS)
	$(CC) $(CFLAGS) Image.c -o Image.o
ImageList.o : ImageList.c $(DEPS)
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
IterativeFilter.o : IterativeFilter.c $(DEPS)
	$(CC) $(CFLAGS) IterativeFilter.c -o IterativeFilter.o
Movie.o : Movie.c $(DEPS)
	$(CC) $(CFLAGS) Movie.c -o Movie.o
MovieIO.o : MovieIO.c $(DEPS)
	$(CC) $(CFLAGS) MovieIO.c -o MovieIO.o

clean:
	rm -f *.o $(DESIGN) `find . -name '*.ppm' ! -name 'HSSOE.ppm'` `find . -name '*.yuv' ! -name 'mouse.yuv' ! -name 'hue.yuv' ! -name 'reverse.yuv'`
