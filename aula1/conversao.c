#include <stdio.h>

void dec2bin(int dec) {

	int bin;
	bin = dec % 2;
	if(dec >= 2) {
		dec2bin(dec/2);
	}
	printf("%d", bin);
}

int main() {

	int num;
	printf("Digite um numero inteiro: ");
	scanf("%d", &num);
	printf("Resultado: ");
	dec2bin(num);
}

