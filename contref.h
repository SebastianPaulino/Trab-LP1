#include <stdio.h>
#include <stdlib.h>

typedef struct endMem
{
    int x; // aqui guarda quantos estao apontados
    void *end; // aqui e o endereco que esta apontado
}endMem;

endMem *y[100]; //faco vetor para o salvar quando chega 0
int pos = 0;

void *malloc2(int TAM)
{
    endMem *aux = (endMem*)malloc(sizeof(endMem)); //aloca
    aux->x = 1; //modifica 
    y[pos] = aux; // bota no vetor
    pos++;
    void *end2 = malloc(TAM);//salva o endereco com tamanho
    aux->end = end2; //guarda no struct
    return aux->end;
}

void refresh(void *end, int info)
{
    for(int i = 0; i < pos; i++)//percorrer vetor
    {
    	if(end == y[i]->end)//se for igual o que foi guardado
	    {
	        y[i]->x = info+y[i]->x;//modifica
	        if(y[i]->x == 0) // e caso continue como 0 (-1 do info)
	        {
	            for(int j=i;j<pos;j++)
				{
					y[j] = y[j+1];//substitui o primeiro pelo proximo, excluindo o outro
				}
				free(y[pos]);//verificar
				pos--;// e diminuindo a pos
	        }
	    }
	}
}

void atrib2(void **end1, void *end2)
{
	refresh(end1, -1); //-1 pois na hora de somar tem que dar 0 ou nao e o que queremos
    refresh(end2, 1); //caso o primeiro refresh seja T este da? F
    *end1 = end2; //atualiza ERRADO
}

void dump()
{
    for(int i = 0; i < pos; i++)//percorre vetor
    {
        printf("Endereco = %d\n", y[i]->end);
        printf("Contador = %d\n", y[i]->x);
        printf("\n");
    }
}
