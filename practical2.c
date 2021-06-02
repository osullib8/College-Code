#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "cond.c"


int pnum;  // number updated when producer runs.
int csum;  // sum computed using pnum when consumer runs.

int count = 0;

pthread_cond_t cond_1, cond_2 ; //= PTHREAD_COND_INITIALIZER ;

pthread_mutex_t m; // = PTHREAD_MUTEX_INITIALIZER ;

int (*pred)(int); // predicate indicating if pnum is to be consumed

int produceT() {
  scanf("%d",&pnum); // read a number from stdin
  count = 1;
  return pnum;
}

void *Produce(void *a) {
  while (1){
  int p;
 
  p=1;
  while (p) {
    pthread_mutex_lock(&m);
    if (count == 1){
         pthread_cond_wait(&cond_1, &m);
    }
    printf("@P-READY\n");
    p = produceT();
    pthread_cond_signal(&cond_2);
    pthread_mutex_unlock(&m);
    printf("@PRODUCED %d\n",p);
  }
  printf("@P-EXIT\n");
  pthread_exit(NULL);
  }
  return (0);
}


int consumeT() {
  if ( pred(pnum) ) { csum += pnum; }
  count = 0;
  return pnum;
}

void *Consume(void *a) {
  while (1){
  int p;

  p=1;
  while (p) {
    pthread_mutex_lock(&m);
    if (count == 0){
    pthread_cond_wait(&cond_2, &m);
    }
    printf("@C-READY\n");
    p = consumeT();
    printf("@CONSUMED %d\n",csum);
    pthread_cond_signal(&cond_1);
    pthread_mutex_unlock(&m);
  }
  printf("@C-EXIT\n");
  pthread_exit(NULL);
  }
  return(0);
}


int main (int argc, const char * argv[]) {
  // the current number predicate
  static pthread_t prod,cons;
	long rc;
	
  pthread_mutex_init(&m, NULL);
  pthread_cond_init(&cond_1, NULL);
  pthread_cond_init(&cond_2, NULL);

  pred = &cond1;
  if (argc>1) {
    if      (!strncmp(argv[1],"2",10)) { pred = &cond2; }
    else if (!strncmp(argv[1],"3",10)) { pred = &cond3; }
  }


  pnum = 999;
  csum=0;
  srand(time(0));

  printf("@P-CREATE\n");
 	rc = pthread_create(&prod,NULL,Produce,(void *)0);
	if (rc) {
			printf("@P-ERROR %ld\n",rc);
			exit(-1);
		}
  printf("@C-CREATE\n");
 	rc = pthread_create(&cons,NULL,Consume,(void *)0);
	if (rc) {
			printf("@C-ERROR %ld\n",rc);
			exit(-1);
		}

  printf("@P-JOIN\n");
  pthread_join( prod, NULL);
  printf("@C-JOIN\n");
  pthread_join( cons, NULL);


  printf("@CSUM=%d.\n",csum);
  printf("@PNUM=%d\n",pnum);
  
  pthread_mutex_destroy(&m);
  pthread_cond_destroy(&cond_1);
  pthread_cond_destroy(&cond_2);

  return 0;
}
