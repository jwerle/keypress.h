
all: clean test

clean:
	rm -f keypress-test

test:
	$(CC) test.c -DUSE_POLL=1 -std=c99 -o keypress-test
	./keypress-test

.PHONY: all clean test
