CXX = \g++
CXXFLAGS = -std=c++17 -O2

a:
	$(CXX) $(CXXFLAGS) src/main.cc src/cvs_reader.cc 
omp:
	$(CXX) $(CXXFLAGS) -fopenmp src/omp.cc src/cvs_reader.cc -o omp
thr:
	$(CXX) $(CXXFLAGS) src/thread.cc src/cvs_reader.cc -o thr 
