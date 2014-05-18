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

all: jimmy-neuron

%.o: %.cpp | obj_dir
		$(CC) $(FLAGS_CC) $(FLAGS_INCLUDE) -o $(PATH_OBJ)/$@ -c $<

jimmy-neuron: main.o libjimmyneuron.a | bin_dir
		$(CC) $(FLAGS_LIB) -o $(PATH_BIN)/$@ $(PATH_OBJ)/main.o -ljimmyneuron

utilities.o: utilities.cpp utilities.hpp
neuron.o: neuron.cpp neuron.hpp utilities.hpp
neuron_network.o: neuron_network.cpp neuron_network.hpp neuron.hpp
truth_table.o: truth_table.cpp truth_table.hpp
neuron_network_fitness.o: neuron_network_fitness.cpp neuron_network_fitness.hpp neuron.hpp neuron_network.hpp utilities.hpp truth_table.hpp
random_factory.o: random_factory.cpp random_factory.hpp utilities.hpp neuron.hpp neuron_network.hpp
evolution.o: evolution.cpp evolution.hpp utilities.hpp neuron.hpp neuron_network.hpp truth_table.hpp neuron_network_fitness.hpp random_factory.hpp
colony.o: colony.cpp colony.hpp utilities.hpp neuron.hpp neuron_network.hpp neuron_network_fitness.hpp evolution.hpp random_factory.hpp
parse_cli.o: parse_cli.cpp parse_cli.hpp
plot.o: plot.cpp plot.hpp
main.o: main.cpp neuron.hpp

libjimmyneuron.a: utilities.o neuron.o neuron_network.o truth_table.o neuron_network_fitness.o random_factory.o evolution.o colony.o parse_cli.o plot.o | lib_dir
		ar -crv $(PATH_LIB)/libjimmyneuron.a $(PATH_OBJ)/utilities.o $(PATH_OBJ)/neuron.o $(PATH_OBJ)/neuron_network.o $(PATH_OBJ)/truth_table.o $(PATH_OBJ)/neuron_network_fitness.o $(PATH_OBJ)/random_factory.o $(PATH_OBJ)/evolution.o $(PATH_OBJ)/colony.o $(PATH_OBJ)/parse_cli.o $(PATH_OBJ)/plot.o
		ranlib $(PATH_LIB)/libjimmyneuron.a

tests: runner.o libjimmyneuron.a | bin_dir
		$(CC) $(FLAGS_LIB) -o $(PATH_BIN)/runner $(PATH_OBJ)/runner.o -ljimmyneuron
		@bin/runner

runner.cpp: test_neuron.hpp test_neuron_network.hpp test_truth_table.hpp
		cd $(PATH_TESTS) && cxxtestgen --error-printer -o runner.cpp test_neuron.hpp test_neuron_network.hpp test_truth_table.hpp

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
