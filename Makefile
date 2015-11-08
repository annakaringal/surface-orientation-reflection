CC = g++
VERS = -std=c++11

all: s1

s1: s1.o BinaryImage.o Object.o ObjectLabeler.o ImageObjectDatabase.o Validation.o Image.o Pgm.o
	$(CC) s1.o BinaryImage.o Object.o ObjectLabeler.o ImageObjectDatabase.o Validation.o Image.o Pgm.o -o s1

s1.o: s1.cpp
	$(CC) -c s1.cpp

BinaryImage.o: BinaryImage.cpp
	$(CC) -c BinaryImage.cpp

Object.o: objects/Object.cpp
	$(CC) -c objects/Object.cpp

ObjectLabeler.o: objects/ObjectLabeler.cpp
	$(CC) -c objects/ObjectLabeler.cpp

ImageObjectDatabase.o: objects/ImageObjectDatabase.cpp
	$(CC) $(VERS) -c objects/ImageObjectDatabase.cpp

Validation.o: Validation.cpp
	$(CC) -c Validation.cpp

Image.o: pgm/Image.cpp
	$(CC) -c pgm/Image.cpp

Pgm.o: pgm/Pgm.cpp
	$(CC) -c pgm/Pgm.cpp

Line.o: pgm/Line.cpp
	$(CC) -c pgm/Line.cpp

clean:
	rm *o s1