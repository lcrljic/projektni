#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dataType.h"
#include "functions.h"

static int brojKontakata = 0;

void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "wb");

	if (fp == NULL) {
		perror("Kreiranje datoteke kontakti.bin");
		exit(EXIT_FAILURE);
	}

	fwrite(&brojKontakata, sizeof(int), 1, fp);

	printf("Kreirana datoteka kontakti.bin\n\n");
	fclose(fp);

}

void dodajKontakt(const char* const ime) {

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Dodavanje kontakta u datoteku kontakti.bin");
		exit(EXIT_FAILURE);
	}

	fread(&brojKontakata, sizeof(int), 1, fp);
	printf("Broj kontakata: %d\n\n", brojKontakata);

	KONTAKT temp = { 0 };
	temp.id = brojKontakata;
	getchar();

	printf("Unesite ime kontakta: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime kontakta: ");
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite adresu kontakta: ");
	scanf("%49[^\n]", temp.adresa);
	getchar();

	printf("Unesite broj mobitela kontakta: ");
	scanf("%10[^\n]", temp.brojMobitela);


	fseek(fp, sizeof(KONTAKT) * brojKontakata, SEEK_CUR);
	fwrite(&temp, sizeof(KONTAKT), 1, fp);
	printf("Novi kontakt dodan.\n\n");

	rewind(fp);
	brojKontakata++;

	fwrite(&brojKontakata, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajKontakte(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {
		perror("Ucitavanje kontakata iz kontakti.bin");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojKontakata, sizeof(int), 1, fp);
	printf("Broj kontakata: %d\n", brojKontakata);

	KONTAKT* poljeKontakata = (KONTAKT*)calloc(brojKontakata, sizeof(KONTAKT));

	if (poljeKontakata == NULL) {
		perror("Zauzimanje memorije za studente");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeKontakata, sizeof(KONTAKT), brojKontakata, fp);

	printf("Svi kontakti uspjesno ucitani.\n\n");

	return poljeKontakata;
}

void ispisiSveKontakte(const KONTAKT* const polje) {

	if (polje == NULL) {
		printf("Polje kontakata prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojKontakata; i++) {
		printf("Kontakt broj %d\tID: %d\tIme: %s\tPrezime: %s\tAdresa: %s\tMobitel: %d\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->adresa,
			(polje + i)->brojMobitela);
	}
}

void* pretraziKontakte(KONTAKT* const polje) {

	if (polje == NULL) {
		printf("Polje kontakata prazno\n");
		return;
	}

	int i;

	int trazeniId;

	printf("Unesite ID kontakta kojeg trazite: \n");
	scanf("%d", &trazeniId);

	for (i = 0; i < brojKontakata; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("Kontakt pronaden.\n");

			return (polje + i);
		}
	}

	return NULL;
}

int izlazIzPrograma(KONTAKT* polje) {

	free(polje);

	return 0;
}