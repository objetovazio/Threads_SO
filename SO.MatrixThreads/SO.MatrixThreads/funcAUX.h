#pragma once

//#define DIM (int) 10000 //Dimenção da matriz
//#define NUM_THREAD 100 //Número de threads
//#define PED DIM/NUM_THREAD //Essa divição tem que dar exata, (DIM % NTHREAD = 0 ), NTHREAD tem q ser divisor de DIM
//#define QPED 

#define TRUE 1					
#define FALSE 0

struct bloco {
	int linha_atual;
	int coluna_atual;
};
typedef struct bloco tBloco, *pBloco;


/**
 * Inicializa variáveis globais da matriz
 */
void iniciar_aux(int LINHA_MATRIZ, int COLUNA_MATRIZ, int LINHA_MB, int COLUNA_MB, int NUM_THREADS);

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
int IsPrimo(int num);

/**
 * Retorna o tempo total dado o intevalo passado por parâmetro
 */
double tempo_total_helper(double inicio, double fim);

/**
 * Imprime a matriz
 */
void imprimir_matriz();

int contagem_paralela(struct pthread_t *threads, struct tBloco *blocoVerificado);

void contagem_thread(void *id);

int contagem_numeros_primos(int isSerial);





/*int contaPrimoPED(int** mat, int Nprimo, int indbloc);

void imprimePED(int** mat, int indbloc);

void inicializablocos(int vet[]);

int setbloco(int vet[]);

void liberaMat(int** mat)*/;