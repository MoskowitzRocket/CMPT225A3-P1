#include <stdexcept>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int nextPrime(int n);

class IndPQ
{

public:
    IndPQ();                                               // —-> constructor creating an empty IndPQ.
    void insert(const std::string &taskid, int p);         // --> Insert taskid with priority p.
    std::string &deleteMin();                              //  --> Remove and return (a reference to) a task ID with smallest priority.
    std::string &getMin();                                 //  --> Return (a reference to) a task ID with the smallest priority.
    void updatePriority(const std::string &taskid, int p); //  --> change the priority for taskid to p.
    void remove(const std::string &tid);                   // --> remove taskid from the PQ
    bool isEmpty();                                        // --> Return true if the PQ is empty, otherwise false.
    int size();                                            //  --> Return the number of tasks in the PQ.
    void clear();                                          //  --> Remove all tasks from the PQ.
    void display();                                        // —-> prints out the queue contents.
    void ddisplay();                                       // —-> prints out a representation of the data structures.
private:
    struct HeapNode
    {
        unsigned int priority;
        string taskid;
        HeapNode() : priority(0), taskid("") {} // Default constructor
        HeapNode(unsigned int p, string &id) : priority(p), taskid(id) {}
    };

    class Heap
    {

    public:
        // explicit Heap(int capacity = 100);
        explicit Heap(const vector<HeapNode> &items) : array(items.size() + 10), currentSize{items.size()}
        {
            for (int i{0}; i < items.size(); ++i)
            {
                array[i + 1] = items[i];
            }
            buildHeap();
        }

        bool isEmpty() const
        {
            return currentSize == 0;
        }

        const HeapNode &findMin() const
        {
            return array[1];
        }

        void insert(const HeapNode &x)
        {
            if (currentSize == array.size())
                array.resize(array.size() * 2);

            // percolate up
            int hole = ++currentSize;
            HeapNode copy = x;

            array[0] = std::move(copy);
            for (; x.priority < array[hole / 2].priority; hole /= 2)
            {
                array[hole] = std::move(array[hole / 2]);
            }
            array[hole] = std::move(array[0]);
        }

        void deleteMin()
        {
            if (isEmpty())
            {
                cerr << "Cannot delete min -> heap is empty" << endl;
            }

            array[1] = std::move(array[currentSize--]);
            percolateDown(1);
        }

        void deleteMin(HeapNode &minItem)
        {
            if (isEmpty())
            {
                cerr << "Cannot delete min -> heap is empty" << endl;
            }
            minItem = std::move(array[1]);
            array[1] = std::move(array[currentSize--]);
            percolateDown(1);
        }
        void makeEmpty()
        {
            currentSize = 0;
        }

        void display() const
        {
            cout << "Heap (Array Representation): ";
            for (int i = 1; i <= currentSize; ++i)
            {
                cout << "[" << array[i].priority << ", " << array[i].taskid << "] \n";
            }
            cout << endl;
        }

        void ddisplay() const
        {
            cout << "Debug Display. CurrentSize: " << currentSize << endl;

            for (int i = 0; i < array.size(); i++)
            {
                cout << "Index " << i << ": [" << array[i].priority << ", " << array[i].taskid << "] \n";
            }
        }

    private:
        int currentSize; // number of elements in the heap
        vector<HeapNode> array;

        void buildHeap()
        {
            for (int i = currentSize / 2; i > 0; --i)
            {
                percolateDown(i);
            }
        }

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
                if (array[hole].priority < tmp.priority)
                {
                    array[hole] = std::move(array[child]);
                }
                else
                {
                    break;
                }
            }

            array[hole] = std::move(tmp);
        }
    };

    //template<typename string, typename int>
    class HMap
    {
    public:
        explicit HMap(int size = 11) : array(nextPrime(size))
        {
            makeEmpty();
        }

        bool contains(const string &x) const
        {
            return isActive(findPos(x));
        }

        void makeEmpty()
        {
            currentSize = 0;
            for (auto &entry : array)
                entry.info = EMPTY;
        }

        int getSize() const
        {
            return currentSize;
        }

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

        bool insert(string &&x)
        {
            // Insert x as active
            int currentPos = findPos(x);
            if (isActive(currentPos))
                return false;

            if (array[currentPos].info != DELETED)
                ++currentSize;

            array[currentPos] = std::move(x);
            array[currentPos].info = ACTIVE;

            // Rehash; see Section 5.5
            if (currentSize > array.size() / 2)
                rehash();

            return true;
        }

        bool remove(const string &x)
        {
            int currentPos = findPos(x);
            if (!isActive(currentPos))
                return false;

            array[currentPos].info = DELETED;
            return true;
        }

        const int &getValue(const string &x) const
        {
            int pos = findPos(x); // Find the index of the key in the hash table
            return array[pos].value;
        }

        enum EntryType
        {
            ACTIVE,
            EMPTY,
            DELETED
        };

        void display()
        {
            for (const auto &entry : array)
            {
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
        struct HashEntry
        {
            string key;
            int value;
            EntryType info;

            HashEntry(const string &e = string{}, EntryType i = EMPTY)
                : key{e}, info{i} {}

            HashEntry(string &&e, EntryType i = EMPTY)
                : key{std::move(e)}, info{i} {}
        };

        vector<HashEntry> array;
        int currentSize;

        bool isActive(int currentPos) const
        {
            return array[currentPos].info == ACTIVE;
        }

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
                if (entry.info == ACTIVE)
                    insert(std::move(entry.key));
        }

        size_t myhash(const string &x) const
        {
            static hash<string> hf;
            return hf(x) % array.size();
        }
    };

    Heap heap;
    HMap hmap;
};
