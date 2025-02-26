#include <string>
#include <iostream>
#include <vector>

using namespace std;

int nextPrime(int n );

class IndPQ {

  public:


    IndPQ(); //—-> constructor creating an empty IndPQ.
    void insert( const std::string & taskid, int p );// --> Insert taskid with priority p.
    std::string & deleteMin();//  --> Remove and return (a reference to) a task ID with smallest priority.
    std::string & getMin(); //  --> Return (a reference to) a task ID with the smallest priority.
    void updatePriority( const std::string & taskid, int p );//  --> change the priority for taskid to p.
    void remove( const std::string & tid );// --> remove taskid from the PQ
    bool isEmpty( );// --> Return true if the PQ is empty, otherwise false.
    int size();//  --> Return the number of tasks in the PQ.
    void clear( );//  --> Remove all tasks from the PQ.
    void display( );// —-> prints out the queue contents.
    void ddisplay( );// —-> prints out a representation of the data structures.
  private:

    class Heap {

    };

    template <typename kt, typename vt>
    class HMap
    {
    public:
        explicit HMap(int size = 11) : array(nextPrime(size))
        {
            makeEmpty();
        }

        bool contains(const kt &x) const
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

        bool insert(const kt &x, const vt &y)
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

        bool insert(kt &&x)
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

        bool remove(const kt &x)
        {
            int currentPos = findPos(x);
            if (!isActive(currentPos))
                return false;

            array[currentPos].info = DELETED;
            return true;
        }

        const vt &getValue(const kt &x) const
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

        void ddisplay()
        {
            for (size_t i = 0; i < array.size(); ++i)
            {
                cout << "Index " << i << ": ";
                if (array[i].info == EMPTY)
                    cout << "EMPTY\t-";
                else if (array[i].info == DELETED)
                    cout << "DELETED\t-";
                else
                    cout << array[i].key << "\t" << array[i].value;
                cout << endl;
            }
        }

    private:
        struct HashEntry
        {
            kt key;
            vt value;
            EntryType info;

            HashEntry(const kt &e = kt{}, EntryType i = EMPTY)
                : key{e}, info{i} {}

            HashEntry(kt &&e, EntryType i = EMPTY)
                : key{std::move(e)}, info{i} {}
        };

        vector<HashEntry> array;
        int currentSize;

        bool isActive(int currentPos) const
        {
            return array[currentPos].info == ACTIVE;
        }

        int findPos(const kt &x) const
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

        size_t myhash(const kt &x) const
        {
            static hash<kt> hf;
            return hf(x) % array.size();
        }
    };


};
