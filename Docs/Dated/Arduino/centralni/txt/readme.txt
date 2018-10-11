napravio:
real time vrijeme
citam temp
spajam se na wifi
primati od espa2 temp
kod za senzore
upravljanje u pomoc interneta
spajanje za senzore

trebam:
-programirati komunikaciju s nextionom
  to sadrzi: -postavljena
			 -trenutna
		     -vrijeme
		     -upali
-popraviti spajanje clienta na AP
		   

		   
Svi ESPovi:
0. Centalni (Dnevni Boravak)
1. Hodnik
2. Plava soba
3. Crvena soba
4. Bijela soba
5. Manji WC
6. Veći WC
7. Veranda
8. Van




nacin rada:

postavis temp u svakoj sobi => treba array postavljena od 9 clanova u kojima se nalazi postavljena temp, def. 20 FLOAT

dobivas temp od svake sobe => spremi u array trenutna isto od 9 clanova u kojima se nalazi trenutna temp def. 404 FLOAT

imas i array grijanje od 9 clanova boolean. True znaci da korisnik hoce da zagrijes sobu. def. false osim 0 tj. centralni

gledamo: ako je temp[i]+1 ugasi, ako je temp[i]-2 upali. Ako iti jedna govori upali ostaje upaljeno, ako svi govore ugasi ugasimo