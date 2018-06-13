#include <stdio.h>
#include <stdlib.h>

struct Casa{
    float val;
    unsigned long long int x;
    unsigned long long int y;
    struct Casa *ant;
    struct Casa *prox;
};
typedef struct Casa Casa;

void criar_casa(unsigned long long int x, unsigned long long int y, float val){
}

void inserir_casa(Casa *casa){
}

void consultar_casa(unsigned long long int x, unsigned long long int y){
}

int main(){
    Casa prim;
    Casa ult;
    unsigned long long int m;
    unsigned long long int n;
    printf("M: ");scanf("%ld", &m);
    printf("N: ");scanf("%ld", &n);
    printf("M: %ld\n",m);
    printf("N: %ld\n",n);
    return 0;
}
