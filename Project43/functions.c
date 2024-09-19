#include "header.h"

// Global variables
Konverzija* konverzije;
int brojKonverzija = 0;
int maxKonverzija = 10;

// Function implementations
void dodajKonverziju(const char* vrsta, const char* ulaz, const char* rezultat) {
	if (brojKonverzija >= maxKonverzija) {
		maxKonverzija *= 2;
		konverzije = realloc(konverzije, maxKonverzija * sizeof(Konverzija));
		if (konverzije == NULL) {
			perror("Realokacija memorije nije uspjela.\n");
			exit(1);
		}
	}

	strcpy(konverzije[brojKonverzija].vrsta, vrsta);
	strcpy(konverzije[brojKonverzija].ulaz, ulaz);
	strcpy(konverzije[brojKonverzija].izlaz, rezultat);
	brojKonverzija++;
}

void pregledajKonverzije() {
	if (brojKonverzija == 0) {
		printf("Nema konverzija za prikaz.\n");
		return;
	}
	for (int i = 0; i < brojKonverzija; i++) {
		printf("%d. %s: %s -> %s\n", i + 1, konverzije[i].vrsta, konverzije[i].ulaz, konverzije[i].izlaz);
	}
}

int usporediKonverzije(const void* a, const void* b) {
	Konverzija* konverzijaA = (Konverzija*)a;
	Konverzija* konverzijaB = (Konverzija*)b;
	return strcmp(konverzijaA->vrsta, konverzijaB->vrsta);
}

void sortirajPoKategoriji() {
	if (brojKonverzija == 0) {
		printf("Nema dostupnih konverzija za sortiranje.\n");
		return;
	}	qsort(konverzije, brojKonverzija, sizeof(Konverzija), usporediKonverzije);

	printf("Konverzije su sortirane po kategoriji.\n");
}

void azurirajKonverziju(int indeks, const char* noviUlaz) {
	if (indeks < 0 || indeks >= brojKonverzija) {
		printf("Nevažeći indeks.\n");
		return;
	}

	// Ažuriraj ulaz
	strcpy(konverzije[indeks].ulaz, noviUlaz);

	// Ažuriraj izlaz (rezultat) na temelju vrste konverzije
	char* noviIzlaz = NULL;
	if (strcmp(konverzije[indeks].vrsta, "Decimalni u Binarni") == 0) {
		noviIzlaz = decimalUBinarni(atoi(noviUlaz));
	}
	else if (strcmp(konverzije[indeks].vrsta, "Binarni u Decimalni") == 0) {
		int decimalniRezultat = binarniUDecimal(noviUlaz);
		snprintf(konverzije[indeks].izlaz, sizeof(konverzije[indeks].izlaz), "%d", decimalniRezultat);
		return;  // Nije potrebna dinamička memorija
	}
	else if (strcmp(konverzije[indeks].vrsta, "Decimalni u Oktalni") == 0) {
		noviIzlaz = decimalUOkatal(atoi(noviUlaz));
	}
	else if (strcmp(konverzije[indeks].vrsta, "Oktalni u Decimalni") == 0) {
		int decimalniRezultat = okatalUDecimal(noviUlaz);
		snprintf(konverzije[indeks].izlaz, sizeof(konverzije[indeks].izlaz), "%d", decimalniRezultat);
		return;  // Nije potrebna dinamička memorija
	}
	else if (strcmp(konverzije[indeks].vrsta, "Heksadecimalni u Binarni") == 0) {
		noviIzlaz = heksadecimalniUBinarni(noviUlaz);
	}
	else if (strcmp(konverzije[indeks].vrsta, "Binarni u Heksadecimalni") == 0) {
		noviIzlaz = binarniUHeksadecimalni(noviUlaz);
	}
	else {
		printf("Nepoznata vrsta konverzije.\n");
		return;
	}

	// Ažuriraj izlaz
	strcpy(konverzije[indeks].izlaz, noviIzlaz);

	// Oslobodi memoriju ako je izlaz dinamički alociran
	free(noviIzlaz);

	printf("Konverzija uspješno ažurirana.\n");
}


void pretraziKonverzije(const char* vrstaPretrage) {
	int pronadeno = 0;
	for (int i = 0; i < brojKonverzija; i++) {
		if (strcmp(konverzije[i].vrsta, vrstaPretrage) == 0) {
			printf("%d. %s: %s -> %s\n", i + 1, konverzije[i].vrsta, konverzije[i].ulaz, konverzije[i].izlaz);
			pronadeno = 1;
		}
	}
	if (!pronadeno) {
		printf("Nema konverzija za vrstu: %s\n", vrstaPretrage);
	}
}
//void inicijalizirajKonverzije(const char* nazivDatoteke) {
	//FILE* file = fopen(nazivDatoteke, "r");
//	if (file != NULL) {
		// Ako datoteka postoji, učitaj konverzije iz nje
//		KonverzijeIzDatoteke(nazivDatoteke);
	//	fclose(file);
//	}
	//else {
		// Ako datoteka ne postoji, samo nastavi (možete napraviti i inicijalizaciju prazne datoteke ako želite)
	//	printf("Datoteka %s ne postoji. Početna inicijalizacija...\n", nazivDatoteke);
//	}
//}

void izbrisiKonverziju(int indeks) {
	if (indeks < 0 || indeks >= brojKonverzija) {
		printf("Nevažeći indeks.\n");
		return;
	}
	for (int i = indeks; i < brojKonverzija - 1; i++) {
		konverzije[i] = konverzije[i + 1];
	}
	brojKonverzija--;
}

char* _strrev(char* str) {
	int i = 0;
	int j = strlen(str) - 1;
	while (i < j) {
		char c = str[i];
		str[i] = str[j];
		str[j] = c;
		i++;
		j--;
	}
}

char* decimalUBinarni(int decimal) {
	char* binarni = (char*)malloc(33);
	if (binarni == NULL) {
		printf("Alokacija memorije nije uspjela.\n");
		exit(1);
	}
	int i = 0;
	while (decimal) {
		binarni[i++] = '0' + (decimal & 1);
		decimal >>= 1;
	}
	binarni[i] = '\0';
	_strrev(binarni);
	return binarni;
}

int binarniUDecimal(char binarni[]) {
	int decimal = 0;
	int duljina = strlen(binarni);
	for (int i = 0; i < duljina; i++) {
		decimal = decimal * 2 + (binarni[i] - '0');
	}
	return decimal;
}

char* decimalUOkatal(int decimal) {
	char* okatal = (char*)malloc(12);
	if (okatal == NULL) {
		printf("Alokacija memorije nije uspjela.\n");
		exit(1);
	}
	sprintf(okatal, "%o", decimal);
	return okatal;
}

int okatalUDecimal(char okatal[]) {
	int decimal = 0;
	int duljina = strlen(okatal);
	for (int i = 0; i < duljina; i++) {
		decimal = decimal * 8 + (okatal[i] - '0');
	}
	return decimal;
}

char* heksadecimalniUBinarni(char hex[]) {
	unsigned int hexNum;
	sscanf(hex, "%x", &hexNum);
	char binarni[33] = "";
	int i = 0;
	while (hexNum) {
		binarni[i++] = '0' + hexNum % 2;
		hexNum /= 2;
	}
	binarni[i] = '\0';
	_strrev(binarni);
	return _strdup(binarni);
}

char* binarniUHeksadecimalni(char binarni[]) {
	int duljina = strlen(binarni);
	int padding = (4 - (duljina % 4)) % 4;
	char popunjeniBinarni[129];
	memset(popunjeniBinarni, '0', padding);
	strcpy(popunjeniBinarni + padding, binarni);

	char* binarniHexZnakovi[] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
	 "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };
	char heksadecimalni[33] = ""; // Alociraj prostor za 32-znamenkasti heksadecimalni niz

	for (int i = 0; i < duljina + padding; i += 4) {
		char grupa[5];
		strncpy(grupa, popunjeniBinarni + i, 4);
		grupa[4] = '\0';

		for (int j = 0; j < 16; j++) {
			if (strcmp(grupa, binarniHexZnakovi[j]) == 0) {
				char hexZnak[2];
				sprintf(hexZnak, "%X", j);
				strcat(heksadecimalni, hexZnak);
				break;
			}
		}
	}

	return _strdup(heksadecimalni);
}
void spremiKonverzijeUDatoteku(const char* nazivDatoteke) {
	FILE* file = fopen(nazivDatoteke, "w");
	if (file == NULL) {
		printf("Greška pri otvaranju datoteke za pisanje.\n");
		return;
	}

	long currentPos = ftell(file); // Get the current position of the file pointer

	for (int i = 0; i < brojKonverzija; i++) {
		fprintf(file, "%s: %s -> %s\n", konverzije[i].vrsta, konverzije[i].ulaz, konverzije[i].izlaz);
	}

	fseek(file, currentPos, SEEK_SET); // Move the file pointer to the previously saved position
	rewind(file); // Move the file pointer to the beginning of the file

	fclose(file);
	printf("Konverzije su spremljene u datoteku %s\n", nazivDatoteke);
}

void obrisiDatoteku(const char* nazivDatoteke) {
	if (remove(nazivDatoteke) == 0) {
		printf("Datoteka %s je uspješno obrisana.\n", nazivDatoteke);
	}
	else {
		printf("Greška pri brisanju datoteke %s.\n", nazivDatoteke);
	}
}
