#include "IndPQ.h"
#include "IndPQv2.h"
#include <iostream>
#include "Heapv2.h"
#include "HMap.h"


int main () {
  
  // IndPQ ipq;
  IndPQv2 ipq;

  ipq.insert("Task A", 6);
  ipq.insert("Task B", 3);
  ipq.insert("Task C", 1);

  ipq.ddisplay();

  ipq.insert("Task D", 5);
  ipq.insert("Task E", 11);
  ipq.insert("Task F", 7);

  ipq.ddisplay();

  


  return 0;
}
