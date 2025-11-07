/*
 * settest.c
 *
 * Program tests the module provided in set.c. 
 * William Bowles. November 5th, 2025.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "file.h"

static void itemprint(FILE* fp, const char* key, void* item);
static void itemfunc(void* arg, const char* key, void* item);
static void itemdelete(void* item);


int main() 
{
  set_t* set1 = NULL; //variables for two sets, name key and line char*, and counts for items put and found
  set_t* set2 = NULL;
  int namecount = 0;
  int setcount = 0;

  printf("Test 1: set_new.\n");
  set1 = set_new();
  if (set1 == NULL) {
    fprintf(stderr, "set_new returned an error.\n");
    return 1;
  }

  printf("Test 2: set_insert null handling. First, null set. Second, null key. Third, null item\n");
  set_insert(NULL, "Key1", "CS50");
  set_insert(set1, NULL, "CS50");
  set_insert(set1, "Key1", NULL);

  printf("To test if insert worked, Test 3: Test set_iterate following test 2. We expect the result to be 0. \n");
  set_iterate(set1, &setcount, itemfunc);
  printf("%d\n", setcount);

  printf("Test 4: set_insert with proper cases.\n");
  set_insert(set1, "Key1", "CS50");
  set_insert(set1, "Key2", "Dartmouth");
  set_insert(set1, "Key3", "William");
  set_insert(set1, "Key4", "Frog"); 
  namecount = 4;

  printf("Count should be %d: \n", namecount);
  setcount = 0;
  set_iterate(set1, &setcount, itemfunc);
  printf("Actual: %d\n", setcount);

  printf("Test 5: Printing the entire set: \n");
  set_print(set1, stdout, itemprint);
  printf("\n");

  printf("Test 6: set_find.\n");
  set2 = set_new();
  if (set2 == NULL) {
    fprintf(stderr, "set_new failed for second set");
    return 2;
  }

  set_insert(set2, "Key1", "CS50");
  char* item = set_find(set2, "Key1");
  printf("Expected CS50. Result: %s\n", item);
  printf("Test 7: Ensure set size remained the same following set_find\n");
  setcount = 0;
  set_iterate(set2, &setcount, itemfunc);
  printf("Expected size: 1. Actual: %d\n", setcount);
	
  printf("Test 8: Delete the sets.\n");
  set_delete(set1, itemdelete);
  set_delete(set2, itemdelete);

  return 0;
}

/* counts items in the bag that aren't null
 */
static void itemfunc(void* arg, const char* key, void* item) 
{
  int* numitems = arg;
  if (numitems != NULL && key != NULL && item != NULL) {
    (*numitems)++;
  }
}

/* prints a key item pair in the form key=item
 */
static void itemprint(FILE* fp, const char* key, void* item) 
{
  char* name = item;
  const char* k = key;
  if (name == NULL || k == NULL) {
    fprintf(fp, "(null)");
  } else {
    fprintf(fp, "%s=%s", k, name);
  }
}

/* deletes an item 
 */
void itemdelete(void* item) 
{
  if (item != NULL) {
    //free(item); **NOTE: ASSUMPTION: No test file is provided. If a test file were provided, the memory for an item 
    //would be dynamically allocated, and therefore free(item); would need to be uncommented. 
  }
}


















