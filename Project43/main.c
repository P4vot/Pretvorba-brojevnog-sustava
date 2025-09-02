#include "header.h"

// Funkcije za provjeru valjanosti brojeva
int validanDecimalni(const char* ulaz) {
    if (!ulaz) return 0;
    for (size_t i = 0; i < strlen(ulaz); i++)
        if (ulaz[i] < '0' || ulaz[i] > '9') return 0;
    return 1;
}

int validanBinarni(const char* ulaz) {
    if (!ulaz) return 0;
    for (size_t i = 0; i < strlen(ulaz); i++)
        if (ulaz[i] != '0' && ulaz[i] != '1') return 0;
    return 1;
}

int validanOktalni(const char* ulaz) {
    if (!ulaz) return 0;
    for (size_t i = 0; i < strlen(ulaz); i++)
        if (ulaz[i] < '0' || ulaz[i] > '7') return 0;
    return 1;
}

int validanHeksadecimalni(const char* ulaz) {
    if (!ulaz) return 0;
    for (size_t i = 0; i < strlen(ulaz); i++) {
        char c = ulaz[i];
        if (!((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f')))
            return 0;
    }
    return 1;
}

int main() {
    globalneKonverzije = malloc(maxKonverzija * sizeof(Konverzija));
    if (!globalneKonverzije) { perror("Memorija"); return 1; }

    int izbor;
    char ulaz[100];
    char* rezultat;
    int indeks;

    while (1) {
        printf("\nIzbornik:\n"
            "1. Decimalni u Binarni\n"
            "2. Binarni u Decimalni\n"
            "3. Decimalni u Oktalni\n"
            "4. Oktalni u Decimalni\n"
            "5. Heksadecimalni u Binarni\n"
            "6. Binarni u Heksadecimalni\n"
            "7. Pregledaj\n"
            "8. Azuriraj\n"
            "9. Izbrisi\n"
            "10. Spremi\n"
            "11. Obrisi datoteku\n"
            "12. Sortiraj\n"
            "13. Pretrazi\n"
            "14. Izlaz\n"
            "Unesite izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1: // Decimalni u Binarni
            printf("Unesite decimalni broj: "); scanf("%s", ulaz);
            if (!validanDecimalni(ulaz)) { printf("GRESKA: Uneseni broj nije decimalni!\n"); break; }
            rezultat = decimalniUBinarni(atoi(ulaz));
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju(DEC_U_BIN, ulaz, rezultat);
            free(rezultat);
            break;
        case 2: // Binarni u Decimalni
            printf("Unesite binarni broj: "); scanf("%s", ulaz);
            if (!validanBinarni(ulaz)) { printf("GRESKA: Uneseni broj nije binarni!\n"); break; }
            {
                int dec = binarniUDecimal(ulaz);
                printf("Rezultat: %d\n", dec);
                char buffer[100]; snprintf(buffer, sizeof(buffer), "%d", dec);
                dodajKonverziju(BIN_U_DEC, ulaz, buffer);
            }
            break;
        case 3: // Decimalni u Oktalni
            printf("Unesite decimalni broj: "); scanf("%s", ulaz);
            if (!validanDecimalni(ulaz)) { printf("GRESKA: Uneseni broj nije decimalni!\n"); break; }
            rezultat = decimalniUOktalni(atoi(ulaz));
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju(DEC_U_OKT, ulaz, rezultat);
            free(rezultat);
            break;
        case 4: // Oktalni u Decimalni
            printf("Unesite oktalni broj: "); scanf("%s", ulaz);
            if (!validanOktalni(ulaz)) { printf("GRESKA: Uneseni broj nije oktalni!\n"); break; }
            {
                int dec = oktalniUDecimal(ulaz);
                printf("Rezultat: %d\n", dec);
                char buffer[100]; snprintf(buffer, sizeof(buffer), "%d", dec);
                dodajKonverziju(OKT_U_DEC, ulaz, buffer);
            }
            break;
        case 5: // Heksadecimalni u Binarni
            printf("Unesite heksadecimalni broj: "); scanf("%s", ulaz);
            if (!validanHeksadecimalni(ulaz)) { printf("GRESKA: Uneseni broj nije heksadecimalni!\n"); break; }
            rezultat = heksadecimalniUBinarni(ulaz);
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju(HEX_U_BIN, ulaz, rezultat);
            free(rezultat);
            break;
        case 6: // Binarni u Heksadecimalni
            printf("Unesite binarni broj: "); scanf("%s", ulaz);
            if (!validanBinarni(ulaz)) { printf("GRESKA: Uneseni broj nije binarni!\n"); break; }
            rezultat = binarniUHeksadecimalni(ulaz);
            printf("Rezultat: %s\n", rezultat);
            dodajKonverziju(BIN_U_HEX, ulaz, rezultat);
            free(rezultat);
            break;
        case 7: pregledajKonverzije(); break;
        case 8:
            pregledajKonverzije();
            printf("Unesite indeks za azuriranje: "); scanf("%d", &indeks);
            indeks--;
            printf("Unesite novi ulaz: "); scanf("%s", ulaz);
            azurirajKonverziju(indeks, ulaz);
            break;
        case 9:
            pregledajKonverzije();
            printf("Unesite indeks za brisanje: "); scanf("%d", &indeks);
            indeks--;
            izbrisiKonverziju(indeks);
            break;
        case 10: spremiKonverzijeUDatoteku("konverzije.txt"); break;
        case 11: obrisiDatoteku("konverzije.txt"); break;
        case 12:
            rekurzivniQuickSort(globalneKonverzije, 0, brojKonverzija - 1, usporediKonverzije);
            printf("Konverzije sortirane\n");
            break;
        case 13:
            printf("Unesite vrstu: "); scanf(" %[^\n]", ulaz);
            {
                Konverzija* pronadeno = NULL;
                int broj = pronadiSveKonverzije(ulaz, &pronadeno);
                if (broj > 0)
                    for (int i = 0; i < broj; i++)
                        printf("%s -> %s\n", pronadeno[i].ulaz, pronadeno[i].izlaz);
                else printf("Nema pronadeno\n");
            }
            break;
        case 14:
            free(globalneKonverzije);
            globalneKonverzije = NULL;
            return 0;
        default: printf("Nevalidan izbor\n");
        }
    }
}
