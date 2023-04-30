#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

#define eps 0.000009

/* 
    gcc -Wall -pedantic -o newtonMethod newtonMethod.c -lm 
    gnuplot
    set terminal png size (1200, 800)
    set output "img.png"
    plot "output.txt" with image pixel
*/

typedef struct{
    double complex *rootsArray;
    int* colorArray;
    int index;
    int size;
} Roots;

/* função: F(x) = x⁴ - 1 */
double complex evalf(double complex x){
    return (cpow(x, 4) - 1);
}

/* F'(x) = 4x³ */
double complex evalDf(double complex x){
    return (4 * cpow(x, 3));
}

double complex newton(double complex x0){
    double complex x1;
    x1 = x0 - (evalf(x0) / evalDf(x0));
    while (cabs(x1 - x0) > eps){
        x0 = x1;
        x1 = x0 - (evalf(x0) / evalDf(x0));
    }
    return x1;
}

Roots* createStruct(Roots* roots){
    roots = malloc(sizeof(Roots*));
    roots->rootsArray = malloc(2 * sizeof(double complex));
    roots->colorArray = malloc(2 * sizeof(int));
    roots->size = 2;
    roots->index = 1;    /* first empty position */

    return roots;
}

Roots *resize(Roots* roots){
    int i;

    Roots* new = malloc(sizeof(Roots*));
    new->rootsArray = malloc(2 * roots->size * sizeof(double complex));
    new->colorArray = malloc(2 * roots->size * sizeof(int));
    new->size = 2 * roots->size;
    new->index = roots->index;

    for(i = 1; i < roots->size; i++){
        new->rootsArray[i] = roots->rootsArray[i];
        new->colorArray[i] = roots->colorArray[i]; 
    }
    return new;
}

void newton_basins(double complex l, double complex u, int p){
    FILE *image;
    int i, j, k;
    int alterou = 0;
    int colorMatrix[p][p];
    double realVector[p];
    double imagVector[p];
    double complex x0;
    double complex root;
    double complex z[p][p];
    Roots* roots = NULL;

    for (i = 0; i < p; i++) {
        realVector[i] = creal(l) + i * (creal(u) - creal(l)) / (p-1);   /* array com as partes reais */
        imagVector[i] = cimag(l) + i * (cimag(u) - cimag(l)) / (p-1);   /* array com as partes imaginarias */
    }
    for (i = 0; i < p; i++) {
        for (j = 0; j < p; j++) {
            z[i][j] = CMPLX(realVector[i], imagVector[j]);
        }
    }

    /* initiate the struct */
    roots = createStruct(roots);

    /* iterate through points and see to which root it converges */
    for(i = 0; i < p; i++){
        for(j = 0; j < p; j++){
            x0 = z[i][j];
            root = newton(x0);

            if(root != root){
                colorMatrix[i][j] = 0;
                alterou = 1;
            }

            for(k = 0; k < roots->index && !alterou; k++){
                if(cabs(root - roots->rootsArray[k]) < eps){
                    colorMatrix[i][j] = roots->colorArray[k] * 3;
                    alterou = 1;
                }
            }

            if(!alterou){
                if(roots->index > roots->size)
                    roots = resize(roots);
                roots->rootsArray[roots->index] = root;
                roots->colorArray[roots->index] = roots->index;

                colorMatrix[i][j] = roots->index;
                roots->index++;
            }
            alterou = 0;
        }
    }

    /* generates the .txt file with the image */
    image = fopen("output.txt", "w");
    for (i = 0; i < p; i++) {
        for (j = 0; j < p; j++) {
            fprintf(image, "%f %f %d\n", realVector[i], imagVector[j], colorMatrix[i][j]);
        }
        fprintf(image, "\n");
    }
    fclose(image);
}

/*
ENTRADAS->  SAÍDAS
 1 1     ->   0, -i
 0 1     ->   0, +i
 1 0     ->   1, 0i
-1 0     ->  -1, 0i
*/
   
int main(){
    int p = 600;
    /*double real;
    double imag;
    double complex X;
    double complex raiz;*/
    double complex l = CMPLX(-30.0, -30.0);
    double complex u = CMPLX(30.0, 30.0);

    /*
    printf("Digite os valores de X0 real e imaginário: ");
    scanf("%lf%lfi", &real, &imag);
    */

    newton_basins(l, u, p);

    /*
    X = CMPLX(real, imag);
    raiz = newton(X);
    

    printf("X = %.1lf + %.1lfi\n", creal(raiz), cimag(raiz));
    */
    return 0;
}