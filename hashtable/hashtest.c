/* 
 * hashtest.c 
 *
 * This program is a unit test for the hashtable module. 
 * It tests a lot of edge/null cases + valid cases for each method
 *
 * William Bowles, November 6th, 2025.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "file.h"

static void itemfunc(void* arg, const char* key, void* item);
static void itemprint(FILE* fp, const char* key, void* item);
static void itemdelete(void* item);

int main()
{
  hashtable_t* ht1 = NULL; //one table
  char* key = NULL; 
  char* name = NULL;
  int namecount = 0; //count of names i put into the hashtable
  int tablecount = 0; //count of names hashtable_iterate found, used for testing that method

  printf("Test 1: Create a hashtable.\n");
  ht1 = hashtable_new(3);
  if (ht1 == NULL) {
    fprintf(stderr, "Test 1 failed.\n");
    return 1;
  }

  printf("Test 2: hashtable_insert with invalid ht, key, and item\n");
  key = "Key1";
  name = "Bob";
  bool test1 = hashtable_insert(NULL, key, name);
  bool test2 = hashtable_insert(ht1, NULL, name);
  bool test3 = hashtable_insert(ht1, key, NULL);
  if ((test1 || test2 || test3) == true) {
    fprintf(stderr, "Test 2 failed.\n");
    return 2;
  }

  printf("Test 3: hashtable_iterate following Test 2. We expect the result to be 0.\n");
  hashtable_iterate(ht1, &tablecount, itemfunc);
  if (tablecount != 0) {
    fprintf(stderr, "Test 3 failed.\n");
    return 3;
  }
  printf("Result: %d\n", tablecount);

  printf("Test 4: hashtable_insert three times.\n");
  bool test4 = hashtable_insert(ht1, "Key1", "Bob");
  namecount += 1;
  bool test5 = hashtable_insert(ht1, "Key2", "Steven");
  namecount += 1;
  bool test6 = hashtable_insert(ht1, "Key3", "Joe");
  namecount += 1;
  if ((test4 || test5 || test6) == false) {
    fprintf(stderr, "Test 4 failed.\n");
    return 4;
  }

  printf("Test 5: hashtable_print on the resulting hash table. Will also give us further info for Test 4.\n");
  hashtable_print(ht1, stdout, itemprint);

  printf("Test 6: hashtable_print with invalid ht, file, and itemprint.\n");
  hashtable_print(NULL, stdout, itemprint); //code should continue and print nothing, see testing.out
  hashtable_print(ht1, NULL, itemprint);
  hashtable_print(ht1, stdout, NULL);

  printf("Test 7: hashtable_insert with an existing key.\n");
  bool test7 = hashtable_insert(ht1, "Key1", "Bart");
  if (test7 == true) {
    fprintf(stderr, "Test 7 failed.\n");
    return 5;
  }
  name = hashtable_find(ht1, "Key1");
  printf("For Test 7, we put existing key 1 and tried to overwrite Bob with Bart. Expected: Bob. Result: %s\n", name);
  printf("Test 8: hashtable_find with valid parameters.\n");
  name = hashtable_find(ht1, "Key1");
  printf("Expected: Bob. Result: %s\n", name);

  printf("Test 9: hashtable_find with invalid parameters.\n");
  name = hashtable_find(NULL, "Key1");
  if (name != NULL) {
    fprintf(stderr, "Test 9 failed.\n");
    return 6;
  }
  printf("If nothing printed below Test 9 before this message, the test passed.\n");
  name = hashtable_find(ht1, "Key4");
  if (name != NULL) {
    fprintf(stderr, "Test 9 failed.\n");
    return 7;
  }

  printf("Test 10: hashtable_delete.");
  hashtable_delete(ht1, itemdelete);

  return 0;
}

/* count the non-null key/item pairs in table
 */
static void itemfunc(void* arg, const char* key, void* item)
{
  int* numitems = arg;

  if (numitems != NULL && key != NULL && item != NULL) {
    (*numitems)++;
  }
}

/* prints a key=item pair
 */
static void itemprint(FILE* fp, const char* key, void* item)
{
  const char* k = key;
  char* name = item;
  if (k == NULL || name == NULL) {
    fprintf(fp, "(null)");
  } else {
    fprintf(fp, "%s=%s", k, name);
  }
}

/* deletes an item by freeing its memory
 */
static void itemdelete(void* item)
{
 if (item != NULL) {
    //free(item); //NOTE: ASSUMPTION: No test file is provided, thus items are not dynamically allocated. 
    //Above is the line that would exist if the item was dynamically allocated, however for my test cases, it is not
    //therefore it will remain commented. If I were to use a test file, file_readLine would use malloc, so this would
    //need to be uncommented
 }
}
