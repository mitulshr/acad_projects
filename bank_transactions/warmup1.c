//Reads the input from file

#ifndef _WARMUP1_C_
#define _WARMUP1_C_

#define MAX_BUFFER 1026
#include<stdio.h>
#include<stdlib.h>  //For EXIT_FAILURE
#include<string.h>
#include<time.h>
#include <errno.h>
#include <sys/stat.h>

#include "validation.h"
#include "my402list.h"
#include "cs402.h"
extern int errno ;

typedef struct bankData
{
    char a[1];
    unsigned int  tstamp;
    char desc[1000];
    int amount;
    int balance;
}data;


//#include "insert.h"
void insertToStruc(int code, char* value, data* inp)
{
    const char* val = value;
    int time;
    //float am;
    int am;
    if(code == 0)
    {
        inp->a[1] = *value;
    }
    if(code == 1)
    {
        time = atoi(val);
        inp->tstamp = time;
    }
    if(code == 2)
    {
        int i,j;
        char x[20];
        char y[20];
        strcpy(y,value);
        //printf("###  %s  ###\n",y);
        for(i=0,j=0; i < strlen(value);i++)
        {
            if(y[i] != '.')
            {
                x[j] = y[i];
                j++;
            }
            //printf("&&&  %s  &&&\n",x);
        }
        x[j] = '\0';
        //strcpy(amount,x);
        //printf("***  %s  ***\n",x);
        
        
        am = atoi(x);
        //printf("Value of miney : %f \n",am);
        inp->amount = am;
    }
    if(code == 3)
    {
        strcpy(inp->desc,value);
        //printf("Value is :  %s", inp->desc);
    }
}





void parseInput(char* , data* );

void printNumbers(int tmpamt, FILE* out,char s)
{
    int i,j;
    char amt[17];
    amt[0] = ' ';
    amt[16] = '|';
    amt[15] = ' ';
    
    if(s == '+')
    {
        amt[14] = ' ';
        amt[1] = ' ';
    }
    else
    {
        amt[14] = ')';
        amt[1] = '(';
    }
    amt[13] =  '0' + tmpamt%10;
    tmpamt = tmpamt/10;
    amt[12] = '0' + tmpamt%10;
    tmpamt = tmpamt /10;
    amt[11] = '.';
    if(tmpamt == 0)
    {
        amt[10] = '0';
        for(i =9; i > 1 ;i--)
        {
            amt[i] = ' ';
        }
        fputs(amt,out);
        return;
    }
    
    for(i =10,j=0; i > 1 ;i--)
    {
        if(j == 3 && tmpamt != 0)
        {
            amt[i] = ',';
            j=0;
            continue;
        }
        else if(tmpamt != 0)
        {
            amt[i] = '0' + tmpamt%10;
            tmpamt = tmpamt/10;
            j++;
        }
        else
            amt[i] = ' ';
    }
    fputs(amt,out);
    return;
    
}
int PrintFileEle(My402ListElem* node, FILE* out,int lasBal)
{
    char buffer[25];
    struct tm *myTime;
    data* tmp = node->obj;
    time_t now = tmp->tstamp;
    myTime = localtime(&now);
    strftime(buffer, 25, "| %a %b %e %Y | ",myTime);
    fputs(buffer,out);
    int descLen = strlen(tmp->desc);
    int i;
    if(descLen-1  <= 24)
    {
        for(i =0; i < descLen-1;i++)
        fprintf(out,"%c",tmp->desc[i]);
        for(i = descLen-1 ; i < 24 ; i++)
        fprintf(out," ");
    }
    else
    {
        for(i=0; i < 24 ; i++)
        fprintf(out,"%c",tmp->desc[i]);
    }
    
    fprintf(out," |");
    
    int x = tmp->amount;
    printNumbers(x,out,tmp->a[1]);
    
    
    int presentBalance = 0;
    if(tmp->a[1] == '+')
    {
        presentBalance = tmp->amount + lasBal;
        if(presentBalance > 999999999)
        fprintf(out,"  ?,???,???.??  |\n");
        else if(presentBalance > 0 && presentBalance <= 999999999)
        {
            printNumbers(presentBalance,out,'+');
            fprintf(out,"\n");
        }
        else
        {
            printNumbers(presentBalance*-1,out,'-');
            fprintf(out,"\n");
        }
    }
    else
    {
        presentBalance = lasBal - tmp->amount;
        if(presentBalance > 999999999)
        fprintf(out,"  ?,???,???.??  |\n");
        else if(presentBalance > 0 && presentBalance <= 999999999)
        {
            printNumbers(presentBalance,out,'+');
            fprintf(out,"\n");
        }
        else
        {
            printNumbers((presentBalance*-1),out,'-');
            fprintf(out,"\n");
        }
        
    }
    return presentBalance;
    //printf("Sign : %c\n",tmp->a[1]);
    //printf("Time : %u\n",tmp->tstamp);
    //printf("Amount : %f\n",tmp->amount);
    //printf("Desc : %s\n",tmp->desc);
    
}
void filePrint(My402List* bankTnx, FILE* out )
{
    fprintf(out,"+-----------------+--------------------------+----------------+----------------+\n");
    fprintf(out,"|       Date      | Description              |         Amount |        Balance |\n");
    fprintf(out,"+-----------------+--------------------------+----------------+----------------+\n");
    My402ListElem* tmp = bankTnx->anchor.next;
    int lastBal = 0;
    while(tmp != &(bankTnx->anchor))
    {
        lastBal = PrintFileEle(tmp,out,lastBal);
        tmp = tmp->next;
    }
    fprintf(out,"+-----------------+--------------------------+----------------+----------------+\n");
    fclose(out);
    
}

void PrintEle(My402ListElem* node)
{
    //data* tmp = node->obj;
    //int i = 123456789;
    //printf("Sign : %c\n",tmp->a[1]);
    //printf("Time : %u\n",tmp->tstamp);
    //printf("Amount : %d\n",tmp->amount);
    //printf("Lenght %d Desc : %s\n",i,tmp->desc);
    return;
}


void Print(My402List* bankTnx)
{
    My402ListElem* tmp = bankTnx->anchor.next;
    
    while(tmp != &(bankTnx->anchor))
    {
        PrintEle(tmp);
        tmp = tmp->next;
    }
    
}

int main(int argc, char *argv[])

{
    My402List* bankTnx = (My402List*)malloc(sizeof(My402List));
    if(!My402ListInit(bankTnx))
    fprintf(stderr,"\nERROR: Unable to Initalize the List!!\n");
    My402ListElem* current;
    FILE* fp;
    FILE* out;
    char buf[MAX_BUFFER];
    buf[MAX_BUFFER-2] = '\0';  //-2
    data* inp;
    //int status;
    struct stat st_buf;
    
    
    
    
    if(argc < 2)
    {
        fprintf(stderr,"\nToo few [%d] command line arguments .\nUsage: warmup1 sort [tfile] [ofile]\n",argc);
        exit(EXIT_FAILURE);
    }
    
    if(argc > 1)
    {
        if(strcmp(argv[1],"sort"))
        {
            fprintf(stderr,"\nPlease check your first command line argument change your argument[%s].Usage: warmup1 sort [tfile] [ofile]\n",argv[1]);
            exit(EXIT_FAILURE);
        }
    }
    if(argc > 2)
    {
        stat(argv[2], &st_buf);
        if (S_ISDIR (st_buf.st_mode))
        {
            fprintf(stderr,"\nERROR in Opening Input File:\n%s is a directory.\n", argv[2]);
            exit(EXIT_FAILURE);
        }
    }
    
    if(argc < 3)
    fp = stdin;
    else
        fp = fopen(argv[2],"r");
    
    if(argc == 4)
    out = fopen(argv[3],"w");
    else
        out = stdout;
    
    if(fp == NULL)
    {
        fprintf(stderr,"ERROR in reading File [%s] DUE TO: %s \n!!TERMINATING PROGRAM!!\n",argv[2],strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if(fgets(buf, sizeof(buf), fp) == NULL)
    {
        fprintf(stderr,"ERROR: File doest conatin any data/ is blank.\n!! Terminating the program !!\n");
        exit(EXIT_FAILURE);
    }
    /*
    
    if(buf == NULL)
    {
    printf("****File doest conatin any data...!!! Terminating the program!!!****\n");
    exit(EXIT_FAILURE);
    }
    */
    while(TRUE)
    {
        inp = (data *) malloc(sizeof(data));
        if(buf[MAX_BUFFER-2] != '\0')   //-2
        {
            fprintf(stderr,"***ERROR In Input File: Exceeds the maximum line limit of 1024.***\n!!TERMINATING PROGRAM!!");
            exit(EXIT_FAILURE);
        }
        parseInput(buf,inp);
        
        
        if(My402ListEmpty(bankTnx))
        {
            My402ListAppend(bankTnx,inp);
        }
        else
        {
            int  b = TRUE;
            data* tmp;
            current = bankTnx->anchor.next ;
            while(current   != &(bankTnx->anchor))
            {
                tmp = current->obj;
                if(tmp->tstamp == inp->tstamp)
                {
                    fprintf(stderr,"\n***ERROR In File: Time Stamp Validation Failed: Two transactions have the same timestamp***\n.!!TERMINATING PROGRAM!!\n");
                    exit(EXIT_FAILURE);
                    
                }
                if(tmp->tstamp < inp->tstamp)
                current = current->next;
                else
                {
                    My402ListInsertBefore(bankTnx,inp,current);
                    b = FALSE;
                    break;
                }
            }
            if(b)
            My402ListAppend(bankTnx,inp);
            
        }
        
        
        
        if(fgets(buf, sizeof(buf), fp) != NULL)
        continue;
        else
        {
            //printf("\n ###############END OF FILE #######\n");
            fclose(fp);
            break;
        }
    }
    //Print(bankTnx);
    filePrint(bankTnx,out);
    exit(EXIT_SUCCESS);
}




void parseInput(char* buf, data* inp)
{
    
    int tab;
    char *start_ptr;
    char *tab_ptr;
    
    for(start_ptr = buf,tab = 0 ; start_ptr != NULL ; start_ptr = tab_ptr,tab++ )
    {
        if(tab > 3)
        {
            fprintf(stderr,"\n***ERROR In Input File: Line exceeds number of filelds/tabs***\n!!TERMINATING PROGRAM!!\n");
            exit(EXIT_FAILURE);
        }
        tab_ptr = strchr(start_ptr, '\t');
        if (tab_ptr != NULL)
        {
            *tab_ptr++ = '\0';
        }
        switch(tab)
        {
            case 0: validateField1(start_ptr);   //sign
            insertToStruc(0,start_ptr,inp);
            break;
            case 1: validateField2(start_ptr);   //TimeStamp
            insertToStruc(1,start_ptr,inp);
            break;
            case 2: validateField3(start_ptr);   //Amount
            insertToStruc(2,start_ptr,inp);
            break;
            case 3: validateField4(start_ptr);   //Desc
            insertToStruc(3,start_ptr,inp);
            break;
            default: fprintf(stderr,"Error in Input File Terminating");
            exit(EXIT_FAILURE);
        }
        
        
    }
    
}

#endif // _WARMUP1_C_
    
