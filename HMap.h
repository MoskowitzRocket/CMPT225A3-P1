#include <string>
#include <iostream>
#include <vector>

using namespace std;

int nextPrime(int n);

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