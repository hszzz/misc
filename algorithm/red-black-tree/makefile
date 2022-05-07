.PHONY : all clean

all : rbtree_test
	./rbtree_test

rbtree_test : rbtree_test.cc rbtree.h
	g++ $^ -o $@

clean :
	rm -rf rbtree_test

