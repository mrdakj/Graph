PROGRAM = pluton
CXX     = g++
CXXFLAGS = -std=c++17 -I include
LDLIBS  = -lstdc++fs 
WFLAGS = -Wall -Wextra
SRC_DIR = src
OBJ_DIR = $(SRC_DIR)/obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(PROGRAM): $(OBJ_FILES)
	$(CXX) -o $(PROGRAM) $(OBJ_FILES) $(LDLIBS) $(WFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDLIBS) $(WFLAGS)
	
.PHONY: clean

clean:
	-rm $(OBJ_DIR)/*.o $(PROGRAM)
