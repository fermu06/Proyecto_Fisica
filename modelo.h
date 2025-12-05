#ifndef __FISICA_H__
#define __FISICA_H__
#include <stdio.h>

struct Punto{
    float x[20];
    float y[20];
    int n;
};
typedef struct Punto Punto;

void operaciones(Punto *p, int n, float *sumx, float *sumy, float *sumxy, float *sumxx);
float pendiente(Punto *p, int n);
float ordenada(Punto *p, int n);
#endif // __FISICA_H_