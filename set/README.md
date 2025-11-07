# CS50 Lab 5, Fall 2025, William Bowles


### set

A `set` is an unordered collection of items that can be identified by their respective key. 
A pair in a set represents an item and its key. The set starts off empty, and can grow as the user inputs items. 
Once added, an individual item cannot be removed/extracted from the set, however the entire set can be deleted. 

### usage

The set module, which was defined in set.h and implemented in set.c, implements a bag of char* keys and void* items. 
It uses these functions:

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp,
               void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg,
                 void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );
```

### implementation

Similar to bag, this set is implemented as a linked list. The set itself points to the head of the list, which is null
if the set is empty. 

Each node is a `struct setnode`, which is defined in the module. Each setnode has a char* key, a pointer to a void* item,
and a pointer to the next node in the list.

The `set_new` method creates an empty set, with the head set to null. 

The `set_insert` method, assuming a valid set pointer, key pointer, and item pointers have been provided. Creates a new 
node for a new key and item if it isn't already present in the set. If it does exist, or if any of the parameters are
null, it returns false.

The `set_find` method, with valid set and key pointers, will return the item at the given key. If the item is not present,
or if any of the parameters are null, it will return null. Also, the item is not removed from the set if it is found.

The `set_print` method prints the set in the form {key1=item1,key2=item2,...,}. It uses a user provided itemprint function.

The `set_iterate` method iterates through the set, unless if the provided itemfunc or set are null. It calls
itemfunc on each key/item pair in the set.

The `set_delete` function frees all dynamically allocated memory, and calls itemdelete on the item pointer. However, if set
or itemdelete are null, it does nothing. All key strings, nodes, and the set itself are freed otherwise. 

### assumptions

I intentionally designed my unit test to cover pretty much the edge cases, cases where I think the code could have gone wrong, but I prevented. However, my test file brute forced this approach, and thus doesn't have a test file. If I had used a test file, I would have used `file_readLine` to read each line, which would have called malloc on these key item pairs. 
Since I did not use this, items are not dynamically allocated, and thus they don't have to be freed in the itemdelete 
function. 

My assumption is this:
The user does not provide a test file in the settest.c script. If they do, I wrote the itemdelete function, and they would
have to uncomment the line I commented out with the note. This way, the dynamically allocated memory would be freed, and
there would be no memory leaks. 

I didn't think a test file would be necessary to accomplish the assignment, since my brute force method calling / setup
approach handles my test cases how I wanted them to be handled. 

### files
* `Makefile` - compilation
* `set.h` - interface
* `set.c` - implementation of interface
* `settest.c` - comprehensive unit test driver
* `testing.out` - output of make test &> testing.out

### compilation

Use `make test &> testing.out` or `make valgrind`.

### testing

My settest.c program effectively uses all methods, and tries to throw edge cases / null parameters to mess up the result.
It results in no memory leaks and since it uses all methods with no errors with the edge cases and valid cases, it should
work properly. You can see for yourself with `make valgrind`. 

Also, the main function in settest.c doesn't have too many comments, since I thought the prints made almost everything
intuitive. Some things are explained with comments, though, but feel free to look at testing.out to see the outputs
of the large amount of tests I did. 







