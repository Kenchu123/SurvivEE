CXX = g++
OBJS = ./build/Utility.o ./build/LoadMedia.o ./build/Obj.o ./build/Bullet.o ./build/Player.o ./build/main.o
INC = ./include
LIB = ./lib
LDFLAGS = -framework SDL2_image -framework SDL2
CXXFLAGS = -std=c++17

all: ./bin/SurvivEE

./build/%.o: ./src/%.cpp
	$(CXX) -c -o $@ $< -g -I$(INC) $(CXXFLAGS)

./bin/SurvivEE: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ./bin/SurvivEE $(OBJS) $(LDFLAGS)

clean:
	rm -f ./build/*
	rm -f ./bin/*