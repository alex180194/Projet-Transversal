#include "servomoteurs.h"
#include "gestion_trame.h"
#include "PCA.h"

void gestion_servos(void){
	unsigned int angle;
	if(out_M1.Etat_Servo==Servo_H){
		angle=(unsigned int) 0xffff-(600+10*(out_M1.Servo_Angle+90)*22)/4;
		PCA(cervoH,angle);
	}
	else{
		if(out_M1.Etat_Servo==Servo_V){
			angle=(unsigned int) 0xffff-(600+10*(out_M1.Servo_Angle+90)*22)/4;
			PCA(cervoV,angle);
		}
	}
	out_M1.Etat_Servo=Servo_non;
	out_M1.Servo_Angle=0;
}