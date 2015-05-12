#ifndef _WARM2_H_
#define _WARM2_H_
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include "my402list.h"

 extern int errno;

 extern My402List* arrivalQ;
 extern My402List* depositQ;

 extern long tokenBuffer;
 extern long token_id;
 extern long num_of_packs;           // Intilalize with number of packets
 extern long maxBuffer;             //B
 extern long tok_per_pack;
 extern double alpha;
 extern double lamda;
 extern double mu;

 extern int flag1;
 extern int finish;
 extern int fileInp;
 extern int interuptflag;

 extern char* fname;
 extern FILE* inp;
 extern char buf[1026];
 extern long fileLineCount;

 extern sigset_t set;

 extern long masterTimeStamp;
 extern struct timeval lastPacket;

 extern double avgInterArrival;
 extern long avgPackService;
 extern double avgService;
 extern double avgServiceSq;
 extern double avgQ1Service;
 extern long avgQ2Service;
 extern long avgS1Service;
 extern long avgS2Service;
 extern long arrivedPacks;
 extern long completedPack;
 extern long droppedtoken;
 extern long droppedpacks;
 extern long removedPacks;
 extern long removedTokens;

 extern pthread_mutex_t mutex;
 extern pthread_mutex_t filemu;
 extern pthread_cond_t cv;

 typedef struct packets
  {
    long size;
    long id;
    struct timeval start;
    struct timeval enterQ1;
    struct timeval enterQ2;
    struct timeval service;
  }packets;

 extern pthread_t thread1;
 extern pthread_t thread2;
 extern pthread_t thread3;
 extern pthread_t thread4;
 extern pthread_t thread5;

 extern void printTimeStamp(struct timeval);
 extern long findLengthOfNum(long);
 extern int checkDot(char*);
 extern void checkSpaces(char*);
 extern void parseInp(char*);
 extern void assignValues(char*, char*);
 extern void* tokenDeposit(void *);
 extern void* packetArrival(void *);
 extern void* firstServer(void *);
 extern void* secondServer(void *);
 extern void* handler();

#endif // _WARM2_H_




