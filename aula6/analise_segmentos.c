/*	Dupla: Caio Palhares e Laura Pianetti 
	Esse programa separa um vetor em segmentos e analisa qual tipo de segmento está se repetindo no vetor */

#include <stdio.h>
#include <stdlib.h>

int *vetor; //vetor que vai ser lido pelo arquivo
int tamanho; //tamanho do vetor lido pelo arquivo

/* função para ler arquivo */
void ler_arquivo() {

	/* lendo o nome do arquivo */	
	char *nome = (char*) malloc(100 *sizeof(char));	
	scanf("%s", nome);
	
	/* abre o arquivo para leitura */
	FILE *arquivo = fopen(nome, "r");
	
	/* lê o tamanho do vetor*/
	fscanf(arquivo, "%d ", &tamanho);
	
	/* alocando dinamicamente o vetor */
	vetor = (int*) malloc(tamanho*(sizeof(int))); 
	
	/* lê os valores do arquivo */
	for(int i=0; i < tamanho; i++) {
		fscanf(arquivo, "%d ", &vetor[i]);
	}

	/* fecha o arquivo */
	fclose(arquivo);
}

/* função para ordenar vetores */
int* ordenar(int *vetor, int tamanho) {

	for(int i=0; i < tamanho; i++) {
		for(int j=(i+1); j < (tamanho-1); j++) {
			int aux;
			if(vetor[i] > vetor[j]) {
				aux = vetor[j];
				vetor[j] = vetor[i];
				vetor[i] = aux; 
			}
		}
	}
	
	return vetor;
}

/* função que calcula a quantidade de segmentos do vetor */
int quant_segmentos(int *vetor, int tamanho) {

	int quant_segmentos=0;
	int vetor_ordenado[tamanho];
	
	for(int i=0; i < tamanho; i++) {
		vetor_ordenado[i] = vetor[i];
	}

	ordenar(vetor_ordenado, tamanho);

	for(int i=0; i < tamanho; i++) {
		if(vetor_ordenado[i] != vetor_ordenado[i-1]) quant_segmentos++;
	}
	
	return quant_segmentos; 
}

/* função que cria um vetor com os numeros referentes de cada segmento*/
int* segmento(int *vetor, int tamanho) {

	int *tipo_segmento;
	tipo_segmento = (int*) malloc(sizeof(int));
	
	int vetor_ordenado[tamanho];
	
	for(int i=0; i < tamanho; i++) {
		vetor_ordenado[i] = vetor[i];
	}
	ordenar(vetor_ordenado, tamanho);
	
	int c=0;
	for (int i=0; i < tamanho; i++) {
		if (i == 0 || vetor_ordenado[i] != vetor_ordenado[i-1]) {
			tipo_segmento[c] = vetor_ordenado[i];
			c++;
		}
    }
        
    return tipo_segmento;
}

/* função que analisa o vetor */
int** analisar_vetor(int* vetor, int tamanho, int* k) {
    	
	/* aloca a matriz dinamicamente */
	int** matriz = (int**)malloc(2 * sizeof(int*));
	matriz[0] = (int*)malloc(tamanho * sizeof(int));
	matriz[1] = (int*)malloc(tamanho * sizeof(int));
    	
    int *tipo_segmento;
	tipo_segmento = (int*) malloc(sizeof(int));
	
	tipo_segmento = segmento(vetor, tamanho); //vetor dos tipos de segmentos contidos no vetor que está sendo analisado
	
	int max_vetor = quant_segmentos(vetor, tamanho); //tamanho máximo do vetor tipo_segmento
    int j = 0; //indice da coluna que vai ser escrita 
	
	for (int i=0; i < tamanho; i++) {
		int c = 0; //indice do vetor tipo_segmento
		if (i == 0 || vetor[i] != vetor[i-1]) { //se tiver uma mudança de segmento
				while(c < max_vetor) {
					if(vetor[i] == tipo_segmento[c]) { //descobre qual é o tipo de segmento do número
						matriz[0][j] = c+1; 
						c = 0; //zera o índice do vetor tipo_segmento para a próxima comparação
						break; //sai do while porque não precisa fazer mais comparações
					}
					else //se ele não for igual ao tipo de segmento
						c++; //vai para o próximo
				}
				matriz[1][j] = 1; //inicia a coluna da segunda linha com 1
				j++; //vai para a próxima coluna
		} 
		else //se os números estiverem no mesmo segmento
			matriz[1][j-1]++; //soma um na coluna da segunda linha, que representa a quantidade de elementos repetidos
	}

	/* redimensiona a matriz para o número exato de segmentos encontrados */
	matriz[0] = (int*)realloc(matriz[0], j * sizeof(int));
	matriz[1] = (int*)realloc(matriz[1], j * sizeof(int));
	
	*k = j;
	
	return matriz;
}

int main() {
    	
	printf("Digite o nome do arquivo: "); //pede para o usuário digitar o nome do arquivo
	ler_arquivo(); //pega os valores lidos pelo arquivo
	
	int k; //quantidade de colunas da matriz

	int** matriz = analisar_vetor(vetor, tamanho, &k);

	printf("Matriz:\n");
	
	/* printando a primeira linha da matriz */
	for (int j = 0; j < k; j++) {
		printf("%d ", matriz[0][j]);
	}
	printf("\n");

	/* printando a segunda linha da matriz */
	for (int j = 0; j < k; j++) {
		printf("%d ", matriz[1][j]);
	}
	printf("\n");

	/* liberar a memória alocada dinamicamente */
	free(matriz[0]);
	free(matriz[1]);
	free(matriz);
}
