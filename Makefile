OBJECTS = cc.o cnt_main.o draw.o inits.o location.o oo.o
HEADERS = datas.h
CC = gcc
OUTPUT = 
DEBUG = -Wall
LINKING_OPTIONS = 
CFLAGS = $(shell allegro-config --cflags)
LDFLAGS = $(shell allegro-config --libs)
WIN_CC = wine c:\\MinGW\\bin\\gcc.exe
WIN_OUTPUT = cypress.exe

cypress: $(OBJECTS)
	 $(CC) $(DEBUG) $(LINKING_OPTIONS) -o cypress $(OBJECTS) $(LDFLAGS)

cc.o: cc.c $(HEADERS)
	 $(CC) $(DEBUG) -c cc.c $(CFLAGS)

cnt_main.o: cnt_main.c $(HEADERS)
	 $(CC) $(DEBUG) -c cnt_main.c $(CFLAGS)

draw.o: draw.c $(HEADERS)
	 $(CC) $(DEBUG) -c draw.c $(CFLAGS)

inits.o: inits.c $(HEADERS)
	 $(CC) $(DEBUG) -c inits.c $(CFLAGS)

location.o: location.c $(HEADERS)
	 $(CC) $(DEBUG) -c location.c $(CFLAGS)

oo.o: oo.c $(HEADERS)
	 $(CC) $(DEBUG) -c oo.c $(CFLAGS)

clean:
	 rm -f $(OBJECTS)

win:
	 $(WIN_CC) $(DEBUG) *.c -o $(WIN_OUTPUT) -lalleg

