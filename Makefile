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
	indent -kr src/*.cc -sc -br
	indent -kr src/*.h -sc -br 
	rm src/*.*~
	

