/*
 * hashtable.c - CS50 hashtable module
 *
 * See hashtable.h for method descriptions
 *
 * William Bowles, November 6th, 2025.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "hash.h"
#include "mem.h"
#include "set.h"

/***********global types********/
typedef struct hashtable {
	size_t size; //how many spots in the table
	set_t** hash; //array of pointers to sets
} hashtable_t;

/***********hashtable_new*********/
/* see hashtable.h for description */
hashtable_t* hashtable_new(const int num_slots) 
{
  if (num_slots < 1) { //cant have 0 spots, calloc wont work
    return NULL;
  }
  size_t size = num_slots;
  hashtable_t* hashtable = mem_malloc(sizeof(hashtable_t)); //mallocs
  if (hashtable == NULL) { 
    return NULL;
  } else { //if successful, makes space
    hashtable->size = size;
    hashtable->hash = mem_calloc(num_slots, sizeof(set_t*)); //array of pointers to sets with size num_slots, use calloc
    return hashtable;
  }
}

/************hashtable_insert**********/
/* see hashtable.h for description */
bool hashtable_insert(hashtable_t* ht, const char* key, void* item) 
{
  if (ht == NULL || key == NULL || item == NULL) { //fails if null parameters
    return false;
  }
  for (size_t i = 0; i < ht->size; i++) { //iterates through each set in the table
    void* thing = set_find(ht->hash[i], key); //runs respective set method
    if (thing != NULL) { //if key already exists
      return false;
    }
  }
  unsigned long hash_spot = hash_jenkins(key, ht->size); //otherwise, determines its spot
  if (ht->hash[hash_spot] == NULL) { //if set isnt created yet at the spot
    set_t* new = set_new(); //creates a new set and inserts the key item pair to that set slot
    bool insert = set_insert(new, key, item);
    if (insert == true) {
      ht->hash[hash_spot] = new;
      return true;
    }
  } else {
    bool insert2 = set_insert(ht->hash[hash_spot], key, item); //otherwise, just inserts it to existing set
    if (insert2 == true) {
      return true;
    }
  }
  return false;
}

/***********hashtable_find**********/
/* see hashtable.h for description */
void* hashtable_find(hashtable_t* ht, const char* key) 
{
  if (ht == NULL || key == NULL) { //cant have null params
    return NULL;
  } else {
    for (size_t i = 0; i < ht->size; i++) { //through each set in table
      void* item = set_find(ht->hash[i], key);
      if (item != NULL) {
        return item;
      }
    }
  }
  return NULL; //couldnt find the key
}

/**********hashtable_print*********/
/* see hashtable.h for description */
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) ) 
{
  if (fp != NULL) { //cant have null table or fp
    if (ht != NULL) {
      fputc('{', fp);
      for (size_t i = 0; i < ht->size; i++) {
        set_print(ht->hash[i], fp, (*itemprint)); //runs set_print for each set in table
	printf("\n");
      }
    } else {
      fputs("(null)\n", fp); //if the table is null
    }
  }
}

/*********hashtable_iterate********/
/* see hashtable.h for description */
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) 
{
  if (ht != NULL && itemfunc != NULL) { 
    for (size_t i = 0; i < ht->size; i++) {
      set_iterate(ht->hash[i], arg, itemfunc); //runs set_iterate for each set
    }
  }
}

/**********hashtable_delete********/
/* see hashtable.h for description */
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ) 
{
  if (ht != NULL) {
    for (size_t i = 0; i < ht->size; i++) {
      set_delete(ht->hash[i], (*itemdelete)); //iterates through each set, and then runs set_delete for the set
    }
    mem_free(ht->hash); //frees the array of pointers to sets
    mem_free(ht); //finally, frees the table
  }
}


















