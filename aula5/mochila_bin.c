/* 	Dupla: Caio Palhares e Laura Pianetti
	Dada uma entrada por meio de um arquivo de texto, esse problema verifica se uma solução é ótima para o problema da mochila binária */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* função que calcula o máximo entre dois números */
int max(int a, int b) {
    
    int ret;
    
    if (a > b) ret = a;
    else ret = b;
    
    return ret;
}

/* função que verifica se um objeto cabe em uma mochila */
int cabe_na_mochila(int peso, int capacidade) {
   
    return peso <= capacidade; //esse retorno vai ser 0 ou 1
}

/* função que utiliza a técnica bottom-up para resolver o problema */
int resolver_mochila(int itens, int* valores, int* pesos, int capacidade_mochila, int* solucao) {
    int i, j;
    int valor_maximo;
    int **subproblemas;

    /* aloca matriz para armazenar os valores máximos de cada subproblema */
    subproblemas = (int**) malloc((itens+1) * sizeof(int*));
    for (i = 0; i <= itens; i++) {
        subproblemas[i] = (int*) malloc((capacidade_mochila+1) * sizeof(int));
    }

    /* preenche a primeira linha e primeira coluna da matriz com zero */
    for (i = 0; i <= itens; i++) {
        subproblemas[i][0] = 0;
    }
    for (int j = 0; j <= capacidade_mochila; j++) {
        subproblemas[0][j] = 0;
    }

    /* calcula o valor máximo para cada subproblema */
    for (i = 1; i <= itens; i++) {
        for (j = 1; j <= capacidade_mochila; j++) {
            if (cabe_na_mochila(pesos[i-1], j)) {
                subproblemas[i][j] = max(valores[i-1] + subproblemas[i-1][j-pesos[i-1]], subproblemas[i-1][j]); //atribui ao novo subproblema com o maior entre o subproblema atual e o anterior
            } 
            else {
                subproblemas[i][j] = subproblemas[i-1][j]; //se não couber na mochila, o subproblema vai ser igual ao anterior
            }
        }
    }

    valor_maximo = subproblemas[itens][capacidade_mochila]; //armazena o valor máximo encontrado

    /* libera a memória alocada para a matriz de subproblemas */
    for (i = 0; i <= itens; i++) {
        free(subproblemas[i]);
    }
    free(subproblemas);

    return valor_maximo; //retorna o valor máximo encontrado
}

int solucao_otima(int itens, int melhor_solucao, int* solucao, int* valor) {
	
	int ret;
	int valor_atual=0;
	
	for(int i=0; i < itens; i++) {
		valor_atual += solucao[i] *valor[i];	
	}
	
	if(valor_atual == melhor_solucao) ret = 1; //se o valor for igual a solução encontrada, a solução é ótima
	else ret = 0;
	
	return ret;
}

int solucao_inviavel(int itens, int capacidade, int* solucao, int* peso) {

	int ret;
	int peso_atual=0;
	
	for(int i=0; i < itens; i++) {
		peso_atual += solucao[i] *peso[i];	
	}
	
	if(peso_atual > capacidade) ret = 1; //se o peso for maior que a capacidade, a solução é inviável
	else ret = 0;
	
	return ret;
}

int main() {
	
	char nome_arq[50];
	FILE *arquivo;
    	int valores_arq[50];
    	int quantidadeValores = 0;
    	
	printf("Digite o nome do arquivo: ");
	for(int i=0; i == '\0'; i++) {
		scanf("%s", &nome_arq[i]);
		if(nome_arq[i] == '\n') nome_arq[i] = '\0';
	}
	
	arquivo = fopen(nome_arq, "r"); //abre o arquivo para leitura
	    
	/* verifica se o arquivo foi aberto com sucesso */
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return 0;
	}

	/* lê os valores inteiros do arquivo */
	while (!feof(arquivo) && quantidadeValores < 50) {
		fscanf(arquivo, "%d", &valores_arq[quantidadeValores]);
		quantidadeValores++;
	}

	fclose(arquivo); //fecha o arquivo
	
	int capacidade_mochila;
    	int itens;
	int i=1;
	
	/* atribui os valores dos arquivos para as variáveis */
	capacidade_mochila = valores_arq[i]; 
	i++; //vai para o próximo valor do arquivo
	
	itens = valores_arq[i];
	i++; //vai para o próximo valor do arquivo
	int inicio_valores = i;
	
	int pesos[itens];
	for(int j=0; j < itens; j++) {
		pesos[j] = valores_arq[i];
		i+=2; //vai para o próximo peso no vetor de valores do arquivo
	}
	
	inicio_valores++;
	i = inicio_valores;
	
	int valores[itens];
	for(int j=0; j < itens; j++) {
		valores[j] = valores_arq[i];
		i+=2;
	}
	
	i--; //como no último for, o índice estava passando de 2 em 2, no final, tem que voltar 1 índice pra continuar percorrendo o vetor normalmente
	
	int solucao[itens];
	for(int j=0; j < itens; j++) {
		solucao[j] = valores_arq[i];
		i++;
	}

	int melhor_solucao = resolver_mochila(itens, valores, pesos, capacidade_mochila, solucao);
	
	if(solucao_otima(itens, melhor_solucao, solucao, valores)) printf("Solucao otima.\n");
	else if(solucao_inviavel(itens, capacidade_mochila, solucao, pesos)) printf("Solucao inviavel.\n");
	else printf("Solucao viavel mas nao otima.\n");
}

