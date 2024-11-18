CC = gcc
FLAGS = 
SRC_DIR = src
BUILD_DIR = build

$(BUILD_DIR)/itstime: dir 
	- $(CC) -o $(BUILD_DIR)/itstime $(SRC_DIR)/main.c $(FLAGS)

dir:
	mkdir -p build

clean: 
	- rm -r build
