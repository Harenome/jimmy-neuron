CC = g++

PATH_SRC = src
PATH_OBJ = obj
PATH_BIN = bin
PATH_LIB = lib
PATH_TESTS = tests
PATH_INCLUDE = include

FLAGS_DBG = -g -Wall
FLAGS_CC = -std=c++98 -pedantic $(FLAGS_DBG)
FLAGS_INCLUDE = -I$(PATH_INCLUDE) -I$(PATH_TESTS)
FLAGS_LIB = -L$(PATH_LIB)

MISC_FILES = makefile Doxyfile AUTHORS COPYING LICENSE README README.md

vpath %.cpp $(PATH_SRC) $(PATH_TESTS)
vpath %.hpp $(PATH_INCLUDE) $(PATH_TESTS)
vpath %.o $(PATH_OBJ)
vpath %.a $(PATH_LIB)

all: main

%.o: %.cpp | obj_dir
		$(CC) $(FLAGS_CC) $(FLAGS_INCLUDE) -o $(PATH_OBJ)/$@ -c $<

main: main.o libjimmyneuron.a | bin_dir
		$(CC) $(FLAGS_LIB) -o $(PATH_BIN)/$@ $(PATH_OBJ)/main.o -ljimmyneuron

neuron.o: neuron.cpp neuron.hpp
neuron_network.o: neuron_network.cpp neuron_network.hpp neuron.hpp
main.o: main.cpp neuron.hpp

libjimmyneuron.a: neuron.o neuron_network.o | lib_dir
		ar -crv $(PATH_LIB)/libjimmyneuron.a $(PATH_OBJ)/neuron.o $(PATH_OBJ)/neuron_network.o
		ranlib $(PATH_LIB)/libjimmyneuron.a

tests: runner.o libjimmyneuron.a | bin_dir
		$(CC) $(FLAGS_LIB) -o $(PATH_BIN)/runner $(PATH_OBJ)/runner.o -ljimmyneuron
		@bin/runner

runner.cpp: test_neuron.hpp
		cd $(PATH_TESTS) && cxxtestgen --error-printer -o runner.cpp test_neuron.hpp

runner.o: runner.cpp | obj_dir
		$(CC) $(FLAGS_CC) $(FLAGS_INCLUDE) -o $(PATH_OBJ)/runner.o -c $(PATH_TESTS)/runner.cpp

obj_dir:
	 	@mkdir -p $(PATH_OBJ)

lib_dir:
		@mkdir -p $(PATH_LIB)

bin_dir:
		@mkdir -p $(PATH_BIN)

doc:
		@doxygen

clean: clean_basic clean_tests
		@echo "Clean."

cleanbasic: clean_basic
clean_basic:
		@rm -rf $(PATH_OBJ) $(PATH_LIB) $(PATH_BIN)

cleandoc: clean_doc
clean_doc:
		@rm -rf $(PATH_DOC)

cleantests: clean_tests
clean_tests:
		@rm -rf $(PATH_TESTS)/*.cpp
		@rm -rf $(PATH_BIN)/runner

cleanarchives: clean_archives
clean_archives:
		@rm -rf $(shell basename `pwd`)_*.tar.gz

cleanall: clean_all
clean_all: clean clean_doc clean_tests clean_archives
		@echo "Super clean."

archive:
		@tar -cvzf $(shell basename `pwd`)_$(shell date "+%Y-%m-%d-%H-%M-%S").tar.gz $(PATH_SRC) $(PATH_INCLUDE) $(PATH_TESTS) $(MISC_FILES)
