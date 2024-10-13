
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <float.h>

typedef struct
{
    float x;
    float y;
    
} Point;

int ComparaX(const void *a, const void *b)
{
    Point *P1 = (Point *)a;
    Point *P2 = (Point *)b;
    
    return (P1->x > P2->x) - (P1->x < P2->x);
}

int ComparaY(const void *a, const void *b)
{
    Point *P1 = (Point *)a;
    Point *P2 = (Point *)b;
    
    return (P1->y > P2->y) - (P1->y < P2->y);
}


float Distancia(Point P1, Point P2)
{
    return sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2));
}

float MasCercano(Point P[], int n)
{
	int i, j, k;
	float dist;
	float minDist = FLT_MAX;
	
    if (n <= 3)
	{   
        for (i = 0; i < n; i++)
		{
            for (j = i + 1; j < n; j++)
			{
                dist = Distancia(P[i], P[j]);
                
                if (dist < minDist)
				{
                    minDist = dist;
                }
            }
        }
        return minDist;
    }

    int mid = n / 2;
    
    Point midPoint = P[mid];

    float dl = MasCercano(P, mid);
    float dr = MasCercano(P + mid, n - mid);
    float d = fmin(dl, dr);

    Point strip[n];
    
    j = 0;
    
    for (i = 0; i < n; i++)
	{
        if (fabs(P[i].x - midPoint.x) < d)
		{
            strip[j] = P[i];
            j++;
        }
    }

    qsort(strip, j, sizeof(Point), ComparaY);

    for (i = 0; i < j; i++)
	{
        for (k = i + 1; k < j && (strip[k].y - strip[i].y) < d; k++)
		{
            d = fmin(d, Distancia(strip[i], strip[k]));
        }
    }

    return d;
}

float Cercano(Point P[], int n)
{
    qsort(P, n, sizeof(Point), ComparaX);
    
    return MasCercano(P, n);
}

void GeneradordePuntos(Point P[], int n)
{
	int i; 
	
    for (i = 0; i < n; i++)
	{
        P[i].x = (rand() % 20001 - 10000) / 100.0;
        P[i].y = (rand() % 20001 - 10000) / 100.0;
    }
}

int main()
{
    srand(time(NULL));

    int sizes[] = {10, 100, 1000, 10000, 100000};
    int n;
    int i;
    
    for (i = 0; i < 5; i++)
	{
        n = sizes[i];
        
        Point *P = (Point *)malloc(n * sizeof(Point));
        
        GeneradordePuntos(P, n);

        clock_t start = clock();
        
        float minDist = Cercano(P, n);
        
        clock_t end = clock();

        double TiempoEjecucion = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\n\n  Para n = %d, la distancia minima es: %f\n  Tiempo de ejecucion: %f segundos\n", n, minDist, TiempoEjecucion);
        
        free(P);
    }

    return 0;
}
