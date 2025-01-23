#
# MAKEFILE ES01
#

CC=gcc
ARGS=-Wall -o
SOURCE=es01A/es01.c
DEST=es01A/es01
INFILE=es01A/inFile.txt
EVENFILE=es01A/pariFile.txt
ODDFILE=es01A/dispariFile.txt

FILE1=es01B/lab01.txt
FILE2=es01B/lab02.txt
FILE3=es01B/lab03.txt

USER=root

A:
	$(CC) $(ARGS) $(DEST) $(SOURCE)
	./$(DEST) < $(INFILE) 1> $(EVENFILE) 2> $(ODDFILE)
	more $(INFILE) $(EVENFILE) $(ODDFILE)

B1:
	ls -1 | wc --l

B2:
	cat $(FILE1) $(FILE2) $(FILE3) | wc --bytes

B3:
	ps -u $(USER) | wc --lines
