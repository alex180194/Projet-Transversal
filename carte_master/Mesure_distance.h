#ifndef Mesure_distance_H_
#define Mesure_distance_H_

void configure_VREF(void);
void configure_ADC0(void);
float mesure_avant_arriere(int dir);
void acquisition_ADC0(void);
void gestion_telemeres(void);
float mesure_distance_avant(void);
float MES_Dist_AR(void);
void Gestion_Vitesse(void);

#endif
