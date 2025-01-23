FILE=lab06e04in.txt

# ordine decrescente per matricola
p1:
	sort -r -k 1,1 -n $(FILE)

# ordine crescente su cognome
p2:
	sort -k 2,2 $(FILE)

# studenti frequentato 2011/2012
p3:
	grep "2011/2012" $(FILE)

# studenti INF1T3 ordinati matricola
p4:
	grep "INF1T3" $(FILE) | sort -k 1,1 -n

# matricole finiscono per 2 o 4 ordinati cognome
p5:
	grep -e "^[0-9]*2\>" -e "^[0-9]*4\>" $(FILE) | sort -k 2,2

# studenti TLC1T3 da frequentare ordinati inversamente matricola
p6:
	grep "TLC1T3" $(FILE) | grep "Da frequentare" | sort -r -k 1,1 -n

# studenti contengono A..A
p7:
	grep "A..A" $(FILE)

# studenti contengono A..A no inizio/fine
p8:
	grep "A..A" $(FILE) | grep -v "\<A" | grep -v "A\>"

# ottieni matricole, 0 -> cancellato, 8 -> 1, elimina duplicati
p9:
	cut -d ' ' -f 1 $(FILE) | tr -d 0 | tr 8 1 | sort -n | uniq

# ottieni matricole, 0 -> cancellato, 8 -> 1, mostra duplicati
p10:
	cut -d ' ' -f 1 $(FILE) | tr -d 0 | tr 8 1 | sort -n | uniq -d
