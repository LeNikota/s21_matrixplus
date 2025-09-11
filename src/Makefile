CC = g++
FLAGS = -Wall -Wextra -Werror -std=c++20 #-fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable
SRC = $(wildcard *.c)
OBJ = $(SRC:.cpp=.o)
ifeq ($(MAKECMDGOALS), gcov_report)
    TEST_FLAGS = -fprofile-arcs -ftest-coverage
else
    TEST_FLAGS =
endif

all: format s21_matrix_opp.a

main: $(OBJ)
	$(CC) $(FLAGS) $(SRC) -o a.out

s21_matrix_opp.a: $(OBJ)
	@ar rcs $@ $^

%.o: %.c
	@gcc $(FLAGS) $(TEST_FLAGS) -c $^ -o $@

clean:
	@rm -rf $(OBJ) *.gcno *.gcda coverage* s21_matrix_opp.a a.out test 

format:
	@find $(git rev-parse --show-toplevel) \( -name "*.c" -o -name "*.h" \) | xargs clang-format -i

static_check:
	@find $(git rev-parse --show-toplevel) \( -name "*.c" -o -name "*.h" \) | xargs cppcheck --enable=all --suppress=missingIncludeSystem

test: all
	@gcc $(FLAGS) -o test ./tests/*.c -L. -l:s21_matrix_opp.a -lcheck -lm -lsubunit -lgcov
	@./test

leak: all
	@gcc $(FLAGS) -o test ./tests/*.c -L. -l:s21_matrix_opp.a -lcheck -lm -lsubunit -lgcov
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./test

gcov_report: clean test
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory coverage_html
	@open ./coverage_html/index.html