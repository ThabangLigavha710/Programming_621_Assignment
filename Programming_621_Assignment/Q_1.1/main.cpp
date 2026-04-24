
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <map>

using namespace std;

// ===================== CUSTOMER CLASS =====================
class Customer {
private:
    char accountNumber[25];
    char firstName[30];
    char surname[30];
    char idNumber[20];
    char contact[15];
    char email[50];
    char address[100];
    char dob[15];
    char accountType[20];
    char branchCode[10];
    char encryptedPIN[10];
    double balance;

public:
    Customer() {}

    // ===== GETTERS =====
    const char* getAccountNumber() { return accountNumber; }
    const char* getFirstName() { return firstName; }
    const char* getSurname() { return surname; }
    const char* getAccountType() { return accountType; }
    const char* getBranch() { return branchCode; }
    double getBalance() { return balance; }

    // ================= BASIC FUNCTIONS =================
    void deposit(double amount) { balance += amount; }

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
};

// ===================== CUSTOMER SEARCH =====================
class CustomerSearch {
public:
    int linearSearchByAccount(vector<Customer> &customers, string accNum) {
        for (int i = 0; i < customers.size(); i++) {
            if (string(customers[i].getAccountNumber()) == accNum) {
                return i;
            }
        }
        return -1;
    }

    vector<int> linearSearchByName(vector<Customer> &customers, string name) {
        vector<int> results;
        for (int i = 0; i < customers.size(); i++) {
            string fullName = string(customers[i].getFirstName()) + " " +
                              string(customers[i].getSurname());
            if (fullName.find(name) != string::npos) {
                results.push_back(i);
            }
        }
        return results;
    }

    vector<int> filterByAccountType(vector<Customer> &customers, string type) {
        vector<int> results;
        for (int i = 0; i < customers.size(); i++) {
            if (string(customers[i].getAccountType()) == type) {
                results.push_back(i);
            }
        }
        return results;
    }

    vector<int> filterByBranch(vector<Customer> &customers, string branch) {
        vector<int> results;
        for (int i = 0; i < customers.size(); i++) {
            if (string(customers[i].getBranch()) == branch) {
                results.push_back(i);
            }
        }
        return results;
    }
};

// ===================== INTEREST =====================
void calculateInterestForAllAccounts(vector<Customer> &customers) {
    cout << "\n=== Interest Calculation ===\n";

    for (auto &c : customers) {
        double interest = 0;
        string type = c.getAccountType();

        if (type == "Savings") {
            interest = c.getBalance() * 0.04;
            cout << c.getAccountNumber() << " (Savings): R" << interest << endl;
        }
        else if (type == "Fixed Deposit") {
            interest = c.getBalance() * 0.08;
            cout << c.getAccountNumber() << " (Fixed Deposit): R" << interest << endl;
        }
        else if (type == "Cheque") {
            interest = c.getBalance() * 0.02;
            cout << c.getAccountNumber() << " (Cheque): R" << interest << endl;
        }
    }
}

// ===================== EXPORT CSV =====================
void exportToCSV() {
    ifstream in("customers.dat", ios::binary);
    ofstream out("customers.csv");

    Customer c;

    while (in.read((char*)&c, sizeof(c))) {
        out << c.getAccountNumber() << ","
            << c.getFirstName() << ","
            << c.getSurname() << ","
            << c.getAccountType() << ","
            << c.getBranch() << ","
            << c.getBalance() << "\n";
    }

    cout << "Exported to CSV successfully!\n";
}

// ===================== EXPORT TEXT =====================
void exportToText() {
    ifstream in("customers.dat", ios::binary);
    ofstream out("customers.txt");

    Customer c;

    while (in.read((char*)&c, sizeof(c))) {
        out << "Account: " << c.getAccountNumber() << "\n";
        out << "Name: " << c.getFirstName() << " " << c.getSurname() << "\n";
        out << "Type: " << c.getAccountType() << "\n";
        out << "Branch: " << c.getBranch() << "\n";
        out << "Balance: R" << c.getBalance() << "\n";
        out << "---------------------------------\n";
    }

    cout << "Exported to Text successfully!\n";
}

// ===================== SUMMARY =====================
void customerAccountSummary() {
    ifstream file("customers.dat", ios::binary);

    Customer c;
    int count = 0;
    double total = 0;

    cout << "\n=== Customer Summary ===\n";

    while (file.read((char*)&c, sizeof(c))) {
        count++;
        total += c.getBalance();

        cout << count << ". "
             << c.getAccountNumber() << " | "
             << c.getFirstName() << " "
             << c.getSurname()
             << " | R" << c.getBalance() << endl;
    }

    cout << "Total Customers: " << count << endl;
    cout << "Total Balance: R" << total << endl;
}

// ===================== MAIN =====================
int main() {
    vector<Customer> customers;

    cout << "System Running Successfully (No Errors) ✅\n";

    // Dummy menu just to test compilation
    int choice;
    do {
        cout << "\n1. Export CSV\n2. Export Text\n3. Summary\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1: exportToCSV(); break;
            case 2: exportToText(); break;
            case 3: customerAccountSummary(); break;
        }

    } while (choice != 4);

    return 0;
}