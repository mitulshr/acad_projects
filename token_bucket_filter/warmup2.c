#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "my402list.h"
#include "warm2.h"


 int errno;

 My402List* arrivalQ;
 My402List* depositQ;

 long tokenBuffer = 0;
 long token_id = 0;
 long num_of_packs;           // Intilalize with number of packets
 long maxBuffer;             //B
 long tok_per_pack;
 double alpha;
 double lamda;
 double mu;

 int flag = 1;
 int finish = 0;
 int fileInp = 0;
 int interuptflag = 0;

 char* fname;
 FILE* inp;
 char buf[1026];
 long fileLineCount = 0;

 long masterTimeStamp = 0;
 struct timeval lastPacket;

 double avgInterArrival = 0;
 long avgPackService = 0;
 double avgService = 0;
 double avgServiceSq = 0;
 double avgQ1Service = 0;
 long avgQ2Service = 0;
 long avgS1Service = 0;
 long avgS2Service = 0;
 long arrivedPacks = 0;
 long completedPack = 0;
 long droppedtoken = 0;
 long droppedpacks = 0;
 long removedPacks = 0;
 long removedTokens = 0;

 sigset_t set;

 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t filemu = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

 pthread_t thread1;
 pthread_t thread2;
 pthread_t thread3;
 pthread_t thread4;
 pthread_t thread5;

 long findLengthOfNum(long number)
  {
     long i =1;
     while (number / 10 > 0)
     {
      i++;
      number = number /10;
     }
     return i;
  }

 void printTimeStamp(struct timeval in)
  {

   long x;
   long diff = (in.tv_sec * 1000000 ) + (in.tv_usec) - masterTimeStamp;
   long mill = diff /1000 ;
   int micro = diff % 1000;
   long l1 = 8 - findLengthOfNum(mill);
   int l2 = 3 - findLengthOfNum(micro);
   //pthread_mutex_lock(&mutex);
   //pthread_mutex_lock(filemu);
   for(x = 0 ; x < l1 ; x++)
       printf("0");
   printf("%ld.",mill);
   for(x = 0 ; x < l2 ; x++)
      printf("0");
   printf("%dms:\t",micro);
   //pthread_mutex_unlock(filemu);
   //pthread_mutex_unlock(&mutex);
  }

 int checkDot(char* val)
  {
    while(*val != '\0')
     {
      if(*val == '.')
        return 1;
      else
        val++;
     }
     return 0;
   }

 void checkSpaces(char* buf)
  {
     int len = strlen(buf);
     if(buf[0] == ' ' || buf[0] == '\t')
        {
         //pthread_mutex_lock(filemu);
         fprintf(stderr,"ERROR In File: Contains Leading Spaces\n!! Terminating the program !!\n");
         //pthread_mutex_unlock(filemu);
         exit(EXIT_FAILURE);
        }
     else if(buf[len-1] == ' ' || buf[len-1] == '\t')
       {
         //pthread_mutex_lock(filemu);
         fprintf(stderr,"ERROR In File: Contains Trailing Spaces\n!! Terminating the program !!\n");
         //pthread_mutex_unlock(filemu);
         exit(EXIT_FAILURE);
       }
   }

 void parseInp(char* buf)
  {
    int itr = 0;
    char* var1;
    char* var2;
    char* var3;

      while(buf[itr] != ' ' && buf[itr] != '\t')
          itr++;

      buf[itr++] = '\0';
      var1 = buf;
      if(checkDot(var1))
      {
           fprintf(stderr,"\nError In File: Incorrect Value of Lamda. Contains Decimal\n");
           exit(EXIT_FAILURE);
      }

      lamda = atol(var1);
      if(lamda == 0)
      {
           fprintf(stderr,"\nError In File: Incorrect value of Lamda\n");
           exit(EXIT_FAILURE);
      }

      while(buf[itr] == ' ' || buf[itr] == '\t')
        itr++;

      var2 = buf+itr;

      while(buf[itr] != ' ' &&  buf[itr] != '\t')
        itr++;

      buf[itr++] = '\0';
      if(checkDot(var2))
        {
           fprintf(stderr,"\nError In File: Incorrect Value of P. Contains Decimal\n");
           exit(EXIT_FAILURE);
        }
      tok_per_pack = atol(var2);
      if(tok_per_pack == 0)
      {
           fprintf(stderr,"\nError In File: Incorrect value of P\n");
           exit(EXIT_FAILURE);
      }

      while(buf[itr] == ' ' &&  buf[itr] == '\t')
        itr++;

      var3 = buf+itr;

      while(buf[itr] != '\n')
        itr++;

      buf[itr++] = '\0';
      if(checkDot(var3))
       {
           fprintf(stderr,"\nError In File: Incorrect Value of mu. Contains Decimal\n");
           exit(EXIT_FAILURE);
       }
      mu = atol(var3);
      if(mu == 0)
      {
           fprintf(stderr,"\nError In File: Incorrect value of mu\n");
           exit(EXIT_FAILURE);
      }

  }

 void assignValues(char* varName, char* varValue)
  {
     if(strcmp(varName,"-t") == 1 && *varValue == '-')
       {
         fprintf(stderr,"\nValues [%s]cannot be negative!!\n",varValue);
         exit(EXIT_FAILURE);
       }
     //else
     //    printf("\n %s = %s",varName,varValue);

    if(!strcmp(varName,"-lambda"))
       {
        lamda = atof(varValue);
        if(lamda <= 0)
         {
           fprintf(stderr,"\nError: Incorrect Value of [%s]\n",varName);
           exit(EXIT_FAILURE);
         }
        if(lamda < 0.1)
           lamda = 0.1;
       }
    else if(!strcmp(varName,"-mu"))
        {
          mu = atof(varValue);
          if(mu <= 0)
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]\n",varName);
           exit(EXIT_FAILURE);
          }
          if(mu < 0.1)
            mu = 0.1;
        }
    else if(!strcmp(varName,"-r"))
        {
         alpha = atof(varValue);
         if(alpha <= 0)
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]\n",varName);
           exit(EXIT_FAILURE);
          }
         if(alpha < 0.1)
           alpha = 0.1;
        }
    else if(!strcmp(varName,"-B"))
      {
        if(checkDot(varValue))
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]. Contains Decimal\n",varName);
           exit(EXIT_FAILURE);
          }
        maxBuffer = atol(varValue);
        if(maxBuffer <= 0)
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]\n",varName);
           exit(EXIT_FAILURE);
          }
        if(maxBuffer > 2147483647)
          {
            fprintf(stderr,"\nBuffer Values [%ld] cannot be more than 2147483647 !!\n",maxBuffer);
            exit(EXIT_FAILURE);
          }
      }
    else if(!strcmp(varName,"-P"))
       {
          if(checkDot(varValue))
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]. Contains Decimal\n",varName);
           exit(EXIT_FAILURE);
          }
         tok_per_pack = atol(varValue);
         if(tok_per_pack <= 0)
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]\n",varName);
           exit(EXIT_FAILURE);
          }
         if(tok_per_pack > 2147483647)
          {
            fprintf(stderr,"\nToken per Packet Values [%ld] cannot be more than 2147483647 !!\n",tok_per_pack);
            exit(EXIT_FAILURE);
          }
       }
    else if(!strcmp(varName,"-n"))
       {
         if(checkDot(varValue))
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]. Contains Decimal\n",varName);
           exit(EXIT_FAILURE);
          }
        num_of_packs = atol(varValue);
        if(num_of_packs <= 0)
          {
           fprintf(stderr,"\nError: Incorrect Value of [%s]\n",varName);
           exit(EXIT_FAILURE);
          }
        if(num_of_packs > 2147483647)
          {
            fprintf(stderr,"\nNumber of Packets Values [%ld] cannot be more than 2147483647 !!\n",num_of_packs);
            exit(EXIT_FAILURE);
          }
       }
    else if(!strcmp(varName,"-t"))
        {
          fileInp = 1;
          struct stat st_buf;
          fname = varValue;
          stat(varName, &st_buf);
          if (S_ISDIR (st_buf.st_mode))
           {
            fprintf(stderr,"\nERROR in Opening Input File:\n%s is a directory.\n", varValue);
            exit(EXIT_FAILURE);
            }

          inp = fopen(varValue,"r");
          if(inp == NULL)
            {
              fprintf(stderr,"ERROR in reading File [%s] DUE TO: %s \n!!TERMINATING PROGRAM!!\n",varValue,strerror(errno));
              exit(EXIT_FAILURE);
            }

          if(fgets(buf, sizeof(buf), inp) == NULL)
            {
              fileLineCount++;
              fprintf(stderr,"ERROR: File doest conatin any data/ is blank.\n!! Terminating the program !!\n");
              exit(EXIT_FAILURE);
            }
          else
           {
                 checkSpaces(buf);
                 if(checkDot(buf))
                  {
                    fprintf(stderr,"\nError In File: Incorrect Value of n. Contains Decimal\n");
                    exit(EXIT_FAILURE);
                  }
                 num_of_packs = atol(buf);
        if(num_of_packs <= 0)
          {
           fprintf(stderr,"\nError In File: Incorrect Value of n\n");
           exit(EXIT_FAILURE);
          }
        if(num_of_packs > 2147483647)
          {
            fprintf(stderr,"\nNumber of Packets Values [%ld] cannot be more than 2147483647 !!\n",num_of_packs);
            exit(EXIT_FAILURE);
          }

            }
          }
    else
      {
        fprintf(stderr,"\nError: Malformed Input [%s]\n",varName);
        exit(EXIT_FAILURE);
      }
   }


int main(int argc, char *argv[])
{
 sigemptyset(&set);
 sigaddset(&set,SIGINT);
 sigprocmask(SIG_BLOCK,&set,0);

 pthread_create(&thread5,NULL,handler,NULL);

 arrivalQ = (My402List*)malloc(sizeof(My402List));
 depositQ = (My402List*)malloc(sizeof(My402List));

   if(!My402ListInit(arrivalQ))
      fprintf(stderr,"\nERROR: Unable to Initalize the Arrival Queue!!\n");

   if(!My402ListInit(depositQ))
      fprintf(stderr,"\nERROR: Unable to Initalize the Deposit Queue!!\n");


  alpha = 1.5;
  lamda  = 1;
  mu = 0.35;
  maxBuffer = 10;
  num_of_packs = 20;
  //long totalPacks = num_of_packs;
  tok_per_pack = 3;
  int i;
  double sqAvgService = 0;
  double AvgServiceSquare = 0;
  if(argc % 2 == 0 )
   {
    fprintf(stderr,"\nERROR: MALFORMED COMMANDLINE: MISSING VALUE!!\n");
        exit(EXIT_FAILURE);
   }
  for(i =1; i < argc ; i = i+2)
    {
      if(*argv[i] != '-')
       {
        fprintf(stderr,"\nERROR: MALFORMED COMMANDLINE: [%s]!!\n",argv[i]);
        exit(EXIT_FAILURE);
       }
      else
        assignValues(argv[i],argv[i+1]);
    }

  if(fileInp)
   {
      if(fgets(buf, sizeof(buf),inp) != NULL)
       {
         fileLineCount++;
         checkSpaces(buf);
         parseInp(buf);
       }
      else
         {
         if(fileLineCount != num_of_packs)
            {
              fprintf(stderr,"\nNumber of packets details is not equal to specified number of packets in File \n");
              exit(EXIT_FAILURE);
            }
         else
           fclose(inp);
         }
   }

   printf("Emulation Parameters:\n");
   printf("    number to arrive = %ld\n",num_of_packs);
   if(!fileInp)
     printf("    lambda = %.6g\n",lamda);
   if(!fileInp)
     printf("    mu = %.6g\n",mu);
   printf("    r = %.6g\n",alpha);
   printf("    B = %ld\n",maxBuffer);
   if(!fileInp)
     printf("    P = %ld\n",tok_per_pack);
   if(fileInp)
     printf("    tsfile = %s\n",fname);



   struct timeval tv;
   //time_t curtime;
   gettimeofday(&tv, NULL);
   masterTimeStamp = (tv.tv_sec * 1000000 ) + (tv.tv_usec);
   //printf("\n%ld Is the master Time stamp\n",masterTimeStamp);
   //gettimeofday(&tv, NULL);
   printTimeStamp(tv);
   printf("emulation starts   \n");
   lastPacket.tv_sec = tv.tv_sec;
   lastPacket.tv_usec = tv.tv_usec;

  pthread_create(&thread5,NULL,handler,NULL);
  pthread_create(&thread1,NULL,tokenDeposit,&alpha);
  pthread_create(&thread2,NULL,packetArrival,&lamda);
  pthread_create(&thread3,NULL,firstServer,&mu);
  pthread_create(&thread4,NULL,secondServer,&mu);
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);
  pthread_join(thread3,NULL);
  pthread_join(thread4,NULL);

  gettimeofday(&tv,NULL);
  printTimeStamp(tv);
  long diff = (tv.tv_sec * 1000000 ) + (tv.tv_usec) - masterTimeStamp;
  printf("emulation ends\n");

  printf("\nStatistics:\n\n");
  if(arrivedPacks)
     printf("   average packet inter-arrival time = %.6g\n",avgInterArrival/(arrivedPacks * 1000000.00));
  else
    printf("   average packet inter-arrival time = N/An");
  if(completedPack)
     printf("   average packet service time = %.6g\n\n",(double)(avgPackService)/ (completedPack * 1000000.00));
  else
     printf("   average packet service time = N/A\n\n");

  printf("   average number of packets in Q1 = %.6g\n",(double)(avgQ1Service) / (double)((diff/1000000.00)));
  printf("   average number of packets in Q2 = %.6g\n",(double)(avgQ2Service) / (double)(diff));
  printf("   average number of packets in S1 = %.6g\n",(double)(avgS1Service) / (double)(diff));
  printf("   average number of packets in S2 = %.6g\n\n",(double)(avgS2Service) / (double)(diff));

  if(completedPack)
     printf("   average time a packet spent in system = %.6g\n",(double)(avgService) / (double)(completedPack));
  else
     printf("   average time a packet spent in system = N/A\n");

  sqAvgService = (double)(avgService) / (double)(completedPack) * (double)(avgService) / (double)(completedPack);
  AvgServiceSquare = (double)(avgServiceSq) / (double)(completedPack);

  if(completedPack)
     printf("   standard deviation for time spent in system = %.6g\n\n",sqrt(AvgServiceSquare - sqAvgService));
  else
     printf("   standard deviation for time spent in system = N/A\n\n");
  if(token_id)
     printf("   token drop probability = %.6g\n", ((double)droppedtoken / (double)token_id ));
  else
     printf("   token drop probability = N/A\n");
  if(arrivedPacks)
     printf("   packet drop probability = %.6g\n\n",((double)droppedpacks / (double)arrivedPacks ));
  else
     printf("   packet drop probability = N/A\n\n");
  return(0);

 }


