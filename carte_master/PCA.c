#include "PCA.h"

#include <c8051f020.h>    
#include <intrins.h>

void PCA_init(void){
	PCA0CN = 0x00; // on desactive le PCA par sécurité
	PCA0MD = 0x08; //System clock
	PCA0CPM0 = 0x82; //16 bit pulse, modulation activé
	PCA0CPM1 = 0x82;
	PCA0CPM2 = 0x82;
	PCA0CN = 0x40;
}

void PCA(enum peripheriquesPCA perif,unsigned int valeur){
	switch(perif){
		case cervoH:
			PCA0CPL0= (unsigned char) valeur>>8;
			PCA0CPH0= (unsigned char) valeur;
		break;
		case cervoV:
			PCA0CPL1= (unsigned char) valeur>>8;
			PCA0CPH1= (unsigned char) valeur;
		break;
		case lumiere:
			PCA0CPL2=valeur<<8;
			PCA0CPH2=valeur;
		break;
		default:
		break;
	}
}