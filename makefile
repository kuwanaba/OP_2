CC := g++

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
IDIR    := include


EXE := $(BIN_DIR)/main
DEPS:= $(wildcard $(IDIR)/*.hpp)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


CPPFLAGS := -Iinclude -MMD -MP
CXXFLAGS := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm


.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -I$(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
