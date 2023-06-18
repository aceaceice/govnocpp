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


# SRC_DIR = src
# BUILD_DIR = build/debug
# CC = g++
# SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) \
# /home/jasos/imgui/backends/imgui_impl_glfw.cpp \
# /home/jasos/imgui/backends/imgui_impl_opengl3.cpp
# OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
# OBJ_NAME = play
# INCLUDE_PATHS = -Iinclude -I/usr/include/opencv4/ -I/usr/include/freetype2 -I/home/jasos/imgui/backends/
# LIBRARY_PATHS = -Llib -L/usr/lib -L/home/jasos/imgui/backends/
# COMPILER_FLAGS = -std=c++11 -Wall -O0 -g -Wno-deprecated-declarations
# LINKER_FLAGS = -lleptonica -lGL -limgui -lsfml-graphics -lsfml-window -lsfml-system -lfreetype -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -lX11 -lXi -ltesseract `pkg-config --cflags --libs gtk+-3.0 opencv4 glew` -lhdf5 -lGL

# $(BUILD_DIR)/$(OBJ_NAME): $(OBJ_FILES)
# 	$(CC) $(OBJ_FILES) $(LINKER_FLAGS) -o $@

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@

# all: $(BUILD_DIR)/$(OBJ_NAME)

# clean:
# 	rm -rf $(BUILD_DIR)/play

# .PHONY: all clean


# SRC_DIR = src
# BUILD_DIR = build/debug
# CC = g++
# SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) \
# imgui/imgui.cpp \
# imgui/imgui_draw.cpp \
# imgui/imgui_widgets.cpp \
# imgui/imgui_tables.cpp \
# imgui/backends/imgui_impl_glfw.cpp \
# imgui/backends/imgui_impl_opengl3.cpp
# OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# OBJ_NAME = play
# INCLUDE_PATHS = -Iimgui -Iimgui/backends/ -I/opt/homebrew/opt/opencv/include/opencv4/ $(foreach dir, $(wildcard /opt/homebrew/opt/*/include), -I$(dir))
# LIBRARY_PATHS = -L lib/opencv2 $(foreach dir, $(wildcard /opt/homebrew/opt/*/lib), -L$(dir))

# COMPILER_FLAGS = -std=c++11 -Wall -O0 -g -Wno-deprecated-declarations
# LINKER_FLAGS = -lleptonica -lGL -lsfml-graphics -lsfml-window -lsfml-system -lfreetype -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -lX11 -lXi -ltesseract -framework ApplicationServices -framework OpenGL  `pkg-config --cflags --libs opencv4 glew` -lhdf5 -lGL

# $(BUILD_DIR)/$(OBJ_NAME): $(OBJ_FILES)
# 	$(CC) $(OBJ_FILES) $(LINKER_FLAGS) -o $@

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@

# all: $(BUILD_DIR)/$(OBJ_NAME)

# clean:
# 	rm -rf $(BUILD_DIR)/*

# .PHONY: all clean


SRC_DIR = src
BUILD_DIR = build/debug
IMGUI_BUILD_DIR = $(BUILD_DIR)/imgui
CC = g++
INCLUDE_DIR = /usr/
# Your additional compiler
OBJCXX = g++

# Your additional source and object files
MY_MM_SRC_FILES = $(wildcard $(SRC_DIR)/*.mm)
MY_MM_OBJ_FILES = $(patsubst $(SRC_DIR)/%.mm,$(BUILD_DIR)/%.o,$(MY_MM_SRC_FILES))

# Compiler and Linker flags for Objective-C++
OBJCXX_COMPILER_FLAGS = -std=c++11 -Wall -O0 -g -Wno-deprecated-declarations -x objective-c++ -fobjc-arc
OBJCXX_LINKER_FLAGS = -framework Cocoa -framework Foundation -lobjc


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
# INCLUDE_PATHS = -Iimgui -Iimgui/backends/ -I/opt/homebrew/opt/opencv/include/opencv4/ $(foreach dir, $(wildcard /opt/homebrew/opt/*/include), -I$(dir))
# LIBRARY_PATHS =  $(foreach dir, $(wildcard /opt/homebrew/opt/*/lib), -L$(dir))
INCLUDE_PATHS = -Iinclude -I/usr/include/opencv4/ -Iimgui -Iimgui/backends/
LIBRARY_PATHS = -Llib -L/usr/lib
COMPILER_FLAGS = -std=c++14 -Wall -O0 -g -Wno-deprecated-declarations
# LINKER_FLAGS = -llept -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -ltesseract -framework ApplicationServices -framework OpenGL  `pkg-config --cflags --libs opencv4 glew` -lhdf5 
LINKER_FLAGS = -lleptonica -lcpprest -lssl -lcrypto -lcurl -lXext -lpng -lglfw -lX11 -lXi -ltesseract `pkg-config --cflags --libs opencv4 glew` -lhdf5

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
