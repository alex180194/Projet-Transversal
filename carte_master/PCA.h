#ifndef PCA_H
#define PCA_H

enum peripheriquesPCA{cervoH,cervoV,lumiere};

void PCA_init(void);
void PCA(enum peripheriquesPCA perif,unsigned int valeur);

#endif