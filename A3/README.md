# CMPT225 A3

## Building the IndPQ

### Heap 

I began by copying the heap code from the textbook and understanding that. 

### HMap

I then copy and pasted my HMap from A2 into a file and removed the template so that it just worked with a string and integer.

### Placing inside of IndPQ

After that I created an IndPQ class and pasted the Heap and HMap into the private section and copied the provided necessary functions into the class.

I went top down beginning with the insert function. My indpq function simply inserted the the taskid into the heap, and the taskid and index into the hmap.
This worked fine until I inputted a lower priority task. This lead to the index being incorrect in lower priority items. The priority also didnt update properly. 

To solve this I went into the heap insert function used print debug statements to understand the indexs that items were being inserted and moved into. This helped me understand where I would need to update the hmap. I struggled to understand how to update the Hmap from inside the heap class, until I realized that simple passing a reference to the hmap into the constructor would solve the issue as I could then directly access Hmap functions. 

I then added a setValue function to the hmap which allowed me to change the integer value of a given taskid and added it into the heaps insert, percolateUp and percolateDown functions.

After this I implemented the delete min function adding a mintaskbuffer to be able to easily return a reference.

GetMin was simple, it just needed to call the heap's getmin function.

update priority worked by finding the index of the taskid from the Hmap and calling setPriority on that index in the Heap.

For remove I remembered that the priorities inputted are supposed to be positive when using it, but the class doesnt prohibit the use of negative numbers, so I simple set the priority of the given taskid to -1 and called removeMin.

All the other functions followed easily, acting as wrapper functions over the heap and hmap clear, display, ddisplay, and size functions. 



