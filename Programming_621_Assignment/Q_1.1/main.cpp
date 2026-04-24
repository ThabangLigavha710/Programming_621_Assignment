#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// Question 1.1.1
class Teller {
private:
    char tellerID[10];
    char fullName[50];
    char password[50]; // stored encrypted
    char branchCode[10];

public:
    // Constructor
    Teller() {}

    Teller(const char* id, const char* name, const char* pass, const char* branch) {
        strcpy(tellerID, id);
        strcpy(fullName, name);
        strcpy(password, encrypt(pass).c_str());
        strcpy(branchCode, branch);
    }

    // Simple encryption (Caesar shift)
    string encrypt(const string& pass) {
        string encrypted = pass;
        for (int i = 0; i < encrypted.length(); i++) {
            encrypted[i] = encrypted[i] + 3; // shift characters
        }
        return encrypted;
    }

    // Check login credentials
    bool authenticate(const string& id, const string& pass) {
        string encryptedInput = encrypt(pass);
        return (id == tellerID && encryptedInput == password);
    }

    void display() {
        cout << "Teller ID: T" << tellerID << endl;
        cout << "Name: " << fullName << endl;
        cout << "Branch: " << branchCode << endl;
    }

    const char* getID() { return tellerID; }
    const char* getBranch() { return branchCode; }
};


// 🔹 Save teller to binary file
void addTeller() {
    ofstream file("tellers.dat", ios::binary | ios::app);

    char id[10], name[50], pass[50], branch[10];

    cout << "Enter Teller ID: T";
    cin >> id;

    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(name, 50);

    cout << "Enter Password: ";
    cin >> pass;

    cout << "Enter Branch Code: ";
    cin >> branch;

    Teller t(id, name, pass, branch);
    file.write((char*)&t, sizeof(t));

    file.close();
    cout << "Teller added successfully!\n";
}


// 🔹 Login system
bool login(string& tellerBranch) {
    ifstream file("tellers.dat", ios::binary);

    string id, pass;
    cout << "\n--- Teller Login ---\n";
    cout << "Enter Teller ID: T";
    cin >> id;

    cout << "Enter Password: ";
    cin >> pass;

    Teller t;

    while (file.read((char*)&t, sizeof(t))) {
        if (t.authenticate(id, pass)) {
            cout << "\nLogin Successful!\n";
            t.display();

            tellerBranch = t.getBranch(); // store branch for access control
            file.close();
            return true;
        }
    }

    file.close();
    cout << "\nInvalid ID or Password!\n";
    return false;
}


// 🔹 Teller menu
void tellerMenu(const string& branch) {
    int choice;

    do {
        cout << "\n--- Teller Menu (Branch: " << branch << ") ---\n";
        cout << "1. View Customer Details\n";
        cout << "2. Process Transactions\n";
        cout << "3. Generate Reports\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Viewing customers for branch: " << branch << endl;
                break;
            case 2:
                cout << "Processing transactions for branch: " << branch << endl;
                break;
            case 3:
                cout << "Generating reports for branch: " << branch << endl;
                break;
            case 4:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);
}
 // End of question 1.1.1

// Question 1.1.2

class Customer {
private:
    char accountNumber[20];
    char encryptedPIN[10];
    double balance;

public:
    Customer() {}

    // 🔐 Encrypt PIN (simple shift)
    string encryptPIN(string pin) {
        for (int i = 0; i < pin.length(); i++) {
            pin[i] = pin[i] + 2;
        }
        return pin;
    }

    // 🔢 Generate 5-digit PIN
    string generatePIN() {
        int pin = rand() % 90000 + 10000; // ensures 10000–99999
        return to_string(pin);
    }

    // 🏦 Create Account
    void createAccount(const char* accNum, double initialBalance) {
        strcpy(accountNumber, accNum);

        string pin = generatePIN();
        cout << "Generated PIN: " << pin << endl;

        string enc = encryptPIN(pin);
        strcpy(encryptedPIN, enc.c_str());

        balance = initialBalance;
    }

    const char* getAccountNumber() { return accountNumber; }

    bool authenticate(string accNum, string pin) {
        return (accNum == accountNumber && encryptPIN(pin) == encryptedPIN);
    }

    void displayBalance() {
        cout << "Balance: R" << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    void changePIN(string newPIN) {
        string enc = encryptPIN(newPIN);
        strcpy(encryptedPIN, enc.c_str());
    }
};


// 💾 Save customer
void saveCustomer(Customer &c) {
    ofstream file("customers.dat", ios::binary | ios::app);
    file.write((char*)&c, sizeof(c));
    file.close();
}


// 🔑 Login with attempt limit
bool loginCustomer(Customer &loggedInCustomer, int &position) {
    ifstream file("customers.dat", ios::binary);

    string accNum, pin;
    int attempts = 0;

    while (attempts < 3) {
        cout << "\nEnter Account Number: ";
        cin >> accNum;

        cout << "Enter PIN: ";
        cin >> pin;

        Customer c;
        position = 0;

        while (file.read((char*)&c, sizeof(c))) {
            if (c.authenticate(accNum, pin)) {
                cout << "\nLogin Successful!\n";
                loggedInCustomer = c;
                file.close();
                return true;
            }
            position++;
        }

        attempts++;
        cout << "Invalid credentials! Attempts left: " << (3 - attempts) << endl;

        file.clear();
        file.seekg(0);
    }

    cout << "\nAccount temporarily locked due to too many failed attempts!\n";
    file.close();
    return false;
}


// 🔄 Update customer in file
void updateCustomer(Customer &c, int position) {
    fstream file("customers.dat", ios::binary | ios::in | ios::out);

    file.seekp(position * sizeof(c));
    file.write((char*)&c, sizeof(c));

    file.close();
}


// 📋 Customer Menu
void customerMenu(Customer &c, int position) {
    int choice;
    double amount;

    do {
        cout << "\n--- Customer Menu ---\n";
        cout << "1. View Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Change PIN\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                c.displayBalance();
                break;

            case 2:
                cout << "Enter amount: ";
                cin >> amount;
                c.deposit(amount);
                updateCustomer(c, position);
                break;

            case 3:
                cout << "Enter amount: ";
                cin >> amount;
                if (c.withdraw(amount)) {
                    updateCustomer(c, position);
                }
                break;

            case 4: {
                string newPIN;
                cout << "Enter new 5-digit PIN: ";
                cin >> newPIN;

                if (newPIN.length() == 5) {
                    c.changePIN(newPIN);
                    updateCustomer(c, position);
                    cout << "PIN changed successfully!\n";
                } else {
                    cout << "Invalid PIN format!\n";
                }
                break;
            }

            case 5:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);
}

// End of question 1.1.2


// 🔹 Main system
int main() {

    // Q - 1.1.1
    int option;
    string branch;

    do {
        cout << "\n=== Banking System ===\n";
        cout << "1. Add Teller\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose option: ";
        cin >> option;

        switch (option) {
            case 1:
                addTeller();
                break;
            case 2:
                if (login(branch)) {
                    tellerMenu(branch);
                }
                break;
            case 3:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }

    } while (option != 3);

    // Q - 1.1.2
    srand(time(0));

    Customer c;
    c.createAccount("ACC-JHB-00001", 1000);
    saveCustomer(c);

    Customer loggedIn;
    int pos;

    if (loginCustomer(loggedIn, pos)) {
        customerMenu(loggedIn, pos);
    }

    return 0;
}