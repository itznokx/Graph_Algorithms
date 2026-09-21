CXX = g++
CXXVERSION = -std=c++14
CXXOTIMIZATIONFLAG = -O2
LIBNAME = visualizer-lib
CPPLIBS = -I./src/lib/cpp/
RAYLIBPATH = -I./$(LIBNAME)/build/external/raylib-master/src/ -L./$(LIBNAME)/build/external/raylib-master/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CXXFLAGS = -Wall $(CXXVERSION) $(CXXOTIMIZATIONFLAG) $(CPPLIBS) $(RAYLIBPATH)
OUTPUT_FOLDER = ./output/

graphtest.out: .FORCE
	$(CXX) graphtest.cpp $(CXXFLAGS) -o $(OUTPUT_FOLDER)graphtest.out

graph: graphtest.out

raylibtest.out: .FORCE
	$(CXX) raylibtest.cpp $(CXXFLAGS) -o $(OUTPUT_FOLDER)raylibtest.out

raylib: raylibtest.out

.FORCE:


clean: .FORCE
	rm -rf *.o
	rm -rf *.out
