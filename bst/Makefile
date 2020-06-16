CXX = g++
TARGET = main
CXXFLAGS = -Wall -O0 -g -std=c++0x

$(TARGET): main.o
	$(CXX) $^ -o $@

main.o: main.cpp bst.h bstexceptions.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.exe $(TARGET)
