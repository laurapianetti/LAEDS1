/* Programa que decompõe um número em todas as somas possíveis de números menores */

#include <stdio.h>
#include <stdlib.h>

int t; //primeira posição vazia do vetor

void empilha(int *p, int n) {
	p[t] = n; //preenche a primeira posição vazia
	t++; //a próxima posição será a nova primeira posição vazia
}

int desempilha(int *p) {
	t--; //vai para a última posição preenchida do vetor
	return p[t]; //retorna o valor da última posição preenchida
}

int main() {
	
	t=0; //inicializando t=0
	int n, ret;
	int *p;
	
	printf("Digite um numero inteiro: ");
	scanf("%d", &n);
	
	p = malloc(n*sizeof(int));
	
	printf("Decomposicao:\n");
	
	empilha(p, n); //a pilha vai ser inicializada com n na primeira posição
	printf("%d\n", p[0]); 
	
	while (p[0] != 1) {
	
		int c=0, soma =0; 
		
		if(p[t-1] != 1) { //se a última posição ocupada do vetor for diferente de 1
			ret = desempilha(p); //remove a última posição
			ret--; //subtrai 1 da última posição
			empilha(p, ret); //empilhar a "nova" última posição
			empilha(p, 1); //devolve o 1 subtraído da última posição para o vetor 
		}
		
		
		else { //se a última posição for igual a 1
			ret = desempilha(p); //remove o 1
			c++; //contador para a quantidade de posições removidas 
			while(ret == 1) { //enquanto a última posição for 1
				ret = desempilha(p); //remove a última posição
				c++; //adiciona 1 no contador
			} //na última repetição do while, o ret será o primeiro número diferente de 1
			
			ret--; 
			empilha(p, ret); 
			if(c > ret) { 
				while(soma < c) { 
					if((c - soma) < ret) {
						empilha(p, (c - soma));
					}
					else {
						empilha(p, ret);
					}
					soma += ret; 
				}
			}
			else 
				empilha(p, c);
		}
		
		/* printa o número decomposto */
		printf("%d", p[0]);
		for(int i=1; i < t; i++) 
			printf(" + %d", p[i]);
		printf("\n");
	}
}
