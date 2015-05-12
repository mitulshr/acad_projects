//Validations for the field

#ifndef _VALIADTION_H_
#define _VALIDATION_H_

#include<stdio.h>
#include<stdlib.h>  //For EXIT_FAILURE
#include<ctype.h>
#include<string.h>
#include<time.h>


void validateField1(char* sign)
{
    int length  = strlen(sign);
    if(length != 1)
    {
        fprintf(stderr,"\n ***ERROR In File:Sign Validation Failed: Length >=2 ****\n. !!TERMINATING PROGRAM!!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        if(*sign == '+' || *sign == '-')
        return;
        else
        {
            fprintf(stderr,"\n ***ERROR In File:Sign Validation Failed:Other Than +/-***\n.!!TERMINATING PROGRAM!!\n");
            //printf("It is : -%s- ",sign);
            exit(EXIT_FAILURE);
            
        }
    }
    
}

void validateField2(char* tmstamp)
{
    int i;
    int present = time(NULL);
    //printf("PRESENT TIME %d ",(int)present);
    int giventime = atoi(tmstamp);
    //printf("In char: %s : Present time %d : Given time %d  ", tmstamp,present,giventime);
    if(giventime > present)
    {
        fprintf(stderr,"\nERROR In File:***Timestamp Validation Failed: Time is after the current local time***.\n !!!TERMINATING PROGRAM!!\n");
        exit(EXIT_FAILURE);
    }
    
    int length  = strlen(tmstamp);
    if(length > 10)
    {
        fprintf(stderr,"\nERROR In File:***Timestamp Validation Failed: Lenght >= 11***\n.!!TERMINATING PROGRAM!!\n");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<length; i++)
    {
        if(!isdigit(*tmstamp))
        {
            fprintf(stderr,"\nERROR In File:***Timestamp Validation Failed: Timestamp contains non digit value***\n.!!TERMINATING PROGRAM!!\n");
            exit(EXIT_FAILURE);
        }
        tmstamp++;
    }
    
    
    
    return;
    
}

void validateField3(char* amount)
{
    char cpyamount[15];
    strcpy(cpyamount,amount);
    char *dot_ptr;
    char *dec_ptr;
    int i;
    int beforeDotLength;
    int afterDotLength;
    
    dot_ptr = strchr(cpyamount, '.');
    
    if (dot_ptr == NULL)
    {
        fprintf(stderr,"***ERROR In File:Amount validation failed:Does't have dot.***\n!!TERMINATING PROGRAM!!!\n");
        exit(EXIT_FAILURE);
    }
    
    *dot_ptr = '\0';
    dot_ptr++;
    
    beforeDotLength = strlen(cpyamount);
    if(beforeDotLength > 7)
    {
        fprintf(stderr,"***ERROR In File:Amount validation failed: Digit length >= 8***\n.!!TERMINATING PROGRAM!!\n");
        exit(EXIT_FAILURE);
    }
    for(i =0;i<beforeDotLength;i++)
    {
        if(!isdigit(*cpyamount))
        {
            fprintf(stderr,"***ERROR In File:Amount validation failed: Contains other than digit.***\n.!!TERMINATING PROGRAM!!\n");
            exit(EXIT_FAILURE);
        }
        
    }
    
    dec_ptr = strchr(dot_ptr,'\0');
    
    if (dec_ptr != NULL)
    {
        *dec_ptr = '\0';
    }
    dec_ptr++;
    
    afterDotLength = strlen(dot_ptr);
    if(afterDotLength != 2)
    {
        fprintf(stderr,"***ERROR In File:Amount validation failed: More/Less than 2 digit after decimal.***\n.!!TERMINATING PROGRAM!!\n");
        exit(EXIT_FAILURE);
    }
    for(i =0;i<afterDotLength;i++)
    {
        if(!isdigit(*dot_ptr))
        {
            fprintf(stderr,"***ERROR In File:Amount validation failed: Contains other than digit.***\n.!!TERMINATING PROGRAM!!\n");
            exit(EXIT_FAILURE);
        }
        dot_ptr++;
    }
    
    return;
    
}

void validateField4(char* desc)
{
    char arrdesc[1000];
    int i=0;
    if(desc == NULL)
    {
        fprintf(stderr,"***ERROR In File:Description Validation Failed: It's BLANK***\n!!TERMINATING PROGRAM!!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(arrdesc,desc);
    while(i < strlen(desc) && arrdesc[i] == ' ')
    {
        i++;
    }
    
    if(i == strlen(desc))
    {
        fprintf(stderr,"***ERROR In File:Description Validation Failed: It contains only spaces***\n!!TERMINATING PROGRAM!!\n");
        exit(EXIT_FAILURE);
    }
    
    else if(i > 0)
    {
        int j;
        char newArray[1000];
        for(j=0; i < strlen(desc)  ; j++,i++ )
        newArray[j] = arrdesc[i];
        strcpy(desc,newArray);
        //printf("$$$$$$$$$$$$  %s $$$$$$$$$", desc);
    }
    
    return;
    
    
}


#endif // _VALIADTION_H_
    
