CC=gcc
STDFLAGS=-Wall -Werror -Wextra -std=c11 #-fsanitize=address
TST_CFLAGS:= -g $(STDFLAGS)
GCOV_FLAGS?=-fprofile-arcs -ftest-coverage
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose 

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o, ${SRC})
# HEADER=$(wildcard s21_*.h)

PREF_TEST_SRC=./unit_tests/
TEST_SRC=$(wildcard $(PREF_TEST_SRC)/s21_*.c)
# TEST_OBJ = $(patsubst %.c,%.o, ${TEST_SRC})

OS := $(shell uname -s)
USERNAME=$(shell whoami)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: install dvi open_exe

install:
	make clean
	mkdir build
	cd ui && qmake && make && make clean && rm Makefile && cd ../ && mv ui/SmartCalc.app build

uninstall:
	rm -rf build*

open_exe:
	$(OPEN_CMD) build/SmartCalc.app

dvi:
	$(OPEN_CMD) readme.html

dist:
	rm -rf SmartCalc_v1.0/
	mkdir SmartCalc_v1.0/
	mkdir SmartCalc_v1.0/src
	mv ./build/SmartCalc.app SmartCalc_v1.0/src/
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	rm -rf SmartCalc_v1.0/

tests:
ifeq ($(OS), Darwin)
	${CC} $(STDFLAGS) ${TEST_SRC} ${SRC} -o unit_test $(LIBS) -g
else
	${CC} $(STDFLAGS) ${TEST_SRC} ${SRC} -o unit_test $(LIBS) $(LINUX_FLAGS)
endif
	./unit_test

gcov_report: clean_test
ifeq ($(OS), Darwin)
	$(CC) $(STDFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS)
else
	$(CC) $(STDFLAGS) $(GCOV_FLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
endif
	./test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	$(OPEN_CMD) ./report/index.html

leaks:
	$(CC) $(TST_CFLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS)
	leaks -atExit -- ./test

valgrind:
	$(CC) $(TST_CFLAGS) ${TEST_SRC} ${SRC} -o test $(LIBS) $(LINUX_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.c *.h
	rm .clang-format

clean_obj:
	rm -rf *.o

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report
	rm -rf test.dSYM

clean: clean_test clean_obj
	rm -rf unit_test
	rm -rf RESULT_VALGRIND.txt
	rm -rf SmartCalc_v1.0
	rm -rf SmartCalc_v1.0.tgz

.PHONY: all clean check lcov
