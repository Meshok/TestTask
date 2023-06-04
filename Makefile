PROJECT_NAME=DailyPlanner
CXXSTANDARD=-std=c++17
CXXFLAGS=-Wall -Wextra -Wpedantic
SRC_DIR=src
BUILD_DIR=build
SOURCES=$(wildcard $(SRC_DIR)/*.cc)
HEADERS=$(wildcard $(SRC_DIR)/*.h)

.PHONY: all build style clean create_dir

$(PROJECT_NAME): create_dir $(SOURCES) $(HEADERS)
	$(CXX) $(CXXSTANDARD) $(SOURCES) -o $(BUILD_DIR)/$(PROJECT_NAME)

all: style build

build: create_dir $(SOURCES) $(HEADERS)
	$(CXX) $(CXXSTANDARD) $(CXXFLAGS) $(SOURCES) -o $(BUILD_DIR)/$(PROJECT_NAME)

style:
	clang-format --style=Google -i $(SOURCES) $(HEADERS)

clean:
	rm -rf $(BUILD_DIR)

create_dir:
	mkdir -p $(BUILD_DIR)
