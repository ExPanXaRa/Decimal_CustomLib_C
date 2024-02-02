LIBS_LINUX=

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)

	Linux_type := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')

	ifeq ($(Linux_type), Arch)
		LIBS_LINUX = -lm
	endif

	ifeq ($(Linux_type), Ubuntu)
		LIBS_LINUX = -lsubunit -lm -pthread -lrt
	endif

	ifeq ($(Linux_type), Debian)
		LIBS_LINUX = -lsubunit -lm -pthread -lrt
	endif

endif

CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g

OBJS=s21*.o
SRCS_OBJ=s21*.c
TESTS_OBJ=*.c

TARGET=s21_decimal
TEST_TARG=check_s21_decimal

SRCS_DIR=functions
TESTS_DIR=tests

SRCS_H =s21*.h

LIBS = -lcheck $(LIBS_LINUX)


ALL_SRC_OBJ = $(shell find $(SRCS_DIR) -type f -name "$(SRCS_OBJ)")
ALL_TESTS_OBJ = $(shell find $(TESTS_DIR) -type f -name "$(TESTS_OBJ)")

ALL_SRC_H = $(shell find $(SRCS_DIR) -type f -name "$(SRCS_H)")
ALL_TESTS_H = $(shell find $(TESTS_DIR) -type f -name "*.h")


all: s21_decimal.a test gcov_report

s21_decimal.a:
	$(CC) $(CFLAGS) $(ALL_SRC_OBJ) -c
	ar rsc s21_decimal.a $(OBJS)
	ranlib s21_decimal.a
	rm -f $(OBJS)

test: s21_decimal.a
	$(CC) $(CFLAGS) $(ALL_TESTS_OBJ) $(LIBS) -L. -l:s21_decimal.a -o $(TEST_TARG) 
	./$(TEST_TARG)

test_val: s21_decimal.a test
	valgrind --tool=memcheck --leak-check=yes -s ./$(TEST_TARG)

gcov_report: 
	$(CC) --coverage $(CFLAGS) $(ALL_SRC_OBJ) $(ALL_TESTS_OBJ) $(LIBS) -o $(TEST_TARG)
	./$(TEST_TARG)
	lcov -t "$(TEST_TARG)" -o $(TEST_TARG).info -c -d .
	genhtml -o report $(TEST_TARG).info
	rm -f *.gcda *.gcno *.info $(TEST_TARG)

check_linters:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n $(ALL_SRC_OBJ) $(ALL_SRC_H) $(ALL_TESTS_OBJ) $(ALL_TESTS_H)
	rm -rf .clang-format

fix_linters:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i $(ALL_SRC_OBJ) $(ALL_SRC_H) $(ALL_TESTS_OBJ) $(ALL_TESTS_H)
	rm -rf .clang-format

clean_lib:
	rm -f *.[oa]

clean_cov:
	rm -f *.gcno *.gcda *.info *.gcov $(TEST_TARG)

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem $(ALL_SRC_OBJ)

clean: clean_lib clean_cov
	rm -f $(TEST_TARG)
	rm -rf report *.dSYM

rebuild: clean all
