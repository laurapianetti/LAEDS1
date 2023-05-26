#include <stdio.h>
#include <stdlib.h>

#define MAXTAM          70
#define CANCELACARATER  '#'
#define CANCELALINHA    '\\'
#define SALTALINHA      '*'
#define MARCAEOF        '~'
#define CANCELAPALAVRA  '$'

typedef char TipoChave;

typedef int TipoApontador;

typedef struct {
    TipoChave Chave;

} TipoItem;

typedef struct {
    TipoItem Item[MAXTAM];
    TipoApontador Topo;

} TipoPilha;

 /* FPVazia */
void FPVazia(TipoPilha *Pilha) { 
	Pilha->Topo = 0;
} 

/* Vazia */
int Vazia(TipoPilha Pilha) { 
	return (Pilha.Topo == 0);
}  

/* Empilha */
void Empilha(TipoItem x, TipoPilha *Pilha) { 
	if (Pilha->Topo == MAXTAM)
        printf("Erro pilha esta cheia\n");
    
    else { 
        Pilha->Topo++;
        Pilha->Item[Pilha->Topo - 1] = x;
    }
}  

/* Desempilha */
void Desempilha(TipoPilha *Pilha, TipoItem *Item) { 
    if (Vazia(*Pilha)) 
        printf("Erro pilha esta vazia\n");
    else { 
        *Item = Pilha->Item[Pilha->Topo - 1];
        Pilha->Topo--;
    }
}  

/* Tamanho */
int Tamanho(TipoPilha Pilha) { 
    return (Pilha.Topo);
}  

void Imprime(TipoPilha *Pilha) { 
    TipoPilha Pilhaux;
    TipoItem x;
    FPVazia(&Pilhaux);
    while (!Vazia(*Pilha)) { 
        Desempilha(Pilha, &x); Empilha(x, &Pilhaux); 
    }
    while (!Vazia(Pilhaux)) { 
        Desempilha(&Pilhaux, &x); putchar(x.Chave); 
    }
    putchar('\n');
} 

int main(int argc, char *argv[]) { 
    TipoPilha Pilha;
    TipoItem x;
    TipoItem aux;
    FPVazia(&Pilha);
  
    x.Chave = getchar();
    if (x.Chave == '\n') x.Chave = ' ';
  
    while (x.Chave != MARCAEOF) { 
        if (x.Chave == CANCELACARATER) { 
            if (!Vazia(Pilha)) Desempilha(&Pilha, &x);
        }
        else if (x.Chave == CANCELALINHA) 
            FPVazia(&Pilha);
        else if (x.Chave == SALTALINHA) 
            Imprime(&Pilha);
        else if (x.Chave == CANCELAPALAVRA) {
            aux.Chave = 'a';
            while(aux.Chave != ' ' && !Vazia(Pilha)) {
                Desempilha(&Pilha, &aux);
            }
        }
        else { 
            if (Tamanho(Pilha) == MAXTAM) Imprime(&Pilha);
            Empilha(x, &Pilha);
        }
        x.Chave = getchar();
        if (x.Chave == '\n') x.Chave = ' ';
    }
    if (!Vazia(Pilha)) Imprime(&Pilha);
    return 0;
} 