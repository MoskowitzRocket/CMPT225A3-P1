/**
 * Copyright 2025 Kale Moskowitz
 * Written for CMPT 225 A3
 * IndPQ.h
 */

#pragma once
#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Function declaration for finding the next prime number
//This function is used to find the next prime number when the hash table is resized
int nextPrime(int n);


/**
 * Indexed Priority Queue Class
 * 
 */
class IndPQ
{

public:
    /**
     * Initialize hash map, heap, and set the current size to zero
     */
    IndPQ() : hmap(), heap(hmap), currentSize(0) {}

    // --> Insert taskid with priority p.
    void insert(const std::string &taskid, int p)
    {
        HeapNode newNode(p, taskid);
        int index = heap.insert(newNode);
        currentSize++;
        hmap.insert(taskid, index); // Store the heap index in hmap
    }

    //  --> Remove and return (a reference to) a task ID with smallest priority.
    std::string &deleteMin()
    {

        std::string &index = getMin();
        // minTaskBuffer = index;
        hmap.remove(index);
        heap.deleteMin();
        currentSize--;
        return index;
    }

    //  --> Return (a reference to) a task ID with the smallest priority.
    std::string &getMin()
    {
        HeapNode minNode = heap.findMin();
        minTaskBuffer = minNode.taskid;

        return minTaskBuffer;
    }

    //  --> change the priority for taskid to p.
    void updatePriority(const std::string &taskid, int p)
    {
        int index = hmap.getValue(taskid);
        heap.setPriority(index, p);
    }

    // --> remove taskid from the PQ
    void remove(const std::string &tid)
    {
        currentSize--;
        int index = hmap.getValue(tid);
        heap.setPriority(index, -1);
        deleteMin();
    }

    // --> Return true if the PQ is empty, otherwise false.
    bool isEmpty()
    {
        return heap.isEmpty();
    }

    //  --> Return the number of tasks in the PQ.
    int size()
    {
        return currentSize;
    }

    //  --> Remove all tasks from the PQ.
    void clear()
    {
        currentSize = 0;
        heap.clear();
        hmap.makeEmpty();
    }

    // —-> prints out the queue contents.
    void display()
    {
        heap.display();
        hmap.display();
    }

    // —-> prints out a representation of the data structures.
    void ddisplay()
    {
        heap.ddisplay();
        hmap.ddisplay();
    }

private:
    // Buffer to store the result of getMin() for returning by reference
    std::string minTaskBuffer;

    // Buffer to store the result of getMin() for returning by reference
    int currentSize;

    // Structure to store a task's priority and ID
    struct HeapNode
    {
        int priority;
        string taskid;
        HeapNode() : priority(0), taskid("") {} // Default constructor
        HeapNode(int p, string id) : priority(p), taskid(id) {}
    };

    // Hash Map and Heap classes

    /**
    * Uses the hash table to store the task IDs and their positions in the heap array
    */
    class HMap
    {
    public:
        // Constructor
        explicit HMap(int size = 11) : array(nextPrime(size))
        {
            makeEmpty();
        }

        // Check if the key is in the hash table
        bool contains(const string &x) const
        {
            return isActive(findPos(x));
        }

        // Make the hash table empty
        void makeEmpty()
        {
            currentSize = 0;
            for (auto &entry : array)
                entry.info = EMPTY;
        }

        // Get the size of the hash table
        int getSize() const
        {
            return currentSize;
        }

        // Insert a key into the hash table
        bool insert(const string &x, const int &y)
        {
            // Insert x as active
            int currentPos = findPos(x);
            if (isActive(currentPos))
                return false;

            if (array[currentPos].info != DELETED)
                ++currentSize;

            array[currentPos].key = x;
            array[currentPos].value = y;
            array[currentPos].info = ACTIVE;

            // Rehash; see Section 5.5
            if (currentSize > array.size() / 2)
                rehash();

            return true;
        }

        // Remove a key from the hash table
        bool remove(const string &x)
        {
            int currentPos = findPos(x);
            if (!isActive(currentPos))
                return false;

            array[currentPos].info = DELETED;
            return true;
        }

        // Get the value of a key in the hash table
        const int &getValue(const string &x) const
        {
            int pos = findPos(x); // Find the index of the key in the hash table
            return array[pos].value;
        }

        // Set the value of a key in the hash table
        void setValue(const string &x, const int &y)
        {
            int pos = findPos(x); // Find the index of the key in the hash table
            array[pos].value = y;
        }

        // Entry states for hash table slots
        enum EntryType
        {
            ACTIVE,
            EMPTY,
            DELETED
        };

        // Display the hash table
        void display()
        {
            cout << "(Taskid, Index in Heap Array)\n";
            for (const auto &entry : array)
            {
                if (entry.info == ACTIVE)
                    cout << "(" << entry.key << ", Index: " << entry.value << ")\n";
            }
            cout << endl;
        }

        // Debug display of the hash table
        void ddisplay()
        {
            for (size_t i = 0; i < array.size(); ++i)
            {
                cout << "Index " << i << ": ";

                if (array[i].info == EMPTY)
                    cout << "EMPTY\t-\t-";
                else if (array[i].info == DELETED)
                    cout << "DELETED\t" << array[i].key << "\t" << array[i].value;
                else
                    cout << "ACTIVE\t" << array[i].key << "\t" << array[i].value;

                cout << endl;
            }
        }

    private:

        /**
         * Structure for a hash table entry
         * 
         * Stores a key, value, and the state of the entry
         */
        struct HashEntry
        {
            string key;
            int value;
            EntryType info;

            HashEntry(const string &e = string{}, EntryType i = EMPTY)
                : key{e}, info{i}
            {
            }

            HashEntry(string &&e, EntryType i = EMPTY)
                : key{std::move(e)}, info{i}
            {
            }
        };

        // Hash table array
        vector<HashEntry> array;
        
        // Number of elements in the hash table
        int currentSize;

        // Check if a slot in the hash table is active
        bool isActive(int currentPos) const
        {
            return array[currentPos].info == ACTIVE;
        }

        // Find the position of a key in the hash table
        int findPos(const string &x) const
        {
            int offset = 1;
            int currentPos = myhash(x);

            while (array[currentPos].info != EMPTY &&
                   array[currentPos].key != x)
            {
                currentPos += offset; // Compute ith probe
                offset += 2;
                if (currentPos >= array.size())
                    currentPos -= array.size();
            }

            return currentPos;
        }

        // Rehash the hash table
        void rehash()
        {
            vector<HashEntry> oldArray = array;

            // Create new double-sized, empty table
            array.resize(nextPrime(2 * oldArray.size()));
            for (auto &entry : array)
                entry.info = EMPTY;

            // Copy table over
            currentSize = 0;
            for (auto &entry : oldArray)
            {
                if (entry.info == ACTIVE)
                {
                    insert(std::move(entry.key), std::move(entry.value));
                }
            }
        }

        // Hash function
        size_t myhash(const string &x) const
        {
            static hash<string> hf;
            return hf(x) % array.size();
        }
    };

    /**
     * Heap class
     * 
     * Implements a binary heap
     */
    class Heap
    {

    public:
        
        // Constructor
        explicit Heap(HMap &hmapref, int capacity = 11) : hmap(hmapref), array(capacity), currentSize{0}
        {

            buildHeap();
        }

        // Constructor with a vector of HeapNodes
        explicit Heap(HMap &hmapref, const vector<HeapNode> &items) : hmap(hmapref), array(static_cast<int>(items.size()) + 10), currentSize{static_cast<int>(items.size())}
        {
            for (int i{0}; i < items.size(); ++i)
            {
                array[i + 1] = items[i];
            }
            buildHeap();
        }

        // Check if the heap is empty
        bool isEmpty() const
        {
            return currentSize == 0;
        }

        // Find the minimum element in the heap
        const HeapNode &findMin() const
        {
            return array[1];
        }

        // Insert a new element into the heap
        int insert(const HeapNode &x)
        {
            if (currentSize + 1 == array.size())
                array.resize(array.size() * 2);

            // percolate up
            int hole = ++currentSize;
            HeapNode copy = x;

            array[0] = std::move(copy);

            // percolate up and update hashmanp
            for (; x.priority < array[hole / 2].priority; hole /= 2)
            {
                array[hole] = std::move(array[hole / 2]);
                //cout << "Moving " << array[hole].taskid << " to index " << hole << endl;
                hmap.setValue(array[hole].taskid, hole);
            }
            array[hole] = std::move(array[0]);
            //cout << "Inserting " << x.taskid << " at index " << hole << endl;
            hmap.setValue(x.taskid, hole);

            return hole;
        }

        // Delete the minimum element from the heap
        void deleteMin()
        {
            if (isEmpty())
            {
                cerr << "Cannot delete min -> heap is empty" << endl;
                return;
            }

            array[1] = std::move(array[currentSize--]);
            percolateDown(1);
        }

       
        // Clear the heap
        void clear()
        {
            // Simply reset the current size
            currentSize = 0;

            // Optional: If you want to reset the values in the array
            // (not strictly necessary since currentSize controls what's "in" the heap)
            for (int i = 1; i <= array.size(); ++i)
            {
                // You might want to update your hashmap too
                if (i < array.size())
                {
                    hmap.remove(array[i].taskid); // Assuming you have a remove function in HMap
                }
            }
        }

        // Display the heap
        void display() const
        {
            cout << "Heap (Array Representation): \n";
            cout << "[Priority, Taskid]\n";
            for (int i = 1; i <= currentSize; ++i)
            {
                cout << "[" << array[i].priority << ", " << array[i].taskid << "] \n";
            }
            cout << endl;
        }

        // Debug display of the heap
        void ddisplay() const
        {
            cout << "Debug Display. CurrentSize: " << currentSize << endl;

            for (int i = 0; i < array.size(); i++)
            {
                cout << "Index " << i << ": [" << array[i].priority << ", " << array[i].taskid << "] \n";
            }
        }

        // Set the priority of an element in the heap
        void setPriority(int index, int p)
        {
            array[index].priority = p;

            if (index > 1 && array[index].priority < array[index / 2].priority)
            {
                percolateUp(index);
            }
            else
                percolateDown(index);
        }

    private:
        int currentSize; // number of elements in the heap
        
        // Array to store the heap
        vector<HeapNode> array;

        // Reference to the hash map
        HMap &hmap;

        // Build the heap
        void buildHeap()
        {
            for (int i = currentSize / 2; i > 0; --i)
            {
                percolateDown(i);
            }
        }

        // Percolate up
        void percolateUp(int hole)
        {
            HeapNode tmp = std::move(array[hole]);

            for (; hole > 1 && tmp.priority < array[hole / 2].priority; hole /= 2)
            {
                array[hole] = std::move(array[hole / 2]);
                hmap.setValue(array[hole].taskid, hole);
            }
            array[hole] = std::move(tmp);
            hmap.setValue(array[hole].taskid, hole);
        }

        // Percolate down
        void percolateDown(int hole)
        {
            int child;
            HeapNode tmp = std::move(array[hole]);

            for (; hole * 2 <= currentSize; hole = child)
            {
                child = hole * 2;
                if (child != currentSize && array[child + 1].priority < array[child].priority)
                {
                    ++child;
                }
                if (array[child].priority < tmp.priority)
                {
                    array[hole] = std::move(array[child]);
                    hmap.setValue(array[hole].taskid, hole);
                }
                else
                {
                    break;
                }
            }

            array[hole] = std::move(tmp);
            hmap.setValue(array[hole].taskid, hole);
        }
    };

    // Heap and Hash Map instances
    Heap heap;
    HMap hmap;
};
