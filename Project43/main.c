#include "header.h"

int main(void) {
    int izbor;
    char ulaz[128], izlaz[128];

    for (;;) {
        printf("\n--- Glavni izbornik ---\n");
        printf("1. Decimalni u binarni\n");
        printf("2. Binarni u dekadski\n");
        printf("3. Decimalni u oktalni\n");
        printf("4. Oktalni u dekadski\n");
        printf("5. Heksadekadski u binarni\n");
        printf("6. Binarni u heksadekadski\n");
        printf("7. Prikaži konverzije\n");
        printf("8. Ažuriraj konverziju\n");
        printf("9. Obriši konverziju\n");
        printf("10. Spremi u datoteku\n");
        printf("11. Obriši datoteku\n");
        printf("12. Sortiraj po vrsti\n");
        printf("13. Pretraži (linearno)\n");
        printf("14. Pretraži (bsearch)\n");
        printf("15. Pretraži (rekurzivno)\n");
        printf("16. Rad s povezanim popisom\n");
        printf("0. Izlaz\n");
        printf("Odabir: ");
        if (scanf("%d", &izbor) != 1) {
            puts("Neispravan unos.");
            break;
        }

        int indeks;
        char* rezultat = NULL;

        switch (izbor) {
        case 1:
            printf("Unesi decimalni: ");
            scanf("%127s", ulaz);
            rezultat = decimalniUBinarni(atoi(ulaz));
            if (!rezultat) { puts("Greška: nema memorije."); break; }
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju("Decimalni u Binarni", ulaz, rezultat);
            free(rezultat); rezultat = NULL;
            break;

        case 2:
            printf("Unesi binarni: ");
            scanf("%127s", ulaz);
            snprintf(izlaz, sizeof(izlaz), "%d", binarniUDekadski(ulaz));
            printf("Rezultat: %s\n", izlaz);
            dodajKonverziju("Binarni u Dekadski", ulaz, izlaz);
            break;

        case 3:
            printf("Unesi decimalni: ");
            scanf("%127s", ulaz);
            rezultat = decimalniUoktalni(atoi(ulaz));
            if (!rezultat) { puts("Greška: nema memorije."); break; }
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju("Decimalni u Oktalni", ulaz, rezultat);
            free(rezultat); rezultat = NULL;
            break;

        case 4:
            printf("Unesi oktalni: ");
            scanf("%127s", ulaz);
            snprintf(izlaz, sizeof(izlaz), "%d", oktalniUDekadski(ulaz));
            printf("Rezultat: %s\n", izlaz);
            dodajKonverziju("Oktalni u Dekadski", ulaz, izlaz);
            break;

        case 5:
            printf("Unesi heksadekadski: ");
            scanf("%127s", ulaz);
            rezultat = heksadekadskiUBinarni(ulaz);
            if (!rezultat) { puts("Greška: nema memorije."); break; }
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju("Heksadekadski u Binarni", ulaz, rezultat);
            free(rezultat); rezultat = NULL;
            break;

        case 6:
            printf("Unesi binarni: ");
            scanf("%127s", ulaz);
            rezultat = binarniUHeksadekadski(ulaz);
            if (!rezultat) { puts("Greška: nema memorije."); break; }
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju("Binarni u Heksadekadski", ulaz, rezultat);
            free(rezultat); rezultat = NULL;
            break;

        case 7:
            prikaziKonverzije();
            break;

        case 8:
            prikaziKonverzije();
            printf("Indeks za ažuriranje: ");
            scanf("%d", &indeks);
            --indeks;
            if (indeks < 0 || indeks >= brojKonverzija) {
                puts("Neispravan indeks.");
                break;
            }
            printf("Novi ulaz: ");
            scanf("%127s", ulaz);
            azurirajKonverziju(indeks, ulaz);
            break;

        case 9:
            prikaziKonverzije();
            printf("Indeks za brisanje: ");
            scanf("%d", &indeks);
            --indeks;
            obrisiKonverziju(indeks);
            break;

        case 10:
            spremiKonverzijeUDatoteku("konverzije.txt");
            break;

        case 11:
            obrisiDatoteku("konverzije.txt");
            break;

        case 12:
            sortirajKonverzijePoVrsti();
            break;

        case 13:
            printf("Vrsta (točan naziv): ");
            scanf(" %99[^\n]", ulaz);
            pretraziKonverzije(ulaz);
            break;

        case 14:
            printf("Vrsta (bsearch): ");
            scanf(" %99[^\n]", ulaz);
            sortirajKonverzijePoVrsti(); /* obavezno prije bsearch */
            {
                const Konverzija* k = pronadiKonverzijuBsearch(ulaz);
                if (k) printf("Pronađeno (bsearch): %s -> %s\n", k->ulaz, k->izlaz);
                else   printf("Nema rezultata.\n");
            }
            break;

        case 15:
            printf("Vrsta (rekurzija): ");
            scanf(" %99[^\n]", ulaz);
            sortirajKonverzijePoVrsti();
            rekurzivnaPretraga(0, brojKonverzija - 1, ulaz);
            break;

        case 16: {
            int p;
            printf("\n--- Povezani popis ---\n1. Dodaj  2. Prikaži  3. Obriši  4. Nazad\nOdabir: ");
            scanf("%d", &p);
            if (p == 1) {
                printf("Vrsta: ");  scanf(" %99[^\n]", ulaz);
                printf("Ulaz: ");   scanf("%127s", izlaz);
                listaDodajKonverziju(ulaz, izlaz, "Primjer");
            } else if (p == 2) {
                listaPrikaziKonverzije();
            } else if (p == 3) {
                printf("Vrsta: ");  scanf(" %99[^\n]", ulaz);
                printf("Ulaz: ");   scanf("%127s", izlaz);
                listaObrisiKonverziju(ulaz, izlaz);
            }
            break;
        }

        case 0:
            free(globalneKonverzije); globalneKonverzije = NULL;
            listaOslobodi();
            return 0;

        default:
            printf("Nepostojeća opcija.\n");
        }
    }

    /* fallback čišćenje ako se izađe iz petlje */
    free(globalneKonverzije); globalneKonverzije = NULL;
    listaOslobodi();
    return 0;
}
