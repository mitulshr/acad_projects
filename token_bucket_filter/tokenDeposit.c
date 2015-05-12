#include "warm2.h"
#include <sys/time.h>
#include <time.h>
#include "my402list.h"

void *tokenDeposit(void *alpha)
  {
    //int i =0;
    struct timeval in;
    //time_t curtime;

    while(num_of_packs != 0 || !My402ListEmpty(arrivalQ))                                                                      // Step1: Stays in Loop
     {

      double tm = 1 / (*(double*)alpha);
      int secs = (int) tm ;
      double decm = tm - secs;
      double milisec = 1000 * decm;                                                 // length of time to sleep, in milisecond
      struct timespec req = {0};
      if(secs >= 10)
        {
          req.tv_sec = 10;
          req.tv_nsec = 0;
        }
      else
        {
          req.tv_sec = secs;
          req.tv_nsec = milisec * 1000000L;
        }

      nanosleep(&req, (struct timespec *)NULL);                                         //Step2: Go to Sleep


      pthread_mutex_lock (&mutex);                                                      //Step3: wakes up & LOCKING MUTEX
      pthread_cleanup_push(pthread_mutex_unlock,&mutex);
      //START OF THE SYNC BOX
      tokenBuffer++;
      token_id++;
      gettimeofday(&in,NULL);                                                                    //Step3.3 Try to increment token count
      printTimeStamp(in);

      if(tokenBuffer > maxBuffer)
       {
        pthread_mutex_lock(&filemu);
        printf("token t%ld arrives, dropped\n",token_id);
        pthread_mutex_unlock(&filemu);
        tokenBuffer--;
        droppedtoken++;
        //pthread_mutex_unlock(&mutex);
        //pthread_cleanup_pop(0);
        //continue;
       }
      else
       {
        pthread_mutex_lock(&filemu);
        if(tokenBuffer == 1)
            printf("token t%ld arrives, token bucket has %ld token\n",token_id,tokenBuffer);
          else
              printf("token t%ld arrives, token bucket has %ld tokens\n",token_id,tokenBuffer);
          pthread_mutex_unlock(&filemu);

          if(!My402ListEmpty(arrivalQ))
            {
              packets *p = (packets*)malloc(sizeof(packets));
              //pthread_cleanup_push(free,p);
              My402ListElem *tmp = My402ListLast(arrivalQ);
              p = tmp->obj;
              //    pthread_cleanup_pop(0);                                                                 //Get the first element of the Arrival Queue.
              if(p->size <= tokenBuffer)                                                    //Step4: Check if can move first packet from Q1 to Q2
                 {
                   My402ListUnlink(arrivalQ,tmp);
                   tokenBuffer = tokenBuffer - (p->size);
                   gettimeofday(&in,NULL);
                   printTimeStamp(in);
                   long dif = ((in.tv_sec * 1000000 ) + (in.tv_usec)) - ((p->enterQ1.tv_sec * 1000000) + (p->enterQ1.tv_usec));
                   avgQ1Service += (dif/1000000.00);
                   long mil = dif /1000 ;
                   int micr = dif % 1000;
                   pthread_mutex_lock(&filemu);
                   if(tokenBuffer == 0)
                     printf("p%ld leaves Q1, time in Q1 = %ld.%d ms, token bucket now has %ld token\n",p->id,mil,micr,tokenBuffer);
                   else
                     printf("p%ld leaves Q1, time in Q1 = %ld.%d ms, token bucket now has %ld token\n",p->id,mil,micr,tokenBuffer);
                   pthread_mutex_unlock(&filemu);

                   My402ListPrepend(depositQ,p);
                   gettimeofday(&in,NULL);
                   printTimeStamp(in);
                   p->enterQ2.tv_sec = in.tv_sec;
                   p->enterQ2.tv_usec = in.tv_usec;
                   pthread_mutex_lock(&filemu);
                   printf("p%ld enters Q2\n",p->id);
                   pthread_mutex_unlock(&filemu);

                   if(My402ListLength(depositQ) ==  1)
                      {
                       pthread_cond_broadcast(&cv);
                      }
                 }
            }
           }
          //END OF THE SYNC BOX
          //For MUTEX UNLOCK
          pthread_cleanup_pop(1);                                                           //Step6: UNLOCKING MUTEX
      //i++;                                                                              //Step7: Goes back to sleep
     }
   return(0);
  }


