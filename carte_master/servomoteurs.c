#include "servomoteurs.h"
#include "gestion_trame.h"
#include "PCA.h"

void gestion_servos(void){
	float fangle;
	unsigned int angle;
	if(out_M1.Etat_Servo==Servo_H){
		fangle=65535.0f-(600.0f+10.0f*(out_M1.Servo_Angle+90.0f))*65535.0f/750000.0f;
		angle=(unsigned int) fangle;
		PCA(cervoH,angle);
	}
	else{
		if(out_M1.Etat_Servo==Servo_V){
			fangle=65535.0f-(600.0f+10.0f*(out_M1.Servo_Angle+90.0f))*65535.0f/750000.0f;
			angle=(unsigned int) fangle;
			PCA(cervoV,angle);
		}
	}
	out_M1.Etat_Servo=Servo_non;
	out_M1.Servo_Angle=0;
}