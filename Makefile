SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude -I/usr/include/opencv4/
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g -Wno-deprecated-declarations
LINKER_FLAGS = -lleptonica  -lXext -lpng -lglfw -lX11 -ltesseract `pkg-config --cflags --libs opencv` -lhdf5 -lGL

$(BUILD_DIR)/$(OBJ_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LINKER_FLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: clean
