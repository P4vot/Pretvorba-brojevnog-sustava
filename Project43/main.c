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
        printf("12. Sortiraj po kategoriji\n");  
        printf("13. Pretraži konverzije\n"); 
        printf("14. Učitaj konverzije iz datoteke\n");
        printf("15. Izlaz\n");
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
            azurirajKonverziju(indeks,ulaz,2 );
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
            sortirajPoKategoriji();  
            break;
        case 13:
            printf("Unesite vrstu konverzije za pretragu (npr. 'Decimalni u Binarni'): ");
            scanf(" %[^\n]", ulaz);  // Unesi cijeli redak
            pretraziKonverzije(ulaz);
            break;
      //      printf("Unesite naziv datoteke za učitavanje: ");
        //    scanf(" %[^\n]", ulaz);  // Unesi cijeli redak
        //    KonverzijeIzDatoteke(ulaz);
         //   break;
        case 15:
            free(konverzije);
            return 0;
        default:
            printf("Nevažeći izbor. Molimo unesite važeću opciju.\n");
        }
    }
}
