//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <pthread.h>
//#include "funcAUX.h"
//
//int tam_linhas_matriz, tam_colunas_matriz, num_threads, total_primos;
//int tam_linhas_bloco, tam_colunas_bloco, total_blocos, contador_blocos;
//double inicio_tempo_bloco, fim_tempo_bloco;
//int **matriz;
//pthread_mutex_t mutex_bloco;
//pthread_mutex_t mutex_count_primos;
//tBloco *bloco_verificado;
//
//void iniciar_aux(int LINHA_MATRIZ, int COLUNA_MATRIZ, int LINHA_MB, int COLUNA_MB, int NUM_THREADS)
//{
//	tam_linhas_matriz = LINHA_MATRIZ;
//	tam_colunas_matriz = COLUNA_MATRIZ;
//	tam_linhas_bloco = LINHA_MB;
//	tam_colunas_bloco = COLUNA_MB;
//	num_threads = NUM_THREADS;
//}
//
//void instanciar_matriz(int qtd_linhas, int qtd_colunas)
//{
//	inicio_tempo_bloco = clock();
//
//	int **m = (int**)malloc(qtd_linhas * sizeof(int*));
//
//	for (int i = 0; i < qtd_linhas; i++)
//	{
//		m[i] = (int*)malloc(qtd_colunas * sizeof(int));
//	}
//
//	fim_tempo_bloco = clock();
//
//	printf("Tempo para instanciar matriz: %.20lf \n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));
//
//	matriz = m;
//}
//
//void preencher_matriz(int inicio, int fim, int seed)
//{
//	srand(seed); // usa sempre a mesma seed
//
//	inicio_tempo_bloco = clock();
//
//	for (int i = 0; i < tam_linhas_matriz; i++)
//	{
//		for (int j = 0; j < tam_colunas_matriz; j++)
//		{
//			matriz[i][j] = (rand() % fim);
//		}
//	}
//
//	fim_tempo_bloco = clock();
//	printf("Tempo para preencher matriz: %.20lf \n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));
//}
//
//int contagem_serial(int **matriz)
//{
//	int total_primos = 0;
//	for (int i = 0; i < tam_linhas_matriz; i++)
//	{
//		for (int j = 0; j < tam_colunas_matriz; j++)
//		{
//			if (is_primo(matriz[i][j])) total_primos++;
//		}
//	}
//
//	return total_primos;
//}
//
//int is_primo(int num) {
//
//	if (num < 2) return FALSE;
//	else if (num >= 2 && num <= 5) return TRUE;
//	else if (num % 2 == 0 || num % 3 == 0) return FALSE;
//	else
//	{
//		int auxiliar = 5;
//		while (auxiliar * auxiliar <= num)
//		{
//			if ((num % auxiliar) == 0) return FALSE;
//			auxiliar++;
//		}
//		return TRUE;
//	}
//}
//
//double tempo_total_helper(double tempo_inicio, double tempo_fim)
//{
//	return  (double)(tempo_fim - tempo_inicio) / CLOCKS_PER_SEC;
//}
//
//void imprimir_matriz() {
//
//	for (int linha = 0; linha < tam_linhas_matriz; ++linha) {
//		for (int coluna = 0; coluna < tam_colunas_matriz; ++coluna) {
//			printf("| %5d |", matriz[linha][coluna]);
//		}
//		printf("\n");
//	}
//	printf("\n");
//}
//
//int contagem_numeros_primos(int isSerial)
//{
//	int resultado;
//	if (isSerial)
//	{
//		printf("\t\t Modo Serial : %d X %d\n\n", tam_linhas_matriz, tam_colunas_matriz);
//		inicio_tempo_bloco = clock();
//		resultado = contagem_serial(matriz);
//		fim_tempo_bloco = clock();
//		printf("Tempo para contar em modo serial: %.20lf \n", tempo_total_helper(inicio_tempo_bloco, fim_tempo_bloco));
//	}
//	else
//	{
//		pthread_t threads[1];
//		tBloco *blocoVerificado = (tBloco*)malloc(sizeof(tBloco*));;
//		blocoVerificado->linha_inicial = blocoVerificado->coluna_inicial = 0;
//
//		pthread_mutex_init(&mutex_count_primos, NULL);
//		pthread_mutex_init(&mutex_bloco, NULL);
//
//		total_blocos = ((tam_linhas_matriz * tam_colunas_matriz) / (tam_linhas_bloco * tam_colunas_bloco));
//
//		inicio_tempo_bloco = clock();
//		resultado = contagem_paralela(threads, blocoVerificado);
//		fim_tempo_bloco = clock();
//
//		pthread_mutex_destroy(&mutex_bloco);
//		pthread_mutex_destroy(&mutex_count_primos);
//	}
//
//	return resultado;
//}
//
//int contagem_paralela(pthread_t *threads, tBloco *bloco_verificado_local)
//{
//	bloco_verificado = bloco_verificado_local;
//
//	for (int i = 0; i < num_threads; i++)
//	{
//		int *thread_id = (int*)malloc(sizeof(int*));
//		*thread_id = i;
//
//		/* Em caso de sucesso, pthread_create retorna 0 */
//		if (pthread_create(&threads[i], NULL, contagem_thread, thread_id) != 0)
//		{
//			free(thread_id);
//			printf("Falha na Thread #%d.\n", i);
//			exit(1);
//		}
//	}
//
//	for (int i = 0; i < num_threads; i++) {
//		/* Em caso de sucesso, pthread_join retorna 0 */
//		if (pthread_join(threads[i], NULL) != 0) {
//			printf("Falha ao retornar a Thread %hi.\n", i);
//			exit(1);
//		}
//	}
//
//	return total_primos;
//}
//
//void* contagem_thread(void *id)
//{
//	short thread_id = *((short*)id);
//	free(id);
//	printf("Thread #%hi iniciada.\n", thread_id);
//	tBloco *bloco_local = malloc(sizeof(tBloco));
//	int contador_primos_local = 0;
//	printf("Thread #%hi: before quantidade_posicoes_macrobloco .\n", thread_id);
//	const int quantidade_posicoes_macrobloco = tam_linhas_bloco * tam_colunas_bloco;
//
//	printf("Thread #%hi: before while.\n", thread_id);
//	while (contador_blocos < total_blocos)
//	{
//		printf("Thread #%hi: Inicio RC Macrobloco.\n", thread_id);
//		//	 In�cio da regi�o cr�tica de macrobloco
//		pthread_mutex_lock(&mutex_bloco);
//		printf("Thread #%hi: Lock Mutex Bloco.\n", thread_id);
//
//		/* Guarda posi��es onde se inicia o macrobloco */
//		bloco_local->linha_inicial = bloco_verificado->linha_inicial;
//		bloco_local->coluna_inicial = bloco_verificado->coluna_inicial;
//
//		printf("Thread #%hi: Guarda posicoes onde se inicia o macrobloco .\n", thread_id);
//
//		/* Guarda onde acaba o macrobloco */
//		bloco_local->linha_final = bloco_local->linha_inicial + tam_linhas_bloco;
//		bloco_local->coluna_final = bloco_local->coluna_inicial + tam_colunas_bloco;
//
//		printf("Thread #%hi: Guarda onde acaba o macrobloco .\n", thread_id);
//
//		/* Atualiza o bloco que representa a matriz para controlar o que j� foi separado para verifica��o */
//		bloco_verificado->coluna_inicial += tam_colunas_bloco;
//		int tem_incremento_linha = bloco_verificado->coluna_inicial / tam_colunas_matriz;
//		if (tem_incremento_linha > 0)
//		{
//			bloco_verificado->linha_inicial += tam_linhas_bloco;
//			bloco_verificado->coluna_inicial = 0;
//		}
//
//		printf("Thread #%hi: Atualiza o bloco que representa a matriz para controlar o que ja foi separado para verificacao .\n", thread_id);
//
//		contador_blocos++;
//
//		// Fim regi�o cr�tica
//		pthread_mutex_unlock(&mutex_bloco);
//		printf("Thread #%hi: Fim RC macrobloco.\n", thread_id);
//
//
//
//		int linha_index = bloco_local->linha_inicial;
//		int coluna_index = bloco_local->coluna_inicial;
//
//		/* Looping pelo tamanho de elementos do macrobloco */
//		/* Para se leu todos os elementos ou se acabou a quantidade de linhas v�lidas da matriz */
//		printf("Thread #%hi: Inicio da contagem. Macrobloco Inicio:%d %d Fim: %d %d.\n", thread_id, bloco_local->linha_inicial, bloco_local->coluna_inicial, bloco_local->linha_final, bloco_local->coluna_final);
//
//		for (int i = 0; i < quantidade_posicoes_macrobloco && linha_index < tam_linhas_matriz; i++)
//		{
//			if (is_primo(matriz[linha_index][coluna_index++])) contador_primos_local++;
//
//			if (coluna_index > tam_colunas_matriz || coluna_index >= bloco_local->coluna_final)
//			{
//				linha_index++;
//				coluna_index = bloco_local->coluna_inicial;
//			}
//		}
//
//		printf("Thread #%hi: FIM da contagem. Macrobloco Inicio:%d %d Fim: %d %d.\n", thread_id, bloco_local->linha_inicial, bloco_local->coluna_inicial, bloco_local->linha_final, bloco_local->coluna_final);
//
//		if (contador_primos_local > 0)
//		{
//			printf("Thread #%hi: Inicio RC Contador Primmos.\n", thread_id);
//			// Regi�o cr�tica do comtador de primos
//			pthread_mutex_lock(&mutex_count_primos);
//			total_primos += contador_primos_local;
//			contador_primos_local = 0;
//			pthread_mutex_unlock(&mutex_count_primos);
//			printf("Thread #%hi: Fim RC Contador Primmos.\n", thread_id);
//		}
//	}
//
//	printf("Thread #%hi finalizada.\n", thread_id);
//	return 0;
//}
//
////
////int contaPrimoPED(int** mat, int Nprimo, int indbloc) {
////
////	int cost = PED * indbloc;
////
////	for (int linha = (0 + cost); linha < (PED + cost); linha++) {
////		for (int coluna = 0; coluna < DIM; ++coluna) {
////			if (primo(mat[linha][coluna]) == 1) {
////				Nprimo++;
////				//printf("%d [%d][%d]\n", mat[linha][coluna], linha, coluna);
////			}
////		}
////	}
////	return Nprimo;
////}
////
//
////
////void imprimePED(int** mat, int indbloc) {
////
////	int cost = PED * indbloc;
////
////	for (int linha = (0 + cost); linha < (PED + cost); linha++) {
////		for (int coluna = 0; coluna < DIM; coluna++) {
////			printf("%d ", mat[linha][coluna]);
////		}
////		printf("\n");
////	}
////	printf("\n");
////}
////
////void inicializablocos(int vet[]) {
////	for (int i = 0; i < NUM_THREAD; i++) {
////		vet[i] = 0;
////	}
////}
////
////int setbloco(int vet[]) {
////
////	for (int i = 0; i < NUM_THREAD; i++) {
////		if (vet[i] == 0) {
////			vet[i] = 1;
////			return i;
////		}
////	}
////	return -1;//todos ocupados
////}
////
////void liberaMat(int** mat) {
////	for (int i = 0; i < DIM; i++) {
////		free(mat[i]);
////	}
////	free(mat);
////}