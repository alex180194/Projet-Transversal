#ifndef GESTION_TRAME_H
#define GESTION_TRAME_H
#include "structures_centrale.c"

extern OUT_M1 xdata out_M1;

void gestion_trame_init();
void commande_init(OUT_M1* out_M1);
void gestion_trame();
enum Epreuve decodeur_type_epreuve(char* str);
char switch_trame(void);

#endif