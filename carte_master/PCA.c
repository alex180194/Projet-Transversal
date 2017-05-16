#include "PCA.h"

#include <c8051f020.h>    
#include <intrins.h>

void PCA_init(void){
	PCA0CN = 0x00; // on desactive le PCA par s�curit�
	PCA0MD = 0x02; //System clock divided by 4
	PCA0CPM0 = 0x82; //16 bit pulse, modulation activ�
	PCA0CPM1 = 0x82;
	PCA0CPM2 = 0x82;
	PCA0CN = 0x40;
}

void PCA(enum peripheriquesPCA perif,unsigned int valeur){
	switch(perif){
		case cervoH:
			PCA0CPL0=valeur<<8;
			PCA0CPH0=valeur;
		break;
		case cervoV:
			PCA0CPL1=valeur<<8;
			PCA0CPH1=valeur;
		break;
		case lumiere:
			PCA0CPL2=valeur<<8;
			PCA0CPH2=valeur;
		break;
		default:
		break;
	}
}