/*****
*Author: Caleb Stephens
*Date: 10/23/2018
*Project Description: In the Process of creating a password/login system
*****/

#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include "Users.h"
using namespace std;

//Global Var
ifstream inStream_U;
ofstream outStream_U;
ifstream inStream_P;
ofstream outStream_P;

//function declarations
void init_IOStreams();
//Initializes the input and output streams by opening the files
void fill_pw_vector(vector<string>&);
//This function reads the password file and applies the contents to a vector named passwords
void fill_un_vector(vector<string>&);
//This function reads the username file and applies the contents to a vector named usernames
int login_menu();
//This function displays the menu of the program
void account_login(vector<string>&, vector<string>&);
//This function allows the user to login
void check_login_values(string, string, vector<string>&, vector<string>&);
//This function tests the login values
void account_create_new(vector<string>&, vector<string>&);
//This function allows a user to create a new login


int main() {
	vector <string> usernames;
	vector <string> passwords;
	bool menu_on;
	int menu_choice;
	
	init_IOStreams();
	fill_un_vector(usernames);
	fill_pw_vector(passwords);
	//Code goes here
	menu_on = true;
	while (menu_on) {
		menu_choice = login_menu();
		switch (menu_choice) {
	case 1:
		account_login(usernames, passwords);
		system("pause");
		break;
	case 2:
		account_create_new(usernames, passwords);
		system("pause");
		break;
	case 3:
		menu_on = false;
		break;
	default:
		cout << "ERROR: you need to enter a correct value.";
		system("pause");
		break;
	}
	}
	inStream_P.close();
	outStream_P.close();
	system("pause");
	return 0;
}

//function definitions
void init_IOStreams() {
	inStream_U.open("Usernames.txt", ios::in);
	outStream_U.open("Usernames.txt", ios::app);
	inStream_P.open("Passwords.txt", ios::in);
	outStream_P.open("Passwords.txt", ios::app);
	if (inStream_P.fail() || inStream_U.fail()) {
		cout << "Input file open failed";
		system("pause");
		exit(1);
	}
	if (outStream_P.fail() || outStream_U.fail()) {
		cout << "Output file open failed";
		system("pause");
		exit(1);
	}
}

void fill_un_vector(vector<string>& usernames) {
	string mystring = "";
	while (!inStream_U.eof()) {
		getline(inStream_U, mystring);
		usernames.push_back(mystring);
	}
}

void fill_pw_vector(vector<string>& passwords) {
	string mystring = "";
	while (!inStream_P.eof()) {
		getline(inStream_P, mystring);
		passwords.push_back(mystring);
	}
}

int login_menu() {
	system("cls");
	int choice;
	cout << "\tMenu\n\n";
	cout << "1. Login\n";
	cout << "2. Create Account\n";
	cout << "3. Exit\n";
	cin >> choice;
	return choice;
}

void account_login(vector<string>& usernames, vector<string>& passwords) {
	string user;
	string pass;
	system("cls");
	cout << "LOGIN TEST\n";
	cout << "USERNAME: ";
	cin.ignore();
	getline(cin, user);
	cout << "PASSWORD: ";
	cin >> pass;
	
	check_login_values(user, pass, usernames, passwords);
}

void check_login_values(string user, string pass, vector<string>& usernames, vector<string>& passwords) {
	int num = size(usernames)-1;
	while (num > -1) {
		if (user == usernames[num] && pass == passwords[num]) {
			cout << "WELCOME!\nYou are now logged in as: \n" << user;
			break;
		}
		else if (num == 0){
			cout << "Your username or password was incorrect\n";
			cout << "1. Try again\n";
			cout << "2. Exit to menu\n";
			int choice = 0;
			cin >> choice;
			switch (choice) {
			case 1:
				account_login(usernames, passwords);
				break;
			case 2:
					break;
			default:
				break;
			}
			break;
		}
		else {
			num--;
		}
		
	}
}

void account_create_new(vector<string>& usernames, vector<string>& passwords) {
	system("cls");
	cout << "CREATE ACCOUNT TEST\n";
	cout << "Username and Password have to have at least 4 characters.\n";
	string user = "";
	string pass = "";
	cout << "Enter new accounts username: ";
	cin.ignore();
	getline(cin, user);
	cout << "\nEnter new accounts password: ";
	cin >> pass;

	if (user.length() > 3 && pass.length() > 3) {
		outStream_U << endl << user;
		outStream_P << endl << pass;
		usernames.push_back(user);
		passwords.push_back(pass);
	}
	else {
		int num = 0;
		cout << "Sorry, but you did not enter correct values.\n";
		cout << "1. Try Again?\n";
		cout << "2. Exit To Menu\n";
		cin >> num;
		if (num == 1) {
			account_create_new(usernames, passwords);
		}
		else if (num == 2) {
		}
		else {
			cout << "You entered an incorrect value, returning to Menu.";
			system("pause");
		}
	}
}
