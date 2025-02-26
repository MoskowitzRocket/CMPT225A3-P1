#include "IndPQ.h"
#include <iostream>
#include "Heap.h"

int main (int argc, char *argv[]) {
  
  std::cout << "TEST" << std::endl;

  std::vector<int> b = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};

  Heap<int> h(b);

  h.display();

  h.ddisplay();

  h.insert(5);

  h.display();

  h.ddisplay();

  
  
  

  return 0;
}
