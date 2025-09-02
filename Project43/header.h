#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* ===== Strukture ===== */
typedef struct {
    char vrsta[50];
    char ulaz[100];
    char izlaz[100];
} Konverzija;

/* Čvor za jednostruko povezani popis */
typedef struct Cvor {
    Konverzija podatak;
    struct Cvor* sljedeci;
} Cvor;

/* ===== Globalne varijable (extern deklaracije) ===== */
extern Konverzija* globalneKonverzije;
extern int brojKonverzija;
extern int maxKonverzija;
extern Cvor* glavaListe;

/* ===== Pomoćne inline/statik funkcije ===== */
static inline void preokreniNiz(char* s) {
    if (!s) return;
    int i = 0, j = (int)strlen(s) - 1;
    while (i < j) {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
        ++i; --j;
    }
}

/* ===== Funkcije konverzija ===== */
char* decimalniUBinarni(int decimalni);
int   binarniUDekadski(const char* binarni);
char* decimalniUoktalni(int decimalni);
int   oktalniUDekadski(const char* oktalni);
char* heksadekadskiUBinarni(const char* heks);
char* binarniUHeksadekadski(const char* binarni);

/* ===== Rad s dinamičkim nizom ===== */
void dodajKonverziju(const char* vrsta, const char* ulaz, const char* izlaz);
void prikaziKonverzije(void);
void azurirajKonverziju(int indeks, const char* noviUlaz);
void obrisiKonverziju(int indeks);
void spremiKonverzijeUDatoteku(const char* datoteka);
void obrisiDatoteku(const char* datoteka);
void sortirajKonverzijePoVrsti(void);
void pretraziKonverzije(const char* vrsta);
const Konverzija* pronadiKonverzijuBsearch(const char* vrsta);
void rekurzivnaPretraga(int lijevo, int desno, const char* vrsta);

/* ===== Rad s povezanim popisom ===== */
void listaDodajKonverziju(const char* vrsta, const char* ulaz, const char* izlaz);
void listaPrikaziKonverzije(void);
void listaObrisiKonverziju(const char* vrsta, const char* ulaz);
void listaOslobodi(void);

#endif /* HEADER_H */
