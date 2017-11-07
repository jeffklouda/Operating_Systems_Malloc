CC=       	gcc
CFLAGS= 	-g -gdwarf-2 -std=gnu99 -Wall
LDFLAGS=
LIBRARIES=      lib/libmalloc-ff.so \
		lib/libmalloc-nf.so \
		lib/libmalloc-bf.so \
		lib/libmalloc-wf.so
TEST_EXECUTABLES = bin/test1 \
                   bin/test2 \
                   bin/test3 \
				   bin/unit_test

all:    $(LIBRARIES) $(TEST_EXECUTABLES)

lib/libmalloc-ff.so:     src/malloc.c
	$(CC) -shared -fPIC $(CFLAGS) -DFIT=0 -o $@ $< $(LDFLAGS)

# TODO: rules for remaining libraries

lib/libmalloc-nf.so:     src/malloc.c
	$(CC) -shared -fPIC $(CFLAGS) -DFIT=1 -o $@ $< $(LDFLAGS)
lib/libmalloc-bf.so:     src/malloc.c
	$(CC) -shared -fPIC $(CFLAGS) -DFIT=2 -o $@ $< $(LDFLAGS)
lib/libmalloc-wf.so:     src/malloc.c
	$(CC) -shared -fPIC $(CFLAGS) -DFIT=3 -o $@ $< $(LDFLAGS)

bin/test1:		src/test1.c
	$(CC) $(CFLAGS) -o $@ $< 

bin/test2:		src/test2.c
	$(CC) $(CFLAGS) -o $@ $<

bin/test3:		src/test3.c
	$(CC) $(CFLAGS) -o $@ $<

bin/unit_test:	src/unit_test.c
	$(CC) $(CFLAGS) -Llib -lmalloc-ff -o $@ $<

clean:
	rm -f $(LIBRARIES) $(TEST_EXECUTABLES)

.PHONY: all clean
