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

void preencheMat(int mat[][DIM]) {
	srand(time(NULL));//atualiza a semente

	for (int linha = 0; linha < DIM; linha++) {
		for (int coluna = 0; coluna < DIM; coluna++) {
			mat[linha][coluna] = (rand() % 10);
		}
	}
}

int contaPrimoPED(int mat[][DIM], int Nprimo, int indbloc) {

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

void imprimeMat(int mat[][DIM]) {

	for (int linha = 0; linha < DIM; ++linha) {
		for (int coluna = 0; coluna < DIM; ++coluna) {
			printf("%d ", mat[linha][coluna]);
		}
		printf("\n");
	}
	printf("\n");
}

void imprimePED(int mat[][DIM], int indbloc) {

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

