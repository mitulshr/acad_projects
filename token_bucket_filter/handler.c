#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include "my402list.h"
#include "warm2.h"


void *handler()
  {
    //int signl;
    struct timeval in;
    while(1)
     {
       sigwait(&set);
       printf("\n");
       interuptflag = 1;
       pthread_mutex_lock(&mutex);
       pthread_cancel(thread1);
       pthread_cancel(thread2);
       if(!My402ListEmpty(arrivalQ))
         {
          removedPacks = My402ListLength(arrivalQ);
          while(!My402ListEmpty(arrivalQ))
            {
              packets *p = (packets*)malloc(sizeof(packets));
              My402ListElem *tmp = My402ListLast(arrivalQ);
              p = tmp->obj;
              gettimeofday(&in,NULL);
              printTimeStamp(in);
              pthread_mutex_lock(&filemu);
              printf("p%ld removed from Q#1\n",p->id);
              pthread_mutex_unlock(&filemu);
              My402ListUnlink(arrivalQ,tmp);
            }
         }
       if(!My402ListEmpty(depositQ))
         {
          removedTokens = My402ListLength(depositQ);
          while(!My402ListEmpty(depositQ))
            {
              packets *p = (packets*)malloc(sizeof(packets));
              My402ListElem *tmp = My402ListLast(depositQ);
              p = tmp->obj;
              gettimeofday(&in,NULL);
              printTimeStamp(in);
              pthread_mutex_lock(&filemu);
              printf("p%ld removed from Q#2\n",p->id);
              pthread_mutex_unlock(&filemu);
              My402ListUnlink(depositQ,tmp);
            }
         }
       finish = 1;
       pthread_cond_broadcast(&cv);
       pthread_mutex_unlock(&mutex);
     }
   
   return 0;
  }




