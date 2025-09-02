#include "header.h"

/* ===== Definicije globalnih varijabli ===== */
Konverzija* globalneKonverzije = NULL;
int brojKonverzija = 0;
int maxKonverzija = 0;
Cvor* glavaListe = NULL;

/* ===== Pomoćni statički usporedni predikati ===== */
static int usporediKonverzije(const void* a, const void* b) {
    const Konverzija* ka = (const Konverzija*)a;
    const Konverzija* kb = (const Konverzija*)b;
    return strcmp(ka->vrsta, kb->vrsta);
}

/* bsearch: key = const char* (vrsta), element = const Konverzija* */
static int usporediKljucVrsta(const void* key, const void* elem) {
    const char* k = (const char*)key;
    const Konverzija* e = (const Konverzija*)elem;
    return strcmp(k, e->vrsta);
}

/* ===== Funkcije konverzija ===== */
char* decimalniUBinarni(int decimalni) {
    if (decimalni == 0) {
        char* s = (char*)malloc(2);
        if (!s) return NULL;
        s[0] = '0'; s[1] = '\0';
        return s;
    }
    char buffer[64] = {0};
    int i = 0;
    while (decimalni > 0) {
        buffer[i++] = (decimalni & 1) ? '1' : '0';
        decimalni >>= 1;
    }
    buffer[i] = '\0';
    preokreniNiz(buffer);
    char* out = (char*)malloc(strlen(buffer) + 1);
    if (!out) return NULL;
    strcpy(out, buffer);
    return out;
}

int binarniUDekadski(const char* binarni) {
    if (!binarni) return 0;
    int val = 0;
    for (size_t i = 0; binarni[i] != '\0'; ++i) {
        if (binarni[i] != '0' && binarni[i] != '1') continue;
        val = (val << 1) + (binarni[i] - '0');
    }
    return val;
}

char* decimalniUoktalni(int decimalni) {
    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%o", decimalni);
    char* out = (char*)malloc(strlen(buffer) + 1);
    if (!out) return NULL;
    strcpy(out, buffer);
    return out;
}

int oktalniUDekadski(const char* oktalni) {
    if (!oktalni) return 0;
    int val = 0;
    for (size_t i = 0; oktalni[i] != '\0'; ++i) {
        if (oktalni[i] < '0' || oktalni[i] > '7') continue;
        val = val * 8 + (oktalni[i] - '0');
    }
    return val;
}

char* heksadekadskiUBinarni(const char* heks) {
    if (!heks) return NULL;
    /* Svaki heks znak -> 4 bita */
    size_t n = strlen(heks);
    char* out = (char*)malloc(n * 4 + 1);
    if (!out) return NULL;
    size_t k = 0;
    for (size_t i = 0; i < n; ++i) {
        char c = heks[i];
        unsigned v = 0;
        if (c >= '0' && c <= '9') v = c - '0';
        else if (c >= 'a' && c <= 'f') v = 10 + (unsigned)(c - 'a');
        else if (c >= 'A' && c <= 'F') v = 10 + (unsigned)(c - 'A');
        else continue;
        out[k++] = (v & 8) ? '1' : '0';
        out[k++] = (v & 4) ? '1' : '0';
        out[k++] = (v & 2) ? '1' : '0';
        out[k++] = (v & 1) ? '1' : '0';
    }
    out[k] = '\0';
    return out;
}

char* binarniUHeksadekadski(const char* binarni) {
    if (!binarni) return NULL;
    size_t n = strlen(binarni);
    size_t padding = (4 - (n % 4)) % 4;
    size_t total = n + padding;

    char* temp = (char*)malloc(total + 1);
    if (!temp) return NULL;
    for (size_t i = 0; i < padding; ++i) temp[i] = '0';
    strcpy(temp + padding, binarni);
    temp[total] = '\0';

    char* out = (char*)malloc(total / 4 + 1);
    if (!out) { free(temp); return NULL; }

    size_t k = 0;
    for (size_t i = 0; i < total; i += 4) {
        unsigned v = 0;
        for (size_t j = 0; j < 4; ++j) {
            v = (v << 1) + (temp[i + j] == '1' ? 1u : 0u);
        }
        out[k++] = (v < 10) ? (char)('0' + v) : (char)('A' + (v - 10));
    }
    out[k] = '\0';
    free(temp);
    return out;
}

/* ===== Dinamički niz konverzija ===== */
void dodajKonverziju(const char* vrsta, const char* ulaz, const char* izlaz) {
    if (!vrsta || !ulaz || !izlaz) {
        fprintf(stderr, "dodajKonverziju: Neispravni argumenti.\n");
        return;
    }
    static int brojRealokacija = 0; /* primjer lokalne static varijable */

    if (brojKonverzija >= maxKonverzija) {
        int noviMaks = (maxKonverzija == 0) ? 4 : maxKonverzija * 2;
        Konverzija* temp = (Konverzija*)realloc(globalneKonverzije, (size_t)noviMaks * sizeof(Konverzija));
        if (!temp) {
            perror("Neuspjela realokacija memorije");
            return;
        }
        globalneKonverzije = temp;
        maxKonverzija = noviMaks;
        (void)brojRealokacija; /* izbjegni warning ako se ne koristi */
    }

    /* Sigurno kopiranje (bez prelijevanja) */
    strncpy(globalneKonverzije[brojKonverzija].vrsta, vrsta,
            sizeof(globalneKonverzije[brojKonverzija].vrsta) - 1);
    globalneKonverzije[brojKonverzija].vrsta[sizeof(globalneKonverzije[brojKonverzija].vrsta) - 1] = '\0';

    strncpy(globalneKonverzije[brojKonverzija].ulaz, ulaz,
            sizeof(globalneKonverzije[brojKonverzija].ulaz) - 1);
    globalneKonverzije[brojKonverzija].ulaz[sizeof(globalneKonverzije[brojKonverzija].ulaz) - 1] = '\0';

    strncpy(globalneKonverzije[brojKonverzija].izlaz, izlaz,
            sizeof(globalneKonverzije[brojKonverzija].izlaz) - 1);
    globalneKonverzije[brojKonverzija].izlaz[sizeof(globalneKonverzije[brojKonverzija].izlaz) - 1] = '\0';

    ++brojKonverzija;
}

void prikaziKonverzije(void) {
    if (brojKonverzija == 0) {
        printf("Nema spremljenih konverzija.\n");
        return;
    }
    for (int i = 0; i < brojKonverzija; ++i) {
        printf("%d. %s: %s -> %s\n",
               i + 1,
               globalneKonverzije[i].vrsta,
               globalneKonverzije[i].ulaz,
               globalneKonverzije[i].izlaz);
    }
}

void azurirajKonverziju(int indeks, const char* noviUlaz) {
    if (indeks < 0 || indeks >= brojKonverzija || !noviUlaz) {
        printf("Neispravan indeks ili ulaz.\n");
        return;
    }
    strncpy(globalneKonverzije[indeks].ulaz, noviUlaz,
            sizeof(globalneKonverzije[indeks].ulaz) - 1);
    globalneKonverzije[indeks].ulaz[sizeof(globalneKonverzije[indeks].ulaz) - 1] = '\0';
    printf("Konverzija ažurirana (izlaz ažurirajte prema vrsti po potrebi).\n");
}

void obrisiKonverziju(int indeks) {
    if (indeks < 0 || indeks >= brojKonverzija) {
        printf("Neispravan indeks.\n");
        return;
    }
    /* Anuliraj zapis koji se briše (opcionalno) */
    memset(&globalneKonverzije[indeks], 0, sizeof(Konverzija));
    /* Pomakni ostatak ulijevo */
    for (int i = indeks; i < brojKonverzija - 1; ++i) {
        globalneKonverzije[i] = globalneKonverzije[i + 1];
    }
    /* Očisti zadnji sada-višak element */
    memset(&globalneKonverzije[brojKonverzija - 1], 0, sizeof(Konverzija));
    --brojKonverzija;
    printf("Konverzija obrisana.\n");
}

void spremiKonverzijeUDatoteku(const char* datoteka) {
    if (!datoteka) {
        fprintf(stderr, "Neispravno ime datoteke.\n");
        return;
    }
    FILE* f = fopen(datoteka, "w");
    if (!f) {
        fprintf(stderr, "Greška pri otvaranju '%s': %s\n", datoteka, strerror(errno));
        return;
    }

    for (int i = 0; i < brojKonverzija; ++i) {
        if (fprintf(f, "%s;%s;%s\n",
                    globalneKonverzije[i].vrsta,
                    globalneKonverzije[i].ulaz,
                    globalneKonverzije[i].izlaz) < 0) {
            fprintf(stderr, "Greška pri pisanju u '%s': %s\n", datoteka, strerror(errno));
            break;
        }
    }

    long kraj = ftell(f); /* demonstracija ftell */
    if (kraj >= 0) printf("Zapisano bajtova: %ld\n", kraj);

    rewind(f);            /* demonstracija rewind (vraćanje na početak) */
    /* ... po potrebi se može čitati ... */

    if (fclose(f) == EOF)
        fprintf(stderr, "Greška pri zatvaranju '%s': %s\n", datoteka, strerror(errno));
    else
        printf("Konverzije spremljene u '%s'.\n", datoteka);
}

void obrisiDatoteku(const char* datoteka) {
    if (!datoteka) return;
    if (remove(datoteka) == 0)
        printf("Datoteka '%s' obrisana.\n", datoteka);
    else
        fprintf(stderr, "Ne mogu obrisati '%s': %s\n", datoteka, strerror(errno));
}

void sortirajKonverzijePoVrsti(void) {
    if (brojKonverzija <= 1) {
        printf("Nije potrebno sortiranje.\n");
        return;
    }
    qsort(globalneKonverzije, (size_t)brojKonverzija, sizeof(Konverzija), usporediKonverzije);
    printf("Konverzije sortirane po vrsti.\n");
}

void pretraziKonverzije(const char* vrsta) {
    if (!vrsta) {
        printf("Neispravan upit.\n");
        return;
    }
    int nadeno = 0;
    for (int i = 0; i < brojKonverzija; ++i) {
        if (strcmp(globalneKonverzije[i].vrsta, vrsta) == 0) {
            printf("Pronađeno: %s -> %s\n",
                   globalneKonverzije[i].ulaz,
                   globalneKonverzije[i].izlaz);
            nadeno = 1;
        }
    }
    if (!nadeno) printf("Nema rezultata za vrstu: %s\n", vrsta);
}

const Konverzija* pronadiKonverzijuBsearch(const char* vrsta) {
    if (!vrsta || brojKonverzija == 0) return NULL;
    return (const Konverzija*)bsearch(
        vrsta, globalneKonverzije, (size_t)brojKonverzija,
        sizeof(Konverzija), usporediKljucVrsta
    );
}

void rekurzivnaPretraga(int lijevo, int desno, const char* vrsta) {
    if (!vrsta) {
        printf("Neispravan upit.\n");
        return;
    }
    if (lijevo > desno) {
        printf("Nije pronađeno (rekurzija).\n");
        return;
    }
    int sred = (lijevo + desno) / 2;
    int cmp = strcmp(globalneKonverzije[sred].vrsta, vrsta);
    if (cmp == 0) {
        printf("Pronađeno rekurzivno: %s -> %s\n",
               globalneKonverzije[sred].ulaz,
               globalneKonverzije[sred].izlaz);
    } else if (cmp > 0) {
        rekurzivnaPretraga(lijevo, sred - 1, vrsta);
    } else {
        rekurzivnaPretraga(sred + 1, desno, vrsta);
    }
}

/* ===== Povezani popis ===== */
void listaDodajKonverziju(const char* vrsta, const char* ulaz, const char* izlaz) {
    Cvor* novi = (Cvor*)malloc(sizeof(Cvor));
    if (!novi) {
        perror("Alokacija čvora nije uspjela");
        return;
    }
    strncpy(novi->podatak.vrsta, vrsta, sizeof(novi->podatak.vrsta) - 1);
    novi->podatak.vrsta[sizeof(novi->podatak.vrsta) - 1] = '\0';
    strncpy(novi->podatak.ulaz, ulaz, sizeof(novi->podatak.ulaz) - 1);
    novi->podatak.ulaz[sizeof(novi->podatak.ulaz) - 1] = '\0';
    strncpy(novi->podatak.izlaz, izlaz, sizeof(novi->podatak.izlaz) - 1);
    novi->podatak.izlaz[sizeof(novi->podatak.izlaz) - 1] = '\0';

    novi->sljedeci = glavaListe;
    glavaListe = novi;
}

void listaPrikaziKonverzije(void) {
    if (!glavaListe) {
        printf("Lista konverzija je prazna.\n");
        return;
    }
    Cvor* t = glavaListe;
    int i = 1;
    while (t) {
        printf("%d. %s: %s -> %s\n",
               i++, t->podatak.vrsta, t->podatak.ulaz, t->podatak.izlaz);
        t = t->sljedeci;
    }
}

void listaObrisiKonverziju(const char* vrsta, const char* ulaz) {
    Cvor* t = glavaListe;
    Cvor* p = NULL;
    while (t) {
        if (strcmp(t->podatak.vrsta, vrsta) == 0 &&
            strcmp(t->podatak.ulaz, ulaz) == 0) {
            if (p) p->sljedeci = t->sljedeci;
            else   glavaListe = t->sljedeci;
            free(t);
            printf("Konverzija iz liste obrisana.\n");
            return;
        }
        p = t;
        t = t->sljedeci;
    }
    printf("Konverzija nije pronađena u listi.\n");
}

void listaOslobodi(void) {
    Cvor* t = glavaListe;
    while (t) {
        Cvor* tmp = t;
        t = t->sljedeci;
        free(tmp);
    }
    glavaListe = NULL;
}
