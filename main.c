#include <stdio.h>
#include <stdlib.h>

struct Celula{
    int x;
    int y;
    float val;
    struct Celula *proxX;
    struct Celula *antX;
    struct Celula *proxY;
    struct Celula *antY;
};
typedef struct Celula Celula;
typedef Celula* Celula_PTR;

void inserir_celula(Celula_PTR, Celula_PTR*, Celula_PTR*);
Celula_PTR criar_celula(int, int, float);
float consultar_celula(int, int, Celula_PTR);

void inserir_celula(Celula_PTR elem, Celula_PTR *headerX, Celula_PTR *headerY){
    printf("[%d,%d] = %.2f\n\n", elem->x, elem->y, elem->val);

    Celula_PTR auxHeaderX, auxHeaderY;
    Celula_PTR newHeaderX, newHeaderY;
    Celula_PTR listaX, listaY;

    if(!*headerX || !*headerY){
        /*lista vazia, criar Header X e Y*/
        newHeaderX = criar_celula(elem->x, -1, 0);
        newHeaderX->proxY = elem;
        *headerX = newHeaderX;
        newHeaderY = criar_celula(-1, elem->y, 0);
        newHeaderY->proxX = elem;
        *headerY = newHeaderY;
    }else{
        auxHeaderX = *headerX;
        while(auxHeaderX){
            if(elem->x < auxHeaderX->x && !auxHeaderX->proxX){
                /*elem esta antes de auxHeaderX mas nao tem mais elementos na fila*/
                /*Criar e inserir HeaderX ANTES de auxHeaderX*/
                newHeaderX = criar_celula(elem->x, -1, 0);
                newHeaderX->proxY = elem;
                newHeaderX->proxX = auxHeaderX;
                newHeaderX->antX = auxHeaderX->antX;
                if(auxHeaderX->antX)
                    auxHeaderX->antX->proxX = newHeaderX;
                else
                    *headerX = newHeaderX;      /*Se nao tinha anterior, elem eh o primeiro HeaderX*/
                auxHeaderX->antX = newHeaderX;
            }else if(elem->x > auxHeaderX->x){
                /*a lista rodou, passou o valor de elem e não achou HeaderX com seu valor*/
                /*Criar e inserir HeaderX DEPOIS de auxHeaderX*/
                newHeaderX = criar_celula(elem->x, -1, 0);
                newHeaderX->proxY = elem;
                newHeaderX->antX = auxHeaderX;
                newHeaderX->proxX = auxHeaderX->proxX;
                if(auxHeaderX->proxX)
                    auxHeaderX->proxX->antX = newHeaderX;
                auxHeaderX->proxX = newHeaderX;
                break;
            }else if(elem->x == auxHeaderX->x){
                /*Achou HeaderX com o valor*/
                listaY = auxHeaderX;
                while(listaY){
                    if(elem->y < listaY->y && !listaY->proxY){
                        /*insere elem ANTES de lista*/
                        elem->antY = listaY->antY;
                        elem->proxY = listaY;
                        listaY->antY->proxY = elem;
                        listaY->antY = elem;
                        return;
                    }else if(elem->y > listaY->y){
                        /*insere elem DEPOIS de lista*/
                        listaY->proxY = elem;
                        elem->antY = listaY;
                        return;
                    }else if(elem->y == listaY->y){
                        printf("Celula ocupada com o valor%.2f\n",listaY->val);
                        return;
                    }
                    listaY = listaY->proxY; /*roda o prox da lista em X*/
                }
            }
            auxHeaderX = auxHeaderX->proxX; /*roda o prox da lista em Y*/
        }

        auxHeaderY = *headerY;
        while(auxHeaderY){
            if(elem->y < auxHeaderY->y && !auxHeaderY->proxY){
                /*Criar e inserir HeaderY ANTES de auxHeaderY*/
                newHeaderY = criar_celula(-1, elem->y, 0);
                newHeaderY->proxX = elem;
                newHeaderY->proxY = auxHeaderY;
                newHeaderY->antY = auxHeaderY->antY;
                if(auxHeaderY->antY)
                    auxHeaderY->antY->proxY = newHeaderY;
                else
                    *headerY = newHeaderY;
                auxHeaderY->antY = newHeaderY;
            }else if(elem->y > auxHeaderY->y){
                /*Criar e inserir HeaderY DEPOIS de auxHeaderY*/
                newHeaderY = criar_celula(-1, elem->y, 0);
                newHeaderY->proxX = elem;
                newHeaderY->antY = auxHeaderY;
                auxHeaderY->proxY = newHeaderY;
                if(auxHeaderY->proxY)
                    auxHeaderY->proxY->antY = newHeaderY;
                auxHeaderY->proxY = newHeaderY;
                break;
            }else if(elem->y == auxHeaderY->y){
                /*Achou HeaderY com o valor*/
                listaX = auxHeaderY;
                while(listaX){
                    if(elem->x < listaX->x && !listaX->proxX){
                        /*insere elem ANTES de lista*/
                        elem->antX = listaX->antX;
                        elem->proxX = listaX;
                        listaX->antX->proxX = elem;
                        listaX->antX = elem;
                        return;
                    }else if(elem->x > listaX->x){
                        /*insere elem DEPOIS de lista*/
                        listaX->proxX = elem;
                        elem->antX = listaX;
                        return;
                    }else if(elem->x == listaX->x){
                        return;
                    }
                    listaX = listaX->proxX; /*roda o prox da lista em X*/
                }
            }
            auxHeaderY = auxHeaderY->proxY; /*roda o prox da lista em Y*/
        }
    }
}

Celula_PTR criar_celula(int x, int y, float val){
    Celula_PTR ret = (Celula_PTR)malloc(sizeof(Celula));
    if(ret){
        ret->val = val;
        ret->x = x;
        ret->y = y;
        ret->proxX = NULL;
        ret->proxY = NULL;
        ret->antX = NULL;
        ret->antY = NULL;
    }else{
        printf("Problema ao alocar Memoria\n");
        exit(10);
    }
    return ret;
}

float consultar_celula(int x, int y, Celula_PTR header){
    Celula_PTR aux;
    while(header){
        aux = header;
        printf("\nX:%d ", header->x);
        if(header->x == x){
            while(header){
                printf("Y:%d ",header->y);
                if(header->y == y)
                    return header->val;
                header = header->proxY;
            }
            break;
        }
        header = aux;
        header = header->proxX;
    }
    return 0;
}

int main(){
    int m, n;
    int x, y;
    int op;
    float val;
    Celula_PTR firstX = NULL, firstY = NULL;
    Celula_PTR elem;

    /*Criar matriz*/
    printf("M: ");setbuf(stdin,NULL);scanf("%d",&m);
    printf("N: ");setbuf(stdin,NULL);scanf("%d",&n);
    while(1){
        printf("opcao:\n1 - Inserir\n2 - Consultar\n");setbuf(stdin,NULL);scanf("%d",&op);
        if(op==1){
            /*Criar celula*/
            printf("x: ");setbuf(stdin,NULL);scanf("%d",&x);
            printf("y: ");setbuf(stdin,NULL);scanf("%d",&y);
            printf("val: ");setbuf(stdin,NULL);scanf("%f",&val);

            elem = criar_celula(x,y,val);
            inserir_celula(elem, &firstX, &firstY);
        }else if(op == 2){
            /*Consultar celula*/
            printf("x: ");setbuf(stdin,NULL);scanf("%d",&x);
            printf("y: ");setbuf(stdin,NULL);scanf("%d",&y);
            val = consultar_celula(x,y,firstX);
            printf("val: %.2f\n", val);
        }
    }
}
