UNAME := $(shell uname)

ifeq ($(UNAME), Linux) 
# Linux-specific settings
INCLUDE_PATHS = -Iinclude -I/usr/include/opencv4/ -Iimgui -Iimgui/backends/
LIBRARY_PATHS = -Llib -L/usr/lib
COMPILER_FLAGS = -std=c++14 -Wall -O0 -g -Wno-deprecated-declarations
LINKER_FLAGS = -lleptonica -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -lX11 -lXi -ltesseract `pkg-config --cflags --libs opencv4 glew` -lhdf5

endif
ifeq ($(UNAME), Darwin) 
# MacOS-specific settings

INCLUDE_PATHS = -Iimgui -Iimgui/backends/ -I/opt/homebrew/opt/opencv/include/opencv4/ $(foreach dir, $(wildcard /opt/homebrew/opt/*/include), -I$(dir))
LIBRARY_PATHS =  $(foreach dir, $(wildcard /opt/homebrew/opt/*/lib), -L$(dir))
COMPILER_FLAGS = -std=c++14 -Wall -O0 -g -Wno-deprecated-declarations
LINKER_FLAGS = -llept -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -ltesseract -framework ApplicationServices -framework OpenGL  `pkg-config --cflags --libs opencv4 glew` -lhdf5 

endif


SRC_DIR = src
BUILD_DIR = build/debug
IMGUI_BUILD_DIR = $(BUILD_DIR)/imgui
CC = g++
INCLUDE_DIR = /usr/
# Your additional compiler

# Your source files
MY_SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
MY_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MY_SRC_FILES))

# ImGui source files
IMGUI_SRC_FILES = imgui.cpp \
imgui_draw.cpp \
imgui_widgets.cpp \
imgui_tables.cpp \
backends/imgui_impl_glfw.cpp \
backends/imgui_impl_opengl3.cpp
IMGUI_OBJ_FILES = $(patsubst %.cpp,$(IMGUI_BUILD_DIR)/%.o,$(IMGUI_SRC_FILES))

OBJ_NAME = play


# $(BUILD_DIR)/$(OBJ_NAME): $(MY_OBJ_FILES) $(IMGUI_OBJ_FILES)
# 	$(CC) $(MY_OBJ_FILES) $(IMGUI_OBJ_FILES) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@


$(BUILD_DIR)/$(OBJ_NAME): $(MY_OBJ_FILES) $(IMGUI_OBJ_FILES)
	$(CC) $(MY_OBJ_FILES) $(IMGUI_OBJ_FILES) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@



$(IMGUI_BUILD_DIR)/%.o: imgui/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@

$(IMGUI_BUILD_DIR)/%.o: imgui/backends/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@


all: $(BUILD_DIR)/$(OBJ_NAME)

# g++ -framework Foundation -framework Cocoa -o key ./keyHandler.mm

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
