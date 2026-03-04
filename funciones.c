#include "header.h"

FILE* abrirArchivo(const char* arch,const char* tipo)
{
    FILE*pf=fopen(arch,tipo);
    if(pf==NULL)
    {
        printf("Error al abrir el archivo %s",arch);
        return NULL;
    }
    return pf;
}

void consolidarArchivos(const char* arch1, const char* arch2,const char* arch3)
{
    FILE*pfA=abrirArchivo(arch1,"rt");
    FILE*pfB=abrirArchivo(arch2,"rt");
    if(pfB==NULL) fclose(pfA);
    FILE*pfFinal=abrirArchivo(arch3,"wt");
    if(pfFinal==NULL)
    {
        fclose(pfA);
        fclose(pfB);
    }

    tPos posA,posB;

    fscanf(pfA,"%ld,%[^,],%lf,%lf\n",&posA.fechaHora,posA.matricula,&posA.latitud,&posA.longitud);
    fscanf(pfB,"%ld,%[^,],%lf,%lf\n",&posB.fechaHora,posB.matricula,&posB.latitud,&posB.longitud);

    while(!feof(pfA) && !feof(pfB))
    {
        if(posA.fechaHora>posB.fechaHora)
        {
            fprintf(pfFinal,"%ld,%8s,%lf,%lf\n",posB.fechaHora,posB.matricula,posB.latitud,posB.longitud);
            fscanf(pfB,"%ld,%[^,],%lf,%lf\n",&posB.fechaHora,posB.matricula,&posB.latitud,&posB.longitud);
        }
        if(posA.fechaHora<posB.fechaHora)
        {
            fprintf(pfFinal,"%ld,%8s,%lf,%lf\n",posA.fechaHora,posA.matricula,posA.latitud,posA.longitud);
            fscanf(pfA,"%ld,%[^,],%lf,%lf\n",&posA.fechaHora,posA.matricula,&posA.latitud,&posA.longitud);
        }
        if(posA.fechaHora==posB.fechaHora)
        {
            if(strcmp(posA.matricula,posB.matricula)==0)
            {
                fprintf(pfFinal,"%ld,%8s,%lf,%lf\n",posB.fechaHora,posB.matricula,posB.latitud,posB.longitud);
            }
            else
            {
                fprintf(pfFinal,"%ld,%8s,%lf,%lf\n",posA.fechaHora,posA.matricula,posA.latitud,posA.longitud);
                fprintf(pfFinal,"%ld,%8s,%lf,%lf\n",posB.fechaHora,posB.matricula,posB.latitud,posB.longitud);

            }
            fscanf(pfB,"%ld,%[^,],%lf,%lf\n",&posB.fechaHora,posB.matricula,&posB.latitud,&posB.longitud);
            fscanf(pfA,"%ld,%[^,],%lf,%lf\n",&posA.fechaHora,posA.matricula,&posA.latitud,&posA.longitud);

        }
    }

    while(!feof(pfA))
    {
        fprintf(pfFinal,"%ld,%8s,%lf,%lf\n",posA.fechaHora,posA.matricula,posA.latitud,posA.longitud);
        fscanf(pfA,"%ld,%[^,],%lf,%lf\n",&posA.fechaHora,posA.matricula,&posA.latitud,&posA.longitud);
    }

    while(!feof(pfB))
    {
        fprintf(pfFinal,"%ld,%8s,%lf,%lf\n",posB.fechaHora,posB.matricula,posB.latitud,posB.longitud);
        fscanf(pfB,"%ld,%[^,],%lf,%lf\n",&posB.fechaHora,posB.matricula,&posB.latitud,&posB.longitud);
    }

    fclose(pfA);
    fclose(pfB);
    fclose(pfFinal);

    printf("El archivo %s con las posiciones consolidadas fue creado con exito.\n\n",arch3);
}

tDistancia* procesarDistancias(const char* arch,int* cantEmb)
{
    FILE* pf=fopen(arch,"rt");
    if(pf==NULL)
    {
        printf("Error al abrir el archivo %s",arch);
        return 0;
    }

    // Puntero para realizar el seguimiento de las posiciones anteriores de cada embarcación
    tDistancia *embarcaciones=malloc(MAX_EMB*sizeof(tDistancia));
    if (embarcaciones == NULL)
    {
        printf("Error al asignar memoria para embarcaciones.");
        fclose(pf);
        return 0;
    }

    tDistancia *IniEmbarcacion=embarcaciones;

    tPos pos_actual;
    char linea[MAX_LINE];
    float distancia=0;
    int i;


    // Inicializa todas las matrículas en las estructuras embarcaciones
    for (i = 0; i < MAX_EMB; i++)
    {
        strcpy(embarcaciones->matricula, "");
        embarcaciones++;
    }

    //Lee cada linea del codigo y separa los datos de la linea
    while(fgets(linea,MAX_LINE,pf)!=NULL)
    {
        distancia=0;
        embarcaciones=IniEmbarcacion;
        sscanf(linea,"%ld,%[^,],%lf,%lf\n",&pos_actual.fechaHora, pos_actual.matricula, &pos_actual.latitud, &pos_actual.longitud);

        //Busca la embarcacion en mi array de embarcaciones/distancias
        for(i=0; i<MAX_EMB; i++)
        {
            if(strcmp(pos_actual.matricula,embarcaciones->matricula)==0) //sale cuando la matricula actual es igual a la de embarcaciones/distancias
            {
                distancia += calcularDistancia(embarcaciones->latitud, embarcaciones->longitud, pos_actual.latitud, pos_actual.longitud);
                embarcaciones->distancia += distancia;
                embarcaciones->latitud = pos_actual.latitud;
                embarcaciones->longitud = pos_actual.longitud;
                break;
            }

            if (strcmp(embarcaciones->matricula, "") == 0)
            {
                strcpy(embarcaciones->matricula, pos_actual.matricula); // Copiar la matricula en la primera dirección VACIA del vector de estructuras embarcaciones
                embarcaciones->latitud = pos_actual.latitud;
                embarcaciones->longitud = pos_actual.longitud;
                embarcaciones->distancia = 0;
                (*cantEmb)++;
                break;
            }

            embarcaciones++;
        }
    }

    embarcaciones=IniEmbarcacion;

    fclose(pf);
    return(embarcaciones);
}

void mostrarDistancias(const tDistancia* embarcaciones,int ce)
{
    int j=0;
    printf("----- RECORRIDO DE LAS EMBARCACIONES -----\n");
    while(j<ce)
    {
        printf("Distancia recorrida por la embarcacion %s: %.3f km\n", embarcaciones->matricula, embarcaciones->distancia);
        j++;
        embarcaciones++;
    }
}

double calcularDistancia(double latitud1, double longitud1, double latitud2, double longitud2)
{
    // Convertir las coordenadas de grados a radianes
    double latitud_radianes1 = latitud1 * M_PI / 180.0;
    double longitud_radianes1 = longitud1 * M_PI / 180.0;
    double latitud_radianes2 = latitud2 * M_PI / 180.0;
    double longitud_radianes2 = longitud2 * M_PI / 180.0;

    // Calcular la diferencia de latitud y longitud
    double delta_latitud = latitud_radianes2 - latitud_radianes1;
    double delta_longitud = longitud_radianes2 - longitud_radianes1;

    // Aplicar la fórmula de Haversine
    double a = sin(delta_latitud / 2) * sin(delta_latitud / 2) +
               cos(latitud_radianes1) * cos(latitud_radianes2) *
               sin(delta_longitud / 2) * sin(delta_longitud / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distancia = RADIO_TIERRA_KM * c;

    return distancia;
}

void mostrar5EmbarcacionesMasKM(const char* arch)
{
    tDistancia* emb;
    int cantEmb=0;
    emb=procesarDistancias(arch,&cantEmb); //tengo un array de struct con cada embarcacion y su distancia
    if (emb==NULL) return;

    tDistancia* embIni=emb;
    ordenar(emb,cantEmb);

    //mostrarDistancias(emb,5); //funciona pero debo hacerlo como matriz
    int j=0;
    printf("\n----- LAS EMBARCACIONES QUE MAS KILOMETROS RECORRIERON -----\n");

    while(j<5 && j<cantEmb)
    {
        printf("%s\t%.3lf km\n", embIni->matricula, embIni->distancia);
        j++;
        embIni++;
    }
    free(emb);
}

void ordenar(tDistancia* emb,int ce)
{
    tDistancia* ult = emb + ce - 1; // Puntero al último elemento del array
    tDistancia* i = emb; // Puntero para iterar sobre el array
    tDistancia* menor; //direccion del menor elemento

    // Itera sobre el array de estructuras
    for (i=emb; i < emb + ce - 1; i++)
    {
        menor=buscarMayor(i,ult);
        if (menor != i)
        {
            intercambiar(menor, i, sizeof(tDistancia));
        }
    }
}
tDistancia* buscarMayor(tDistancia* ini, tDistancia* fin)
{
    tDistancia* PosMay = ini;
    tDistancia* j;
    for(j=ini+1; j<=fin; j++)
    {
        if(j->distancia > PosMay->distancia)
            PosMay = j;
    }
    return PosMay;
}


void intercambiar(void*x, void*y, size_t tamElem)
{
    void* valorX = malloc(tamElem);

    memcpy(valorX,x,tamElem);
    memcpy(x,y,tamElem);
    memcpy(y,valorX,tamElem);

    free(valorX);
}

