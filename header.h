#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM_MAT 9
#define MAX_EMB 10
#define MAX_LINE 1024
#define RADIO_TIERRA_KM 6371

typedef struct
{
    long fechaHora;
    char matricula[TAM_MAT];
    double latitud;
    double longitud;
}tPos;

typedef struct
{
    char matricula[TAM_MAT];
    float distancia;
    double latitud;
    double longitud;
}tDistancia;

FILE* abrirArchivo(const char* arch,const char* tipo);

void consolidarArchivos(const char* arch1, const char* arch2,const char* arch3);
tDistancia* procesarDistancias(const char* arch,int* cantEmb);
double calcularDistancia(double latitud1, double longitud1, double latitud2, double longitud2);
void mostrarDistancias(const tDistancia* embarcaciones, int ce);
void mostrar5EmbarcacionesMasKM(const char* arch);

void ordenar(tDistancia* embarcaciones, int n);
void ordenar2(tDistancia* emb, int n);

tDistancia* buscarMayor(tDistancia* ini, tDistancia* fin);
void intercambiar(void*x, void*y,size_t tamElem);


#endif // HEADER_H_INCLUDED
