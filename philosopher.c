#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define PHILS 5
#define preventdeadlock true

pthread_mutex_t fork_mutex[0];

void *philosopher (void *i)
{
  int n = (int)i;
  printf("Hej jeg er philosopher %d\n", n);
  int j;
  int first, second;

  for(j = 0;;j++) {
    first = n;
    second = (n + 1) % PHILS;

    if(preventdeadlock && n == PHILS - 1) {
      first = 0;
      second = PHILS - 1;
    }

    pthread_mutex_lock(&fork_mutex[first]);
    pthread_mutex_lock(&fork_mutex[second]);

    printf("Hej jeg er philosopher %d og lige nu spiser jeg for %d. gang.\n", n, j);

    pthread_mutex_unlock(&fork_mutex[first]);
    pthread_mutex_unlock(&fork_mutex[second]);

    printf("Jeg philosopher %d er færdig med at spise hah!\n", n);
  }

  pthread_exit(NULL);
}

int main()
{
  int i;
  pthread_t threads[PHILS];

  for (i = 0; i < PHILS; i++) {
    pthread_mutex_init(&fork_mutex[i], NULL);
  }

  for (i = 0; i < PHILS; i++) {
    pthread_create(&threads[i], NULL, philosopher, (void *)i);
  }

  for(i = 0; i < PHILS; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
