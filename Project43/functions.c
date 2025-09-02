#include "header.h"

// -------------------- Globalne varijable --------------------
Konverzija* globalneKonverzije = NULL;
int brojKonverzija = 0;
int maxKonverzija = 10;

// -------------------- Static funkcije --------------------
static void* preokreniNiz(char* niz) {
    int i = 0, j = strlen(niz) - 1;
    while (i < j) {
        char tmp = niz[i];
        niz[i] = niz[j];
        niz[j] = tmp;
        i++; j--;
    }
    return niz;
}

// -------------------- Funkcije za konverzije --------------------
char* decimalniUBinarni(int decimal) {
    char* binarni = malloc(33);
    if (!binarni) { perror("Memorija"); exit(1); }
    int i = 0;
    if (decimal == 0) binarni[i++] = '0';
    while (decimal) {
        binarni[i++] = '0' + (decimal & 1);
        decimal >>= 1;
    }
    binarni[i] = '\0';
    return _strdup(preokreniNiz(binarni));
}

int binarniUDecimal(const char* binarni) {
    if (!binarni) return 0;
    int decimal = 0;
    for (size_t i = 0; i < strlen(binarni); i++)
        decimal = decimal * 2 + (binarni[i] - '0');
    return decimal;
}

char* decimalniUOktalni(int decimal) {
    char* oktal = malloc(12);
    if (!oktal) { perror("Memorija"); exit(1); }
    sprintf(oktal, "%o", decimal);
    return oktal;
}

int oktalniUDecimal(const char* oktal) {
    if (!oktal) return 0;
    int decimal = 0;
    for (size_t i = 0; i < strlen(oktal); i++)
        decimal = decimal * 8 + (oktal[i] - '0');
    return decimal;
}

char* heksadecimalniUBinarni(const char* hex) {
    if (!hex) return NULL;
    unsigned int broj;
    sscanf(hex, "%x", &broj);
    char binarni[33] = "";
    int i = 0;
    if (broj == 0) binarni[i++] = '0';
    while (broj) {
        binarni[i++] = '0' + (broj % 2);
        broj /= 2;
    }
    binarni[i] = '\0';
    return _strdup(preokreniNiz(binarni));
}

char* binarniUHeksadecimalni(const char* binarni) {
    if (!binarni) return NULL;
    int duljina = strlen(binarni);
    int padding = (4 - (duljina % 4)) % 4;
    char popunjeni[129];
    memset(popunjeni, '0', padding);
    strcpy(popunjeni + padding, binarni);

    char* binHex[] = { "0000","0001","0010","0011","0100","0101","0110","0111",
                       "1000","1001","1010","1011","1100","1101","1110","1111" };
    char hex[33] = "";

    for (int i = 0; i < duljina + padding; i += 4) {
        char grupa[5]; strncpy(grupa, popunjeni + i, 4); grupa[4] = '\0';
        for (int j = 0; j < 16; j++) {
            if (strcmp(grupa, binHex[j]) == 0) {
                char znak[2]; sprintf(znak, "%X", j);
                strcat(hex, znak);
                break;
            }
        }
    }
    return _strdup(hex);
}

// -------------------- Upravljanje konverzijama --------------------
void dodajKonverziju(const char* vrsta, const char* ulaz, const char* rezultat) {
    if (!vrsta || !ulaz || !rezultat) return;
    if (brojKonverzija >= maxKonverzija) {
        maxKonverzija *= 2;
        Konverzija* temp = realloc(globalneKonverzije, maxKonverzija * sizeof(Konverzija));
        if (!temp) { perror("Memorija"); exit(1); }
        globalneKonverzije = temp;
    }
    strncpy(globalneKonverzije[brojKonverzija].vrsta, vrsta, 29);
    globalneKonverzije[brojKonverzija].vrsta[29] = '\0';
    strncpy(globalneKonverzije[brojKonverzija].ulaz, ulaz, 99);
    globalneKonverzije[brojKonverzija].ulaz[99] = '\0';
    strncpy(globalneKonverzije[brojKonverzija].izlaz, rezultat, 99);
    globalneKonverzije[brojKonverzija].izlaz[99] = '\0';
    brojKonverzija++;
}

void pregledajKonverzije() {
    if (brojKonverzija == 0) { printf("Nema konverzija\n"); return; }
    for (int i = 0; i < brojKonverzija; i++)
        printf("%d. %s: %s -> %s\n", i + 1,
            globalneKonverzije[i].vrsta,
            globalneKonverzije[i].ulaz,
            globalneKonverzije[i].izlaz);
}

void azurirajKonverziju(int indeks, const char* noviUlaz) {
    if (!noviUlaz || indeks < 0 || indeks >= brojKonverzija) return;
    strncpy(globalneKonverzije[indeks].ulaz, noviUlaz, 99);
    globalneKonverzije[indeks].ulaz[99] = '\0';
    char* noviIzlaz = NULL;

    if (strcmp(globalneKonverzije[indeks].vrsta, DEC_U_BIN) == 0)
        noviIzlaz = decimalniUBinarni(atoi(noviUlaz));
    else if (strcmp(globalneKonverzije[indeks].vrsta, BIN_U_DEC) == 0) {
        int dec = binarniUDecimal(noviUlaz);
        snprintf(globalneKonverzije[indeks].izlaz, 100, "%d", dec);
        return;
    }
    else if (strcmp(globalneKonverzije[indeks].vrsta, DEC_U_OKT) == 0)
        noviIzlaz = decimalniUOktalni(atoi(noviUlaz));
    else if (strcmp(globalneKonverzije[indeks].vrsta, OKT_U_DEC) == 0) {
        int dec = oktalniUDecimal(noviUlaz);
        snprintf(globalneKonverzije[indeks].izlaz, 100, "%d", dec);
        return;
    }
    else if (strcmp(globalneKonverzije[indeks].vrsta, HEX_U_BIN) == 0)
        noviIzlaz = heksadecimalniUBinarni(noviUlaz);
    else if (strcmp(globalneKonverzije[indeks].vrsta, BIN_U_HEX) == 0)
        noviIzlaz = binarniUHeksadecimalni(noviUlaz);

    if (noviIzlaz) {
        strncpy(globalneKonverzije[indeks].izlaz, noviIzlaz, 99);
        globalneKonverzije[indeks].izlaz[99] = '\0';
        free(noviIzlaz);
    }
}

void izbrisiKonverziju(int indeks) {
    if (indeks < 0 || indeks >= brojKonverzija) return;
    for (int i = indeks; i < brojKonverzija - 1; i++)
        globalneKonverzije[i] = globalneKonverzije[i + 1];
    brojKonverzija--;
}

// -------------------- Sortiranje i pretraga --------------------
int usporediKonverzije(const void* a, const void* b) {
    return strcmp(((Konverzija*)a)->vrsta, ((Konverzija*)b)->vrsta);
}

void rekurzivniQuickSort(Konverzija* polje, int lijevo, int desno, int (*usporedi)(const void*, const void*)) {
    if (!polje || lijevo >= desno || !usporedi) return;
    Konverzija pivot = polje[desno];
    int i = lijevo - 1;
    for (int j = lijevo; j < desno; j++) {
        if (usporedi(&polje[j], &pivot) <= 0) {
            i++;
            Konverzija tmp = polje[i];
            polje[i] = polje[j];
            polje[j] = tmp;
        }
    }
    Konverzija tmp = polje[i + 1];
    polje[i + 1] = polje[desno];
    polje[desno] = tmp;
    int p = i + 1;
    rekurzivniQuickSort(polje, lijevo, p - 1, usporedi);
    rekurzivniQuickSort(polje, p + 1, desno, usporedi);
}

int pronadiSveKonverzije(const char* vrsta, Konverzija** rezultati) {
    if (!vrsta || !rezultati || brojKonverzija == 0) return 0;
    Konverzija key; strncpy(key.vrsta, vrsta, 29); key.vrsta[29] = '\0';
    Konverzija* found = (Konverzija*)bsearch(&key, globalneKonverzije, brojKonverzija,
        sizeof(Konverzija), usporediKonverzije);
    if (!found) return 0;
    int index = found - globalneKonverzije;
    int start = index, end = index;
    while (start > 0 && strcmp(globalneKonverzije[start - 1].vrsta, vrsta) == 0) start--;
    while (end < brojKonverzija - 1 && strcmp(globalneKonverzije[end + 1].vrsta, vrsta) == 0) end++;
    *rezultati = &globalneKonverzije[start];
    return end - start + 1;
}

// -------------------- Funkcije za datoteke --------------------
void spremiKonverzijeUDatoteku(const char* nazivDatoteke) {
    if (!nazivDatoteke) return;
    FILE* f = fopen(nazivDatoteke, "w");
    if (!f) { perror("Problem s otvaranjem datoteke"); return; }
    for (int i = 0; i < brojKonverzija; i++)
        fprintf(f, "%s: %s -> %s\n", globalneKonverzije[i].vrsta,
            globalneKonverzije[i].ulaz, globalneKonverzije[i].izlaz);
    fclose(f);
    printf("Konverzije spremljene\n");
}

void obrisiDatoteku(const char* nazivDatoteke) {
    if (!nazivDatoteke) return;
    if (remove(nazivDatoteke) == 0) printf("Datoteka obrisana\n");
    else perror("Problem s brisanjem datoteke");
}
