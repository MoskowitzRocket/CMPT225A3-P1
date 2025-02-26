#include <vector>

#include <iostream>

template <typename Comparable>
class Heap {

    public:
        explicit Heap( int capacity = 100);
        explicit Heap( const std::vector<Comparable> & items ) : array( items.size( ) + 10 ), currentSize{ items.size( ) } {
            for(int i =0; i < items.size(); ++i) {
                array[i + 1] = items[i];
            }
            buildHeap();
        }

        bool isEmpty( ) const;
        const Comparable & findMin( ) const;

        void insert( const Comparable & x ) {
            if (currentSize == array.size() - 1) {
                array.resize(array.size() * 2);

            }
            //percolate up
            int hole = ++currentSize;
            Comparable copy = x;

            array[0] = std::move( copy );
            for( ; x < array[hole/2]; hole /=2){
                array[hole] = std::move(array[hole/2]);
            }
            array[hole] = std::move(array[0]);
        }
        
        void deleteMin( ) {
            if( isEmpty()) {
                std::cerr << "Cant delete min -> heap is empty" << std::endl;
                return; 
            }

            array[1] = std::move(array[currentSize--]);
            percolateDown( 1 );
        }
        void deleteMin(Comparable & minItem) {
            if( isEmpty()) {
                std::cerr << "Cant delete min -> heap is empty" << std::endl;
                return; 
            }

            minItem = std::move( array[ 1 ] );
            array[ 1 ] = std::move( array[ currentSize-- ] );
            percolateDown( 1 );
        }
        void makeEmpty( );

        void display() const {
            for(int i = 1; i <= currentSize; ++i) {
                std::cout << array[i] << " ";
            }
            std::cout << std::endl;
        }

        void ddisplay() const {
            std::cout << "Heap structure (entire array):" << std::endl;
            for(int i = 0; i < array.size(); ++i) {
                std::cout << "Index " << i << ": " << array[i] << std::endl;
            }
        }

    private:
        int currentSize;
        std::vector<Comparable> array; //Heap array

        void buildHeap( ) {
            for (int i = currentSize / 2; i > 0; --i)
            {
                percolateDown(i);
            }
        }

        void percolateDown( int hole ) {
            int child;
            Comparable temp = std::move(array[hole]);

            for(; hole * 2 <= currentSize; hole = child) 
            {
                child = hole * 2;
                if(child != currentSize && array[child + 1] < array[child]) {
                    ++child;
                }
                if( array[ child ] < temp )
                    array[ hole ] = std::move( array[ child ] );
                else
                    break;
            }
            array[hole] = std::move(temp);
        }

};