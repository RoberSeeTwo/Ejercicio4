
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

#define PUNTOS 10

typedef struct
{
    int x;
    int y;
    
} Punto;

int Coords(int min, int max)
{
    return min + (rand() / (RAND_MAX / (max - min)));
}

int DistanciaEuclidiana(Punto P1, Punto P2)
{
    return sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
}

int main()
{
	int i, j;
	int Distancia;
    
    Punto Puntos[PUNTOS];
    
    srand(time(NULL));

	printf("\n Puntos generados:\n");
	
    for (i = 0; i < PUNTOS ; i++)
	{
        Puntos[i].x = Coords(-10, 10);
        Puntos[i].y = Coords(-10, 10);
        
        printf("\n %d: (%d, %d)", i + 1, Puntos[i].x, Puntos[i].y);
    }

    Punto Punto1, Punto2;
    
    int distanciaMinima = DBL_MAX;
    
    clock_t start = clock();

    for (i = 0; i < PUNTOS; i++)
	{
        for (j = i + 1; j < PUNTOS; j++)
		{
            Distancia = DistanciaEuclidiana(Puntos[i], Puntos[j]);
            
            if (Distancia < distanciaMinima)
			{
                distanciaMinima = Distancia;
                Punto1 = Puntos[i];
                Punto2 = Puntos[j];
            }
        }
    }
    
    clock_t end = clock();
    
    double tiempoEjecucion = (double)(end - start) / CLOCKS_PER_SEC;
	
    printf("\n\n El par de puntos mas cercano es: (%d, %d) y (%d, %d)\n", Punto1.x, Punto1.y, Punto2.x, Punto2.y);
    
    printf("\n La distancia entre ellos es: %d\n", distanciaMinima);
    
    printf("\n Tiempo de ejecucion: %.6f segundos\n", tiempoEjecucion);
	
    return 0;
}
