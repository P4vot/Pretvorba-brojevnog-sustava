#pragma once
#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Konstante za vrste konverzija
#define DEC_U_BIN "Decimalni u Binarni"
#define BIN_U_DEC "Binarni u Decimalni"
#define DEC_U_OKT "Decimalni u Oktalni"
#define OKT_U_DEC "Oktalni u Decimalni"
#define HEX_U_BIN "Heksadecimalni u Binarni"
#define BIN_U_HEX "Binarni u Heksadecimalni"

// Struktura za konverzije
typedef struct {
    char vrsta[30];
    char ulaz[100];
    char izlaz[100];
} Konverzija;

// Globalne varijable
extern Konverzija* globalneKonverzije;
extern int brojKonverzija;
extern int maxKonverzija;

// Funkcije za provjeru validnosti brojeva
int validanDecimalni(const char* ulaz);
int validanBinarni(const char* ulaz);
int validanOktalni(const char* ulaz);
int validanHeksadecimalni(const char* ulaz);

// Funkcije za konverzije
char* decimalniUBinarni(int decimal);
int binarniUDecimal(const char* binarni);
char* decimalniUOktalni(int decimal);
int oktalniUDecimal(const char* oktal);
char* heksadecimalniUBinarni(const char* hex);
char* binarniUHeksadecimalni(const char* binarni);

// Funkcije za upravljanje konverzijama
void dodajKonverziju(const char* vrsta, const char* ulaz, const char* rezultat);
void pregledajKonverzije();
void azurirajKonverziju(int indeks, const char* noviUlaz);
void izbrisiKonverziju(int indeks);
int usporediKonverzije(const void* a, const void* b);
void rekurzivniQuickSort(Konverzija* polje, int lijevo, int desno, int (*usporedi)(const void*, const void*));
int pronadiSveKonverzije(const char* vrsta, Konverzija** rezultati);

// Funkcije za datoteke
void spremiKonverzijeUDatoteku(const char* nazivDatoteke);
void obrisiDatoteku(const char* nazivDatoteke);

#endif // HEADER_H
