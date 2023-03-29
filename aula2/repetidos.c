#include <stdio.h>

/* função para preencher o vetor */
void preencher(int n, int v[]) {

	for(int i=0; i < n; i++) 
		scanf("%d", &v[i]);
	printf("\n");
}

/* função para printar o vetor */
void printar(int n, int v[]) {

	for(int i=0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");
}

int main() {
	
	int n;
	
	printf("Digite a quantidade de numeros: ");
	scanf("%d", &n);
	
	int v[n];
	
	printf("Digite a sequencia de numeros: ");
	preencher(n, v);
	
	/* percorrendo o vetor */
	for(int i=0; i < n; i++) { 
		if(v[i] == v[i+1]) {
			/* leva o número repetido para o final do vetor */
			for(int j=i; j <= (n-1); j++) { 
				int aux;
				aux = v[j+1];
				v[j+1] = v[j];
				v[j] = aux;
			}
			n--; // diminui o tamanho do vetor para não printar os números repetidos que estão no final
			i--; // é necessário conferir de novo em caso de números que se repetem mais de uma vez
		}
	}
	
	printf("Resultado: existe(m) %d numero(s) na sequencia final\n", n);
	printf("Sequencia final: ");
	printar(n, v);
}

