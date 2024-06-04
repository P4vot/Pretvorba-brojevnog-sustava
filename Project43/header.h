#pragma once
#ifndef HEADER_H
#define HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
char* decimalUBinarni(int decimal);
int binarniUDecimal(char binarni[]);
char* decimalUOkatal(int decimal);
int okatalUDecimal(char okatal[]);
char* heksadecimalniUBinarni(char hex[]);
char* binarniUHeksadecimalni(char binarni[]);
char* strrev(char* str);

// Struct for storing conversion records
typedef struct {
	char vrsta[10];
	char ulaz[100];
	char izlaz[100];
} Konverzija;

// Function prototypes for conversion records management
void dodajKonverziju(const char* vrsta, const char* ulaz, const char* izlaz);
void pregledajKonverzije();
void azurirajKonverziju(int indeks, const char* ulaz, const char* izlaz);
void izbrisiKonverziju(int indeks);

// Function prototypes for file management
void spremiKonverzijeUDatoteku(const char* nazivDatoteke);
void obrisiDatoteku(const char* nazivDatoteke);

extern Konverzija* konverzije;
extern int brojKonverzija;
extern int maxKonverzija;

#endif // HEADER_H
