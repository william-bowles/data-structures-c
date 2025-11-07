# CS50 Lab 5
# William Bowles, November 6th, 2025.

### hashtable

A hashtable is an unordered collection of sets that contain key/item pairs.
It starts off with each index in the hash table containing empty sets. 
Once a key/item pair is inserted, a calculation is done to determine which spot in the table it goes in. 
From there, the sets in the table grows, but the number of slots/sets remain the same. 

### usage

The hashtable module, defined in hashtable.h and implemented in hashtable.c, implements a hashtable of 
set* hashes, with each set* acting as a linked list. Each node contains a key/item pair. 
It has the following functions:

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### implementation

This hashtable is implemented as an array of pointers to sets, with the number of slots equal to the number provided
in `hashtable_new`. 

Each of the slots will work the exact same as a set, so feel free to check out the README.md for set. 

The hashtable insert method loops through each set and runs `set_find` to determine if a key is already present in the
table. If so, returns false. If not, inserts it into the table with a spot determined by `hash_jenkins` and returns true.
If a set doesn't exist, creates a new set and inserts it into the new set. If not, inserts into existing set. 

The hashtable find method simply loops through each slot in the table and runs `set_find`. If it returns a nonnull item,
we return that item, since it found a matching key.

The hashtable print method prints a slot on each line, running `set_print` for each slot. (null) if null slot/table.

The hashtable iterate function runs `set_iterate` for each slot in the table.

The hashtable delete function runs `set_delete` for each set on the table, then frees the array of pointers to the sets,
and finally, frees the table itself. 

Since a good number of these functions mainly involved looping through each set in the table and running its respective
set function, I made sure to make use of the set module. 

### assumptions

Similar to the previous two modules (and for the same reason), I assume that no input files are provided in to the test.
Since I brute forced my test cases (which I found to be more fruitful), there was no need for me to free items, since 
those were not dynamically allocated. If it came from a file, item strings would be dynamically allocated, so the user
needs to uncomment the line in itemdelete in hashtest.c. 

Also, caller is responsible for non null / valid parameters, but if it's messed up my code should still work fine. Assume
it's valid, though, I guess. 

### files
* `Makefile` - compilation
* `hashtable.h` - interface
* `hashtable.c` - implementation
* `hashtest.c` - unit test driver
* `testing.out` - result from running `make test &> testing.out`

### compilation

Run `make test &> testing.out`

### testing

I found my hashtest.c program to be pretty comprehensive in terms of testing. It covers null/edge cases, as well as valid
cases for every single function provided in hashtable.c. There aren't a lot of comments in the code, simply because I 
think `testing.out` does a good job explaining my tests. Everything unrelated to the testing itself has a comment, though.

Run `make test &> testing.out` to see the `testing.out` file. To see no memory leaks, run `make valgrind`. 



 
