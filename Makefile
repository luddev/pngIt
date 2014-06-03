#		Makefile pngIt
#	Author : ludkiller
#	Date : 01/06/2014
#	Usage : Makefile for pngIt.


#compiler
CC = g++

#linker
LD = g++

#Compiler Flags
#CCFLAGS = 

#linker Flags
LDFLAGS = -lpng16 -lc -lstdc++

#debug flag
DFLAGS = -ggdb

all:link

compile:
	${CC} src/*.cc -c

link:compile
	${LD} ${LDFLAGS} *.o -o build/pngIt

clean:
	rm *.o

install:
	chmod a+x ./build/pngIt
	cp ./build/pngIt /usr/bin/
indent:
	indent -kr src/*.* -sc -br 
	rm src/*.*~
	
debug:
	${CC} ${DFLAGS} ${LDFLAGS} src/*.cc -o build/dpngIt
