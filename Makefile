CXX = g++
CXXFLAGS = -O2

a:
	$(CXX) $(CXXFLAGS) src/main.cc src/cvs_reader.cc 
