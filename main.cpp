
#include"Suffix.h"



void menu() {
	using namespace std;
	bool running = true;

	// Unique pointer so that we can easily reset the instance of the SUffix Tree
	unique_ptr<PrintableSuffixTree>tree = std::make_unique<PrintableSuffixTree>();

	while (running) {
		cout << "    Ukkonen's Suffix Algorithm     \n";
		cout << "           Visualization           \n";
		cout << "\n\n\n";
		cout << "Please enter the operation that you want to perform\n";

		cout << "\n1. Add Single Character into Suffix Tree";
		cout << "\n2. Add String into Suffix Tree, Stepwise visualization";
		cout << "\n3. Add String into Suffix Tree Instantly";
		cout << "\n4. Print the Suffix Tree";
		cout << "\n5. Reset the Suffix Tree";
		cout << "\n6. Exit";
		cout << "\n";

		int choice;
		cin >> choice;

		// Inorder to ignore the \n delimiter in the stream
		cin.ignore();

		switch (choice) {

		case 1: {
			cout << "\n Enter the Character that you want to append into suffix tree";
			cout << "\n:";

			char c;
			cin >> c;

			(*tree) += c;
			break;
		}

		case 2: {
			cout << "\n Enter the String that you want to append into suffix tree (Stepwise)";
			cout << "\n:";

			string str;
			cin >> str;

			// Inorder to ignore the \n delimiter in the stream
			cin.ignore();

			tree->addStepWise(str);
			break;
		}

		case 3: {
			cout << "\n Enter the String that you want to append into suffix tree (Instantly)";
			cout << "\n:";

			string str;
			cin >> str;

			// Inorder to ignore the \n delimiter in the stream
			cin.ignore();

			(*tree) += str;
			break;

		}

		case 4:
			cout << "\n\n\t\t\tTree\n";
			tree->print();
			cout << "\n\n";
			PauseConsole();
			break;

		case 5:
			tree = std::make_unique<PrintableSuffixTree>();
			cout << "\n Suffix Tree Reset Successful!";
			break;
		case 6:
			running = false;
			break;

		default:
			cout << "\n Invalid Choice";
		}

	}
}

int main() {

	menu();

	return 0;
}

