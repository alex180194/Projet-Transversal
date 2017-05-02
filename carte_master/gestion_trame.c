#include <c8051f020.h>    // SFR declarations
#include <stdio.h>
#include <stdlib.h>
#include <intrins.h>

#include "UART0.h"
#include "UART1.h"
#include "F0_M3.h"
#include "gestion_trame.h"

OUT_M1 xdata out_M1;
char xdata trame[20]="";

void gestion_trame_init(){
	char c;
	commande_init(&out_M1);
	for(c=0;c<20;c++)
		trame[c]=0;
}

/**********************************************
 * Initialisation de la structure de commande *
 **********************************************/

void commande_init(OUT_M1* out_M1) {

	out_M1->Etat_Epreuve = Epreuve_non;
	out_M1->Etat_Mouvement = Mouvement_non;
	out_M1->Vitesse = 0 ;
	out_M1->Coord_X = 0;
	out_M1->Coord_Y = 0;
	out_M1->Angle = 0;
	out_M1->Etat_ACQ_Son = ACQ_non;
	out_M1->ACQ_Duree = 0 ;
	out_M1->Etat_DCT_Obst = DCT_non;
	out_M1->Etat_Lumiere = Lumiere_non;
	out_M1->Lumiere_Intensite = 0;
	out_M1->Lumiere_Duree = 0;
//	out_M1->Lumiere_Extinction = 0;
	out_M1->Lumiere_Nbre = 0;
	out_M1->Etat_Servo = Servo_non;
	out_M1->Servo_Angle=0;

}

/**********************
 * Analyse du message *
 **********************/


void gestion_trame() {
	char c=0;
	char commande_geree=0;
	UART0_scan(trame);
	
	switch(trame[0]) {

		case 'D' : /********** D [type_épreuve] - Début de l'épreuve **********/
			out_M1.Etat_Epreuve=decodeur_type_epreuve(&trame[2]);
			commande_geree=1;
			break;

		case 'E' : /********** E - Fin de l'épreuve **********/
			out_M1.Etat_Epreuve=Fin_Epreuve;
			commande_geree=1;
			break;

		case 'Q' : /********** Q - Arrêt d'urgence **********/
			out_M1.Etat_Epreuve=Stop_Urgence;
			commande_geree=1;
			break;

		case 'T' : /********** TV vitesse - Réglage vitesse de déplacement **********/
			out_M1.Vitesse=atoi(&trame[3]);
			commande_geree=1;
			break;

		case 'A' :
			switch(trame[1]) {
				case ' ' : /********** A [vitesse] - Avancer **********/
					out_M1.Etat_Mouvement=Avancer;
					if(trame[2]!=0)
						out_M1.Vitesse=atoi(&trame[2]);
					break;
//				case 'U' : /********** AUX [] - Commandes auxiliaires **********/
//					while(c==0) {
//						c=UART0_print("Commandes aux");
//					}
//					c=0;
//					break;
//				case 'S' :
//					switch(trame[2]) { /********** ASS [durée] - Acquisition de signaux sonores **********/
//						case 'S' :
//							while(c==0) {
//								c=UART0_print("Acq signaux sonores");
//							}
//							c=0;
//							break;
					}
				commande_geree=1;
				break;
					/*switch(trame[3]) { /********** AS [H/V] - Servomoteur positionné **********
						case 'H' :
							while(c==0) {
								c=UART0_print("servoH positionné");
							}
							c=0;
							break;
						case 'V' :
							while(c==0) {
								c=UART0_print("servoV positionné");
							}
							c=0;
							break;
					}*/
//			}

		case 'B' : /********** B [vitesse] - Reculer **********/
			out_M1.Etat_Mouvement=Reculer;
					if(trame[2]!=0)
						out_M1.Vitesse=atoi(&trame[2]);
					commande_geree=1;
			break;

		case 'S' :
			switch(trame[1]) {
				case ' ' : /********** S - STOP - Fin des commandes de déplacement A et B de la base roulante **********/
					out_M1.Etat_Mouvement=Stopper;
					commande_geree=1;
					break;
//				case 'D' : /********** SD [F:code_fréquence] [P:durée_son] [W:durée_silence] [B:nombre_bips] - Génération de signaux sonores **********/
//					while(c==0) {
//						c=UART0_print("Géné signaux sonores");
//					}
//					c=0;
//					break;
//				case 'P' : /********** SPH - Arrêt de la prise de photoraphie en continue **********/
//					while(c==0) {
//						c=UART0_print("Arrêt photo continue");
//					}
//					c=0;
//					break;
			}
		break;

		case 'R' : /********** Rotations **********/
			switch(trame[1]) {
				case 'D' : /********** RD - Rotation à droite de 90° **********/
					out_M1.Etat_Mouvement=Rot_90D;
					commande_geree=1;
					break;
				case 'G' : /********** RG - Rotation à gauche de 90° **********/
					out_M1.Etat_Mouvement=Rot_90G;
					commande_geree=1;
					break;
//				case 'A' : /********** RA sens:valeur - Rotation de la base roulante d'un angle donné **********/
//					out_M1.Angle=0;
//					commande_geree=1;
//					break;
				case 'C' : /********** RC [D/G] - Rotation complète de la base roulante de 180° **********/
					switch(trame[3]) {
						case 'D' :
							out_M1.Etat_Mouvement=Rot_180D;
							commande_geree=1;
							break;
						case 'G' :
							out_M1.Etat_Mouvement=Rot_180G;
							commande_geree=1;
							break;
					}
					break;
			}
			break;

//		case 'G' : /********** G X:valeur_x Y:valeur_y A:angle - Déplacement de la base roulante par coordonnées **********/
//			while(c==0) {
//				c=UART0_print("Dpt base par coord");
//			}
//			c=0;
//			break;

//		case 'M' :
//			switch(trame[1]) {
//				case 'I' : /********** MI - Mesure de courant **********/
//					while(c==0) {
//						c=UART0_print("Mesure de courant");
//					}
//					c=0;
//					break;
//				case 'E' : /********** ME - Mesure d'énergie **********/
//					while(c==0) {
//						c=UART0_print("Mesure d'énergie");
//					}
//					c=0;
//					break;
//				case 'O' :
//					switch(trame[2]) {
//						case 'U' : /********** MOU [D] - Détection d'obstacle unique **********/
//							while(c==0) {
//								c=UART0_print("Détec obst unique");
//							}
//							c=0;
//							break;
//						case 'B' : /********** MOB [D] [A:résolution_angulaire] - Détection des obstacles par balayage **********/
//							while(c==0) {
//								c=UART0_print("Détec obst balayage");
//							}
//							c=0;
//							break;
//					}
//			}

//		case 'I' : /********** IPO X:valeur_x Y:valeur_y A:angle - Initialisation de la position de la base roulante **********/
//			while(c==0) {
//				c=UART0_print("I");
//			}
//			c=0;
//			break;
			/*switch(trame[1]) {
				case ' ' : /********** I [chaine_de_caractères] - Invite de commande **********
					while(c==0) {
						c=UART0_print("Invite de commande");
					}
					c=0;
					break;
				case 'A' : /********** IA [chaine_de_caractères] - Informations auxiliaires **********
					while(c==0) {
						c=UART0_print("Informations aux");
					}
					c=0;
					break;
				case 'E' :
					while(c==0) {
						c=UART0_print("Init pos base roul");
					}
					c=0;
					break;
			}*/

//		case 'P' :
//			switch(trame[1]) {
//				case 'O' : /********** POS - Position de la base roulante **********/
//					while(c==0) {
//						c=UART0_print("Pos base roulante");
//					}
//					c=0;
//					break;
//				case 'P' : /********** PPH [O/C/S] [E:Durée] [N:Nombre] - Prise de photographie **********/
//					while(c==0) {
//						c=UART0_print("Prise photographie");
//					}
//					c=0;
//					break;
//			}

//		case 'L' :
//			switch(trame[1]) {
//				case ' ' : /********** L [I:Intensité] [D:Durée] [E:Durée] [N:Nombre] - Allumage du pointeur lumineux **********/
//					while(c==0) {
//						c=UART0_print("Allum ptr lumi");
//					}
//					c=0;
//					break;
//				case 'S' : /********** LS - Fin de l'allumage du pointeur lumineux **********/
//					while(c==0) {
//						c=UART0_print("Fin allum ptr lumi");
//					}
//					c=0;
//					break;
//			}

		case 'C' : /********** CS [H/V] [A:Angle] - Pilotage du servomoteur **********/
			switch(trame[3]) {
				case 'H' : /********** Pilotage du servomoteur horizontal **********/
					out_M1.Etat_Servo=Servo_H;
					if(trame[5]!=0)
						out_M1.Servo_Angle=atoi(&trame[5]);
					commande_geree=1;
					break;
				case 'V' : /********** Pilotage du servomoteur vertical **********/
					out_M1.Etat_Servo=Servo_V;
					if(trame[5]!=0)
						out_M1.Servo_Angle=atoi(&trame[5]);
					commande_geree=1;
					break;
					default:
						if(trame[3]!=0){
							out_M1.Servo_Angle=atoi(&trame[3]);
							commande_geree=1;
						}
					break;
			}
			

		case 0 :
			while(c==0) {
				c=UART0_print("");
			}
			commande_geree=1;
			break;
			default:
			commande_geree=0;
			break;
		}
				c=0;
	if(commande_geree==0){
		while(c==0)
				c=UART0_print("\r\n#");
}
	else{
		while(c==0&&trame[0]!=0)
					c=UART0_print("\r\n>");
	}
			
	for(c=0;c<20;c++)
		trame[c]=0;
}

void switch_trame(void){
	
}

enum Epreuve decodeur_type_epreuve(char* str){
	char c= atoi(str);
	switch(c){
		case 0:
			return Epreuve_non;
		break;
		case 1:
			return epreuve1;
		break;
		case 2:
			return epreuve2;
		break;
		case 3:
			return epreuve3;
		break;
		case 4:
			return epreuve4;
		break;
		case 5:
			return epreuve5;
		break;
		case 6:
			return epreuve6;
		break;
		case 7:
			return epreuve7;
		break;
		case 8:
			return epreuve8;
		break;
		default:
			return Epreuve_non;
		break;
	}
}
