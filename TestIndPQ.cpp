#include "IndPQ.h"
#include <iostream>



int main() {

	// IndPQ ipq;
	IndPQ ipq;

	// ipq.insert("Task A", 2);
	// ipq.insert("Task B", 4);
	// ipq.insert("Task C", 6);
	// ipq.insert("Task D", 8);
	// ipq.insert("Task E", 7);
	// ipq.insert("Task F", 9);
	// ipq.insert("Task G", 12);


	// ipq.display();

	// cout << "\n\n\n Deleting Min\n\n\n";

	// ipq.deleteMin();
	// ipq.ddisplay();

	// cout << "\n\n\n Updating Priority\n\n\n";

	// ipq.updatePriority("Task C", 1);
	// ipq.ddisplay();

	ipq.insert("Saffat",4);
	ipq.ddisplay();

	ipq.insert("Bryce",3);
	
	ipq.ddisplay();

	ipq.updatePriority("Saffat",1);
	ipq.ddisplay();


	return 0;
}