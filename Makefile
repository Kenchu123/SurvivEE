CXX = g++
OBJS = ./build/Utility.o ./build/LoadMedia.o ./build/Obj.o ./build/Item.o ./build/Bullet.o ./build/Player.o ./build/main.o ./build/button.o ./build/rObstacle.o ./build/Timer.o
INC = ./include
CXXFLAGS = -std=c++17
LIB = ./lib

ifeq ($(OS),Windows_NT)
LDFLAGS = -lmingw32 -lSDL2_image -lSDL2_mixer -lSDL2main -lSDL2
else ($(PLATFORM),Darwin)
LDFLAGS = -F/Library/Frameworks -framework SDL2_image -framework SDL2 -framework SDL2_mixer
endif



all: ./bin/SurvivEE

./build/%.o: ./src/%.cpp
	$(CXX) -c -o $@ $< -g -I$(INC) -L$(LIB) $(CXXFLAGS) $(LDFLAGS)

./bin/SurvivEE: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ./bin/SurvivEE $(OBJS) -L$(LIB) $(LDFLAGS)

clean:
	rm -f ./build/*
	rm -f ./bin/*