#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataType.h"

int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajKontakt(const char* const);
void* ucitajKontakte(const char* const);
void ispisiSveKontakte(const KONTAKT* const);
void* pretraziKontakte(KONTAKT* const);
int izlazIzPrograma(KONTAKT*);

#endif