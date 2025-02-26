#include "IndPQ.h"
#include <iostream>
#include "Heapv2.h"
#include "HMap.h"

int main () {
  
  // std::cout << "TEST" << std::endl;

  // std::vector<int> b = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};

  // Heap<int> h(b);

  // h.display();

  // h.ddisplay();

  // h.insert(5);

  // h.display();

  // h.ddisplay();

  // vector<HeapNode> tasks = {};

  // Heap h(tasks);

  // h.display();



  // h.ddisplay();

  // h.insert({6, "Task A"});
  // h.display();
  // h.ddisplay();

  // h.insert({3, "Task B"});
  // h.display();
  // h.ddisplay();

  // h.insert({2, "Task C"});
  // h.display();
  // h.ddisplay();

  // h.insert({5, "Task D"});
  // h.display();
  // h.ddisplay();
  
  // h.insert({1, "Task E"});
  // h.display();
  // h.ddisplay();
  
  // h.makeEmpty();

  // h.display();
  // h.ddisplay();

  // for (int i = 1; i < 12; i++){
  //   h.insert({i,to_string(i)});
  // }
  // h.ddisplay();

  // h.deleteMin();

  // h.ddisplay();

  // Heap h1;

  // h1.insert({5,"Task One"});
  // h1.insert({8,"Task Two"});
  // h1.insert({2,"Task Thee"});
  // h1.insert({54,"Task Four"});
  // h1.insert({3,"Task Five"});
  // h1.ddisplay();

  // HMap hashTable(11);

  // // Insert key-value pairs
  // cout << "Inserting key-value pairs:\n";
  // hashTable.insert("Alice", 25);
  // hashTable.insert("Bob", 30);
  // hashTable.insert("Charlie", 35);
  // hashTable.insert("David", 40);

  // // Display the table
  // cout << "\nHash Table after insertions:" << endl;
  // hashTable.display();
  // hashTable.ddisplay();

  // // Test retrieval
  // cout << "\nRetrieving values:" << endl;
  // cout << "Alice: " << hashTable.getValue("Alice") << endl;
  // cout << "Bob: " << hashTable.getValue("Bob") << endl;
  // cout << "Charlie: " << hashTable.getValue("Charlie") << endl;

  // // Test deletion
  // cout << "\nRemoving 'Bob' from the hash table." << endl;
  // hashTable.remove("Bob");
  
  // // Display the table after deletion
  // cout << "\nHash Table after removing 'Bob':" << endl;
  // hashTable.display();
  // hashTable.ddisplay();

  // // Check if removed key is still accessible
  // cout << "\nChecking if 'Bob' is still in the table: ";
  // if (hashTable.contains("Bob")) {
  //     cout << "Found with value: " << hashTable.getValue("Bob") << endl;
  // } else {
  //     cout << "Not found." << endl;
  // }



  IndPQ ipq;

  ipq.ddisplay();

  cout <<"\n\n\nBBBBB\b\b";

  ipq.insert("Task A", 8);
  ipq.insert("Task B", 2);
  ipq.insert("Task C", 3);
  ipq.insert("Task D", 6);
  ipq.insert("Task E", 1);


  ipq.ddisplay();

  cout << "\n\nDELETINGMIN\n\n";
  ipq.deleteMin();

  //ipq.insert("Task F", 1);

  ipq.ddisplay();

  cout << "\n\n\tHEAPTESTTIME\n\n";
  Heap h;

  
  h.insert({8,"Task A"});
  h.insert({2,"Task B"});
  h.insert({3,"Task C"});
  h.insert({1,"Task D"});
  h.insert({6,"Task E"});

  h.ddisplay();
  h.deleteMin();
  h.ddisplay();
  h.deleteMin();
  h.ddisplay();
  

  return 0;
}
