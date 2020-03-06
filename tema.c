// Ciobanu Alin-Matei 315CB
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ull unsigned long long
#define BYTE 8
void afisare( unsigned long long harta) {
    int index = 63;
	int octet = index;

	while ( index >= 0 ) {
		if (harta & (((unsigned long long) 1) << index)) {
			printf("#");
		} else {
		    printf(".");
		}
        index--;
        if (octet - index == 8) {
            printf("\n");
            octet = index;
		}
    }
	printf("\n");
}
int max_stanga(int piesa) {
    int i, poz1, poz2, m;

    if (piesa > 255) { // piesa e reprezentata pe 2 octeti
        for(i = 15; i >= 8; i--) {
            m = 1 << i;
            if(piesa & m) {
                poz1 = 15 - i;
                break;
            }
        }
        for (i = 7; i >= 0; i--) {
            m = 1 << i;
            if (piesa & m) {
                poz2 = 7 - i;
                break;
            }
        }
        if (poz1 <= poz2) return poz1;
            else return poz2;

    } else { // piesa e reprezentata pe un singur octet
        for (i = 7; i >= 0; i--) {
            m = 1<< i;
            if (piesa & m)
                return (7 - i);

        }

    }
    return 0;
}

int max_dreapta(int piesa) {
    int m,i,poz1,poz2;

    if(piesa > 255) {
        for (i = 8 ;i <= 15; i++) {
            m = 1 << i;
            if (piesa & m) {
                poz1 = i - 8;
                break;
            }
        }
        for(i = 0; i <= 7; i++) {
            m = 1 << i;
            if (piesa & m) {
                poz2 = i;
                break;
            }
        }

        if (poz1 <= poz2) return poz1;
        return poz2;

    } else {
        for (i = 0; i <= 7; i++) {
            m = 1 << i;
            if (piesa & m) return i;
        }
    }
    return 0;
}

int main() {
    ull harta, lines, piesa_mutata64, m, piesa64, supH, infH;
    int piesa, i, mutare=0, piesa2, ok, y, pas=0;
	int nrbit, nrbit2, linie_completa=0, nr_mutari, j, v[BYTE];
  
    scanf("%llu%d", &harta, &nr_mutari);
    afisare(harta);

    for (j = 1; j <= nr_mutari; j++) {
        scanf("%d",&piesa);
        pas = 0;
        for (i = 7; i >= 0; i--) {
            scanf("%d", &v[i]);
        }

        for (i = 7; i >= 0; i--) {
            ok = 1;
            mutare = 0;
            if(harta & (((ull)piesa) << BYTE * i)) {
                break;

            } else {
                if (v[i] >= 0) {
                    mutare = 0;
                    piesa2 = piesa;
                    while (ok) {
                        piesa2 = piesa2 >> 1;
                        mutare++;
                        piesa64 = ((ull)piesa2) << (BYTE * i);
                        if (harta & piesa64) {
                            if(v[i] < mutare) {
                                piesa = piesa >> v[i];
                                break;
                            } else {
                                piesa = piesa >> (mutare - 1);
                                break;
                            }
                        }

                        if (mutare > max_dreapta(piesa)) {
                            mutare = max_dreapta(piesa);
                            if (v[i] < mutare) {
                                piesa = piesa >> v[i];
                                break;
                            } else {
                                piesa = piesa >> mutare;
                                break;
                            }
                        }
                    }

                    piesa_mutata64 = ((ull)piesa) << (BYTE * i);
                    if (harta & piesa_mutata64) {
                        break;
                    } else {
                        afisare(harta | piesa_mutata64);
                        pas++;
                    }

                } else if (v[i] < 0) {
                    y=-v[i];
                    mutare=0;
                    piesa2 = piesa;
                    while (ok) {
                        piesa2 = piesa2 << 1;
                        mutare++;
                        piesa64 = ((ull)piesa2) << (BYTE * i);

                        if(harta & piesa64) {
                            if( y < mutare) {
                                piesa = piesa << y;
                                break;
                            } else {
                                piesa = piesa << (mutare - 1);
                                break;
                            }
                        }

                        if (mutare > max_stanga(piesa)) {
                            mutare = max_stanga(piesa);

                            if (y < mutare) {
                                piesa = piesa << y;
                                break;
                            } else {
                                piesa = piesa << mutare;
                                break;
                            }
                        }
                    }

                    piesa_mutata64 = ((ull)piesa) << (BYTE * i);
                    if (harta & piesa_mutata64) {
                        break;
                    } else {
                        afisare(harta | piesa_mutata64);
                        pas++;
                    }
                }
            }
        }

        if (pas > 0) {
            harta = harta | (((ull)piesa) << (BYTE * (i + 1)));
        } else {
            afisare(harta);
        }
        if(pas == 1 && piesa > 255) {
		// in caz ca piesa nu are loc in totalitate pe harta
                afisare(harta);
        }

        if (pas == 1) { //  piesa se afla pe prima linie in cadrul hartii
            nrbit = 0;
            lines = (harta >> 56) << 56;
            m = ((ull)1) << 56;
            for (i = 0; i <= 7; i++) {
                if(lines & m) {
                    nrbit++; // contorizez bitii unari
                } else {
                    break;
                }
                m = m << 1; // actualizare masca
            }
            if (nrbit == BYTE) {
                harta = harta << BYTE >> BYTE;
                afisare(harta);
                linie_completa++;
            }

        } else if (pas == BYTE) { // piesa se afla pe ultima linie a hartii
            lines = harta << 48; // ultimele 2 linii pot fi complete
            m = ((ull)1) << 48;
            nrbit = nrbit2 = 0;
            for (i = 0;i <= 7; i++) {
                if (lines & m) {
                    nrbit++;
                } else {
                	break;
                }
                m = m << 1;
            }

            m = ((ull)1) << 56;
            for (i = 0; i <= 7; i++) {
                if (lines & m) {
                    nrbit2++;
                } else {
                	break;
                }
                m = m << 1;
            }

            if (nrbit == BYTE) {
                if (nrbit2 == BYTE) { // 2 linii de eliminat
                    harta = harta >> 16;
                    afisare(harta);
                    linie_completa += 2;
                }
                 else { // o singura linie de eliminat
                    harta = harta >> BYTE;
                    afisare(harta);
                    linie_completa++;
                }

            } else if (nrbit2 == BYTE) { // o singura linie de eliminat
                supH = harta >> 16 << BYTE;
                infH = harta;
                infH = infH << 56 >> 56;
                harta = infH | supH;
                afisare(harta);
                linie_completa++;
            }

        } else if (pas > 1 || pas < 8) {
        	lines = (harta >> (BYTE * (8 - pas))) << 48;
            m = ((ull)1) << 48;
            nrbit = nrbit2 = 0;
            for (i = 0; i <= 7; i++) {
                if (lines & m) {
                    nrbit++;
                } else {
                    break;
                }
                m = m << 1;
            }
            m = ((ull)1) << 56;
            for (i = 0; i <= 7; i++) {
                if (lines & m) {
                    nrbit2++;
                } else {
                    break;
                }
                m = m << 1;
            }

            if (nrbit == BYTE) { // linia "de jos" dintre cele doua verificate
                if (nrbit2 == BYTE) { //2 linii de eliminat
                    supH = harta >> BYTE * (8 - pas + 2);
                    supH = supH << BYTE * (8 - pas);
                    infH = harta;
                    infH = infH << BYTE * pas;
                    infH = infH >> BYTE * pas;
                    harta = infH | supH;
                    afisare(harta);
                    linie_completa += 2;
                } else { // doar linia "de jos"
                    supH = harta >> BYTE * (8 - pas + 1);
                    supH = supH << BYTE * (8 - pas);
                    infH = harta;
                    infH = infH << BYTE * pas;
                    infH = infH >> BYTE * pas;
                    harta = infH | supH;
                    afisare(harta);
                    linie_completa++;
                }
            } else if (nrbit2 == BYTE) { // doar linia de deasupra
                supH = harta >> BYTE * (8 - pas + 2);
                supH = supH << BYTE * (8 - pas + 1);
                infH = harta;
                infH = infH << BYTE * (pas - 1);
                infH = infH >> BYTE * (pas - 1);
                harta = infH | supH;
                afisare(harta);
                linie_completa++;
			}
        } else {
            afisare(harta);
        }
		if (pas == 1 && piesa > 255) {
            break; // piesa nu are loc complet pe harta
		}
    }

    int index = 63, zero = 0;
    float score = 0;
    while (index >= 0){
        if((harta & (((ull)1) << index)) == 0) {
            zero++;
        }
        index--;
    }

    score = ((float)sqrt(zero)) + pow(((float)1.25), linie_completa);
    printf("GAME OVER!\nScore:%.2f\n", score);

    return 0;
}

