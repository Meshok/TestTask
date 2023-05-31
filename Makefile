PROJECT_NAME=DailyPlanner
CXXFLAGS=-Wall -Wextra -pedantic

.PHONY: all build clean style

all: style build

build:
	$(CXX) $(CXXFLAGS) *.cc -o $(PROJECT_NAME)

clean:
	rm $(PROJECT_NAME)

style:
	clang-format --style=Google -i *.cc *.h
