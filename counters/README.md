# CS50 Lab 5, Fall 2025, William Bowles.


### counters

'Counters' is an unordered collection of integer key and integer count pains. 
It starts empty, and grows as the caller adds key count pairs. 
It can only grow or be deleted entirely. It is not possible to remove specific counter.
However, a count for a specific key may be decremented, if the user chooses to do so.


### usage

The counters module defined in counters.h and implemented in counters.c uses these functions:
```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg,
                                       const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### implementation

Similar to the bag module, it is implemented as a linked list. The counters points to the head, which will be null for
an empty counters. Each node is a struct countersnode, which includes a integer key and unsigned int count. 

To create a new counters, we malloc space for a new ```counters_t``` struct, and set its head to null.

To add to this counters, if a key already exists in a node, we increment its count by one. Otherwise, we create a new
node for the given key and set its count to 1. 

To get a count at a specific key, we iterate through the linked list in search of a matching key. If we find it, return
the count at that key. If not, or if counters is null or key is less than 0, return 0. 

To set a count at a specific key, if the key already exists at a node, we set its count to the given count. If the key
isn't present in the struct, we create a new node for it and set its count to the given count. 

The counters print method will print all of the nodes in the format {key1=count1,key2=count2,...,}. 

The counters iterate method calls the provided itemfunc to count each node that has a nonnull key and count. 

Finally, the counters delete method frees dynamically allocated memory for each node and the entire counters struct. 

### assumptions

My test cases in counterstest.c are provided in a brute force manner, but I think it comprehensively covers the measures 
I have taken to prevent errors. Therefore, I had no need for an input file. My assumption is that an input file is not
used for testing. 

For the specifics for the keys and counts, we assume the count cannot be set below 0, and a key cannot be below 0. 


### files
* `Makefile` - compilation procedure
* `counters.h` - Interface
* `counters.c` - Implementation
* `counterstest.c` - Unit test
* `testing.out` - Output of unit test, obtained from running make test &> testing.out

### compilation
To run the module with the test file, run `make test &> testing.out`.

### testing

My testing covers every single function provided in the module, following the user running `make test &> testing.out`. 
It will test null/invalid inputs for each of the functions, as well as valid inputs and periodic count checks to 
ensure the methods worked properly.

As a note, my main function doesn't have too many comments, simply due to the print statements covering what would
have been said in comments. Anything not intuitive from the print statements actually has a comment, though.  
