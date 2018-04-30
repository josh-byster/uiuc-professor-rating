# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
    OF_ROOT=$(realpath ../../../../../../Downloads/of_v0.9.8_osx_release)
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk



CXX2 = clang++
CXXFLAG2 = -std=c++11 -c -g -O0 -Wall -Wextra 
LD2 = clang++
LDFLAG2 = -std=c++11

CXX2 = clang++
CXXFLAG2 = -std=c++11 -c -g -O0 -Wall -Wextra
LD2 = clang++
LDFLAG2 = -std=c++11

testing: data_test.o test_main.o dataframe.o
	$(LD2) $^ $(LDFLAG2) -o $@


data_test.o: test/data_test.cpp src/*.h
	$(CXX2) $< $(CXXFLAG2)

test_main.o: test/test_main.cpp src/*.h
	$(CXX2) $< $(CXXFLAG2)

dataframe.o: src/DataFrame.cpp src/CSVReader.cpp src/Course.cpp src/SemesterClass.cpp
	$(CXX2) $^ $(CXXFLAG2)


