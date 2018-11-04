#pragma once

//#define DIM (int) 10000 //Dimen��o da matriz
//#define NUM_THREAD 100 //N�mero de threads
//#define PED DIM/NUM_THREAD //Essa divi��o tem que dar exata, (DIM % NTHREAD = 0 ), NTHREAD tem q ser divisor de DIM
//#define QPED 

#define TRUE 1					
#define FALSE 0

struct bloco {
	int linha_atual;
	int coluna_atual;
};
typedef struct bloco tBloco, *pBloco;


/**
 * Inicializa vari�veis globais da matriz
 */
void iniciar_aux(int LINHA_MATRIZ, int COLUNA_MATRIZ, int LINHA_MB, int COLUNA_MB, int NUM_THREADS);

/**
 * Instancia e malloca o espa�o de mem�ria da matriz
 * que ser� preenchido posteriormente
 */
void instanciar_matriz(int qtd_linhas, int qtd_colunas);

/**
 * Preenche a matriz com n�meros aleat�rios
 */
void preencher_matriz(int inicio, int fim, int seed);

/**
 * Faz a contagem de n�meros primos de forma serial (sequencial)
 */
int contagem_serial(int **matriz);

/**
 * Verifica se o n�mero passado como par�metro � Primo
 */
int IsPrimo(int num);

/**
 * Retorna o tempo total dado o intevalo passado por par�metro
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