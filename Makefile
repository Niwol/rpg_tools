CC = g++
CFLAGS = -Wall
LDFLAGS = -lSDL2 -lSDL2_image

ifeq ($(DEBUG), yes)
	CFLAGS += -g
else
	CFLAGS += -O3
endif

EXEC = bin/main
SRC = $(wildcard src/*.cpp)
OBJ = $(subst src,obj, $(SRC:.cpp=.o))

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm obj/*

mrproper: clean
	rm bin/*