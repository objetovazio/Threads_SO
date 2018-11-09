#pragma once

#pragma region Includes  
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#pragma endregion 

#pragma region Defines  
#define LINHA_MATRIZ  15000					// Número total de linhas da matriz
#define COLUNA_MATRIZ 15000					// Número total de colunas da matriz

#define LINHA_MB  100						// Quantidade de linhas de um macrobloco
#define COLUNA_MB 100						// Quantidade de colunas de um macrobloco

#define VALOR_MAX 29999						// Valor máximo a ser preenchido na matriz
#define VALOR_MIN 0							// Valor mínimo a ser preenchido na matriz

#define TRUE 1					
#define FALSE 0

#define NUM_THREADS 8						// Número de threads
#define IS_SERIAL FALSE						// TRUE para busca serial; FALSE para busca paralela
#define SEED 10				
#pragma endregion 

#pragma region Variáveis Globais  
struct bloco {
	int linha_inicial;
	int coluna_inicial;

	int linha_final;
	int coluna_final;
};
typedef struct bloco tBloco, *pBloco;

int total_numeros_primos = 0;
double inicio_tempo_execucao, fim_tempo_execucao, tempo_total_execucao = 0;
int total_blocos, contador_blocos;
double inicio_tempo_bloco, fim_tempo_bloco;

int **matriz;
pthread_mutex_t mutex_bloco;
pthread_mutex_t mutex_count_primos;
tBloco *bloco_verificado;
#pragma endregion 

#pragma region Declaração de funções  
/**
 * Instancia e malloca o espaço de memória da matriz
 * que será preenchido posteriormente
 */
void instanciar_matriz(int qtd_linhas, int qtd_colunas);

/**
 * Preenche a matriz com números aleatórios
 */
void preencher_matriz(int inicio, int fim, int seed);

/**
 * Faz a contagem de números primos de forma serial (sequencial)
 */
int contagem_serial(int **matriz);

/**
 * Verifica se o número passado como parâmetro é Primo
 */
int is_primo(int num);

/**
 * Retorna o tempo total dado o intevalo passado por parâmetro
 */
double tempo_total_helper(double inicio, double fim);

/**
 * Imprime a matriz
 */
void imprimir_matriz();

/**
 * Desaloca matriz
 */
void desalocar_matriz(int qtd_linhas, int qtd_colunas);

int contagem_paralela(pthread_t threads[NUM_THREADS], tBloco *blocoVerificado);

void* contagem_thread(void *id);

int contagem_numeros_primos(int isSerial);
#pragma endregion

int main()
{
	printf("\t\t..::Iniciando o programa::..\n\n");
	printf("Matrix: %dx%d\tMacrobloco: %dx%d\n", LINHA_MATRIZ, COLUNA_MATRIZ, LINHA_MB, COLUNA_MB);
	printf("Serial: %s\t%d Threads\n\n", IS_SERIAL ? "Sim" : "Nao", NUM_THREADS);

	inicio_tempo_execucao = clock();
	printf("Instanciando matriz: ");
	instanciar_matriz(LINHA_MATRIZ, COLUNA_MATRIZ);

	printf("Preenchendo matriz: ");
	preencher_matriz(VALOR_MIN, VALOR_MAX, SEED);

	printf("Iniciando Contagem\n");
	total_numeros_primos = contagem_numeros_primos(IS_SERIAL);
	fim_tempo_execucao = clock();

	printf("Total de numeros primos encontrados: %d\n", total_numeros_primos);
	printf("Tempo total de execucao: %.3lf segs\n", tempo_total_helper(inicio_tempo_execucao, fim_tempo_execucao));

	printf("\nDesalocando memoria.\n");
	desalocar_matriz(LINHA_MATRIZ, COLUNA_MATRIZ);
	printf("\n\t\t..:: Fim do Programa::..\n");


	//imprimir_matriz();

	getchar();
	return 0;
}

#pragma region Funções  
void instanciar_matriz(int qtd_linhas, int qtd_colunas)
{
	inicio_tempo_bloco = clock();

	int **m = (int**)malloc(qtd_linhas * sizeof(int*));

	for (int i = 0; i < qtd_linhas; i++)
	{
		m[i] = (int*)malloc(qtd_colunas * sizeof(int));
	}

	fim_tempo_bloco = clock();

	printf("%.3lf segs\n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));

	matriz = m;
}

void desalocar_matriz(int qtd_linhas, int qtd_colunas)
{

	int **m = matriz;

	for (int i = 0; i < qtd_linhas; i++)
	{
		free(m[i]);
	}

	free(m);
}

void preencher_matriz(int inicio, int fim, int seed)
{
	srand(seed); // usa sempre a mesma seed

	inicio_tempo_bloco = clock();

	for (int i = 0; i < LINHA_MATRIZ; i++)
	{
		for (int j = 0; j < COLUNA_MATRIZ; j++)
		{
			matriz[i][j] = (rand() % fim);
		}
	}

	fim_tempo_bloco = clock();
	printf("%.3lf segs\n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));
}

int contagem_serial(int **matriz)
{
	int total_primos = 0;
	for (int i = 0; i < LINHA_MATRIZ; i++)
	{
		for (int j = 0; j < COLUNA_MATRIZ; j++)
		{
			if (is_primo(matriz[i][j])) total_primos++;
		}
	}

	return total_primos;
}

int contagem_numeros_primos(int isSerial)
{
	int resultado;
	if (isSerial)
	{
		inicio_tempo_bloco = clock();
		resultado = contagem_serial(matriz);
		fim_tempo_bloco = clock();
		printf("Tempo para contar em modo serial: %.3lf segs\n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));
	}
	else
	{
		pthread_t threads[NUM_THREADS];
		tBloco *blocoVerificado = (tBloco*)malloc(sizeof(tBloco*));;
		blocoVerificado->linha_inicial = blocoVerificado->coluna_inicial = 0;

		pthread_mutex_init(&mutex_count_primos, NULL);
		pthread_mutex_init(&mutex_bloco, NULL);

		total_blocos = ((LINHA_MATRIZ * COLUNA_MATRIZ) / (LINHA_MB * COLUNA_MB));

		inicio_tempo_bloco = clock();
		resultado = contagem_paralela(threads, blocoVerificado);
		fim_tempo_bloco = clock();

		printf("Tempo para contar com threads: %.3lf segs\n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));

		pthread_mutex_destroy(&mutex_bloco);
		pthread_mutex_destroy(&mutex_count_primos);
	}

	return resultado;
}

int contagem_paralela(pthread_t *threads, tBloco *bloco_verificado_local)
{
	bloco_verificado = bloco_verificado_local;

	printf("Threads Iniciadas: ");

	for (int i = 0; i < NUM_THREADS; i++)
	{
		int *thread_id = (int*)malloc(sizeof(int*));
		*thread_id = i;

		/* Em caso de sucesso, pthread_create retorna 0 */
		if (pthread_create(&threads[i], NULL, contagem_thread, thread_id) != 0)
		{
			free(thread_id);
			printf("Falha na Thread #%d.\n", i);
			getchar();
			exit(1);
		}
	}

	for (int i = 0; i < NUM_THREADS; i++) {
		/* Em caso de sucesso, pthread_join retorna 0 */
		if (pthread_join(threads[i], NULL) != 0) {
			printf("Falha ao retornar a Thread %hi.\n", i);
			getchar();
			exit(1);
		}
	}

	printf("\n\n");
	return total_numeros_primos;
}

void* contagem_thread(void *id)
{
	short thread_id = *((short*)id);
	free(id);
	printf("#%hi ", thread_id);
	tBloco *bloco_local = malloc(sizeof(tBloco));
	int contador_primos_local = 0;
	const int quantidade_posicoes_macrobloco = LINHA_MB * COLUNA_MB;

	while (contador_blocos < total_blocos)
	{
		//	 Início da região crítica de macrobloco
		pthread_mutex_lock(&mutex_bloco);

		/* Guarda posições onde se inicia o macrobloco */
		bloco_local->linha_inicial = bloco_verificado->linha_inicial;
		bloco_local->coluna_inicial = bloco_verificado->coluna_inicial;

		/* Guarda onde acaba o macrobloco */
		bloco_local->linha_final = bloco_local->linha_inicial + LINHA_MB;
		bloco_local->coluna_final = bloco_local->coluna_inicial + COLUNA_MB;

		/* Atualiza o bloco que representa a matriz para controlar o que já foi separado para verificação */
		bloco_verificado->coluna_inicial += COLUNA_MB;
		int tem_incremento_linha = bloco_verificado->coluna_inicial / COLUNA_MATRIZ;
		if (tem_incremento_linha > 0)
		{
			bloco_verificado->linha_inicial += LINHA_MB;
			bloco_verificado->coluna_inicial = 0;
		}

		contador_blocos++;

		// Fim região crítica
		pthread_mutex_unlock(&mutex_bloco);

		int linha_index = bloco_local->linha_inicial;
		int coluna_index = bloco_local->coluna_inicial;

		/* Looping pelo tamanho de elementos do macrobloco */
		/* Para se leu todos os elementos ou se acabou a quantidade de linhas válidas da matriz */

		for (int i = 0; i < quantidade_posicoes_macrobloco && linha_index < LINHA_MATRIZ; i++)
		{
			if (is_primo(matriz[linha_index][coluna_index++])) contador_primos_local++;

			if (coluna_index > COLUNA_MATRIZ || coluna_index >= bloco_local->coluna_final)
			{
				linha_index++;
				coluna_index = bloco_local->coluna_inicial;
			}
		}

		if (contador_primos_local > 0)
		{
			// Região crítica do comtador de primos
			pthread_mutex_lock(&mutex_count_primos);
			total_numeros_primos += contador_primos_local;
			contador_primos_local = 0;
			pthread_mutex_unlock(&mutex_count_primos);
		}
	}

	return 0;
}

int is_primo(int num) {

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

	for (int linha = 0; linha < LINHA_MATRIZ; ++linha) {
		for (int coluna = 0; coluna < COLUNA_MATRIZ; ++coluna) {
			printf("| %5d |", matriz[linha][coluna]);
		}
		printf("\n");
	}
	printf("\n");
}

#pragma endregion 
