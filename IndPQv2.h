#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int nextPrime(int n);

class IndPQv2 {
public:
    // Constructor creating an empty IndPQ.
    IndPQv2() : heap(), hmap(), currentSize(0) {}
    
    // Insert taskid with priority p.
    void insert(const std::string &taskid, int p) {
        HeapNode newNode(p, taskid);
        int position = heap.insert(newNode);
        hmap.insert(taskid, position);
        currentSize++;
    }
    
    // Remove and return (a reference to) a task ID with smallest priority.
    std::string &deleteMin() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        HeapNode minNode = heap.findMin();
        minTaskBuffer = minNode.taskid; // Store before deletion
        
        // Update the HMap as nodes move in the heap
        int oldPosition = 1; // Min is always at position 1
        hmap.remove(minTaskBuffer);
        
        // Delete min from heap - this will move nodes and return the new position of the moved node
        string movedTaskId = heap.deleteMin();
        
        // If the queue is not empty after deletion and a node was moved
        if (!isEmpty() && !movedTaskId.empty()) {
            // Update the position of the moved task in the map
            hmap.insert(movedTaskId, 1);
        }
        
        currentSize--;
        return minTaskBuffer;
    }
    
    // Return (a reference to) a task ID with the smallest priority.
    std::string &getMin() {
        if (isEmpty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        
        HeapNode minNode = heap.findMin();
        minTaskBuffer = minNode.taskid;
        return minTaskBuffer;
    }
    
    // Change the priority for taskid to p.
    void updatePriority(const std::string &taskid, int p) {
        // Use the map to find the position in the heap
        if (!hmap.contains(taskid)) {
            throw std::runtime_error("Task ID not found in priority queue");
        }
        
        int position = hmap.getValue(taskid);
        int newPosition = heap.updatePriority(position, p);
        
        // Update the map with the new position if it changed
        if (position != newPosition) {
            hmap.insert(taskid, newPosition);
        }
    }
    
    // Remove taskid from the PQ
    void remove(const std::string &tid) {
        if (!hmap.contains(tid)) {
            return; // Task not found, nothing to do
        }
        
        int position = hmap.getValue(tid);
        string movedTaskId = heap.removeAt(position);
        
        // Remove the task from the map
        hmap.remove(tid);
        
        // If a task was moved during the removal, update its position in the map
        if (!movedTaskId.empty() && movedTaskId != tid) {
            hmap.insert(movedTaskId, position);
        }
        
        currentSize--;
    }
    
    // Return true if the PQ is empty, otherwise false.
    bool isEmpty() {
        return currentSize == 0;
    }
    
    // Return the number of tasks in the PQ.
    int size() {
        return currentSize;
    }
    
    // Remove all tasks from the PQ.
    void clear() {
        heap.makeEmpty();
        hmap.makeEmpty();
        currentSize = 0;
    }
    
    // Print out the queue contents.
    void display() {
        cout << "Priority Queue Contents:" << endl;
        heap.display();
    }
    
    // Print out a representation of the data structures.
    void ddisplay() {
        cout << "Detailed Display of IndPQ:" << endl;
        cout << "Current Size: " << currentSize << endl;
        cout << "Heap Structure:" << endl;
        heap.ddisplay();
        cout << "Hash Map Structure:" << endl;
        hmap.ddisplay();
    }
    
private:
    std::string minTaskBuffer;
    int currentSize;
    
    struct HeapNode {
        int priority;
        string taskid;
        
        HeapNode() : priority(0), taskid("") {} // Default constructor
        HeapNode(int p, string id) : priority(p), taskid(id) {}
    };
    
    class Heap {
    public:
        explicit Heap(int capacity = 11) : array(capacity), currentSize{0} {
            // Reserve space for 0th index which is not used (except temporarily)
            array[0] = HeapNode();
        }
        
        bool isEmpty() const {
            return currentSize == 0;
        }
        
        const HeapNode &findMin() const {
            if (isEmpty()) {
                throw std::runtime_error("Heap is empty");
            }
            return array[1];
        }
        
        // Modified to return the position where the node was inserted
        int insert(const HeapNode &x) {
            if (currentSize + 1 >= array.size())
                array.resize(array.size() * 2);
            
            // Percolate up
            int hole = ++currentSize;
            HeapNode copy = x;
            array[0] = copy; // Temporary storage
            
            for (; hole > 1 && copy.priority < array[hole / 2].priority; hole /= 2) {
                array[hole] = array[hole / 2];
            }
            
            array[hole] = copy;
            return hole; // Return the final position
        }
        
        // Modified to return the new position of the updated node
        int updatePriority(int index, int p) {
            if (index <= 0 || index > currentSize) {
                throw std::runtime_error("Invalid index in updatePriority");
            }
            
            int oldPriority = array[index].priority;
            array[index].priority = p;
            
            int newPosition;
            if (p < oldPriority) {
                newPosition = percolateUp(index);
            } else if (p > oldPriority) {
                newPosition = percolateDown(index);
            } else {
                newPosition = index; // Priority didn't change
            }
            
            return newPosition;
        }
        
        // Modified to return the task ID of the node that was moved to position 1
        string deleteMin() {
            if (isEmpty()) {
                throw std::runtime_error("Heap is empty");
            }
            
            string movedTaskId = "";
            if (currentSize > 1) {
                movedTaskId = array[currentSize].taskid;
            }
            
            array[1] = array[currentSize--];
            percolateDown(1);
            
            return movedTaskId;
        }
        
        // New method to remove a node at a specific position
        string removeAt(int index) {
            if (index <= 0 || index > currentSize) {
                throw std::runtime_error("Invalid index in removeAt");
            }
            
            string movedTaskId = "";
            if (index != currentSize) {
                movedTaskId = array[currentSize].taskid;
                array[index] = array[currentSize];
                
                // Determine whether to percolate up or down
                if (index > 1 && array[index].priority < array[index / 2].priority) {
                    percolateUp(index);
                } else {
                    percolateDown(index);
                }
            }
            
            currentSize--;
            return movedTaskId;
        }
        
        void makeEmpty() {
            currentSize = 0;
        }
        
        void display() const {
            cout << "Heap (priority, taskid): ";
            for (int i = 1; i <= currentSize; ++i) {
                cout << "(" << array[i].priority << ", " << array[i].taskid << ") ";
            }
            cout << endl;
        }
        
        void ddisplay() const {
            cout << "Debug Display. CurrentSize: " << currentSize << endl;
            for (int i = 0; i <= currentSize; i++) {
                cout << "Index " << i << ": [" << array[i].priority << ", " << array[i].taskid << "]" << endl;
            }
        }
        
    private:
        int currentSize; // Number of elements in the heap
        vector<HeapNode> array;
        
        // Modified to return the final position after percolation
        int percolateUp(int hole) {
            HeapNode tmp = array[hole];
            
            for (; hole > 1 && tmp.priority < array[hole / 2].priority; hole /= 2) {
                array[hole] = array[hole / 2];
            }
            
            array[hole] = tmp;
            return hole;
        }
        
        // Modified to return the final position after percolation
        int percolateDown(int hole) {
            int child;
            HeapNode tmp = array[hole];
            
            for (; hole * 2 <= currentSize; hole = child) {
                child = hole * 2;
                
                if (child != currentSize && array[child + 1].priority < array[child].priority) {
                    ++child;
                }
                
                if (array[child].priority < tmp.priority) {
                    array[hole] = array[child];
                } else {
                    break;
                }
            }
            
            array[hole] = tmp;
            return hole;
        }
    };
    
    class HMap {
    public:
        explicit HMap(int size = 11) : array(nextPrime(size)) {
            makeEmpty();
        }
        
        bool contains(const string &x) const {
            return isActive(findPos(x));
        }
        
        void makeEmpty() {
            currentSize = 0;
            for (auto &entry : array)
                entry.info = EMPTY;
        }
        
        int getSize() const {
            return currentSize;
        }
        
        bool insert(const string &x, const int &y) {
            // Insert x as active
            int currentPos = findPos(x);
            
            if (isActive(currentPos)) {
                // Update existing value
                array[currentPos].value = y;
                return true;
            }
            
            if (array[currentPos].info != DELETED)
                ++currentSize;
                
            array[currentPos].key = x;
            array[currentPos].value = y;
            array[currentPos].info = ACTIVE;
            
            // Rehash if load factor gets too high
            if (currentSize > array.size() / 2)
                rehash();
                
            return true;
        }
        
        bool remove(const string &x) {
            int currentPos = findPos(x);
            if (!isActive(currentPos))
                return false;
                
            array[currentPos].info = DELETED;
            return true;
        }
        
        const int &getValue(const string &x) const {
            int pos = findPos(x); // Find the index of the key in the hash table
            
            if (!isActive(pos)) {
                throw std::runtime_error("Key not found in hash map");
            }
            
            return array[pos].value;
        }
        
        enum EntryType {
            ACTIVE,
            EMPTY,
            DELETED
        };
        
        void display() {
            for (const auto &entry : array) {
                if (entry.info == ACTIVE)
                    cout << "(" << entry.key << "," << entry.value << ") ";
            }
            cout << endl;
        }
        
        void ddisplay() {
            for (size_t i = 0; i < array.size(); ++i) {
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
        struct HashEntry {
            string key;
            int value;
            EntryType info;
            
            HashEntry(const string &e = string{}, EntryType i = EMPTY)
                : key{e}, value{0}, info{i} {}
        };
        
        vector<HashEntry> array;
        int currentSize;
        
        bool isActive(int currentPos) const {
            return array[currentPos].info == ACTIVE;
        }
        
        int findPos(const string &x) const {
            int offset = 1;
            int currentPos = myhash(x);
            
            while (array[currentPos].info != EMPTY &&
                   array[currentPos].key != x) {
                currentPos += offset; // Compute ith probe
                offset += 2;
                if (currentPos >= array.size())
                    currentPos -= array.size();
            }
            
            return currentPos;
        }
        
        void rehash() {
            vector<HashEntry> oldArray = array;
            
            // Create new double-sized, empty table
            array.resize(nextPrime(2 * oldArray.size()));
            for (auto &entry : array)
                entry.info = EMPTY;
                
            // Copy table over
            currentSize = 0;
            for (auto &entry : oldArray) {
                if (entry.info == ACTIVE) {
                    insert(entry.key, entry.value);
                }
            }
        }
        
        size_t myhash(const string &x) const {
            static hash<string> hf;
            return hf(x) % array.size();
        }
    };
    
    Heap heap;
    HMap hmap;
};