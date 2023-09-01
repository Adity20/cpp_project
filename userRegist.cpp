#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include<conio.h>
#include<ctime>
#include<stdio.h>
#include<windows.h>



using namespace std;

struct UserProfile {
    string fullName;
    string email;
    string username;
    string password;
    
    // Add other fields as needed
};

void AddTransaction() {
    system("cls"); // Clear the screen

    cout << "\nAdd Transaction\n";
    cout << "----------------\n";

    string date, description, category;
    float amount;

    cin.ignore(); // Clear the newline character from previous input
    cout << "Date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Description: ";
    getline(cin, description);

    cout << "Amount: ";
    cin >> amount;

    cin.ignore(); // Clear the newline character from previous input
    cout << "Category (Income/Expense): ";
    getline(cin, category);

    // Save the transaction details to a text file

    ofstream transactionFile("transactions.txt", ios::app);
    if (transactionFile.is_open()) {
        transactionFile << date << "\t" << amount << "\t" << description << "\t" << category << "\n";
        cout << "\nTransaction added successfully!\n";
        transactionFile.close();
    } else {
        cout << "\nFailed to open transaction file.\n";
    }

    cout << "\nPress enter to continue...";
    cin.get();
}

map<string, UserProfile> userProfiles;

const string COLOR_RED = "\033[1;34m";  // Blue color
const string COLOR_RESET = "\033[0m";

void PrintTitle() {
    cout << COLOR_RED << R"(
  ____                _                  _     ____                _       _         
 |  _ \              | |                | |   |  _ \              | |     | |        
 | |_) |  _   _    __| |   __ _    ___  | |_  | |_) |  _   _    __| |   __| |  _   _ 
 |  _ <  | | | |  / _` |  / _` |  / _ \ | __| |  _ <  | | | |  / _` |  / _` | | | | |
 | |_) | | |_| | | (_| | | (_| | |  __/ | |_  | |_) | | |_| | | (_| | | (_| | | |_| |
 |____/   \__,_|  \__,_|  \__, |  \___|  \__| |____/   \__,_|  \__,_|  \__,_|  \__, |
                           __/ |                                                __/ |
                          |___/                                                |___/ 
    )" << COLOR_RESET << endl;
}

void SaveUserDataToCSV(const string& filename, const UserProfile& userProfile) {
    ofstream outFile(filename, ios::app); // Append mode to add new records
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    // Specify the order of columns in the CSV file
    outFile << userProfile.username << ",";
    outFile << userProfile.fullName << ",";
    outFile << userProfile.email << ",";
    outFile << userProfile.password << "\n";
    
    cout << "User data saved to CSV file.\n";
}

// Structure to store monthly expenses
struct MonthlyExpenses {
    float housingEx;
    float utilitiesEx;
    float householdEx;
    float transportationEx;
    float foodEx;
    float medicalEx;
    float insuranceEx;
    float entertainmentEx;
    float clothingEx;
    float miscellaneousEx;
};



bool AuthenticateUser(const string& username, const string& password) {
    if (userProfiles.find(username) != userProfiles.end() && userProfiles[username].password == password) {
        return true;
    }
    return false;
}

void RegisterUser() {
    UserProfile newUser;

    cout << "User Registration\n";
    cout << "Enter your full name: ";
    getline(cin >> ws, newUser.fullName);

    cout << "Enter your email address: ";
    cin >> newUser.email;

    cout << "Enter a username: ";
    cin >> newUser.username;

    if (userProfiles.find(newUser.username) != userProfiles.end()) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> newUser.password;

    userProfiles[newUser.username] = newUser;

    // Save to CSV file
    SaveUserDataToCSV("userdata.csv", newUser);

    cout << "User registered successfully!\n";
}

void PrintMenu() {
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Add Transactions\n";
    cout<<"4. Exit\n";
    cout << "-----------------------------\n";
    cout << "Enter your choice: ";
}

void CollectMonthlyExpenses(MonthlyExpenses& me, int count) {
    cout << "Enter your housing expenses for month " << count << ":\n";
    cin >> me.housingEx;
    cout << "Enter your utilities expenses for month " << count << ":\n";
    cin >> me.utilitiesEx;
    cout << "Enter the cost of your household expenses for month " << count << ":\n";
    cin >> me.householdEx;
    cout << "Enter your transportation expenses for month " << count << ":\n";
    cin >> me.transportationEx;
    cout << "Enter your food expenses for month " << count << ":\n";
    cin >> me.foodEx;
    cout << "Enter your medical expenses for month " << count << ":\n";
    cin >> me.medicalEx;
    cout << "Enter your insurance expenses for month " << count << ":\n";
    cin >> me.insuranceEx;
    cout << "Enter your entertainment expenses for month " << count << ":\n";
    cin >> me.entertainmentEx;
    cout << "Enter your clothing expenses for month " << count << ":\n";
    cin >> me.clothingEx;
    cout << "Enter your miscellaneous expenses for month " << count << ":\n";
    cin >> me.miscellaneousEx;
    
}



int main() {
    // Load existing user data from CSV file (if any)
    ifstream inFile("userdata.csv");
    if (inFile) {
        string line;
        while (getline(inFile, line)) {
            UserProfile user;
            size_t pos = 0;
            pos = line.find(",");
            user.username = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            user.fullName = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            user.email = line.substr(0, pos);
            line.erase(0, pos + 1);
            user.password = line;
            userProfiles[user.username] = user;
        }
        inFile.close();
    }


    int numberOfMonths;
    cout << "Enter the number of months: ";
    cin >> numberOfMonths;

    vector<MonthlyExpenses> allExpenses;

    char choice;

    do {
       system("cls");
	 //cout<<date;
	 char title[]="\t\t\t\t----------------------------\n\t\t\t\t\tBUDGET BUDDY\n\t\t\t\t----------------------------";
	 char *ptr=&title[0];
	 for(int i=0;i<sizeof(title);i++)
	      {   cout << *(ptr+i);    Sleep(40);  } 
            PrintTitle();
            PrintMenu();
       char choice;
        cin >> choice;

        switch (choice) {
            case '1':
                // Register user
                break;
            case '2':
                // Login user
                break;
            case '4':
                cout << "\nExiting...\n";
                break;
            case '3':
                system("cls");
                cout << "3. Add Expenses\n";
                 for (int i = 1; i <= numberOfMonths; ++i) {
                MonthlyExpenses me;
                CollectMonthlyExpenses(me, i);
                allExpenses.push_back(me);
    }
 // Call the new function
                break;
            case '5':
                // Collect and store monthly expenses
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
        }

        cout << "\nPress enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != '3');

    return 0;
}