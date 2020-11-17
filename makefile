SRC_DIR := src
OBJ_DIR := build
CMP = g++ 

# Get all .cpp files in ./src dir
CPP_FILES := $(wildcard $(SRC_DIR)/*/*.cpp $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(CPP_FILES:.cpp=.o))

CPPFLAGS := -O -std=c++20 -lstdc++ `pkg-config gtkmm-3.0 --cflags --libs`

GameSettings: $(OBJ_FILES)
		$(CMP) $(CPPFLAGS) -o $(OBJ_DIR)/$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		mkdir -p $(dir $@)
		$(CMP) $(CPPFLAGS) -c $< -o $@

clean:
		rm -r -f $(OBJ_DIR)