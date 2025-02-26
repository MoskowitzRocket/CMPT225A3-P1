#include "IndPQ.h"
#include <iostream>
#include "Heapv2.h"

int main (int argc, char *argv[]) {
  
  // std::cout << "TEST" << std::endl;

  // std::vector<int> b = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};

  // Heap<int> h(b);

  // h.display();

  // h.ddisplay();

  // h.insert(5);

  // h.display();

  // h.ddisplay();

  vector<HeapNode> tasks = {};

  Heap h(tasks);

  h.display();



  h.ddisplay();

  h.insert({6, "Task A"});
  h.display();
  h.ddisplay();

  h.insert({3, "Task B"});
  h.display();
  h.ddisplay();

  h.insert({2, "Task C"});
  h.display();
  h.ddisplay();

  h.insert({5, "Task D"});
  h.display();
  h.ddisplay();
  
  h.insert({1, "Task E"});
  h.display();
  h.ddisplay();
  
  h.makeEmpty();

  h.display();
  h.ddisplay();

  for (int i = 1; i < 12; i++){
    h.insert({i,to_string(i)});
  }
  h.ddisplay();

  h.deleteMin();

  h.ddisplay();

  

  return 0;
}
