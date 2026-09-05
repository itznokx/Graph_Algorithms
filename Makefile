CXX = g++
CXXVERSION = -std=c++14
CXXOTIMIZATIONFLAG = -O2
LIBNAME = visualizer-lib
RAYLIBPATH = -I./$(LIBNAME)/build/external/raylib-master/src/ -L./$(LIBNAME)/build/external/raylib-master/src/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CXXFLAGS = -Wall $(CXXVERSION) $(CXXOTIMIZATIONFLAG) $(RAYLIBPATH)


graphtest.out: .FORCE
	$(CXX) graphtest.cpp $(CXXFLAGS) -o graphtest.out

graph: graphtest.out

.FORCE:


clean:
	rm -rf *.o
	rm -rf libcpp/*.gch
