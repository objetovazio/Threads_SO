#pragma once

#define DIM 4 //Dimen��o da matriz
#define NTHREAD 2 //N�mero de threads
#define PED DIM/NTHREAD //Essa divi��o tem que dar exata, (DIM % NTHREAD = 0 ), NTHREAD tem q ser divisor de DIM
#define QPED 

int primo(int num);

void preencheMat(int mat[][DIM]);


int contaPrimoPED(int mat[][DIM], int Nprimo, int indbloc);

void imprimeMat(int mat[][DIM]);

void imprimePED(int mat[][DIM], int indbloc);

void inicializablocos(int vet[]);

int setbloco(int vet[]);