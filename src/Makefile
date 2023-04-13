CFLAGS = -std=c++17 -Wall -Werror -Wextra 

all: test

rebuild: clean all

test: clean
	g++ $(CFLAGS) test.cpp -o test -lgtest
	./test

clean:
	$(RM)  *.o *.a *.out *.gch *.gcda *.gcno *.info
	$(RM)r report
	$(RM) test
	$(RM) main

autocheck: clean linter gcov_report leaks linter 

gcov_report:
	g++ test.cpp -o test $(CFLAGS) --coverage -lgtest
	./test
	lcov -t “test” -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

valgrind: test
	valgrind --leak-check=full --track-origins=yes ./test

leaks: test
	CK_FORK=no leaks --atExit -- ./test
