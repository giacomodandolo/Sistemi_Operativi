CC=gcc
ARGS=-Wall -o
TARGET=dirRecursive
SOURCE=dirRecursive.c

target:
	$(CC) $(ARGS) $(TARGET) $(SOURCE) 

install:
	mkdir ../bin 
	mv $(TARGET) ../bin

clean:
	rm $(TARGET) 

distclean: clean
	rm -r ../bin
