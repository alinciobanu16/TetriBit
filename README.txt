Ciobanu Alin-Matei 315CB

Sursa contine:
	- o functie de afisare a hartii: void afisare(unsigned long long harta)
	- functia int max_stanga(int piesa) care returneaza distanta dintre marginea din stanga si cel mai din stanga
	  bit al piesei (ex: pt piesa:   ....#... functia va returna valoarea 4)
	  In body-ul acestei functii am considerat doua cazuri: piesa reprezentata pe un octet (<=255),
	  respectiv pe 2 octeti. Implementarea am realizat-o cu ajutorul unei masti m care parcurge bitii piesei
	  pana cand intalneste bitul dorit.
	- functia int max_dreapta(int piesa) analog cu precedenta
	- rezolvarea propriu-zisa a problemei in body-ul int main ()

	int main () :
	- citire harta si numar piese
	- citire piesa si cele 8 mutari efectuate
	- vectorului v[] pentru a citi cele 8 mutari ale piesei este folosit pentrua nu exista probleme in cazul unei
	  coliziuni cand celelalte mutari nu mai trebuie luate in considerare ( in aceasta rezolvare a temei, 
      checker-ul ar fi citit urmatoarea mutare considerand-o piesa)
	- conditie de continuare pentru verificare daca piesa poate cobori pe linia curenta pt a-si efectua mutarea
	- 2 cazuri: mutare piesa la dreapta sau la stanga
	- 2 while-uri pentru cele 2 cazuri in care shiftez piesa cate o unitate in cadrul liniei curente
	  pana cand intalniste o coliziune (sau nu)
    - actualizare harta + conditie de oprire in cazul in care piesa nu are loc pe harta
	- variabila pas retine linia de pe harta pe care piesa respectiva s-a oprit
	  daca piesa este reprezentata pe 16 biti se ia in considerare indicele liniei unde s-a oprit 
       "a 2 a linie" a acesteia
	- linii complete: parcurgere linii folosind o masca m si contorizand bitii de 1
		 supH retine partea superioara a hartii ( de la linia/ liniile complete in sus)
		 infH retine partea inferioara a hartii 
      		 actualizare harta folosind | ( supH | infH)
	- cazuri particulare pentru piesa aflata pe prima linie sau pe a 8 a in cadrul hartii (pas == 1, pas == 8)
	- calculare scor
