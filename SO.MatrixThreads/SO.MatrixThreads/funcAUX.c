#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "funcAUX.h"

int tam_linhas_matriz, tam_colunas_matriz, num_threads, total_primos;

int tam_linhas_bloco, tam_colunas_bloco, max_blocos, count_blocos;

double inicio_tempo_execucao, fim_tempo_execucao, tempo_total_execucao = 0;

double inicio_tempo_bloco, fim_tempo_bloco;

int **matriz;

pthread_mutex_t mutex_bloco;
pthread_mutex_t mutex_count_primos;

void iniciar_aux(int LINHA_MATRIZ, int COLUNA_MATRIZ, int LINHA_MB, int COLUNA_MB, int NUM_THREADS)
{
	tam_linhas_matriz = LINHA_MATRIZ;
	tam_colunas_matriz = COLUNA_MATRIZ;
	tam_linhas_matriz = LINHA_MB;
	tam_colunas_bloco = COLUNA_MATRIZ;
	num_threads = NUM_THREADS;
}

void instanciar_matriz(int qtd_linhas, int qtd_colunas)
{
	inicio_tempo_bloco = clock();


	int **m = (int**)malloc(qtd_linhas * sizeof(int*));

	for (int i = 0; i < qtd_linhas; i++)
	{
		m[i] = (int*)malloc(qtd_colunas * sizeof(int));
	}

	fim_tempo_bloco = clock();

	printf("Tempo para instanciar matriz: %.20lf \n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));

	matriz = m;
}

void preencher_matriz(int inicio, int fim, int seed)
{
	srand(seed); // usa sempre a mesma seed

	inicio_tempo_bloco = clock();

	for (int i = 0; i < tam_linhas_matriz; i++)
	{
		for (int j = 0; j < tam_colunas_matriz; j++)
		{
			matriz[i][j] = (rand() % fim);
		}
	}

	fim_tempo_bloco = clock();
	printf("Tempo para preencher matriz: %.20lf \n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));
}

int contagem_serial(int **matriz)
{
	int total_primos = 0;
	for (int i = 0; i < tam_linhas_matriz; i++)
	{
		for (int j = 0; j < tam_colunas_matriz; j++)
		{
			if (IsPrimo(matriz[i][j])) total_primos++;
		}
	}

	return total_primos;
}

int IsPrimo(int num) {

	if (num < 2) return FALSE;
	else if (num >= 2 && num <= 5) return TRUE;
	else if (num % 2 == 0 || num % 3 == 0) return FALSE;
	else
	{
		int auxiliar = 5;
		while (auxiliar * auxiliar <= num)
		{
			if ((num % auxiliar) == 0) return FALSE;
			auxiliar++;
		}
		return TRUE;
	}
}

double tempo_total_helper(double tempo_inicio, double tempo_fim)
{
	return  (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;
}

void imprimir_matriz() {

	for (int linha = 0; linha < tam_linhas_matriz; ++linha) {
		for (int coluna = 0; coluna < tam_colunas_matriz; ++coluna) {
			printf("| %5d |", matriz[linha][coluna]);
		}
		printf("\n");
	}
	printf("\n");
}

int contagem_numeros_primos(int isSerial)
{
	int resultado;
	if (isSerial)
	{
		inicio_tempo_bloco = clock();
		resultado = contagem_serial(matriz);
		fim_tempo_bloco = clock();
		printf("Tempo para contar em modo serial: %.20lf \n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));
	}
	else
	{
		pthread_t *threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t*));
		tBloco *blocoVerificado =  (tBloco*)malloc(sizeof(tBloco*));;
		blocoVerificado->linhaAtual = blocoVerificado->colunaAtual = 0;

		pthread_mutex_init(&mutex_count_primos, NULL);
		pthread_mutex_init(&mutex_bloco, NULL);

		max_blocos = (tam_linhas_matriz * tam_colunas_matriz) / (tam_linhas_bloco * tam_colunas_bloco);

		inicio_tempo_bloco = clock();
		resultado = contagem_paralela(threads, blocoVerificado);
		fim_tempo_bloco = clock();

		//contagem_paralela(matriz);
	}

	return resultado;
}

int contagem_paralela(pthread_t *threads, tBloco *blocoVerificado)
{
	for (int i = 0; i < num_threads; i++)
	{
		int *thread_id = (int*)malloc(sizeof(int*));
		*thread_id = i;

		pthread_create(&threads[i], NULL, contagem_thread, thread_id);
	}

	return 0;
}

int contagem_thread(void *id)
{
	short thread_id = *((short*)id);
	free(id);
	printf("Thread #%hi iniciada.\n", thread_id);

	return 0;
}

//
//int contaPrimoPED(int** mat, int Nprimo, int indbloc) {
//
//	int cost = PED * indbloc;
//
//	for (int linha = (0 + cost); linha < (PED + cost); linha++) {
//		for (int coluna = 0; coluna < DIM; ++coluna) {
//			if (primo(mat[linha][coluna]) == 1) {
//				Nprimo++;
//				//printf("%d [%d][%d]\n", mat[linha][coluna], linha, coluna);
//			}
//		}
//	}
//	return Nprimo;
//}
//

//
//void imprimePED(int** mat, int indbloc) {
//
//	int cost = PED * indbloc;
//
//	for (int linha = (0 + cost); linha < (PED + cost); linha++) {
//		for (int coluna = 0; coluna < DIM; coluna++) {
//			printf("%d ", mat[linha][coluna]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//
//void inicializablocos(int vet[]) {
//	for (int i = 0; i < NUM_THREAD; i++) {
//		vet[i] = 0;
//	}
//}
//
//int setbloco(int vet[]) {
//
//	for (int i = 0; i < NUM_THREAD; i++) {
//		if (vet[i] == 0) {
//			vet[i] = 1;
//			return i;
//		}
//	}
//	return -1;//todos ocupados
//}
//
//void liberaMat(int** mat) {
//	for (int i = 0; i < DIM; i++) {
//		free(mat[i]);
//	}
//	free(mat);
//}