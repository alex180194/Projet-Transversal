 //TELEMETRE MESURE DE DISTANCES

 
#include <c8051f020.h>    
#include <stdio.h>
#include <intrins.h>
#include <Mesure_distance.h>
#include "gestion_trame.h"
#include "gestion_serializer.h"

int code_recup;
float Vout_tel;
unsigned int distance_avant;
unsigned int distance_arriere;

void configure_VREF(void)
{
REF0CN &= 0x0f; //on met à 0 le bit4 qui correspond a prendre VREF0 comme source de tension
REF0CN |= 0x03; //bits à 1 pour utiliser l’ADC
}

void configure_ADC0(void)
{
AMX0CF=0x00; //on selectionne le mode "single-ended"
AMX0SL = 0x01; //On prend AIN0.1 comme entrée
///ADC0CF=0x50; // on choisit GAIN=1      	
AD0LJST=0; //On utilise right justified
AD0EN=1;//on active ADC
}

//float MES_AV_AR(int dir)
//{
//	//int distance_mes;
//if (dir==1)
//{
//	AMX0SL = 0x01; //On prend AIN0.3 comme entrée
//  return MES_Dist_AV();
//}


//  AMX0SL = 0x00; //On prend AIN0.0 comme entrée
//	return MES_Dist_AR();

//}

void acquisition_ADC0(void)
{
	unsigned int adc_code;
	AMX0SL = 0x01;
	AD0INT=0;//Ce drapeau doit être mis à 0 de facon logicielle
	AD0BUSY=1;//on lance une conversion
	while(AD0INT!=1)//tant que la conversion n est pas finie
	{
	//on attend
	}
//la conversion est finie on doit retourner cette valeur qu on recupère dans ADC0H et ADC0L

	adc_code=(ADC0H*256) + ADC0L;
	distance_avant=(2.400*(float)adc_code)/4096.0;
	distance_avant=(53.528/(distance_avant+0.004));
	
	AMX0SL = 0x00;
	AD0INT=0;//Ce drapeau doit être mis à 0 de facon logicielle
	AD0BUSY=1;//on lance une conversion
	while(AD0INT!=1)//tant que la conversion n est pas finie
	{
	//on attend
	}
//la conversion est finie on doit retourner cette valeur qu on recupère dans ADC0H et ADC0L

	adc_code=(ADC0H*256) + ADC0L;
	distance_arriere=(2.400*(float)adc_code)/4096.0;
	distance_arriere=(53.528/(distance_arriere +0.004));
}

void gestion_telemeres(void){
	acquisition_ADC0();
	if(distance_avant<30||distance_arriere<30){
		out_M1.Etat_Mouvement=Stopper;
	}
}

// float mesure_distance_avant(void){
//	
//code_recup=ACQ_ADC();
//Vout_tel=(2.400*(float)code_recup)/4096.0;
//distance=(53.528/(Vout_tel+0.004));
//	
//if(distance>150) //On ne peut pas mesurer si la distance est supÈrieur a 150 cm
//{
//distance=0;
//}
//if (distance<20)
//{
//	distance=0;
//}
//return distance; // AIN0.3 A31
//}

//float mesure_avant_arriere(void){
//	
//code_recup=ACQ_ADC();
//Vout_tel=(2.400*(float)code_recup)/4096.0;
//distance=(53.528/(Vout_tel+0.004));
//	
//if(distance>150) //On ne peut pas mesurer si la distance est supÈrieur a 150 cm
//{
//distance=0;
//}
//if (distance<20)
//{
//	distance=0;
//}
//return distance; // AIN0.0 A32  
//}

//void Gestion_Vitesse(void){
//if (MES_AV_AR(1)<30 && MES_AV_AR(1)>20)
//{ out_M1.Vitesse=0;
//}
//if (MES_AV_AR(0)<30 && MES_AV_AR(0)>20)
//{ out_M1.Vitesse=0;
//}
//}
