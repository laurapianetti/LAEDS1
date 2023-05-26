/* Programa que calcula a potência de um número */

#include <stdio.h>

/* função para calcular a potência de um número */
int multi(int base, int exp) {

	int ret;
	
	if(exp == 0) 
		ret = 1;
	else
		ret = base * multi(base, exp-1);
			
	return ret;
}

int main() {

	int b, e, res;
	printf("Digite a base e o expoente inteiros: ");
	scanf("%d %d", &b, &e);
	res = multi(b, e);
	printf("Resultado: %d\n", res);	
}
