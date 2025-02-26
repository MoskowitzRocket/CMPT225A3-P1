#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct HeapNode {
    unsigned int priority;
    string taskid;

    HeapNode() : priority(0), taskid("") {}  // Default constructor
    HeapNode(unsigned int p, const string& id) : priority(p), taskid(id) {}
};


class Heap {

        

    public:
        explicit Heap( int capacity = 10) : array(capacity), currentSize{0} {
            
            buildHeap();
        }
        explicit Heap(const vector<HeapNode> & items) : array(items.size() + 10), currentSize{items.size()} {
            for( int i{0}; i < items.size(); ++i) {
                array[ i + 1 ] = items[ i ];
            }
            buildHeap();
        }

        bool isEmpty() const {
            return currentSize == 0;
        }

        const HeapNode & findMin( ) const {
            return array[1];
        }

        void insert( const HeapNode & x) {
            if (currentSize + 1 == array.size())
                array.resize(array.size() * 2);

            //percolate up
            int hole = ++currentSize;
            HeapNode copy = x;

            array[ 0 ] = std::move( copy );
            for( ; x.priority < array[hole / 2].priority; hole /= 2) {
                array[ hole ] = std::move( array[ hole / 2 ] );
            }
            array[ hole ] = std::move( array[ 0 ] );
        }

        void deleteMin() {
            if( isEmpty( ) )
            {
                cerr << "Cannot delete min -> heap is empty" << endl;
                return;
            }

            array[ 1 ] = std::move( array[ currentSize-- ] );
            percolateDown( 1 );
        }

        void deleteMin(HeapNode & minItem) {
            if( isEmpty( ) )
            {
                cerr << "Cannot delete min -> heap is empty" << endl;
                return;
            }
            minItem = std::move( array[ 1 ] );
            array[ 1 ] = std::move( array[ currentSize-- ] );
            percolateDown( 1 );
        }
        void makeEmpty(){
            currentSize = 0;
        }

        void display() const {
            cout << "Heap (Array Representation): ";
            for (int i = 1; i <= currentSize; ++i) {
                cout << "[" << array[i].priority << ", " << array[i].taskid << "] \n";
            }
            cout << endl;
        }
    
        void ddisplay() const {
            cout << "Debug Display. CurrentSize: " << currentSize << endl;
            
            for (int i = 0; i < array.size(); i++) {
                cout << "Index " << i << ": [" << array[i].priority << ", " << array[i].taskid << "] \n";
            }
        }


    private:
        
        int currentSize; //number of elements in the heap
        vector<HeapNode> array;
        
        void buildHeap() {
            for( int i = currentSize / 2; i > 0; --i) {
                percolateDown(i);
            }
        }

        void percolateDown(int hole) {
            int child;
            HeapNode tmp = std::move( array[ hole ] );

            for ( ; hole * 2 <= currentSize; hole = child){
                child = hole * 2;
                if( child!=currentSize && array[ child + 1 ].priority < array[ child ].priority) {
                    ++child;
                }
                if( array[ child ].priority < tmp.priority ) {
                    array[ hole ] = std::move( array[ child ] );
                } else {
                    break;
                }
            }

            array[ hole ] = std::move( tmp );
        }

};
