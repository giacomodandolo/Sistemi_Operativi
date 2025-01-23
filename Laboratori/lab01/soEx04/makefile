# 
# Makefile
#

compile01:
	gcc -Wall es01.c -o es01.exe

compile04_b:
	gcc -Wall es04_b.c -o es04_b.exe

test01:
	./es01.exe esempio1.txt esempio2.txt
	diff esempio1.txt esempio2.txt.1
	rm esempio2.txt.1

test04_b:
	./es04_b.exe esempio1.txt esempio2.txt
	diff esempio1.txt esempio2.txt
	rm esempio2.txt

clean:
	rm -f *.o 
