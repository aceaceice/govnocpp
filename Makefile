# SRC_DIR = src
# BUILD_DIR = build/debug
# CC = g++
# SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
# OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
# OBJ_NAME = play
# INCLUDE_PATHS = -Iinclude -I/usr/include/opencv4/ -I/usr/include/freetype2  -I/home/jasos/cshit/vcpkg/installed/x64-linux/include -I/home/jasos/cshit//vcpkg/buildtrees/imgui/src/v1.89.4-8c703ccfb7.clean/backends
# LIBRARY_PATHS = -Llib -L/usr/lib -L/home/jasos/cshit/vcpkg/installed/x64-linux/lib
# COMPILER_FLAGS = -std=c++11 -Wall -O0 -g -Wno-deprecated-declarations
# LINKER_FLAGS = -lleptonica -lGL -limgui -lsfml-graphics -lsfml-window -lsfml-system -lfreetype -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -lX11 -lXi  -ltesseract `pkg-config --cflags --libs gtk+-3.0 opencv4 glew` -lhdf5 -lGL

# # $(BUILD_DIR)/$(OBJ_NAME): $(OBJ_FILES)
# # 	$(CC) $(OBJ_FILES) $(LINKER_FLAGS) -o $@

# # $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# # 	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) $(LINKER_FLAGS) -c $< -o $@
# all:
# 	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)

# clean:
# 	rm -rf $(BUILD_DIR)/play
	
# .PHONY: clean


SRC_DIR = src
BUILD_DIR = build/debug
CC = g++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) \
/home/jasos/imgui/backends/imgui_impl_glfw.cpp \
/home/jasos/imgui/backends/imgui_impl_opengl3.cpp
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
OBJ_NAME = play
INCLUDE_PATHS = -Iinclude -I/usr/include/opencv4/ -I/usr/include/freetype2 -I/home/jasos/imgui/backends/
LIBRARY_PATHS = -Llib -L/usr/lib -L/home/jasos/imgui/backends/
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g -Wno-deprecated-declarations
LINKER_FLAGS = -lleptonica -lGL -limgui -lsfml-graphics -lsfml-window -lsfml-system -lfreetype -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -lX11 -lXi -ltesseract `pkg-config --cflags --libs gtk+-3.0 opencv4 glew` -lhdf5 -lGL

$(BUILD_DIR)/$(OBJ_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LINKER_FLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@

all: $(BUILD_DIR)/$(OBJ_NAME)

clean:
	rm -rf $(BUILD_DIR)/play

.PHONY: all clean
