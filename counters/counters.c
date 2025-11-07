/*
 * counters.c 
 *
 * see counters.h for more information.
 *
 * William Bowles. November 5th, 2025.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "mem.h"

/*******local types*******/
typedef struct countersnode {
  int key; //integer key for this one
  unsigned int count; //count for how many times a key has appeared, cannot be negative
  struct countersnode *next; //next node
} countersnode_t;

/*******global types******/
typedef struct counters {
  struct countersnode *head;
} counters_t;

/********local functions****/
static countersnode_t* countersnode_new(const int key);

/*******counters_new()*******/
/* see counters.h for description */
counters_t* counters_new(void) 
{
  counters_t* counters = mem_malloc(sizeof(counters_t));
  if (counters == NULL) {
    return NULL; //returns error if struct wasn't created properly
  } else {
    counters->head = NULL; //otherwise, initializes head
    return counters;
  }
}

/*******counters_add*******/
/* see counters.h for description */
int counters_add(counters_t* ctrs, const int key) 
{
  if (ctrs == NULL || key < 0) { //ctrs cant be null and key needs to be positive
    return 0;
  } else {
    for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) { //iterates through counters
      if (node->key == key) { //checks if key matches
        node->count += 1; //if so, increment count
        return node->count;
      }
    }
  }
  countersnode_t* new = countersnode_new(key); //otherwise, create a new entry in struct.
  if (new != NULL) {
    new->next = ctrs->head;
    ctrs->head = new;
    return 1;
  }
  return 0; //node creation failed
}

/*******counters_get********/
/* see counters.h for description */
int counters_get(counters_t* ctrs, const int key) 
{
  if (ctrs == NULL || key < 0) { //key cant be negative and ctrs cant be null
    return 0;
  }
  for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) { //iterates through
    if (node->key == key) { //checks if key matches
      return node->count; //returns the count
    } 
  }
  return 0; //not found
}

/********counters_set*******/
/* see counters.h for description */
bool counters_set(counters_t* ctrs, const int key, const int count) 
{
  if (ctrs == NULL || key < 0 || count < 0) { //TODO: figure out what "if out of memory" means
    return false;
  }
  for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
    if (node->key == key) { //iterates through, if key found, set count to provided count
      node->count = count;
      return true;
    }
  }
  countersnode_t* new = countersnode_new(key); //otherwise, create a new node and sets the count there
  if (new != NULL) {
    new->count = count;
    new->next = ctrs->head;
    ctrs->head = new;
  }
  return true;
}

/*******countersnode_new*******/
/* creates a new countersnode and initializes the given key and sets the count to 1 */
static countersnode_t* countersnode_new(const int key) 
{
  countersnode_t* node = mem_malloc(sizeof(countersnode_t));

  if (node == NULL) {
    return NULL; //if creating the node failed
  } else {
    node->key = key; //sets the key to key
    node->count = 1; //sets the count to 1
    return node;
  }
}

/********counters_print*******/
/* see counters.h for description */
void counters_print(counters_t* ctrs, FILE* fp) 
{
  if (fp != NULL) { //fp cant be null
    if (ctrs != NULL) { //if ctrs isnt null
      fputc('{', fp);
      for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) {
        fprintf(fp, "%d=%d", node->key, node->count); //format: key=count
        fputc(',', fp);
      }
      fputc('}', fp);
    } else {
      fputs("(null)", fp); //null if ctrs is empty
    } 
  }
}

/*********counters_iterate******/
/* see counters.h for description */
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count) ) 
{
  if (ctrs != NULL && itemfunc != NULL) { //these can't be null
    for (countersnode_t* node = ctrs->head; node != NULL; node = node->next) { //iterates through
      (*itemfunc)(arg, node->key, node->count); //runs itemfunc user provided function
    }
  }
}

/********counters_delete*******/
/* see counters.h for description */
void counters_delete(counters_t* ctrs) 
{ 
  if (ctrs != NULL) {
    for (countersnode_t* node = ctrs->head; node != NULL;) {
      countersnode_t* next = node->next;
      mem_free(node); //frees node
      node = next;
    }
    mem_free(ctrs); //frees ctrs
  }
}











