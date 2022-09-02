#include <pthread.h>
#include <stdio.h>

int cnt;
pthread_mutex_t mutex;

void *thread(void *vargp)
{
  pthread_mutex_lock(&mutex);
  cnt = 0;
  for (int i = 0; i < 10; i++)
    printf("%d\n", cnt++);
  pthread_mutex_unlock(&mutex);

  return (0);
}

int main()
{
  pthread_t tid_1, tid_2;
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&tid_1, NULL, thread, NULL);
  pthread_create(&tid_2, NULL, thread, NULL);
  pthread_join(tid_1, NULL);
  pthread_join(tid_2, NULL);
}

