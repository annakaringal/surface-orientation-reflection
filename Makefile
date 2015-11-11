CC = g++
VERS = -std=c++11

all: s1 s2 s3

s1: s1.o BinaryImage.o Object.o ObjectLabeler.o ImageObjectDatabase.o Sphere.o Validation.o Image.o Pgm.o
	$(CC) s1.o BinaryImage.o Object.o ObjectLabeler.o ImageObjectDatabase.o Sphere.o Validation.o Image.o Pgm.o -o s1

s2: s2.o Sphere.o Validation.o 3dVec.o Image.o Pgm.o
	$(CC) s2.o Sphere.o Validation.o 3dVec.o Image.o Pgm.o -o s2

s3: s3.o SurfaceNormalMap.o Validation.o 3dVec.o Image.o Pgm.o Line.o
	$(CC) s3.o SurfaceNormalMap.o Validation.o 3dVec.o Image.o Pgm.o Line.o -o s3

s1.o: s1.cpp
	$(CC) -c s1.cpp

s2.o: s2.cpp
	$(CC) -c s2.cpp

s3.o: s3.cpp
	$(CC) -c s3.cpp

3dVec.o: 3dVec.cpp
	$(CC) -c 3dVec.cpp

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

Sphere.o: Sphere.cpp
	$(CC) -c Sphere.cpp

SurfaceNormalMap.o: SurfaceNormalMap.cpp
	$(CC) -c SurfaceNormalMap.cpp

Image.o: pgm/Image.cpp
	$(CC) -c pgm/Image.cpp

Pgm.o: pgm/Pgm.cpp
	$(CC) -c pgm/Pgm.cpp

Line.o: pgm/Line.cpp
	$(CC) -c pgm/Line.cpp

clean:
	rm *o s1 s2 s3