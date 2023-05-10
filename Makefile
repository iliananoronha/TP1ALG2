# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall
#CXXFLAGS = -std=c++11 -O3 -Wall

# folders
SRC_FOLDER = ./src/
OBJ_FOLDER = ./obj/

# all sources, objs, and header files
MAIN = Main
TARGET = tp1.out
SRC = src/main.cpp
OBJ = obj/main.o

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(TARGET) obj/main.o

run:$(TARGET)
	./$(TARGET) -c 1tp1.txt	

clean:
	@rm -rf $(OBJ_FOLDER)* $(TARGET)
