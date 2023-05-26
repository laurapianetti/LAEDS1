/*Programa que calcula o mdc entre dois números inteiros*/

#include <stdio.h>

/*função paracalcular o mdc*/ 
int mdc(int a, int b) {

	int ret;
	
	if(a % b == 0) 
		ret = b;
	else
		ret = mdc(a, a % b);
	
	return ret;
}

int main() {

	int a, b, res;
	
	printf("Digite dois numeros inteiros: ");
	scanf("%d %d", &a, &b);
	
	if (b > a) { //lógica para inverter os valores se b for maior que a
	
		int aux;
		aux = b;
		b = a;
		a = aux;
	}
	
	res = mdc(a, b);
	printf("Resultado: %d\n", res);
}
