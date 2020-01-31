// Giles Reger, 2019

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "global.h"
#include "pq.h"

// Some helper functions for checking the results of calls in tests
void check_result(int testno, char* expected, char* found){
 if(found == NULL){
   fprintf(stderr,"Test %d Failed when %s expected and NULL found\n",testno,expected);
   exit(-1);
 }
 if(strcmp(expected,found) != 0){
   fprintf(stderr,"Test %d Failed when %s expected and %s found\n",testno,expected,found);
   exit(-1);
 }
}
void assert(int testno, bool value, char* reason){
  if(!value){
   fprintf(stderr,"Test %d Failed as %s\n",testno,reason);
   exit(-1);
  }
}

// Check that hello and goodbye are poped in the right order
void run_test0(){
  printf("TEST 0\n");
  PriorityQueue queue = initialize_pq(10);
  printf("Initialised...\n");
  insert(queue,"hello",1);
  printf("Inserted hello with priority 1...\n");
  insert(queue,"goodbye",2);
  printf("Inserted goodbye with priority 2...\n");
  check_result(0,"hello",pop_min(queue));
  printf("Popped hello...\n");
  check_result(0,"goodbye",pop_min(queue));
  printf("Popped goodbye...\n");
  assert(0,is_empty(queue)," queue is meant to be empty");
  printf("Queue now empty\n");
  tidy(queue);
}
void run_test1(){
  printf("TEST 1\n");
  PriorityQueue queue = initialize_pq(2);
  printf("Initialised...\n");
  insert(queue,"hi",1);
  printf("Inserted hi with priority 1...\n");
  insert(queue,"see you later",2);
  printf("Inserted see you later with priority 2...\n");
  check_result(1,"hi",pop_min(queue));
  printf("Popped hi...\n");
  check_result(1,"see you later",pop_min(queue));
  printf("Popped see you later...\n");
  assert(1,is_empty(queue)," queue is meant to be empty");
  printf("Queue now empty\n");
  tidy(queue);
}
void run_test2(){
  printf("TEST 2\n");
  PriorityQueue queue = initialize_pq(1);
  printf("Initialised...\n");
  insert(queue,"hey",1);
  printf("Inserted hey with priority 1...\n");
  contains(queue, "hey",1);
  printf("Checked that queue contains hey with priority 1...\n");
  check_result(2,"hey",pop_min(queue));
  printf("Popped hey...\n");
  assert(2,is_empty(queue)," queue is meant to be empty");
  printf("Queue now empty\n");
  tidy(queue);
}
void run_test3(){
  printf("TEST 3\n");
  PriorityQueue queue = initialize_pq(3);
  printf("Initialised...\n");
  insert(queue,"Ziad",2);
  printf("Inserted Ziad with priority 2...\n");
  insert(queue,"hey",1);
  printf("Inserted hey with priority 1...\n");
  check_result(3,"hey",pop_min(queue));
  printf("Popped hey...\n");
  check_result(3,"Ziad",pop_min(queue));
  printf("Popped Ziad...\n");
  assert(3,is_empty(queue)," queue is meant to be empty");
  printf("Queue now empty\n");
  tidy(queue);
}
void run_test4(){
  printf("TEST 4\n");
  PriorityQueue queue = initialize_pq(3);
  printf("Initialised...\n");
  insert(queue,"Ziad",1);
  printf("Inserted Ziad with priority 1...\n");
  insert(queue,"Fady",2);
  printf("Inserted Fady with priority 2...\n");
  insert(queue,"Abdo",3);
  printf("Inserted Abdo with priority 3...\n");
  insert(queue,"Salem",4);
  printf("Tried Inserting Salem with priority 4...\n");
  if (contains(queue, "Salem",4) == false)
  {
    printf("Salem not inserted as queue has size 3\n");

  }
  check_result(4,"Ziad",pop_min(queue));
  printf("Popped Ziad...\n");
  check_result(4,"Fady",pop_min(queue));
  printf("Popped Fady...\n");
  check_result(4,"Abdo",pop_min(queue));
  printf("Popped Abdo...\n");
  assert(4,is_empty(queue)," queue is meant to be empty");
  printf("Queue now empty\n");
  tidy(queue);
}
void run_test5(){
  printf("TEST 5\n");
  PriorityQueue queue = initialize_pq(2);
  printf("Initialised...\n");
  insert(queue,"hi",1);
  printf("Inserted hi with priority 1...\n");
  insert(queue,"see you later",2);
  printf("Inserted see you later with priority 2...\n");
  if (contains(queue, "hi",2) == true)
  {
    printf("Hi is inserted at the wrong place\n");

  }
  if (contains(queue, "see you later",1) == true)
  {
    printf("see you later is inserted at the wrong place\n");
  }
  check_result(5,"hi",pop_min(queue));
  printf("Popped hi...\n");
  check_result(5,"see you later",pop_min(queue));
  printf("Popped see you later...\n");
  assert(5,is_empty(queue)," queue is meant to be empty");
  printf("Queue now empty\n");
  tidy(queue);
}

char* prog_name = 0;
int main (int argc, char *argv[])
{
 prog_name=argv[0];
 if(argc != 2){
   fprintf(stderr,"Supply test number\n");
   return -1;
 }
 char* tmp;
 int test_number = strtol(argv[1],&tmp,0);
 if(*tmp != '\0'){
   fprintf(stderr,"Supply test number as an integer\n");
   return -1;
 }
 switch(test_number){
   case 0: run_test0(); break;
   case 1: run_test1(); break;
   case 2: run_test1(); break;
   case 3: run_test1(); break;
   case 4: run_test1(); break;
   case 5: run_test1(); break;
   default:
     fprintf(stderr,"Test number %d not recognised\n",test_number);
 }
 return 0;
}
