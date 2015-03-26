#include <pthread.h>
#include <stdio.h>

int i = 0;
	
void *thread(void *tid) {
    for(int j = 0; j < 400000000; j++) {
		i++;
	}
	pthread_exit(NULL);
}

int main () {
	void * status;
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread, (void *)1);
    pthread_create(&thread2, NULL, thread, (void *)2);
	pthread_join(thread1, &status);
	pthread_join(thread2, &status);
	printf("%d\n", i);
    pthread_exit(NULL);
}
