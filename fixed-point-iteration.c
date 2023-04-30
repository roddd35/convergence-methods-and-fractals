#include <stdio.h>
#include <math.h>

#define eps 0.00000009
/* gcc -O2 -o fixed-point-iteration fixed-point-iteration.c -lm */

double fixedPointLog(double x){
    while(x - log(2 * (x * x)) > eps || x - log(2 * (x * x)) < -eps)
        x = log(2 * (x * x));
    return x;
}

double fixedPointPositive(double x){
    while(x - sqrt(exp(x) / 2) > eps || x - sqrt(exp(x) / 2) < -eps)
        x = sqrt(exp(x) / 2);
    return x;
}

double fixedPointNegative(double x){
    while(x + sqrt(exp(x) / 2) > eps || x + sqrt(exp(x) / 2) < -eps)
        x = -sqrt(exp(x) / 2);
    return x;
}

int main(){
    double x;
    double res;

    printf("Digite o valor de X: ");
    scanf("%lf", &x);

    if(x <= 2 && x >= 0)
        res = fixedPointPositive(x);
    else if(x > 2)
        res = fixedPointLog(x);
    else
        res = fixedPointNegative(x);
        
    printf("\n\nO resultado da iteração de ponto fixo é: %.7lf\n", res);
    
    return 0;
}