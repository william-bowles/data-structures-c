/*
 * set.c  William Bowles  November 5, 2025
 *
 * All functions explained in set.h. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "mem.h"

/*******local types******/
typedef struct setnode {
  void* item; //pointer for data for any item that can fill this spot
  char* key; //key for this item
  struct setnode *next; //links to the next node
} setnode_t;

/******global types*******/
typedef struct set {
  struct setnode *head;
} set_t;

/*****local functions*****/
static setnode_t* setnode_new(char* key, void* item);

/*******set_new()*******/
/* see set.h for description */
set_t* set_new(void) 
{
  set_t* set = mem_malloc(sizeof(set_t)); //allocates space for the bag
  if (set == NULL) {
    return NULL; //error creating bag
  } else {
    set->head = NULL; //initialize the head of the bag
    return set;
  }
}

/******set_insert*******/
/* see set.h for description */
bool set_insert(set_t* set, const char* key, void* item) 
{
  if (set == NULL || key == NULL || item == NULL) { //if any of the parameters are null, return false.
    return false;
  }
  char* k = malloc(strlen(key) + 1); //copies key string for use by the set
  strcpy(k, key);
  for (setnode_t* node = set->head; node != NULL; node = node->next) { //otherwise, iterate through set
    if (strcmp(node->key, k) == 0) { //if matching key, can't have duplicate keys, return false
      return false;
    }
  }
  setnode_t* new = setnode_new(k, item); //otherwise, allocate new node and add it to the head
  if (new != NULL) {
    new->next = set->head;
    set->head = new;
    return true;
  }
  return false; //if allocating failed, return false
}

/********setnode_new*********/
/*Allocates and initalizes a new setnode */
static setnode_t* setnode_new(char* key, void* item)
{
  setnode_t* node = mem_malloc(sizeof(setnode_t));
  if (node == NULL) { //if creating node failed, return null
    return NULL;
  } else { //set values in node to provided values. 
    node->item = item;
    node->key = key;
    node->next = NULL;
    return node;  
  }
}

/********set_find*********/
/* see set.h for description */
void* set_find(set_t* set, const char* key) 
{
  if (set == NULL || key == NULL) { //if null parameters, or empty set, return nll
    return NULL;
  } else if (set->head == NULL) {
    return NULL;
  } 
  for (setnode_t* node = set->head; node != NULL; node = node->next) { //otherwise, iterate through list 
    if (strcmp(node->key, key) == 0) { //find matching key
      void* item = node->item;
      return item;
    } 
  }
  return NULL; //return null if nothing found
}

/********set_print********/
/* see set.h for description */
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) ) 
{
  if (fp != NULL) { //if fp and set are not null
    if (set != NULL) {
      fputc('{', fp);
      for (setnode_t* node = set->head; node != NULL; node = node->next) {
        if (itemprint != NULL) {
          (*itemprint)(fp, node->key, node->item); //formatting depending on user created itemprint
          fputc(',', fp);
        }
      }
      fputc('}', fp);
    } else {
      fputs("(null)", fp); //if empty set
    }
  }
}

/*******set_iterate*******/
/* see set.h for description */
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) 
{
  if (set != NULL && itemfunc != NULL) { //if nonnull params
    for (setnode_t* node = set->head; node != NULL; node = node->next) { //iterate through list
      (*itemfunc)(arg, node->key, node->item); //run user provided function
    }
  }
}

/********set_delete********/
/* see set.h for description */
void set_delete(set_t* set, void (*itemdelete)(void* item) ) 
{
  if (set != NULL) { //if set is not null
    for (setnode_t* node = set->head; node != NULL;) { //iterate through and run itemdelete function for each item
      if (itemdelete != NULL) {
        (*itemdelete)(node->item);
      }
      setnode_t* next = node->next;
      free(node->key); //frees key copy
      mem_free(node); //free memory
      node = next;
    }
    mem_free(set); //free memory
  }
}















