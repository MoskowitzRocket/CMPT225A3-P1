#include <iostream>
#include <string>
#include "IndPQ.h" // Assuming your class is in this header file

using namespace std;

// Function to print a divider for better readability
void printDivider(const string& title) {
    cout << "\n==== " << title << " ====\n";
}



int main() {
    //testFunc();

	IndPQ ipq;
    
    //Need to Test
    /*
        Insert
        deleteMin
        getMin
        updatePriority
        remove
        isEmpty
        size
        clear
        display
        ddisplay
    */
    printDivider("Inserting Tasks");
    ipq.insert("Task1",10);
    ipq.insert("Task2",2);
    ipq.insert("Task3",5);
    ipq.insert("Task4",14);
    ipq.insert("Task5",6);
    ipq.insert("Task6",7);
    ipq.insert("Task7",94);
    
    printDivider("DDisplay after initial insertion");
    ipq.ddisplay();

    printDivider("Updating Task7 to have priority 1");
    ipq.updatePriority("Task7",1);
    ipq.display();

    printDivider("Getting Minimum");
    cout << ipq.getMin() << endl;

    printDivider("Deleteing Minimum");
    cout << ipq.deleteMin() << endl;
    ipq.display();

    printDivider("Removing Task3");
    ipq.remove("Task3");
    ipq.display();

    printDivider("Testing Public Info Functions");
    cout << "Is ipq empty: " << ipq.isEmpty() << endl;
    cout << "Size: " << ipq.size() << endl;
 
    printDivider("Clearing IPQ");
    ipq.clear();
    ipq.display();
    printDivider("Debug Display after clear");
    ipq.ddisplay();

    ipq.insert("Task A", 5);
    ipq.insert("Task B", 3);
    ipq.insert("Task C", 2);

    ipq.display();

    printDivider("Decreasing priority of Task C");
    ipq.updatePriority("Task C", 7);
    ipq.ddisplay();
    printDivider("Increasing Priority of of Task A");
    ipq.updatePriority("Task A", 1);
    ipq.ddisplay();
    
  
}
