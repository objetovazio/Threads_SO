#pragma once

#define DIM (int) 10000 //Dimen��o da matriz
#define NTHREAD 100 //N�mero de threads
#define PED DIM/NTHREAD //Essa divi��o tem que dar exata, (DIM % NTHREAD = 0 ), NTHREAD tem q ser divisor de DIM
#define QPED 

int primo(int num);

int** criaMat();

int contaPrimoPED(int** mat, int Nprimo, int indbloc);

void imprimeMat(int** mat);

void imprimePED(int** mat, int indbloc);

void inicializablocos(int vet[]);

int setbloco(int vet[]);

void liberaMat(int** mat);