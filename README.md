# CMPT225 Assignment Three: Part A
# Introduction

The main operations of a priority queue are insert( O, P  ), which inserts object O with priority P, and deleteMin() which deletes and returns the object of highest priority.   In typical uses, these objects would be tasks, processes, or customers, for example.  In class we described using a heap to implement a priority queue, but in our heap descriptions we only considered the priority values, not the objects associated with them.   If we only need the operations insert and deleteMin, then it is easy to modify the design from lecture to address this.   We simply change the array so that instead of storing priority values it stores pairs consisting of an object and its associated priority.  (And of course modify some functions to pass the objects as arguments or return values.)   This is similar to the way we modified the HashTable class, which stores a set, to make a HMap class, which stores key-value pairs, in assignment 2, by modifying the hash table array elements.

However, we might also want our priority queue class to have an operation update operation.   If O is an object in the priority queue with priority P, then updatePriority( O, Q ) changes the priority associated with object O to Q.   The problem is that the pair (O,P) is somewhere in the heap array, but we have no easy way to find it.   A sequential search of the array will work, but is too inefficient.   To implement updatePriority() efficiently, we’ll need to maintain a map — let’s call it M — from objects to their array indices (aka node numbers).  To implement  updatePriority( O, Q ), we use M to look up where the pair (O,P) is in the array, change P to Q, and then do a percolate_up or percolate_down as needed. 

The percolate_up and percolate_down functions move object-priority pairs around in the array.   As they are moved around, they need to keep the map M up to date.   Each time a heap operation calls percolate_up() or percolate_down(), there could be many movements of pairs in the array, resulting in many updates of M.  Therefore, we want updating M to be very efficient.

A data structure that enhances a heap with a map to support updatePriority() is sometimes called an "indexed heap".  There are many possible designs for indexed heaps.  If you search online for some, you will probably find that most examples give easy solutions based on very restrictive assumptions about the objects involved, such as that they are just numbers 1 through n.  We would like a more general solution.  Conveniently, we just had practice in implementing a map as a template class, and for which we expect insert and remove to be quite efficient.  

# The IndPQ Class

Your main task is to implement an Indexed Priority Queue class, called IndPQ.   For this class, priorities will be non-negative integers with 0 being the highest priority, and the objects will be instances of the C++ string class std::string.  We will call the strings “task ID’s”.   The public functions are:  

IndPQ() —-> constructor creating an empty IndPQ.
void insert( const std::string & taskid, int p ) --> Insert taskid with priority p.
std::string & deleteMin()  --> Remove and return (a reference to) a task ID with smallest priority.
std::string & getMin()  --> Return (a reference to) a task ID with the smallest priority.
void updatePriority( const std::string & taskid, int p )  --> change the priority for taskid to p.
void remove( const std::string & tid ) --> remove taskid from the PQ
bool isEmpty( ) --> Return true if the PQ is empty, otherwise false.
int size()  --> Return the number of tasks in the PQ.
void clear( )  --> Remove all tasks from the PQ.
void display( ) —-> prints out the queue contents.
void ddisplay( ) —-> prints out a representation of the data structures.

IndPQ Implementation

Your IndPQ class must be implemented by making use of two data structures.  The first is a heap (lets call it H) in which "nodes" contain a pair consisting of a priority (non-negative int) and a task ID (a string).   You must implement the heap class yourself, as described below.  The second is an instance (lets call it M) of an HMap class, like the one from Assignment 2.  unordered_map, which you use to map task IDs to integers which are heap node numbers (i.e., array indices). The idea is that, to implement the IndPQ function updatePriority(taskid,p), you use M to find which node of the heap holds taskid, and then call a heap function to update the priority of that task in the heap. 

Notice that the heap update function is not of the form update( id, new_priority ), but rather of the form update( node_number, new_priority ), where node_number is the heap node (i.e., array index) of the task whose priority we want to update.   This a use of heap nodes outside the heap class is an exposure of internal information which would normally be private.   Since this exposure is specifically for our IndPQ implementation, we'll address it simply by making our heap class a private inner class of IndPQ.

So the IndPQ implementation is like this:  It has two private inner classes, Heap and HMap.  It uses one instance of each of these to implement the priority queue. 

The implementation of the heap class is a standard and straightforward heap implementation, with the exception that the heap operations have to keep M up to date: Each time a task is moved in the heap, the map M must be updated to reflect its new position. 

# References and Arrays

You should have some idea of the difference between call-by-value and call-by-reference.  Suppose our insert function was declared as void insert( std::string taskid, int priority), and extract min as std::string extractMin().   Recall that the function parameters are actually local variable in the function.  If we call insert( S, P ), then the variable taskid becomes a copy of the string S. The priority P is inserted into the heap, say at index i, and the pair (S,i) is inserted into to the map M.

A problem with this is that, if the strings are very large, we’re making copies of large strings and storing them.  We can imagine that the objects of interest might be even larger, and this would be inefficient in terms of both space and time.  To avoid this, the functions are declared void insert( std::string & taskid, int priority) and std::string & extractMin().   Here, the string is passed as a reference.  In this case, when calling insert( S, P ), the local variable taskid is not a copy of S, but rather an alias for S.  Similarly, extractMin does not return a copy of the string S, but a reference to the original string S.   

So far so good, but there is a problem:  We need to store S in the array the implements our map, but references aren’t objects, so cannot be stored in arrays.  There are a couple of way to address this, but the simplest is to instead store a pointer to S in the map. 

# Finally

The code you submit must be your own.   You can of course reference other examples, including the heap implementation in the textbook or other places, but you should type in all of your own code. (Really)  

You should also:

    Write a program that does a thorough job of testing your IPQ class;
    Document both your testing regimen design and your IPQ class design choices
    Have a make file that does the usual
