#include "UART1.h"
#include "UART0.h"
#include "gestion_trame.h"
#include "gestion_serializer.h"
#include <stdio.h>

char envoyer_message=0;
char arret=0;
char vitesseAbs=0;
enum Mouvement type_mouvement;
char xdata message[30];

void gestion_serializer(void){
	if(out_M1.Etat_Epreuve>Epreuve_non&&out_M1.Etat_Epreuve<Fin_Epreuve){
		arret=0;
		evoi_message();
	}	
	else{
		out_M1.Etat_Mouvement=Mouvement_non;
		out_M1.Vitesse=0;
		if(arret==0){
			UART1_print("stop\r");
			arret=1;
		}
	}
}

void evoi_message(void){
		if(out_M1.Vitesse!=0){
		vitesseAbs=out_M1.Vitesse;
		if(out_M1.Etat_Mouvement==Mouvement_non)
			out_M1.Etat_Mouvement=type_mouvement;
	}
	out_M1.Vitesse=0;
	if(out_M1.Etat_Mouvement!=Mouvement_non)
		type_mouvement=out_M1.Etat_Mouvement;
	switch(out_M1.Etat_Mouvement){
		case Avancer:
			sprintf(message,"mogo 1:%bd 2:%bd\r",vitesseAbs,vitesseAbs);
			UART1_print(message);
		break;
		case Stopper:
			UART1_print("stop\r");
		break;
		case Reculer:
			sprintf(message,"mogo 1:%bd 2:%bd\r",-vitesseAbs,-vitesseAbs);
			UART1_print(message);
		break;
		case Rot_90D:
			UART1_print("digo 1:2500:20 2:-2500:20\r");
		break;
		case Rot_90G:
			UART1_print("digo 1:-2500:20 2:2500:20\r");
		break;
		case Rot_180G:
			UART1_print("digo 1:-5000:20 2:5000:20\r");
		break;
		case Rot_180D:
			UART1_print("digo 1:5000:20 2:-5000:20\r");
		break;
	}
	if(out_M1.Etat_Mouvement!=Mouvement_non)
	{
		type_mouvement=out_M1.Etat_Mouvement;
		envoyer_message=1;
	}
	out_M1.Etat_Mouvement=Mouvement_non;
	envoyer_message=0;
}