#include "IndPQ.h"
#include <iostream>



int main() {

	// IndPQ ipq;
	IndPQ ipq;

	ipq.insert("Task A", 2);
	ipq.insert("Task B", 4);
	ipq.insert("Task C", 6);

	ipq.ddisplay();

	ipq.insert("Task D", 3);

	

	ipq.ddisplay();

	cout << "\n\n\n Deleting Min\n\n\n";

	ipq.deleteMin();
	ipq.ddisplay();




	return 0;
}