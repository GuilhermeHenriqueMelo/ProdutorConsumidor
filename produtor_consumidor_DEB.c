#include <stdio.h> 
#include <pthread.h> 


pthread_cond_t buffer_cheio = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_vazio = PTHREAD_COND_INITIALIZER;


#define TOTAL 50
int posicoes_ocupadas=0;

int valor=0;

int buffer[TOTAL];

pthread_mutex_t mutexP;
pthread_mutex_t mutexC;


void *produtor(void *argumentos){
	
	while (1){
		if (posicoes_ocupadas == TOTAL) {
			printf("!!! Produtor Esperando   !!!\n");
			pthread_cond_wait(&buffer_cheio, &mutexP); // Estou tentando com esses mutex's! Caso não dê certo, utilizar os mutex's que a professora criou!!!
		} else {
			pthread_mutex_lock(&mutexP);
		 
			buffer[posicoes_ocupadas] = valor;
			printf("Valor produzido: %d\n", buffer[posicoes_ocupadas]);
			valor++;
			posicoes_ocupadas++;
		
			pthread_mutex_unlock(&mutexP);
		}
		
	}

	pthread_exit(NULL);
}

void *consumidor(void *argumentos){	

	int leitura;

	while(1){
		if (posicoes_ocupadas == 0) {
			printf("!!!  Consumidor Esperando  !!!\n");
			pthread_cond_wait(&buffer_vazio, &mutexC);
		} else {
			pthread_mutex_lock(&mutexC);

			leitura = buffer[posicoes_ocupadas];
			printf("Valor lido: %d\n", leitura);
			posicoes_ocupadas--;
		
			pthread_mutex_unlock(&mutexC);
		}

	}

	pthread_exit(NULL);
}

int main (){
pthread_t thread_produtor;
pthread_t thread_consumidor;

	pthread_mutex_init(&mutexC, NULL);
	pthread_mutex_init(&mutexP, NULL);

// Criando thread do produtor
	pthread_create(&thread_produtor, NULL, produtor, NULL);
// Criando thread do consumidor
	pthread_create(&thread_consumidor, NULL, consumidor, NULL);

	pthread_exit(NULL);
	return 0; /* O programa não vai chegar aqui. */
}