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
