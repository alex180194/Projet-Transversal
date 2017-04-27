// TELEMETRE MESURE DE DISTANCES

 
#include <c8051f020.h>    
#include <stdio.h>
#include <intrins.h>
#include <Mesure_distance.h>

int adc_code;
int code_recup;
float Vout_tel;
float distance;

void CFG_VREF(void)
{
REF0CN &= 0x0f; //on met ‡ 0 le bit4 qui correspond a prendre VREF0 comme source de tension
REF0CN |= 0x03; //bits ‡ 1 pour utiliser líADC
}

void CFG_ADC0(void)
{
AMX0CF=0x00; //on selectionne le mode "single-ended"
AMX0SL = 0x03; //On prend AIN0.3 comme entrÈe
///ADC0CF=0x50; // on choisit GAIN=1      	
AD0LJST=0; //On utilise right justified
AD0EN=1;//on active ADC
}

float MES_AV_AR(int dir)
{
	//int distance_mes;
if (dir==1)
{
	AMX0SL = 0x03; //On prend AIN0.3 comme entrÈe
  return MES_Dist_AV();
}


  AMX0SL = 0x00; //On prend AIN0.0 comme entrÈe
	return MES_Dist_AR();

}

unsigned int ACQ_ADC(void)
{
AD0INT=0;//Ce drapeau doit Ítre mis ‡ 0 de facon logicielle
AD0BUSY=1;//on lance une conversion
while(AD0INT!=1)//tant que la conversion n est pas finie
{
//on attend
}
//la conversion est finie on doit retourner cette valeur qu on recupËre dans ADC0H et ADC0L

adc_code=(ADC0H*256) + ADC0L;
return adc_code;
}

 float MES_Dist_AV(void){
	
code_recup=ACQ_ADC();
Vout_tel=(2.400*(float)code_recup)/4096.0;
distance=(53.528/(Vout_tel+0.004));
	
if(distance>150) //On ne peut pas mesurer si la distance est sup»rieur a 150 cm
{
distance=0;
}
if (distance<20)
{
	distance=0;
}
return distance; // AIN0.3 A31
}

float MES_Dist_AR(void){
	
code_recup=ACQ_ADC();
Vout_tel=(2.400*(float)code_recup)/4096.0;
distance=(53.528/(Vout_tel+0.004));
	
if(distance>150) //On ne peut pas mesurer si la distance est sup»rieur a 150 cm
{
distance=0;
}
if (distance<20)
{
	distance=0;
}
return distance; // AIN0.0 A32  
}