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

	if (num > 1) {
		return 1;//É primo
	}
	else {
		return 0;//Não é primo
	}
}

int** criaMat() {
	srand(time(NULL));//atualiza a semente

	int **m = (int**)malloc(DIM * sizeof(int*));

	for (int i = 0; i < DIM; i++) {
		m[i] = (int*)malloc(DIM * sizeof(int)); 
		for (int j = 0; j < DIM; j++) {
			m[i][j] = (rand() % 29990);
		}
	}
	return m;
}

int contaPrimoPED(int** mat, int Nprimo, int indbloc) {

	int cost = PED * indbloc;

	for (int linha = (0 + cost); linha < (PED + cost); linha++) {
		for (int coluna = 0; coluna < DIM; ++coluna) {
			if (primo(mat[linha][coluna]) == 1) {
				Nprimo++;
				//printf("%d [%d][%d]\n", mat[linha][coluna], linha, coluna);
			}
		}
	}
	return Nprimo;
}

void imprimeMat(int** mat) {

	for (int linha = 0; linha < DIM; ++linha) {
		for (int coluna = 0; coluna < DIM; ++coluna) {
			printf("%d ", mat[linha][coluna]);
		}
		printf("\n");
	}
	printf("\n");
}

void imprimePED(int** mat, int indbloc) {

	int cost = PED * indbloc;

	for (int linha = (0 + cost); linha < (PED + cost); linha++) {
		for (int coluna = 0; coluna < DIM; coluna++) {
			printf("%d ", mat[linha][coluna]);
		}
		printf("\n");
	}
	printf("\n");
}

void inicializablocos(int vet[]) {
	for (int i = 0; i < NTHREAD; i++) {
		vet[i] = 0;
	}
}

int setbloco(int vet[]) {
	
	for (int i = 0; i < NTHREAD; i++) {	
		if (vet[i] == 0) {
			vet[i] = 1;
			return i;
		}
	}
	return -1;//todos ocupados
}

void liberaMat(int** mat) {
	for (int i = 0; i < DIM; i++) {
		free(mat[i]);
	}
	free(mat);
}

