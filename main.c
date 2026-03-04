#include "header.h"

int main()
{
    tDistancia* emb;
    int ce=0;
    consolidarArchivos("posicionesA.csv","posicionesB.csv","posicionesFinal.csv");
    emb=procesarDistancias("posicionesFinal.csv",&ce);
    mostrarDistancias(emb,ce);
    free(emb);
    mostrar5EmbarcacionesMasKM("posicionesFinal.csv");

    return 0;
}

