/**********************************************************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Alunos: Caio Palhares e Laura Pianetti

Data: 01/06/2023

***********************************************************/

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
	free(nome);
}

typedef int TipoChave;

typedef struct {
  int Chave;
  int Tipo;
  int NumElementos;
  int PontoMedio;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* implementação do ziviani para criar uma lista vazia */
void FLVazia(TipoLista *Lista) { 
    Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Primeiro;
    Lista -> Primeiro -> Prox = NULL;
}

/* implementação do ziviani para inserir um item na lista */
void Insere(TipoItem x, TipoLista *Lista) { 
	Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
	Lista -> Ultimo = Lista -> Ultimo -> Prox;
	Lista -> Ultimo -> Item = x;
	Lista -> Ultimo -> Prox = NULL;
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
int quant_segmentos(int* vetor, int tamanho, int sel) {

	int quant_segmentos=0;
	int vetor_ordenado[tamanho];
	
	for(int i=0; i < tamanho; i++) {
		vetor_ordenado[i] = vetor[i];
	}

	ordenar(vetor_ordenado, tamanho);

	/* para o vetor ordenado calcula a quantidade de segmentos */
	if(sel == 0) {
		for(int i=0; i < tamanho; i++) {
			if(vetor_ordenado[i] != vetor_ordenado[i-1]) quant_segmentos++;	
		}
	}

	/* para o vetor não ordenado, calcula a quantidade de vezes que acontece uma mudança de segmento */
	if(sel == 1) {
		for(int i=0; i < tamanho; i++) {
			if(vetor[i] != vetor[i-1]) quant_segmentos++;
		}
		quant_segmentos++;
	}

	return quant_segmentos; 
}

/* função que retorna um vetor com os tipos de segmento (números referentes de cada segmento) */
int* segmento(int *vetor, int tamanho) {

	int *tipo_segmento;
	tipo_segmento = (int*) malloc(tamanho*sizeof(int));
	
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

/* função que analisa o vetor e retorna a chave e o numero de elementos de cada segmento */
int** analisar_vetor(int* vetor, int tamanho, int* k) {
    	
	/* aloca a matriz dinamicamente */
	int** retorno = (int**)malloc(2 * sizeof(int*));
	retorno[0] = (int*)malloc(tamanho * sizeof(int));
	retorno[1] = (int*)malloc(tamanho * sizeof(int));
    	
    int *tipo_segmento;
	tipo_segmento = (int*) malloc(sizeof(int));
	
	tipo_segmento = segmento(vetor, tamanho); //vetor dos tipos de segmentos contidos no vetor que está sendo analisado
	
	int max_vetor = quant_segmentos(vetor, tamanho, 0); //tamanho máximo do vetor tipo_segmento
    int j = 0; //indice da coluna que vai ser escrita 
	
	for (int i=0; i < tamanho; i++) {
		int c = 0; //indice do vetor tipo_segmento
		if (i == 0 || vetor[i] != vetor[i-1]) { //se tiver uma mudança de segmento
				while(c < max_vetor) {
					if(vetor[i] == tipo_segmento[c]) { //descobre qual é o tipo de segmento do número
						retorno[0][j] = c+1; 
						c = 0; //zera o índice do vetor tipo_segmento para a próxima comparação
						break; //sai do while porque não precisa fazer mais comparações
					}
					else //se ele não for igual ao tipo de segmento
						c++; //vai para o próximo
				}
				retorno[1][j] = 1; //inicia a coluna da segunda linha com 1
				j++; //vai para a próxima coluna
		} 
		else //se os números estiverem no mesmo segmento
			retorno[1][j-1]++; //soma um na coluna da segunda linha, que representa a quantidade de elementos repetidos
	}

	/* redimensiona a matriz para o número exato de segmentos encontrados */
	retorno[0] = (int*)realloc(retorno[0], j * sizeof(int));
	retorno[1] = (int*)realloc(retorno[1], j * sizeof(int));
	
	*k = j;
	
	return retorno;
}

/* função que calcula o ponto médio de cada segmento */
int* pontomedio(int* vetor, int tamanho) {

	int p=0, q=0; //variáveis auxiliares
	
	/*criando o vetor que vai guardar os pontos médios dos segmentos*/
	int* pm;
	pm = (int*) malloc(tamanho*sizeof(int));

	int c=0; //índice do vetor pm

	for(int i=0; i < tamanho+1; i++) {
		if(vetor[i] != vetor[i-1]) {
			q = i; //o último num do segmento vai ser o q
			pm[c] = (p+q)/2; //calcula o ponto medio
			c++; //vai para o próximo elemento do vetor
			p = i-1; //o primeiro elemento do próximo segmento é i-1
		}
	}

	return pm;
}

/* função que confere se o padrão foi encontrado */
int padrao(int** resposta, int tamanho) {

	int res = 0; //variável de retorno
	int c = 0;
	for (int i = 0; i < tamanho; i++) {
		c++;
		if(resposta[0][i-1] == 1) i--;
		if(resposta[0][i] == 1) {
			i++;
			if(resposta[0][i] == 3) {
				i++;
				if(resposta[0][i] == 2) {
					i++;
					if(resposta[0][i] == 3) {
						i++;
						if(resposta[0][i] == 1) {
							res = 1;
							break;
						}
					}
				}
			}
		}
	}

	return res;
}

int main() {

    printf("Digite o nome do arquivo: "); //pede para o usuário digitar o nome do arquivo
    ler_arquivo(); //pega os valores lidos pelo arquivo

    TipoLista lista; //declarando a lista
    TipoItem item; //declarando o item

	FLVazia(&lista); //criando uma lista vazia

	/*criando um vetor dos tipos de segmento*/
	int *tipo_segmento = segmento(vetor, tamanho);

	/*criando uma matriz em que a primeira coluna representa a Chave e a segunda o NumElementos*/
	int max_resposta = quant_segmentos(vetor, tamanho, 1); //quantidade de linhas da matriz resposta
	int k; //quantidade de colunas da matriz resposta
	int** resposta = analisar_vetor(vetor, tamanho, &k);

	/*criando um vetor dos pontos médios*/
	int* ponto_medio = pontomedio(vetor, tamanho);

	/*insere cada item na lista, com seus respectivos campos*/
  	for (int i = 0; i < max_resposta; i++) { 
		item.Chave = resposta[0][i];
		item.Tipo = tipo_segmento[item.Chave-1];
		item.NumElementos = resposta[1][i];
		item.PontoMedio = ponto_medio[i];
		Insere(item, &lista);
    }

	int resultado = padrao(resposta, max_resposta); //cria uma variável com o resultado (se o padrão foi encontrado ou não)

	if(resultado == 1) printf("Resultado: Padrao encontrado.\n");
	else printf("Resultado: Padrao nao encontrado.\n");

	/* liberar a memória alocada dinamicamente */
	free(resposta[0]);
	free(resposta[1]);
	free(resposta);
}