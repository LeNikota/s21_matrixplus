CXX = g++
FLAGS = -Wall -Wextra -Werror -std=c++20 #-fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
ifeq ($(MAKECMDGOALS), gcov_report)
    TEST_FLAGS = -fprofile-arcs -ftest-coverage
else
    TEST_FLAGS =
endif

all: format s21_matrix_opp.a

s21_matrix_opp.a: $(OBJ)
	@ar rcs $@ $^

%.o: %.cpp
	@$(CXX) $(FLAGS) $(TEST_FLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ) *.gcno *.gcda coverage* s21_matrix_opp.a test_runner 

format:
	@find $(git rev-parse --show-toplevel) \( -name "*.c" -o -name "*.cpp" -o -name "*.h" \) | xargs clang-format -i

static_check:
	@find $(git rev-parse --show-toplevel) \( -name "*.c" -o -name "*.cpp" -o -name "*.h" \) | xargs cppcheck --enable=all --suppress=missingIncludeSystem

test: all
	@$(CXX) $(FLAGS) -o test_runner ./tests/*.cpp -L. -l:s21_matrix_opp.a  -lgtest -lgtest_main -pthread -lgcov
	@./test_runner

leak: all
	@$(CXX) $(FLAGS) -o test ./tests/*.c -L. -l:s21_matrix_opp.a  -lgtest -lgtest_main -pthread
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./test

gcov_report: clean test
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory coverage_html
	@open ./coverage_html/index.html