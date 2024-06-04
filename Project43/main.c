#include "header.h"

int main() {
	konverzije = malloc(maxKonverzija * sizeof(Konverzija));
	if (konverzije == NULL) {
		perror("Alokacija memorije nije uspjela.\n");
		return 1;
	}

	int izbor;
	while (1) {
		printf("\nIzbornik:\n");
		printf("1. Decimalni u Binarni\n");
		printf("2. Binarni u Decimalni\n");
		printf("3. Decimalni u Oktalni\n");
		printf("4. Oktalni u Decimalni\n");
		printf("5. Heksadecimalni u Binarni\n");
		printf("6. Binarni u Heksadecimalni\n");
		printf("7. Pregledaj konverzije\n");
		printf("8. Ažuriraj konverziju\n");
		printf("9. Izbriši konverziju\n");
		printf("10. Spremi konverzije u datoteku\n");
		printf("11. Izbriši datoteku\n");
		printf("12. Izlaz\n");
		printf("Unesite svoj izbor: ");
		scanf("%d", &izbor);

		char ulaz[100];
		char* rezultat;
		int binarniRezultat, okatalniRezultat, indeks;

		switch (izbor) {
		case 1:
			printf("Unesite decimalni broj: ");
			scanf("%s", ulaz);
			rezultat = decimalUBinarni(atoi(ulaz));
			printf("Decimalni u Binarni: %s\n", rezultat);
			dodajKonverziju("Decimalni u Binarni", ulaz, rezultat);
			free(rezultat);
			break;
		case 2:
			printf("Unesite binarni broj: ");
			scanf("%s", ulaz);
			binarniRezultat = binarniUDecimal(ulaz);
			printf("Binarni u Decimalni: %d\n", binarniRezultat);
			snprintf(ulaz, sizeof(ulaz), "%d", binarniRezultat);
			dodajKonverziju("Binarni u Decimalni", ulaz, ulaz);
			break;
		case 3:
			printf("Unesite decimalni broj: ");
			scanf("%s", ulaz);
			rezultat = decimalUOkatal(atoi(ulaz));
			printf("Decimalni u Oktalni: %s\n", rezultat);
			dodajKonverziju("Decimalni u Oktalni", ulaz, rezultat);
			free(rezultat);
			break;
		case 4:
			printf("Unesite oktalni broj: ");
			scanf("%s", ulaz);
			okatalniRezultat = okatalUDecimal(ulaz);
			printf("Oktalni u Decimalni: %d\n", okatalniRezultat);
			snprintf(ulaz, sizeof(ulaz), "%d", okatalniRezultat);
			dodajKonverziju("Oktalni u Decimalni", ulaz, ulaz);
			break;
		case 5:
			printf("Unesite heksadecimalni broj: ");
			scanf("%s", ulaz);
			rezultat = heksadecimalniUBinarni(ulaz);
			printf("Heksadecimalni u Binarni: %s\n", rezultat);
			dodajKonverziju("Heksadecimalni u Binarni", ulaz, rezultat);
			free(rezultat);
			break;
		case 6:
			printf("Unesite binarni broj: ");
			scanf("%s", ulaz);
			rezultat = binarniUHeksadecimalni(ulaz);
			printf("Binarni u Heksadecimalni: %s\n", rezultat);
			dodajKonverziju("Binarni u Heksadecimalni", ulaz, rezultat);
			free(rezultat);
			break;
		case 7:
			pregledajKonverzije();
			break;
		case 8:
			pregledajKonverzije();
			printf("Unesite indeks konverzije za ažuriranje: ");
			scanf("%d", &indeks);
			indeks--;
			printf("Unesite novi ulaz: ");
			scanf("%s", ulaz);
			rezultat = ulaz;
			if (strcmp(konverzije[indeks].vrsta, "Decimalni u Binarni") == 0) {
				rezultat = decimalUBinarni(atoi(ulaz));
			}
			else if (strcmp(konverzije[indeks].vrsta, "Binarni u Decimalni") == 0) {
				binarniRezultat = binarniUDecimal(ulaz);
				snprintf(ulaz, sizeof(ulaz), "%d", binarniRezultat);
				rezultat = ulaz;
			}
			else if (strcmp(konverzije[indeks].vrsta, "Decimalni u Oktalni") == 0) {
				rezultat = decimalUOkatal(atoi(ulaz));
			}
			else if (strcmp(konverzije[indeks].vrsta, "Oktalni u Decimalni") == 0) {
				okatalniRezultat = okatalUDecimal(ulaz);
				snprintf(ulaz, sizeof(ulaz), "%d", okatalniRezultat);
				rezultat = ulaz;
			}
			else if (strcmp(konverzije[indeks].vrsta, "Heksadecimalni u Binarni") == 0) {
				rezultat = heksadecimalniUBinarni(ulaz);
			}
			else if (strcmp(konverzije[indeks].vrsta, "Binarni u Heksadecimalni") == 0) {
				rezultat = binarniUHeksadecimalni(ulaz);
			}
			azurirajKonverziju(indeks, ulaz, rezultat);
			if (rezultat != ulaz) {
				free(rezultat);
			}
			break;
		case 9:
			pregledajKonverzije();
			printf("Unesite indeks konverzije za brisanje: ");
			scanf("%d", &indeks);
			indeks--;
			izbrisiKonverziju(indeks);
			break;
		case 10:
			spremiKonverzijeUDatoteku("konverzije.txt");
			break;
		case 11:
			obrisiDatoteku("konverzije.txt");
			break;
		case 12:
			free(konverzije);
			return 0;
		default:
			printf("Nevažeći izbor. Molimo unesite važeću opciju.\n");
		}
	}
}
