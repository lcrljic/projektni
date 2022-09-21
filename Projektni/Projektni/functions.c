#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "dataType.h"
#include "functions.h"
#include <string.h>

static int brojKontakata = 0;
void kreiranjeDatoteke(const char* const ime) {

	FILE* fp = fopen(ime, "rb");

	if (fp == NULL) {

		fp = fopen(ime, "wb");
		fwrite(&brojKontakata, sizeof(int), 1, fp);

		fclose(fp);
	}
	else {
		fclose(fp);
	}
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
	temp.id = brojKontakata + 1;
	getchar();

	printf("Unesite ime kontakta: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime kontakta: ");
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite godine kontakta: ");
	scanf("%d", &temp.godine);
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
		perror("Ucitavanje kontakata iz kontakti.txt");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojKontakata, sizeof(int), 1, fp);
	printf("Broj kontakata: %d\n", brojKontakata);

	KONTAKT* poljeKontakata = (KONTAKT*)calloc(brojKontakata, sizeof(KONTAKT));

	if (poljeKontakata == NULL) {
		perror("Zauzimanje memorije za kontakte");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeKontakata, sizeof(KONTAKT), brojKontakata, fp);

	fclose(fp);

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
		printf("Kontakt broj %d\nID: %d\nIme: %s\nPrezime: %s\nGodine: %d\nAdresa: %s\nMobitel: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->godine,
			(polje + i)->adresa,
			(polje + i)->brojMobitela);
	}
}

KONTAKT* pretraziKontakte(KONTAKT* const polje) {

	if (polje == NULL) {
		printf("Polje kontakata prazno\n");
		return NULL;
	}

	int i;

	int trazeniId;

	printf("Unesite ID kontakta kojeg trazite: \n");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojKontakata) {
			printf("Kontakt s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojKontakata);

	for (i = 0; i < brojKontakata; i++) {

		if (trazeniId == (polje + i)->id) {
			printf("Kontakt pronaden.\n");

			return (polje + i);
		}
	}

	return NULL;
}

void uredivanjeKontakta(KONTAKT* polje, const char* const ime) {

	if (brojKontakata == 0) {
		printf("Polje kontakata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Azuriranje kontakata");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID kontakta kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 0 || trazeniId > brojKontakata) {
			printf("Kontakt s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 0 || trazeniId > brojKontakata);

	KONTAKT temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite ime kontakta (trenutno: %s): ", (polje + trazeniId - 1)->ime);
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime korisnika (trenutno %s): ", (polje + trazeniId - 1)->prezime);
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite godine korisnika (trenutno %d): ", (polje + trazeniId - 1)->godine);
	scanf("%d", &temp.godine);
	getchar();

	printf("Unesite adresu korisnika (trenutno %s): ", (polje + trazeniId - 1)->adresa);
	scanf("%49[^\n]", temp.adresa);
	getchar();

	printf("Unesite broj mobitela korisnika (trenutno %s): ", (polje + trazeniId - 1)->brojMobitela);
	scanf("%10[^\n]", temp.brojMobitela);

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(KONTAKT) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(KONTAKT), 1, fp);

	printf("Kontakt uspjesno azuriran\n");

	fclose(fp);
}

void brisanjeKontakta(KONTAKT* const polje, const char* const ime) {

	if (brojKontakata == 0) {
		printf("Polje kontakata prazno\n");
		return;
	}

	FILE* fp = fopen(ime, "rb+");

	if (fp == NULL) {
		perror("Brisanje kontakata");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID kontakta kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojKontakata) {
			printf("Kontakt s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojKontakata);

	KONTAKT* pomocnoPolje = (KONTAKT*)calloc(brojKontakata - 1, sizeof(KONTAKT));

	if (polje == NULL) {
		perror("Neuspjelo dinamicko zauzimanje memorije");
		exit(EXIT_FAILURE);
	}

	int c = 0;

	for (i = 0; i < brojKontakata; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + c) = *(polje + i);

			if ((pomocnoPolje + c)->id > trazeniId) {
				(pomocnoPolje + c)->id -= 1;
			}

			fwrite((pomocnoPolje + c), sizeof(KONTAKT), 1, fp);
			c++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&c, sizeof(int), 1, fp);
	fclose(fp);

	printf("Kontakt je uspjesno obrisan\n");
}

void zamjena(KONTAKT* const veci, KONTAKT* const manji) {
	KONTAKT temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void* sortitajPoGodinama(const KONTAKT* polje) {

	int min = -1;
	for (int i = 0; i < brojKontakata - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < brojKontakata; j++)
		{
			if ((polje + j)->godine < (polje + min)->godine) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	return polje;
}

void ispisiPoGodinama(const KONTAKT* polje) {

	if (polje == NULL) {
		printf("Polje kontakata prazno\n");
		return;
	}

	int i;

	polje = sortitajPoGodinama(polje);

	for (i = 0; i < brojKontakata; i++) {
		printf("Kontakt broj %d\nID: %d\nIme: %s\nPrezime: %s\nGodine: %d\nAdresa: %s\nMobitel: %s\n\n",
			i + 1,
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->godine,
			(polje + i)->adresa,
			(polje + i)->brojMobitela);
	}
}

int izlazIzPrograma(KONTAKT* polje) {

	free(polje);

	return 0;
}