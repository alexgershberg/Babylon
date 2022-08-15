CXX            := clang++
CXXFLAGS       := -std=c++20 -Wall -MMD
BIN_NAME       := exe
SOURCE_DIR     := src
BIN_DIR        := bin
ETC_DIR        := $(BIN_DIR)/etc
SOURCES        := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS        := $(patsubst $(SOURCE_DIR)/%.cpp, $(ETC_DIR)/%.o, $(SOURCES))
DEPENDS        := $(patsubst $(SOURCE_DIR)/%.cpp, $(ETC_DIR)/%.d, $(SOURCES))

all: directories $(BIN_NAME)
	@ # echo "Making symlink $(BIN_NAME) -> $(BIN_DIR)/$(BIN_NAME)"
	@rm -f $(BIN_NAME)
	@ln -s $(BIN_DIR)/$(BIN_NAME) $(BIN_NAME)

directories:
	@mkdir -p $(ETC_DIR)

# Link
$(BIN_NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$@ $^

# Compile
$(ETC_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<  

clean: 
	@rm -r $(BIN_DIR)
	@rm $(BIN_NAME)

-include $(DEPENDS)

.PHONY: all 
