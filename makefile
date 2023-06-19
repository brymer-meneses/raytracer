
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra

SRC_DIR := src
OBJ_DIR := build/obj
BIN_DIR := build
INC_DIR := include

EXEC := raytracer

SRCS := $(wildcard $(SRC_DIR)/*.cc)
OBJS := $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean
.SILENT: run

all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN_DIR)/$(EXEC)
	@$(BIN_DIR)/$(EXEC)

clean:
	@$(RM) -r $(BIN_DIR) $(OBJ_DIR)
