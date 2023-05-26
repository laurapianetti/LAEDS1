#include <stdio.h>
#include <stdlib.h>

int* soma(int **p, int n) {
	
	int *ret;
	ret = malloc(2 *sizeof(int));
	int soma_fileiras=0, soma_caixas=0, maior_soma=0;
	
	for(int i=0; i < n; i++) { 
		soma_fileiras += soma_caixas; //depois de ter somado o valor total das caixas da fileira, adiciona a soma total das fileiras
		soma_caixas = 0; //reinicia a soma das caixas para a proxima fileira
		for(int j=0; j < (i+1); j++) {
			soma_caixas += p[i][j]; //soma as caixas da fileira
			soma_fileiras += p[i][j]; //soma o valor da(s) fileira(s) anteriores ao valor da caixa
			if(soma_fileiras > maior_soma) {
				maior_soma = soma_fileiras;
				ret[0] = (i+1); //armazenando a melhor fileira
				ret[1] = (j+1); //armazenando a melhor caixa
				//soma 1 porque a contagem começa no 0
			}
			soma_fileiras -= p[i][j]; //tira o valor da caixa, para somr a próxima da fileira
		}
	}
	return ret;
}

int main() {

	int **caixa, quant_fileiras;
	int *resp; 
	char nome_arq[50];
	FILE *arq;
	
	/*lendo os valores do arquivo*/
	printf("Digite o nome do arquivo de entrada: ");
	for(int i=0; i == '\0'; i++) {
		scanf("%s", &nome_arq[i]);
		if(nome_arq[i] == '\n') nome_arq[i] = '\0';
	}
	
	arq = fopen(nome_arq, "r");
	
	if(arq == NULL) printf("Erro ao abrir arquivo. \n");
	
	fscanf(arq, "%d", &quant_fileiras);
	
	/* alocando dinamicamnete a matriz caixa */
	caixa = malloc(quant_fileiras *sizeof(int *));
	
	for(int i=0; i < quant_fileiras; i++) {
		caixa[i] = malloc((i+1) *sizeof(int));
	} 
	
	/* preenchendo a matriz com os valores lidos no arquivo */
	for(int i=0; i < quant_fileiras; i++) {
		for(int j=0; j < (i+1); j++) fscanf(arq, "%d", &caixa[i][j]);
	}
	
	resp = soma(caixa, quant_fileiras); //guarda o vetor com as somas das caixas na variável resp
	printf("Resposta: fileira %d, caixa %d.\n", resp[0], resp[1]); //printa as primeiras posiçoes do vetor resposta (melhor solução)
}
