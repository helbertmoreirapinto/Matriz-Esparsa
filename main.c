#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Casa{
    float val;
    unsigned long long int x;
    unsigned long long int y;
    struct Casa *ant;
    struct Casa *prox;
};
typedef struct Casa Casa;

/* Funcoes */
int main();
Casa* criar_casa(unsigned long long int, unsigned long long int, float);
void inserir_casa(Casa*, Casa**, Casa**);
Casa* consultar_casa(Casa*, unsigned long long int, unsigned long long int);

int main(){
    char respUsu;
    char delConfirm;
    unsigned long long int m = 0, n = 0, x, y;
    float val;
    Casa *first = NULL;
    Casa *last = NULL;

    do{
        printf("|************************|\n");
        printf("|         Matriz         |\n");
        printf("|************************|\n");
        if(!m || !n)
            printf("|Inicializar matriz  | 1 |\n");
        else{
            printf("|Excluir matriz      | 2 |\n");
            printf("|Adicionar valor     | 3 |\n");
            printf("|Consultar valor     | 4 |\n");
            printf("|Somar linha         | 5 |\n");
            printf("|Somar coluna        | 6 |\n");
        }
        printf("|Sair                | 0 |\n");
        printf("|************************|\n");
        printf("|Selecione: ");
        setbuf(stdin, NULL);
        fscanf(stdin, "%c", &respUsu);

        if(respUsu == '1' && (!m || !n)){
            setbuf(stdin,NULL); printf("Insira valor de M: ");fscanf(stdin, "%I64u", &m);
            setbuf(stdin,NULL); printf("Insira valor de N: ");fscanf(stdin, "%I64u", &n);
            printf("%llu %llu\n",m,n);
            getch();
        }else if((respUsu >= '2' && respUsu <= '6') && (m && n)){
            switch(respUsu){
            case '2':
                do{
                    setbuf(stdin, NULL);
                    printf("Deseja excluir matriz? [S/N] ");fscanf(stdin, "%c", &delConfirm);
                }while(delConfirm!='S' && delConfirm!='s' && delConfirm!='N' && delConfirm!='n');

                if(delConfirm == 'S' || delConfirm == 's'){
                    m = n = 0;
                    first = last = NULL;
                }
                break;
            case '3':
                do{
                    setbuf(stdin, NULL); printf("Poscicao [x y]: ");fscanf(stdin, "%I64u %I64u", &x, &y);
                    setbuf(stdin, NULL); printf("Valor: ");fscanf(stdin, "%f", &val);
                }while((x < 0 || x >= m) || (y < 0 || y >= n));
                inserir_casa(criar_casa(x,y,val), &first, &last);
                break;
            case '4':

                break;
            case '5':

                break;
            }
        }

        system("CLS");

        /* Mensagens cabecalho */
        if(respUsu < '0' || respUsu > '5')
            printf("Valor invalido\n");
        else if(respUsu == '1')
            printf("Matriz criada com sucesso!\n");
        else if(respUsu == '2' && (delConfirm == 'S' || delConfirm == 's'))
            printf("Matriz removida com sucesso!\n");
        system("PAUSE");
    }while(respUsu != '0');
}

Casa* criar_casa(unsigned long long int x, unsigned long long int y, float val){
    Casa *casa = malloc(sizeof(Casa));
    if(casa){
        casa->ant = NULL;
        casa->prox = NULL;
        casa->x = x;
        casa->y = y;
        casa->val = val;
    }else{
        printf("Memoria cheia\n");
        getch();
        exit(0);
    }
    return casa;
}

void inserir_casa(Casa *elem, Casa **first, Casa **last){
    Casa *aux = consultar_casa((*first), elem->x, elem->y);
    Casa *atual, *ant;
    char updateConfirm;
    if(aux){
        printf("Posicao preenchida com o valor %f\n",aux->val);
        do{
            printf("Substituir valor na posicao? [S/N] ");
            setbuf(stdin,NULL);
            fscanf(stdin, "%c", &updateConfirm);
        }while(updateConfirm != 'S' && updateConfirm != 'N' && updateConfirm != 's' && updateConfirm != 'n');
    }else{
        if(*first){
            atual = *first;
			ant = NULL;
			while(atual){
				if(atual->x < elem->x || ( (atual->x == elem->x)&&(atual->y < elem->y) )){
					ant = atual;
					atual = atual->prox;
				}else{
					if(atual->ant){
						atual->ant->prox = elem;
						elem->prox = atual;
                        elem->ant = atual->ant;
						atual->ant = elem;
						return;
					}
					elem->prox = atual;
					elem->ant = NULL;
					atual->ant = elem;
					*first = elem;
					return;
				}
			}
            ant->prox = elem;
            elem->prox = NULL;
            elem->ant = ant;
            *last = elem;
        }else{
            *first = elem;
            *last = elem;
        }
    }
}

Casa* consultar_casa(Casa *first, unsigned long long int x, unsigned long long int y){
    Casa *current = first;
	while(current){
		if(x == current->x && y == current->y)
			return current;
		current = current->prox;
	}
	return NULL;
}
