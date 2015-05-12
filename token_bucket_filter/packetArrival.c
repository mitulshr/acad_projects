#include "warm2.h"
#include <sys/time.h>
#include <time.h>
#include "my402list.h"


void *packetArrival(void *lamda)
  {
    int pack_count = 0;
    struct timeval in;
    while(num_of_packs)                                                                   //Step1: Stays in Loop
     {

      if(fileInp)
       {
            double tm = (*(double*)lamda) / 1000.00;
            int secs = (int) tm;
            double decm = tm - secs;
            double milisec = 1000 * decm;                                                 // length of time to sleep, in milisecond
            struct timespec req = {0};
            req.tv_sec = secs;
            req.tv_nsec = milisec * 1000000L;
            nanosleep(&req, (struct timespec *)NULL);
       }
      else
       {
            double tm = 1 / (*(double*)lamda);
            int secs = (int) tm ;
            double decm = tm - secs;
            double milisec = 1000 * decm;                                                 // length of time to sleep, in milisecond
            struct timespec req = {0};
            req.tv_sec = secs;
            req.tv_nsec = milisec * 1000000L;
            nanosleep(&req, (struct timespec *)NULL);
       }
                                            //Step2: Goes to sleep


      packets *newPack = (packets*)malloc(sizeof(packets));                             //Step3.1: Wakes Up & craete a packet
      newPack->id = pack_count+1;
      newPack->size = tok_per_pack;
      gettimeofday(&in,NULL);
      printTimeStamp(in);
      newPack->start.tv_sec = in.tv_sec;
      newPack->start.tv_usec = in.tv_usec;
      long diff = ((in.tv_sec * 1000000 ) + (in.tv_usec)) - ((lastPacket.tv_sec * 1000000) + (lastPacket.tv_usec));
      avgInterArrival += diff;
      long mill = diff /1000 ;
      int micro = diff % 1000;

    if(newPack->size > maxBuffer)
        {
         pthread_mutex_lock(&filemu);
         printf("p%ld arrives, needs %ld tokens, inter-arrival time = %ld.%d ms, dropped\n",newPack->id,newPack->size,mill,micro);
         pthread_mutex_unlock(&filemu);
         droppedpacks++;
         arrivedPacks++;

         pthread_mutex_lock(&mutex);
         pthread_cleanup_push(pthread_mutex_unlock,&mutex);

         pack_count++;
         num_of_packs--;

         if(num_of_packs == 0)
         {
          if(My402ListEmpty(depositQ) && My402ListEmpty(arrivalQ) && num_of_packs == 0)
             finish = 1;
          pthread_cond_broadcast(&cv);
          pthread_mutex_unlock(&mutex);
          break;
         }
        if(fileInp)
        {
            {
            if(fgets(buf, sizeof(buf),inp) != NULL)
            {
             fileLineCount++;
             checkSpaces(buf);
             parseInp(buf);
            }
            else
             {
                if(fileLineCount + num_of_packs != fileLineCount)
                {
                   pthread_mutex_lock(&filemu);
                  fprintf(stderr,"\nNumber of packets details is %ld not equal to specified number of packets in File %ld \n",fileLineCount,num_of_packs);
                  pthread_mutex_unlock(&filemu);
                  exit(EXIT_FAILURE);
                }
             else
               fclose(inp);
              }
             }
        }
         pthread_cleanup_pop(1);
         continue;
     }
      else
        {
          pthread_mutex_lock(&filemu);
          if(newPack->size == 1)
            printf("p%ld arrives, needs %ld token, inter-arrival time = %ld.%d ms\n",newPack->id,newPack->size,mill,micro);
          else
            printf("p%ld arrives, needs %ld tokens, inter-arrival time = %ld.%d ms\n",newPack->id,newPack->size,mill,micro);
          pthread_mutex_unlock(&filemu);
         arrivedPacks++;
        }

      lastPacket.tv_sec = in.tv_sec;
      lastPacket.tv_usec = in.tv_usec;

      pthread_mutex_lock (&mutex);                                                      //Step3.2:LOCKING MUTEX
      pthread_cleanup_push(pthread_mutex_unlock,&mutex);
      //START OF SYNC BOX
      //printf("After Sleep:Arrival: %s%ld\n",buffer,tvl.tv_usec);
      gettimeofday(&in,NULL);
      printTimeStamp(in);
      newPack->enterQ1.tv_sec = in.tv_sec;
      newPack->enterQ1.tv_usec = in.tv_usec;
      pthread_mutex_lock(&filemu);
      printf("p%ld enters Q1\n",newPack->id);
      My402ListPrepend(arrivalQ,newPack);
      pthread_mutex_unlock(&filemu);                                                //Syep4: Enqueue Packet to Q1
      packets *p = (packets*)malloc(sizeof(packets));
      //pthread_cleanup_push(free,p);
      My402ListElem *tmp = My402ListLast(arrivalQ);
      p = tmp->obj;
      //pthread_cleanup_pop(0);                                                                      //Get the last element of the Arrival Queue.
          if(p->size <= tokenBuffer)                                                    //Step5: Check if can move first packet from Q1 to Q2
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
                 printf("p%ld leaves Q1, time in Q1 = %ld.%03d ms, token bucket now has %ld token\n",p->id,mil,micr,tokenBuffer);
               else
                 printf("p%ld leaves Q1, time in Q1 = %ld.%03d ms, token bucket now has %ld token\n",p->id,mil,micr,tokenBuffer);
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
                   //printf("\nNeed to broadcast to server as DepositQ was empty\n");       //Step6: Sends signal to server
                   pthread_cond_broadcast(&cv);
                  }
             }

      pack_count++;
      num_of_packs--;
      if(num_of_packs == 0)
        pthread_cond_broadcast(&cv);

      if(fileInp)
       {
        {
          if(fgets(buf, sizeof(buf),inp) != NULL)
           {
             fileLineCount++;
             checkSpaces(buf);
             parseInp(buf);
           }
          else
             {
             if(fileLineCount + num_of_packs != fileLineCount)
                {
                  pthread_mutex_lock(&filemu);
                  fprintf(stderr,"\nNumber of packets details is %ld not equal to specified number of packets in File %ld \n",fileLineCount,num_of_packs);
                  pthread_mutex_unlock(&filemu);
                  exit(EXIT_FAILURE);
                }
             else
               fclose(inp);
             }
        }
       }

      pthread_cleanup_pop(1);                                                   //Step7: UNLOCKING MUTEX

     }                                                                                 //Step8: Return to loop
   return(0);
 }



