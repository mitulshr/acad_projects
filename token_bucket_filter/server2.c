#include "warm2.h"
#include <sys/time.h>
#include <time.h>
#include "my402list.h"


void *secondServer(void *mu)
  {
    struct timeval in;                                                   //Step1: Stays in Loop
    while(!finish)
    {
     pthread_mutex_lock(&mutex);

     while(My402ListEmpty(depositQ) && !finish)                               // Changing from While to IF
    {
        pthread_cond_wait(&cv,&mutex);
    }
    
     packets *p = (packets*)malloc(sizeof(packets));
     p->id = 0;
     if(!finish)
       {
        My402ListElem *tmp = My402ListLast(depositQ);
        p = tmp->obj;
        gettimeofday(&in,NULL);
        My402ListUnlink(depositQ,tmp);
        printTimeStamp(in);
        long di = ((in.tv_sec * 1000000 ) + (in.tv_usec)) - ((p->enterQ2.tv_sec * 1000000) + (p->enterQ2.tv_usec));
        avgQ2Service += di;
        long mi = di /1000 ;
        int mic = di % 1000;
        pthread_mutex_lock(&filemu);
        printf("p%ld leaves Q2, time in Q2 = %ld.%03d ms\n",p->id,mi,mic);
        pthread_mutex_unlock(&filemu);
        gettimeofday(&in,NULL);
        printTimeStamp(in);
        p->service.tv_sec = in.tv_sec;
        p->service.tv_usec = in.tv_usec;
        pthread_mutex_lock(&filemu);
        if(fileInp)
           printf("p%ld begins service at S2, requesting %f ms of service\n",p->id,(*(double*)mu));
        else
           printf("p%ld begins service at S2, requesting %.3f ms of service\n",p->id,(1 /(*(double*)mu))*1000);
        pthread_mutex_unlock(&filemu);
        completedPack++;
       }

    if(My402ListEmpty(depositQ) && My402ListEmpty(arrivalQ) && num_of_packs == 0)
       {
         finish = 1;
       }
    pthread_mutex_unlock(&mutex);

     if(!interuptflag && p->id != 0)
      {
        if(fileInp)
       {
            double tm = (*(double*)mu) / 1000.00;
            int secs = (int) tm;
            double decm = tm - secs;
            double milisec = 1000 * decm;                                                 // length of time to sleep, in milisecond
            struct timespec req = {0};
            req.tv_sec = secs;
            req.tv_nsec = milisec * 1000000L;
            nanosleep(&req, (struct timespec *)NULL);
            gettimeofday(&in,NULL);
            printTimeStamp(in);

           long d1 = ((in.tv_sec * 1000000 ) + (in.tv_usec)) - ((p->service.tv_sec * 1000000) + (p->service.tv_usec));
           avgS2Service += d1;
           avgPackService += d1;
           long m1 = d1 /1000 ;
           int mi1 = d1 % 1000;

           long d2 = ((in.tv_sec * 1000000 ) + (in.tv_usec)) - ((p->start.tv_sec * 1000000) + (p->start.tv_usec));
           avgService += (d2 / 1000000.00);
           avgServiceSq = (avgServiceSq + (d2/1000000.00) * (d2/1000000.00));
           long m2 = d2 /1000 ;
           int mi2 = d2 % 1000;
           pthread_mutex_lock(&filemu);
           printf("p%ld departs from S2, service time = %ld.%03d ms, time in system = %ld.%03d ms\n",p->id,m1,mi1,m2,mi2);
           pthread_mutex_unlock(&filemu);
           completedPack++;
       }
      else
        {
          double tm = 1 / (*(double*)mu);
          int secs = (int) tm;
          double decm = tm - secs;
          double milisec = 1000 * decm;                                                 // length of time to sleep, in milisecond
          struct timespec req = {0};
          req.tv_sec = secs;
          req.tv_nsec = milisec * 1000000L;
          nanosleep(&req, (struct timespec *)NULL);
          gettimeofday(&in,NULL);
          printTimeStamp(in);

          long d1 = ((in.tv_sec * 1000000 ) + (in.tv_usec)) - ((p->service.tv_sec * 1000000) + (p->service.tv_usec));
          avgS2Service += d1;
          avgPackService += d1;
          long m1 = d1 /1000 ;
          int mi1 = d1 % 1000;
          long d2 = ((in.tv_sec * 1000000 ) + (in.tv_usec)) - ((p->start.tv_sec * 1000000) + (p->start.tv_usec));
          avgService += (d2/1000000.00);
           avgServiceSq = (avgServiceSq + (d2/1000000.00) * (d2/1000000.00));
          long m2 = d2 / 1000 ;
          int mi2 = d2 % 1000;
          pthread_mutex_lock(&filemu);
          printf("p%ld departs from S2, service time = %ld.%03d ms, time in system = %ld.%03d ms\n",p->id,m1,mi1,m2,mi2);
          pthread_mutex_unlock(&filemu);
        }                                         //Step2: Goes to sleep
     }
    }
    return(0);
}




