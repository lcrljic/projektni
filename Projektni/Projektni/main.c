#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "dataType.h"

int main(void) {

    int odgovor = 1;

    char* datoteka = "kontakti.bin";

    while (odgovor) {
        odgovor = izbornik(datoteka);
    }

    printf("Kraj programa");

    return 0;
}