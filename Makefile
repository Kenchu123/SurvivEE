CXX = g++
OBJS = ./build/Utility.o ./build/LoadMedia.o ./build/Obj.o ./build/Item.o ./build/Bullet.o ./build/Player.o ./build/main.o ./build/button.o ./build/Obstacle.o ./build/Timer.o
INC = ./include
LIB = ./lib
OBJDIR = ./build
EXEDIR = ./bin

ifeq ($(OS),Windows_NT)
LDFLAGS = -lmingw32 -lSDL2_image -lSDL2_mixer -lSDL2main -lSDL2
else ($(PLATFORM),Darwin)
LDFLAGS = -F/Library/Frameworks -framework SDL2_image -framework SDL2 -framework SDL2_mixer
endif



all: directories $(EXEDIR)/SurvivEE

directories: $(OBJDIR) $(EXEDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEDIR):
	mkdir -p $(EXEDIR)

$(OBJDIR)/%.o: ./src/%.cpp
	$(CXX) -c -o $@ $< -g -I$(INC) -L$(LIB) $(LDFLAGS)

$(EXEDIR)/SurvivEE: $(OBJS)
	$(CXX) $(CXXFLAGS) -o ./bin/SurvivEE $(OBJS) -L$(LIB) $(LDFLAGS)

clean:
	rm -f $(OBJDIR)/*
	rm -f $(EXEDIR)/*.exe
