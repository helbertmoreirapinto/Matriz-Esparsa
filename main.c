#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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

/*Prototipo das funcoes*/
void inserir_celula(Celula_PTR, Celula_PTR*, Celula_PTR*);
Celula_PTR criar_celula(int, int, float);
float consultar_celula(int, int, Celula_PTR);
float somar_linha(Celula_PTR, int);
float somar_coluna(Celula_PTR, int);
int update_celula();
void remove_celula(int, int, Celula_PTR);
void apagar_matriz(int*, int*, Celula_PTR*, Celula_PTR*);

void apagar_matriz(int *m, int *n, Celula_PTR *headerX, Celula_PTR *headerY){
    *m = *n = 0;        /*Free nos espacos alocados*/
    Celula_PTR aux;
    while(*headerX){
        aux = *headerX;
        while(aux){
            if(aux->antY)
                free(aux->antY);
            aux = aux->proxY;
        }
        if((*headerX)->antX)
            free((*headerX)->antX);
        *headerX = (*headerX)->proxX;
    }
    while(*headerY){
        if((*headerY)->antY)
            free((*headerY)->antY);
        *headerY = (*headerY)->proxY;
    }
}

/*Ver logica para remover headers*/
void remove_celula(int x, int y, Celula_PTR header){
    while(header){
        if(header->x == x){
            while(header){
                if(header->y == y){
                    if(header->antX) header->antX->proxX = header->proxX;
                    if(header->antY) header->antY->proxY = header->proxY;
                    if(header->proxX) header->proxX->antX = header->antX;
                    if(header->proxY) header->proxY->antY = header->antY;
                    free(header);
                    return;
                }
                header = header->proxY;
            }
            return;
        }
        header = header->proxX;
    }
}

int update_celula(){
    char op = '\0';
    do{
        printf("Deseja alterar os dados? [S/N] ");
        setbuf(stdin,NULL);
        scanf("%c",&op);
    }while(op != 'S' && op != 's' && op != 'N' && op != 'n');
    if(op == 'S' || op == 's')
        return 1;
    else
        return 0;
}

float somar_coluna(Celula_PTR header, int coluna){
    float soma = 0;
    while(header){
        if(header->y == coluna){
            while(header){
                soma+=header->val;
                header = header->proxX;
            }
            break;
        }
        header = header->proxY;
    }
    return soma;
}

float somar_linha(Celula_PTR header, int linha){
    float soma = 0;
    while(header){
        if(header->x == linha){
            while(header){
                soma+=header->val;
                header = header->proxY;
            }
            break;
        }
        header = header->proxX;
    }
    return soma;
}

void inserir_celula(Celula_PTR elem, Celula_PTR *headerX, Celula_PTR *headerY){
    printf("[%d,%d] = %.2f\n\n", elem->x, elem->y, elem->val);
    Celula_PTR auxHeaderX, auxHeaderY;
    Celula_PTR newHeaderX, newHeaderY;
    Celula_PTR listaX, listaY;

    if(!*headerX || !*headerY){
        /*lista vazia, criar Header X e Y*/
        newHeaderX = criar_celula(elem->x, -1, 0);
        newHeaderX->proxY = elem;
        elem->antY = newHeaderX;
        *headerX = newHeaderX;
        newHeaderY = criar_celula(-1, elem->y, 0);
        newHeaderY->proxX = elem;
        elem->antX = newHeaderY;
        *headerY = newHeaderY;
    }else{
        auxHeaderX = *headerX;
        while(auxHeaderX){
            if(elem->x < auxHeaderX->x){
                /*se elem eh menor, ja insere*/
                /*Criar e inserir HeaderX ANTES de auxHeaderX*/
                newHeaderX = criar_celula(elem->x, -1, 0);
                newHeaderX->proxY = elem;
                elem->antY = newHeaderX;
                newHeaderX->proxX = auxHeaderX;
                newHeaderX->antX = auxHeaderX->antX;
                if(auxHeaderX->antX)
                    auxHeaderX->antX->proxX = newHeaderX;
                else
                    *headerX = newHeaderX;      /*Se nao tinha anterior, elem eh o primeiro HeaderX*/
                auxHeaderX->antX = newHeaderX;
                break;
            }else if(elem->x > auxHeaderX->x && !auxHeaderX->proxX){
                /*a lista rodou, passou o valor de elem e não achou HeaderX com seu valor*/
                /*Criar e inserir HeaderX DEPOIS de auxHeaderX*/
                newHeaderX = criar_celula(elem->x, -1, 0);
                newHeaderX->proxY = elem;
                elem->antY = newHeaderX;
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
                        if(listaY->antY){
                            listaY->antY->proxY = elem;
                            listaY->antY = elem;
                        }
                        break;
                    }else if(elem->y > listaY->y && !listaY->proxY){
                        /*insere elem DEPOIS de lista*/
                        listaY->proxY = elem;
                        elem->antY = listaY;
                        break;
                    }else if(elem->y == listaY->y){
                        listaY->val = elem->val;
                        break;
                    }
                    listaY = listaY->proxY; /*roda o prox da lista em X*/
                }
                break;
            }
            auxHeaderX = auxHeaderX->proxX; /*roda o prox da lista em Y*/
        }

        auxHeaderY = *headerY;
        while(auxHeaderY){
            if(elem->y < auxHeaderY->y){
                /*se elem eh menor, ja insere*/
                /*Criar e inserir HeaderY ANTES de auxHeaderY*/
                newHeaderY = criar_celula(-1, elem->y, 0);
                newHeaderY->proxX = elem;
                elem->antX = newHeaderY;
                newHeaderY->proxY = auxHeaderY;
                newHeaderY->antY = auxHeaderY->antY;
                if(auxHeaderY->antY)
                    auxHeaderY->antY->proxY = newHeaderY;
                else
                    *headerY = newHeaderY;      /*Se nao tinha anterior, elem eh o primeiro HeaderY*/
                auxHeaderY->antY = newHeaderY;
                break;
            }else if(elem->y > auxHeaderY->y && !auxHeaderY->proxY){
                /*a lista rodou, passou o valor de elem e não achou HeaderY com seu valor*/
                /*Criar e inserir HeaderY DEPOIS de auxHeaderY*/
                newHeaderY = criar_celula(-1, elem->y, 0);
                newHeaderY->proxX = elem;
                elem->antX = newHeaderY;
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
                    if(elem->x < listaX->x){
                        /*insere elem ANTES de lista*/
                        elem->antX = listaX->antX;
                        elem->proxX = listaX;
                        if(listaX->antX){
                            listaX->antX->proxX = elem;
                            listaX->antX = elem;
                        }
                        break;
                    }else if(elem->x > listaX->x && !listaX->proxX){
                        /*insere elem DEPOIS de lista*/
                        listaX->proxX = elem;
                        elem->antX = listaX;
                        break;
                    }else if(elem->x == listaX->x){
                        listaX->val = elem->val;
                        break;
                    }
                    listaX = listaX->proxX; /*roda o prox da lista em X*/
                }
                break;
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
        exit(0);
    }
    return ret;
}

float consultar_celula(int x, int y, Celula_PTR header){
    Celula_PTR aux;
    while(header){
        aux = header;
        if(header->x == x){
            while(header){
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
    int m , n;
    int x, y;
    int i;
    int op=-1;
    m = n = 0;
    float val, aux;
    Celula_PTR firstX = NULL, firstY = NULL;

    while(op){
        printf("|****************************|\n");
        printf("|       Matriz Esparsa       |\n");
        printf("|****************************|\n");
        printf("| 1 |Inicializar Matriz      |\n");
        printf("| 2 |Remover Matriz          |\n");
        printf("| 3 |Inserir Elemento[x y]   |\n");
        printf("| 4 |Consultar Elemento[x y] |\n");
        printf("| 5 |Somar Linha             |\n");
        printf("| 6 |Somar Coluna            |\n");
        printf("| 0 |Sair                    |\n");
        printf("|****************************|\n");
        printf("|Selecione: ");
        setbuf(stdin,NULL);
        scanf("%d",&op);
        switch(op){
        case 1: /*Criar Matriz*/
            if(m && n)
                printf("Matriz ja esta inicializada\n");
            else{
                printf("Digite valor de M: ");
                setbuf(stdin,NULL);
                scanf("%d",&m);
                printf("Digite valor de N: ");
                setbuf(stdin,NULL);
                scanf("%d",&n);
                printf("Matriz inicializada com sucesso!\n");
            }
            break;
        case 2: /*Remove Matriz*/
            if(!m && !n)
                printf("Matriz nao inicializada!\n");
            else{
                apagar_matriz(&m, &n, &firstX, &firstY);
                printf("Matriz removida com sucesso!\n");
            }
            break;
        case 3: /*Criar celula*/
            if(!m || !n){
                printf("Matriz nao inicializada!\n");
                break;
            }
            do{
                printf("Digite a posicao [x y]: ");
                setbuf(stdin,NULL);
                scanf("%d %d",&x,&y);
            }while(x < 0 || y < 0 || x >= m || y >= n);   /*Enquanto nao digitar um X e um Y validos nao avanca*/
            printf("Digite o valor: ");
            setbuf(stdin,NULL);
            scanf("%f",&val);
            aux = consultar_celula(x,y,firstX);
            if(aux){
                printf("Casa ocupada com o valor %.2f\n",aux);
                if(!update_celula())    /*Se usuario nao confirmar volta para o menu*/
                    break;
                if(!val)                /*Se valor novo eh 0, e usuario deseja atualizar valor, remover celula*/
                    remove_celula(x, y, firstX);
            }
            inserir_celula(criar_celula(x,y,val), &firstX, &firstY);
            break;
        case 4: /*Consultar celula*/
            do{
                printf("Digite a posicao [x y]: ");
                setbuf(stdin,NULL);
                scanf("%d %d",&x,&y);
            }while(x < 0 || y < 0 || x >= m || y>= n);   /*Enquanto nao digitar um X e um Y validos nao avanca*/
            val = consultar_celula(x,y,firstX);
            printf("[%d,%d]: %.2f\n",x,y,val);
            break;
        case 5: /*Somar Linha*/
            do{
                printf("Digite a linha: ");
                setbuf(stdin,NULL);
                scanf("%d",&i);
            }while(i < 0 || i >= m);   /*Enquanto nao digitar uma linha valida nao avanca*/
            val = somar_linha(firstX, i);
            printf("Soma da linha %d: %.2f\n",i, val);
            break;
        case 6: /*Somar Coluna*/
            do{
                printf("Digite a coluna: ");
                setbuf(stdin,NULL);
                scanf("%d",&i);
            }while(i < 0 || i >= n);   /*Enquanto nao digitar uma coluna valida nao avanca*/
            val = somar_coluna(firstY, i);
            printf("Soma da coluna %d: %.2f\n",i, val);
            break;
        case 0:
            printf("Encerrando . . .\n");
            break;
        default:
            system("CLS");
            printf("Opcao Invalida!\n");
        }
        if(op>0&&op<=6){
            getch();
            system("CLS");
        }
    }
}
