#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataType.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajKontakt(const char* const);
void* ucitajKontakte(const char* const);
void ispisiSveKontakte(const KONTAKT* const);
KONTAKT* pretraziKontakte(KONTAKT* const);
void uredivanjeKontakta(KONTAKT*, const char* const);
void brisanjeKontakta(KONTAKT* const, const char* const);
void ispisiPoGodinama(const KONTAKT*);
int izlazIzPrograma(KONTAKT*);

#endif