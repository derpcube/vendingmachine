/*
02/09/2023

Simulates a simple vending machine that sells chips, candy, and soda.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#pragma warning (disable:4996)

using namespace std;

class Snack {
private:
	string name;
	double price;
	int quantity;
	int numberSold;
	string* ptr = nullptr;

	string getCurrentTime() {
		time_t t = time(0);
		struct tm ts;
		char buff[10];
		ts = *localtime(&t);
		strftime(buff, sizeof(buff), "%X", &ts);
		return buff;
	}

public:
	Snack() {
		name = "void";
		price = 0;
		quantity = 0;
		numberSold = 0;
	}

	Snack(string nam, double pric, int quant) {
		name = nam;
		price = pric;
		quantity = quant;
		numberSold = 0;
		ptr = new string[quant];
	}

	void setName(string n) {
		name = n;
	}
	void setPrice(double p) {
		price = p;
	}
	void setQuantity(int q) {
		quantity = q;
		ptr = new string[q];
	}
	void setNumberSold(int nS) {
		numberSold = nS;
	}

	string getName() const {
		return name;
	}
	double getPrice() const {
		return price;
	}
	int getQuantity() const {
		return quantity;
	}
	int getNumberSold() const {
		return numberSold;
	}

	bool buyItem(double& moneyEntered) {
		if (moneyEntered >= price) {

			if (quantity == 0) {
				cout << "Error: item is sold out!\n";
				return false;
			}

			moneyEntered -= price;
			quantity--;
			numberSold++;

			ptr[numberSold - 1] = getCurrentTime();

			cout << "Item has been dispensed below\n";

			return true;
		}
		if (moneyEntered < price) {
			cout << "Not enough money\n";

			return false;
		}
	}

	~Snack() {
		cout << "\nClosing info for " << name << ":"
			<< "\n\t" << quantity << " in stock\n"
			<< "\t" << numberSold << " sold for a profit of $"
			<< numberSold * price << endl;

		if (ptr) {
			cout << "\nTransactions occured at:\n";

			for (int i = 0; i < numberSold; i++) {
				cout << "\t" << ptr[i] << endl;
			}

			cout << "\n";
		}

		delete[] ptr;
	}
};

void displayVendingMachine(const Snack[], int);
int getQuarters();
void userBuyItem(Snack[], int);
bool promptToContinue();

int main() {
	Snack snack[3] =
	{
		Snack(),
		Snack("Candy", 1.25, 5),
		Snack("Soda", 1.00, 2)
	};

	snack[0].setName("Chips");
	snack[0].setPrice(1.75);
	snack[0].setQuantity(3);

	cout << "Welcome to the vending machine!\n\n";

	userBuyItem(snack, 3);
	promptToContinue();

	while (true) {
		userBuyItem(snack, 3);
		if (!promptToContinue()) {
			break;
		}
	}

	return 0;
}

/*
This function is responsible for displaying the vending machine’s contents.
It accepts the array of Snack objects and the number of elements in the array and displays the contents in a formatted fashion.
*/

void displayVendingMachine(const Snack snack[], int numElements) {
	cout << "Item #\tItem Name";
	cout << "       Price     # in-stock";
	cout << "\n--------------------------------------------";

	for (int i = 0; i < numElements; i++) {
		cout << endl << i + 1 << "\t" << snack[i].getName()
			<< "\t\t" << fixed << setprecision(2) << snack[i].getPrice()
			<< "\t  " << snack[i].getQuantity();
	}
}

/*
This function prompts the user to enter a number of quarters.
If the number entered is less than 1, the program displays an error message and prompt them again.
Once a valid number is entered, the program returns that value.
*/

int getQuarters() {
	int quarters;

	cout << "\n\nEnter number of quarters: ";
	cin >> quarters;

	while (quarters < 1) {
		cout << "Please enter a number greater than 0";

		cout << "\n\nEnter number of quarters: ";
		cin >> quarters;
	}

	return quarters;
}

/*
This function accepts the array of Snack objects and the number of elements in the array and first displays the contents of the vending machine and prompts the user to enter a number of quarters.
It will then display the amount entered in dollars and cents.
The user will then be prompted to enter an item number to buy.
If an invalid item number is entered, the program displays an error message and prompt them again.
Once a valid choice has been made, the program uses the appropriate method on the appropriate Snack object to buy the item.
*/

void userBuyItem(Snack snack[], int numElements) {
	double totalEntered = 0;
	int selection = 0;

	displayVendingMachine(snack, numElements);

	totalEntered = getQuarters() * 0.25;

	cout << "Amount Entered: $" << fixed << setprecision(2) << totalEntered;

	cout << "\n\nEnter a number between 1 and 3 to make your selection: ";
	cin >> selection;

	while (selection - 1 < 1 && selection - 1 > 3) {
		cout << "Please enter a number between 1 and 3: ";
		cin >> selection;
	}

	snack[selection - 1].buyItem(totalEntered);

	if (totalEntered == 0) {
		return;
	}

	cout << "$" << fixed << setprecision(2)
		<< totalEntered << " dispensed below\n";
}

/*
This function will ask the user if they want to continue running the program.
The user input is case-insensitive.
If the user enters ‘Y’ or ‘y’, return true; otherwise, return false
It will also display the times at which successful transactions occured.
*/

bool promptToContinue() {
	string response;

	cout << "\nContinue? (Y / N): ";

	cin.ignore();
	getline(cin, response);

	while (response.length() != 1) {
		cout << "Please enter a single character, Y or N: ";
		getline(cin, response);
	}

	while (response != "Y" && response != "y"
		&& response != "N" && response != "n") {
		cout << "Invalid input. Please enter 'Y' or 'N': ";
		cin >> response;
	}

	cout << endl;

	return(toupper(response[0]) == 'Y');
}

/*
Welcome to the vending machine!

Item #  Item Name       Price     # in-stock
--------------------------------------------
1       Chips           1.75      3
2       Candy           1.25      5
3       Soda            1.00      2

Enter number of quarters: -1
Please enter a number greater than 0

Enter number of quarters: 8
Amount Entered: $2.00

Enter a number between 1 and 3 to make your selection: 3
Item has been dispensed below
$1.00 dispensed below

Continue? (Y / N): y

Item #  Item Name       Price     # in-stock
--------------------------------------------
1       Chips           1.75      3
2       Candy           1.25      5
3       Soda            1.00      1

Enter number of quarters: 4
Amount Entered: $1.00

Enter a number between 1 and 3 to make your selection: 3
Item has been dispensed below

Continue? (Y / N): y

Item #  Item Name       Price     # in-stock
--------------------------------------------
1       Chips           1.75      3
2       Candy           1.25      5
3       Soda            1.00      0

Enter number of quarters: 10
Amount Entered: $2.50

Enter a number between 1 and 3 to make your selection: 1
Item has been dispensed below
$0.75 dispensed below

Continue? (Y / N): y

Item #  Item Name       Price     # in-stock
--------------------------------------------
1       Chips           1.75      2
2       Candy           1.25      5
3       Soda            1.00      0

Enter number of quarters: 5
Amount Entered: $1.25

Enter a number between 1 and 3 to make your selection: 2
Item has been dispensed below

Continue? (Y / N): y

Item #  Item Name       Price     # in-stock
--------------------------------------------
1       Chips           1.75      2
2       Candy           1.25      4
3       Soda            1.00      0

Enter number of quarters: 9
Amount Entered: $2.25

Enter a number between 1 and 3 to make your selection: 1
Item has been dispensed below
$0.50 dispensed below

Continue? (Y / N): n


Closing info for Soda:
		0 in stock
		2 sold for a profit of $2.00

Transactions occured at:
		01:37:22
		01:37:28


Closing info for Candy:
		4 in stock
		1 sold for a profit of $1.25

Transactions occured at:
		01:37:39


Closing info for Chips:
		1 in stock
		2 sold for a profit of $3.50

Transactions occured at:
		01:37:33
		01:37:44


*/
