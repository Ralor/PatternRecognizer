CC=g++
CFLAGS=-std=c++11 -c -Wall

INC=-IC:\opencv\build\include
#LIB=-L$(OPENCV_DIR)\staticlib -lm -lopencv_core300 -lopencv_highgui300 -lopencv_imgproc300 -lopencv_features2d300 -lopencv_calib3d300
LIB=-L$(OPENCV_DIR)\lib -lm -lopencv_world300

all: test

rnd: rect.o
	$(CC) $(LIB) $(INC) build\rect.o -o bin\rnd.exe
    
rect.o: src\rect.cpp
	$(CC) $(CFLAGS) $(INC) src\rect.cpp -o build\rect.o
	
test: helloworld.o
	$(CC) $(LIB) $(INC) build\helloworld.o -o bin\helloworld.exe
	
helloworld.o: src\helloworld.cpp
	$(CC) $(CFLAGS) $(INC) src\helloworld.cpp -o build\helloworld.o