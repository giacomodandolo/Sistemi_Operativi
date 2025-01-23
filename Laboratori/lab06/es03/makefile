p1:
	find / -name "*.exe" -size +1k -executable

p2:
	find / -name "*.c" -size +100c

p3:
	find / -regextype posix-extended -regex "(.*A.*a.*)|(.*a.*A.*)" -exec tail -n 3 '{}' \; 

p4a:
	find / -mindepth 3 -maxdepth 5 -type f -user giacomo -size +250c -name "????" -exec wc -c '{}' \;

p4b:
	find / -mindepth 3 -maxdepth 5 -type f -user giacomo -size +250c -name "????" -exec wc -l '{}' \;

p5:
	find / -regex ".*\/A.*zzz.*\...." -exec tar -zcvf '{}'.tar.gz '{}' \;

p6:
	find / -type d -name "bin" -exec ls -la '{}' \;

p7:
	find / -name "*.c" ! -user giacomo

p8:
	find / -maxdepth 1 -user giacomo -exec chmod go-xrw '{}' \;
