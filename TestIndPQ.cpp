#include <iostream>
#include <string>
#include "IndPQ.h" // Assuming your class is in this header file

using namespace std;

// Function to print a divider for better readability
void printDivider(const string& title) {
    cout << "\n==== " << title << " ====\n";
}

void testFunc();

int main() {
    //testFunc();

	IndPQ ipq;
	// ipq.insert("saffat", 30);
	// ipq.insert("bryce", 20);
	// ipq.insert("nathan", 10);
	// ipq.insert("ethan", 15);
	// ipq.insert("ryan", 25);
	// ipq.insert("henry", 5);
	// ipq.insert("justin",23);
	// ipq.insert("kale", 35);
	// ipq.insert("alasdair", 18);


	// ipq.display();
	// ipq.ddisplay();

	// ipq.remove("henry");
	// ipq.display();
	// ipq.ddisplay();

	// ipq.clear();
	// ipq.display();
	// ipq.ddisplay();

	// ipq.insert("saffat", 30);
	// ipq.insert("bryce", 20);

	// ipq.display();
	// ipq.ddisplay();

	ipq.insert("saffat", 30);
	ipq.insert("bryce", 20);
	ipq.insert("nathan", 10);
	ipq.ddisplay();


    return 0;
}


void testFunc()
{
	// Create a new Indexed Priority Queue
    IndPQ pq;
    
    printDivider("Initial State");
    cout << "Is empty: " << (pq.isEmpty() ? "Yes" : "No") << endl;
    cout << "Size: " << pq.size() << endl;
    
    // Insert the initial tasks with priorities
    printDivider("Inserting Initial Tasks");
    pq.insert("saffat", 30);
    cout << "Inserted 'saffat' with priority 30" << endl;
    
    pq.insert("bryce", 20);
    cout << "Inserted 'bryce' with priority 20" << endl;
    
    pq.insert("nathan", 10);
    cout << "Inserted 'nathan' with priority 10" << endl;
    
    // Display the current state
    printDivider("After Initial Insertions");
    cout << "Is empty: " << (pq.isEmpty() ? "Yes" : "No") << endl;
    cout << "Size: " << pq.size() << endl;
    cout << "Current queue contents:" << endl;
    pq.display();
    
    // Insert additional names with varying priorities
    printDivider("Inserting Additional Names");
    
    pq.insert("ethan", 15);
    cout << "Inserted 'ethan' with priority 15" << endl;
    
    pq.insert("ryan", 25);
    cout << "Inserted 'ryan' with priority 25" << endl;
    
    pq.insert("henry", 5);
    cout << "Inserted 'henry' with priority 5" << endl;
    
    pq.insert("kale", 35);
    cout << "Inserted 'kale' with priority 35" << endl;
    
    pq.insert("alasdair", 18);
    cout << "Inserted 'alasdair' with priority 18" << endl;
    
    // Display the state after all insertions
    printDivider("After All Insertions");
    cout << "Queue size: " << pq.size() << endl;
    cout << "Current queue contents:" << endl;
    pq.display();
    
    // Test getMin (peek)
    printDivider("Testing getMin");
    string minTask = pq.getMin();
    cout << "Minimum priority task: " << minTask << " (should be 'henry')" << endl;
    cout << "Size after getMin: " << pq.size() << " (should be unchanged)" << endl;
    
    // Test extracting multiple minimums
    printDivider("Extracting Multiple Minimums");
    cout << "Extracting tasks in priority order:" << endl;
    
    for (int i = 0; i < 3; i++) {
        string deletedTask = pq.deleteMin();
        cout << "Deleted task #" << (i+1) << ": " << deletedTask << endl;
    }
    
    cout << "Size after three deletions: " << pq.size() << " (should be 5)" << endl;
    cout << "Current queue contents:" << endl;
    pq.display();
    
    // Test update priority for multiple items
    printDivider("Testing Multiple Priority Updates");
    
    // Make kale highest priority
    pq.updatePriority("kale", 2);
    cout << "Updated 'kale' priority from 35 to 2" << endl;
    
    // Adjust alasdair's priority
    pq.updatePriority("alasdair", 12);
    cout << "Updated 'alasdair' priority from 18 to 12" << endl;
    
    cout << "Queue after updates:" << endl;
    pq.display();
    
    // Verify the min changed
    string newMin = pq.getMin();
    cout << "New minimum priority task: " << newMin << " (should be 'kale')" << endl;
    
    // Extract all remaining elements to test complete emptying
    printDivider("Extracting All Remaining Elements");
    cout << "Remaining elements in priority order:" << endl;
    
    while (!pq.isEmpty()) {
        string task = pq.deleteMin();
        cout << "Extracted: " << task << endl;
    }
    
    cout << "Is empty after all extractions: " << (pq.isEmpty() ? "Yes" : "No") << endl;
    
    // Test reinserting after complete extraction
    printDivider("Reinserting After Complete Extraction");
    pq.insert("henry", 10);
    pq.insert("ryan", 5);
    cout << "Inserted two tasks after emptying" << endl;
    cout << "Size: " << pq.size() << endl;
    cout << "Current queue contents:" << endl;
    pq.display();
    
    // Advanced: Debug display to see internal structures
    printDivider("Debug Display");
    pq.ddisplay();

	printDivider("Removing henry");
	pq.remove("henry");
	cout << "Size after removing henry: " << pq.size() << endl;
	cout << "Current queue contents:" << endl;
	pq.display();
}