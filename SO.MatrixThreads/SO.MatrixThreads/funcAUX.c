#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcAUX.h"

int primo(int num) {

	for (int i = 2; i <= num -1; i++) {
		if (num % i == 0) {
			return 0;//Não é primo 
		}
	}
	return 1;//É primo

}

void preencheMat(int mat[][DIM]) {
	int linha, coluna;
	srand(time(NULL));//atualiza a semente

	for (linha = 0; linha < DIM; linha++) {
		for (coluna = 0; coluna < DIM; coluna++) {
			mat[linha][coluna] = rand();
		}
	}
}

