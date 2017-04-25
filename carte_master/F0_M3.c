#include <c8051f020.h>    
#include <intrins.h>

#include "F0_M3.h"

char Angle_actuel;
unsigned char temps_deplacement;
int valeur_PCA;
int nb_pas;
int tps_us;

void Config_PCA() {   //configuration initiale du PCA

	PCA0CN = 0x00;    // on desactive le PCA par sécurité
	
	PCA0CPM0 = 0xC2;  //16 bit pulse, comparateur et modulation sont activés activé
	PCA0MD = 0x02;    //on utilise la SYSCLK comme base de temps

	PCA0L = 0x00;     //initialisation du timer
	PCA0H = 0x00;

}

unsigned char CDE_servo_Horizontal (char Angle) {		
	
	temps_deplacement = 1;
		
		
	if(Angle >= -90 && Angle <= 90) {
		tps_us = 600+10*(Angle+90);  //si l'angle rentré est correct, on effectue une rotation selon l'angle souhaité que l'on convertit en durée
	}
	else {
		tps_us = 600;                //si l'angle est hors de l'intervalle on se place a la position 0
	}

	nb_pas = (tps_us*22.1184)/4;
	valeur_PCA = 65536-nb_pas; 
	PCA0CPL0 = valeur_PCA; 
	valeur_PCA = valeur_PCA >> 8;
	PCA0CPH0 = valeur_PCA;
	PCA0CN = 0x40;

	temps_deplacement += (0.3*Angle);
	Angle_actuel = Angle;

	return temps_deplacement;        //retourne le temps de déplacement en centième de secondes

}