#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "file.h"

static void itemfunc(void* arg, const int key, const int count);

int main()
{
  counters_t* ctrs1 = NULL; //one counters
  int key = 1; //key, starts at 1 for first count
  int count = 10; //count to set the key to
  int inputcount = 0; //number of keys put into counters
  int ctrscount = 0; //number of keys found in counters

  printf("Test 1: create counters\n");
  ctrs1 = counters_new();
  if (ctrs1 == NULL) {
    fprintf(stderr, "Test 1 failed.\n");
    return 1;
  }

  printf("Test 2: counters_add with existing key, and new key\n");
  int test1 = counters_add(ctrs1, key);
  int test2 = counters_add(ctrs1, key);
  inputcount += 1;
  if (test1 == 0 || test2 == 0) {
    fprintf(stderr, "Test 2 failed.\n");
    return 1;
  }
  counters_iterate(ctrs1, &ctrscount, itemfunc);
  printf("Number of items in counters: %d. Expected: 1\n", ctrscount);

  printf("Test 3: counters_add with null counters or negative key.\n");
  int test3 = counters_add(NULL, key);
  int test4 = counters_add(ctrs1, -1);
  if (test3 != 0 || test4 != 0) {
    fprintf(stderr, "Test 3 failed.\n");
    return 2;
  }

  printf("Test 4: counters_get with valid key first, invalid key second.\n");
  int test5 = counters_get(ctrs1, key);
  key += 1;
  int test6 = counters_get(ctrs1, key);
  if (test5 == 0 || test6 != 0) {
    fprintf(stderr, "Test 4 failed.\n"); 
  }
  printf("Result: %d. Expected 2.\n", test5);

  //set up more keys in the counters
  key += 1;
  int test7 = counters_add(ctrs1, key);
  inputcount += 1;
  key += 1;
  int test8 = counters_add(ctrs1, key);
  inputcount += 1;
  key += 1;
  int test9 = counters_add(ctrs1, key);
  inputcount += 1;
  if (test7 == 0 || test8 == 0 || test9 == 0) {
    return 3; //didnt create them properly
  }

  printf("Test 5: counters_set with invalid key, null ctrs, invalid count, and valid params\n");
  bool test10 = counters_set(NULL, 1, count);
  bool test11 = counters_set(ctrs1, -1, count);
  bool test12 = counters_set(ctrs1, 1, -1);
  bool test13 = counters_set(ctrs1, key, count);
  if ((test10 || test11 || test12) == true || (test13 == false)) {
    fprintf(stderr, "Test 5 failed.\n");
    return 4;
  }
  printf("See result in Test 6. Expected count %d at key %d\n", count, key);

  printf("Test 6: counters_print\n");
  counters_print(ctrs1, stdout);
  printf("\n");

  ctrscount = 0;
  printf("Test 7: counters_iterate with null ctrs, itemfunc, and then a third, valid test\n");
  counters_iterate(NULL, &ctrscount, itemfunc);
  counters_iterate(ctrs1, &ctrscount, NULL);
  counters_iterate(ctrs1, &ctrscount, itemfunc);
  printf("Expected: %d. Result: %d. \n", inputcount, ctrscount);

  printf("Test 8: counters_delete\n");
  counters_delete(ctrs1);

  return 0;
}

/* count the non null items in the bag */
static void itemfunc(void* arg, const int key, const int count) 
{
  int* numitems = arg;
  if (numitems != NULL && key > -1 && count > -1) {
    (*numitems)++;
  }
}






