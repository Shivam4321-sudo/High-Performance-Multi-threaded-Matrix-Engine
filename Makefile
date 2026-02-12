CXX = g++
CXXFLAGS = -std=c++17 -O3 -pthread

all:
	$(CXX) $(CXXFLAGS) src/main.cpp src/Matrix.cpp -Iinclude -o MatrixEngine

run:
	./MatrixEngine

clean:
	rm -f MatrixEngine
