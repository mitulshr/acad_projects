#ifndef _MYLIST_C_
#define _MYLIST_C_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cs402.h"
#include "my402list.h"

//#include "init.h"
extern int My402ListInit(My402List* List)
 {
   if(List != NULL)
     {
        List->num_members = 0;
        List->anchor.next = &(List->anchor);
        List->anchor.prev = &(List->anchor);
        List->anchor.obj = NULL;
        return TRUE;
    }
   else
        return FALSE;
 }



//#include "find.h"

extern My402ListElem* My402ListFirst(My402List* List)
 {
  if(List->anchor.next == NULL)
    return NULL;
else
    return List->anchor.next;
 }


//extern My402ListElem *My402ListLast(My402List*);
//Returns the last list element or NULL if the list is empty.

extern My402ListElem* My402ListLast(My402List* List)
 {
  if(List->anchor.prev == NULL)
    return NULL;
else
    return List->anchor.prev;
 }

extern My402ListElem* My402ListFind(My402List* List, void* searchData)
{
   My402ListElem *node = List->anchor.next;
   while(node != &(List->anchor))//last
    {

      if(node->obj == searchData)
        return node;
      node = node->next;
    }

    return NULL;
}


//#include "checks.h"

int  My402ListLength(My402List* List)
{
  return List->num_members;
}

extern int  My402ListEmpty(My402List* List)
{
    if(List->num_members == 0)
       return TRUE;
    else
       return FALSE;
}

//extern My402ListElem *My402ListNext(My402List*, My402ListElem*);
//Returns elem->next or NULL if elem is the last item on the list. Please do not check if elem is on the list.
extern My402ListElem* My402ListNext(My402List* List,My402ListElem* Node)
 {
  if((Node->next) == &(List->anchor)) // you might need to compare each element for the array
    return NULL;
else
    return Node->next;
 }

  //extern My402ListElem *My402ListPrev(My402List*, My402ListElem*);
//Returns elem->prev or NULL if elem is the first item on the list. Please do not check if elem is on the list.

 extern My402ListElem* My402ListPrev(My402List* List, My402ListElem* Node)
 {
  if((Node->prev) == &(List->anchor)) // you might need to compare each element for the array
    return NULL;
else
    return Node->prev;
 }

//extern void My402ListPrintEle(My402ListElem* node)
//{
//   data* tmp = node->obj;

//   printf("Sign : %c\n",tmp->a[1]);
//   printf("Time : %ul\n",tmp->tstamp);
//   printf("Date : %d\n",tmp->amount);
   //printf("Desc : %s\n",*(tmp->desc));

//}

//extern void My402ListPrint(My402List* List)
//{
 //  My402ListElem* tmp = List->anchor.next;
  // while(tmp != &(List->anchor))
  //   {
  //    My402ListPrintEle(tmp);
  //    tmp = tmp->next;
  //   }

//}




//#include "addlink.h"
extern int  My402ListAppend(My402List* List, void* insData)
{

   My402ListElem *newNode = (My402ListElem *) malloc(sizeof(My402ListElem));

   if(newNode != NULL)
     {
        newNode->obj = insData;
        if(My402ListEmpty(List))
            {
                List->anchor.next = newNode;
                List->anchor.prev = newNode;
                newNode->next = &(List->anchor);
                newNode->prev = &(List->anchor);
                (List->num_members)++;
                return TRUE;
            }
        else
            {
                My402ListElem *lastNode = My402ListLast(List);
                lastNode->next = newNode;
                newNode->next = &(List->anchor);
                List->anchor.prev = newNode;
                newNode->prev = lastNode;
                (List->num_members)++;
                return TRUE;
            }

     }
     return FALSE;
}

extern int  My402ListPrepend(My402List* List, void* insData)
 {
   My402ListElem *newNode = (My402ListElem *) malloc(sizeof(My402ListElem));

   if(newNode != NULL)
    {
        newNode->obj = insData;
        if(My402ListEmpty(List))
            {
                List->anchor.next = newNode;
                List->anchor.prev = newNode;
                newNode->next = &(List->anchor);
                newNode->prev = &(List->anchor);
                (List->num_members)++;
                return TRUE;
            }
        else
            {
                My402ListElem *firstNode = My402ListFirst(List);
                List->anchor.next = newNode;
                newNode->next = firstNode;
                firstNode->prev = newNode;
                newNode->prev = &(List->anchor);
                (List->num_members)++;
                return TRUE;
            }
    }
     return FALSE;

 }

 extern int  My402ListInsertAfter(My402List* List, void* insData, My402ListElem* givenNode)
{

   My402ListElem *newNode = (My402ListElem *) malloc(sizeof(My402ListElem));
   if(newNode != NULL)
    {
        newNode->obj = insData;
        if(givenNode == NULL)
            {
                return My402ListAppend(List,insData);
            }
        else
            {
                My402ListElem *nextNode = givenNode->next;//BE CAREFULL
                givenNode->next = newNode;
                newNode->next = nextNode;
                nextNode->prev = newNode;
                newNode->prev = givenNode;
                (List->num_members)++;
                return TRUE;
            }
    }
     return FALSE;
}

extern int  My402ListInsertBefore(My402List* List, void* insData, My402ListElem* givenNode)
{
   My402ListElem *newNode = (My402ListElem *) malloc(sizeof(My402ListElem));

   if(newNode != NULL)
     {
        newNode->obj = insData;
        if(givenNode == NULL)
         {
           return My402ListPrepend(List,insData);
         }
        else
         {
           My402ListElem *prevNode = givenNode->prev;//BE CAREFULL
           prevNode->next = newNode;
           newNode->next = givenNode;
           givenNode->prev = newNode;
           newNode->prev = prevNode;
           (List->num_members)++;
           return TRUE;
         }
      }

return FALSE;

}

//extern void My402ListUnlink(My402List*, My402ListElem*);
//Unlink and delete elem from the list.
//Please do not delete the object pointed to by elem and do not check if elem is on the list.
//extern void My402ListUnlinkAll(My402List*);
//Unlink and delete all elements from the list and make the list empty.
//Please do not delete the objects pointed to be the list element

extern void My402ListUnlink(My402List* List, My402ListElem* node)
 {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    (List->num_members)--;
 }

extern void My402ListUnlinkAll(My402List* List)
 {
    My402ListElem* tmp;
    while (List->anchor.next != &(List->anchor))
        {
         tmp = List->anchor.next;
         List->anchor.next = List->anchor.next->next;
         free(tmp);
        }
    List->num_members = 0;
    List->anchor.next = &(List->anchor);
    List->anchor.prev = &(List->anchor);
 }





#endif // _MYLIST_C_
