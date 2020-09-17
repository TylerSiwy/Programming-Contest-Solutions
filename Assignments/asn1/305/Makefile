CXX=g++
CXXFLAGS= -std=c++11 -g -fprofile-arcs -ftest-coverage

LINKFLAGS= -lgtest

SRC_DIR = src
# Add a list of your source code files here
SRCS = src/card.cpp src/deck.cpp src/gameData.cpp src/oldMaidController.cpp src/player.cpp

TEST_DIR = test

GMOCK = /usr/src/gmock/gmock-all.cc -lpthread

SRC_INCLUDE = include
TEST_INCLUDE = test
INCLUDE = -I ${SRC_INCLUDE} -I ${TEST_INCLUDE}

GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage
MEMCHECK_RESULTS = memcheckResults.xml

STATIC_ANALYSIS = cppcheck

STYLE_CHECK = cpplint.py

BROWSER = firefox

PROGRAM = cardGame
PROGRAM_TEST = testGame

.PHONY: all
all: clean-all $(PROGRAM) $(PROGRAM_TEST) memcheck-test docs static style coverage

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno *\#* $(COVERAGE_RESULTS) $(COVERAGE_DIR)


.PHONY: clean-all
clean-all: clean
	rm -rf $(PROGRAM) $(PROGRAM_TEST)

$(PROGRAM):
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) -I $(SRC_INCLUDE) $(SRC_DIR)/*.cpp $(LINKFLAGS)

$(PROGRAM_TEST):
	$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST) $(INCLUDE) $(TEST_DIR)/*.cpp $(SRCS) $(LINKFLAGS) $(GMOCK)
	$(PROGRAM_TEST)

memcheck-game: $(PROGRAM)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM)


memcheck-test: $(PROGRAM_TEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST)

coverage: $(PROGRAM_TEST)
	$(LCOV) --capture --gcov-tool $(GCOV) --directory . --output-file $(COVERAGE_RESULTS)
	$(LCOV) --extract $(COVERAGE_RESULTS) "*/OldMaid/src/*" -o $(COVERAGE_RESULTS)
	genhtml $(COVERAGE_RESULTS) --output-directory $(COVERAGE_DIR)
	rm -f *.gc*

static: ${SRC_DIR}
	cppcheck --verbose --enable=all --xml ${SRC_DIR} ${TEST_DIR} ${INCLUDE} --suppress=missingInclude

style: ${TEST_DIR} ${SRC_INCLUDE} ${SRC_DIR}
	${STYLE_CHECK} $(SRC_INCLUDE)/* ${TEST_DIR}/* ${SRC_DIR}/*

.PHONY: docs
docs: ${SRC_INCLUDE}
	doxygen
