/*
* Kurt Kangas
* CIS 1202 C++ Programming II
* Week 10 Project
* Inventory Management (using Binary)
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

const int NAME_SIZE = 40;

struct Product_S
{
	long number;
	char name[NAME_SIZE];
	double price;
	int quantity;
};

int showMenu();
void createFile(fstream&);
void displayFile(fstream&);
void displayRecord(fstream&, int);
void modifyRecord(fstream&);


int main()
{
	char choice;
	int recordNumber;

	// 1st step
	fstream myBinFile("inventory.dat", ios::binary | ios::out);
	if (myBinFile.fail())
	{
		cout << "File not found...program will end";
		system("pause");
		return 0;
	}
	// second
	createFile(myBinFile);
	// third
	do
	{
		choice = showMenu();
		switch (choice)
		{
		case 'a':
			cout << "\nDisplaying the entire inventory. ";
			displayFile(myBinFile);
			break;
		case 'b':
			cout << "\nEnter the record number> ";
			cin >> recordNumber;
			displayRecord(myBinFile, recordNumber);
			break;
		case 'c':
			cout << "\nEnter the record number to be modified> ";
			modifyRecord(myBinFile);
			break;
		case 'd':
			cout << "\nExiting the program...";
			system("pause");
			return 0;
		}

	} while (choice != 'd');

	// final close
	myBinFile.close();

	cout << endl << endl;
	system("pause");
	return 0;
}
int showMenu()
{
	bool notValid = true;
	while (notValid)
	{
		notValid = false;
		char choice;
		cout << "\na.Display the entire inventory";
		cout << "\nb.Display a particular product";
		cout << "\nc.Modify a product";
		cout << "\nd.Exit the program";
		cout << endl;
		cin >> choice;
		if (choice < 'a' || choice > 'd')
		{
			cout << "Not a valid choice. Try again.\n";
			notValid = true;
		}
		else {
			return choice;
		}
	}
}
void createFile(fstream& myFile)
{
	Product_S TempProduct_S;

	long num;
	char nam[NAME_SIZE];
	double pri;
	int quant;

	int counter = 0;

	bool again = true;
	while (again)
	{
		Product_S TempProduct_S;

		cout << "\nYou are entering in information for record number: " << counter << endl;

		cout << "Enter the product number> ";
		cin >> num;
		TempProduct_S.number = num;

		cout << "Enter the name of the product> ";
		cin.ignore();
		cin.get(nam, NAME_SIZE);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		strcpy(TempProduct_S.name, nam);

		cout << "Enter the price of the product> ";
		cin >> pri;
		TempProduct_S.price = pri;

		cout << "Enter the quantity of the product> ";
		cin >> quant;
		TempProduct_S.quantity = quant;


		myFile.write((char*)&TempProduct_S, sizeof(TempProduct_S));


		cout << "\nEnter 1 for more data else enter 0> ";
		cin >> again;

		cin.ignore();
		counter++;
	}
	myFile.close();
}
void displayFile(fstream& myFile)
{
	Product_S TempProduct_S;
	int record = 0;

	myFile.open("inventory.dat", ios::in | ios::binary);
	if (!myFile)
	{
		cout << "\nInvalid; cannot open file." << endl;
		exit(0);
	}
	//while (myFile.read(reinterpret_cast<char*> (&TempProduct_S), sizeof(Product_S)))
	while (!myFile.eof())
		//while (myFile >> TempProduct_S.number)
	{
		myFile.read(reinterpret_cast<char*> (&TempProduct_S), sizeof(Product_S));
		if (myFile)
		{
			cout << "\nRecord: " << record;
			cout << "\nProduct Number: " << TempProduct_S.number;
			cout << "\nProduct Name: " << TempProduct_S.name;
			cout << "\nPrice: $" << TempProduct_S.price;
			cout << "\nQuantity: " << TempProduct_S.quantity;
			cout << endl;

			record++;
		}
	}
	myFile.close();
}
void displayRecord(fstream& myFile, int recNo)
{
	Product_S TempProduct_S;

	myFile.open("inventory.dat", ios::in | ios::binary);
	if (myFile.fail())
	{
		cout << "\nFile not found...program will end";
		system("pause");
		exit(0);
	}

	myFile.seekg(recNo * sizeof(Product_S));
	myFile.read((char*)&TempProduct_S, sizeof(Product_S));

	if (TempProduct_S.quantity <= 0)
	{
		cout << "\nRecord not found.. program will end\n";
		system("pause");
		exit(0);
	}
	else {


		cout << "Product Number: " << TempProduct_S.number << endl
			<< "Product Name: " << TempProduct_S.name << endl
			<< "Price: $" << TempProduct_S.price << endl
			<< "Quantity: " << TempProduct_S.quantity << endl;
	}
	myFile.close();
}
void modifyRecord(fstream& myFile)
{
	Product_S TempProduct_S;

	long num;
	char nam[NAME_SIZE];
	double pri;
	int quant;

	int recordNumber;

	myFile.open("inventory.dat", ios::in | ios::binary | ios::out);

	cin >> recordNumber;

	myFile.seekg(recordNumber * sizeof(Product_S), ios::beg);
	myFile.read(reinterpret_cast<char*>(&TempProduct_S), sizeof(TempProduct_S));

	cout << "Enter the product number> ";
	cin >> num;
	TempProduct_S.number = num;

	cout << "Enter the name of the product> ";
	cin >> nam;
	strcpy(TempProduct_S.name, nam);

	cout << "Enter the price of the product> ";
	cin >> pri;
	TempProduct_S.price = pri;

	cout << "Enter the quantity of the product> ";
	cin >> quant;
	TempProduct_S.quantity = quant;


	myFile.write((char*)&TempProduct_S, sizeof(TempProduct_S));

	myFile.close();
}