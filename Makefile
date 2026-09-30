CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Isource/headers

ifeq ($(OS),Windows_NT)
    TARGET := CCMS.exe
else
    TARGET := CCMS
endif

SRCS := main.cpp $(wildcard source/src/*.cpp)

.PHONY: all clean rebuild run

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean all