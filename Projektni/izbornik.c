#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "functions.h"

static int brojKontakata = 0;

int izbornik(const char* const ime) {

	printf("\t\t_____________________________________________\n\n");
	printf("\t\tOdaberite jednu od ponudenih opcija: \n\n");
	printf("\t\t_____________________________________________\n\n");

	printf("\t\tOpcija 1: Kreiranje datoteke\n");
	printf("\t\tOpcija 2: Dodavanje kontakta\n");
	printf("\t\tOpcija 3: Ucitaj sve kontakte\n");
	printf("\t\tOpcija 4: Ispisi podatke o svim kontaktima\n");
	printf("\t\tOpcija 5: Pretrazivanje kontakata po ID-u\n");
	printf("\t\tOpcija 6: Uredivanje kontakta\n");
	printf("\t\tOpcija 7: Brisanje kontakta\n");
	printf("\t\tOpcija 8: Izlaz iz programa\n\n");


	printf("\t\t_____________________________________________\n\n");

	int odgovor = 0;

	static KONTAKT* poljeKontakta = NULL;
	static KONTAKT* pronadeniKontakt = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) {
	case 1:
		kreiranjeDatoteke(ime);
		break;
	case 2:
		dodajKontakt(ime);
		break;
	case 3:
		if (poljeKontakta != NULL) {
			free(poljeKontakta);
			poljeKontakta = NULL;
		}

		poljeKontakta = (KONTAKT*)ucitajKontakte(ime);

		if (poljeKontakta == NULL) {
			exit(EXIT_FAILURE);
		}
		break;
	case 4:
		ispisiSveKontakte(poljeKontakta);
		break;
	case 5:
		pronadeniKontakt = (KONTAKT*)pretraziKontakte(poljeKontakta);

		if (pronadeniKontakt != NULL) {
			printf("ID: %d\n", pronadeniKontakt->id);
			printf("Ime: %s\n", pronadeniKontakt->ime);
			printf("Prezime: %s\n", pronadeniKontakt->prezime);
			printf("Adresa: %s\n", pronadeniKontakt->adresa);
			printf("Broj mobitela: %s\n", pronadeniKontakt->brojMobitela);
		}
		else {
			printf("Ne postoji clan s tim ID-em.\n");
		}

		break;
	case 6:
		odgovor = izlazIzPrograma(poljeKontakta);
		break;
	default:
		odgovor = 0;
	}

	return odgovor;
}
