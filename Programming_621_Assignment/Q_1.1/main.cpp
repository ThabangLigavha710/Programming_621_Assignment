#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <map>
#include <algorithm>

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

// Question 1.1.2 - Enhanced Customer Class with Full Registration

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

    // 🔐 Encrypt PIN
    string encryptPIN(string pin) {
        for (int i = 0; i < pin.length(); i++) {
            pin[i] += 2;
        }
        return pin;
    }

    // 🔢 Generate PIN
    string generatePIN() {
        int pin = rand() % 90000 + 10000;
        return to_string(pin);
    }

    // 🔢 Generate Account Number
    string generateAccountNumber(string branch) {
        static int counter = 1;
        char acc[30];
        sprintf(acc, "ACC-%s-%05d", branch.c_str(), counter++);
        return string(acc);
    }

    // ✅ Validation functions
    bool isDigits(string str) {
        for (char c : str)
            if (!isdigit(c)) return false;
        return true;
    }

    bool validEmail(string email) {
        return (email.find('@') != string::npos && email.find('.') != string::npos);
    }

    // 🏦 Register Customer (Teller Function)
    void registerCustomer(string tellerBranch) {
        string temp;

        cout << "\n--- Register New Customer ---\n";

        cout << "First Name: ";
        cin >> temp;
        strcpy(firstName, temp.c_str());

        cout << "Surname: ";
        cin >> temp;
        strcpy(surname, temp.c_str());

        // ID validation
        do {
            cout << "ID Number (13 digits): ";
            cin >> temp;
        } while (temp.length() != 13 || !isDigits(temp));
        strcpy(idNumber, temp.c_str());

        // Contact validation
        do {
            cout << "Contact Number (10 digits): ";
            cin >> temp;
        } while (temp.length() != 10 || !isDigits(temp));
        strcpy(contact, temp.c_str());

        // Email validation
        do {
            cout << "Email: ";
            cin >> temp;
        } while (!validEmail(temp));
        strcpy(email, temp.c_str());

        cout << "Address: ";
        cin.ignore();
        cin.getline(address, 100);

        cout << "Date of Birth (DD/MM/YYYY): ";
        cin >> temp;
        strcpy(dob, temp.c_str());

        // Account Type
        cout << "Account Type (Savings/Cheque/Student): ";
        cin >> temp;
        strcpy(accountType, temp.c_str());

        // Minimum balance rule
        double minDeposit = 0;
        if (temp == "Savings") minDeposit = 500;
        else if (temp == "Cheque") minDeposit = 1000;
        else if (temp == "Student") minDeposit = 100;

        do {
            cout << "Initial Deposit (Minimum R" << minDeposit << "): ";
            cin >> balance;
        } while (balance < minDeposit);

        // Assign branch
        strcpy(branchCode, tellerBranch.c_str());

        // Generate Account Number
        string accNum = generateAccountNumber(tellerBranch);
        strcpy(accountNumber, accNum.c_str());

        // Generate PIN
        string pin = generatePIN();
        cout << "\nGenerated PIN (show once): " << pin << endl;

        string enc = encryptPIN(pin);
        strcpy(encryptedPIN, enc.c_str());

        // Save to file
        ofstream file("customers.dat", ios::binary | ios::app);
        file.write((char*)this, sizeof(*this));
        file.close();

        cout << "\nAccount Created Successfully!\n";
        cout << "Account Number: " << accountNumber << endl;
    }

    // Getters
    const char* getAccountNumber() { return accountNumber; }
    const char* getFirstName() { return firstName; }
    const char* getSurname() { return surname; }
    const char* getIDNumber() { return idNumber; }
    const char* getContact() { return contact; }
    const char* getEmail() { return email; }
    const char* getAddress() { return address; }
    const char* getDOB() { return dob; }
    const char* getAccountType() { return accountType; }
    const char* getBranch() { return branchCode; }

    // Authentication
    bool authenticate(string accNum, string pin) {
        return (accNum == accountNumber && encryptPIN(pin) == encryptedPIN);
    }

    // Balance operations
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

    // Display customer details (for teller view)
    void displayDetails() {
        cout << "\n--- Customer Details ---\n";
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << firstName << " " << surname << endl;
        cout << "ID Number: " << idNumber << endl;
        cout << "Contact: " << contact << endl;
        cout << "Email: " << email << endl;
        cout << "Address: " << address << endl;
        cout << "Date of Birth: " << dob << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Branch: " << branchCode << endl;
        cout << "Balance: R" << balance << endl;
    }
};

// ============================================================
// Account Types Implementation using Inheritance
// ============================================================

// 🔷 Base Class
class Account {
protected:
    string accountNumber;
    string accountHolder;
    double balance;
    string branchCode;

public:
    Account(string accNum, string holder, double bal, string branch)
        : accountNumber(accNum), accountHolder(holder), balance(bal), branchCode(branch) {}

    // Virtual functions (important for overriding)
    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposit successful. New balance: R" << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. New balance: R" << balance << endl;
        } else {
            cout << "Insufficient funds!\n";
        }
    }

    virtual void displayAccount() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nHolder: " << accountHolder;
        cout << "\nBalance: R" << balance;
        cout << "\nBranch: " << branchCode << endl;
    }

    virtual ~Account() {} // Destructor
    
    // Getters
    string getAccountNumber() { return accountNumber; }
    string getAccountHolder() { return accountHolder; }
    double getBalance() { return balance; }
    string getBranchCode() { return branchCode; }
};

// 🔷 Derived Class: Savings Account
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(string accNum, string holder, double bal, string branch)
        : Account(accNum, holder, bal, branch), interestRate(0.04) {}

    void displayAccount() override {
        cout << "\n=== Savings Account ===";
        Account::displayAccount();
        cout << "Interest Rate: " << (interestRate * 100) << "%" << endl;
    }

    void calculateInterest() {
        double interest = balance * interestRate;
        cout << "Interest earned: R" << interest << endl;
    }
};

// 🔷 Derived Class: Cheque Account
class ChequeAccount : public Account {
private:
    double overdraftLimit;

public:
    ChequeAccount(string accNum, string holder, double bal, string branch)
        : Account(accNum, holder, bal, branch), overdraftLimit(5000) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            cout << "Withdrawal successful (including overdraft). New balance: R" << balance << endl;
        } else {
            cout << "Insufficient funds! Overdraft limit exceeded.\n";
        }
    }

    void displayAccount() override {
        cout << "\n=== Cheque Account ===";
        Account::displayAccount();
        cout << "Overdraft Limit: R" << overdraftLimit << endl;
    }
};

// 🔷 Derived Class: Fixed Deposit Account
class FixedDepositAccount : public Account {
private:
    int termMonths;
    double fixedInterestRate;

public:
    FixedDepositAccount(string accNum, string holder, double bal, string branch, int term)
        : Account(accNum, holder, bal, branch), termMonths(term), fixedInterestRate(0.08) {}

    void displayAccount() override {
        cout << "\n=== Fixed Deposit Account ===";
        Account::displayAccount();
        cout << "Term: " << termMonths << " months";
        cout << "\nFixed Interest Rate: " << (fixedInterestRate * 100) << "%" << endl;
    }

    void calculateMaturity() {
        double interest = balance * fixedInterestRate * (termMonths / 12.0);
        double maturityValue = balance + interest;
        cout << "Maturity Value: R" << maturityValue << endl;
    }
};

// 🔷 Derived Class: Student Account
class StudentAccount : public Account {
private:
    string studentID;

public:
    StudentAccount(string accNum, string holder, double bal, string branch, string studID)
        : Account(accNum, holder, bal, branch), studentID(studID) {}

    void displayAccount() override {
        cout << "\n=== Student Account ===";
        Account::displayAccount();
        cout << "Student ID: " << studentID << endl;
    }

    void withdraw(double amount) override {
        // Student account has no minimum balance requirement
        balance -= amount;
        cout << "Withdrawal successful. New balance: R" << balance << endl;
    }
};

// ============================================================
// 1.4 Multi-Branch Management
// ============================================================

struct Branch {
    string branchCode;
    string branchName;
    string location;
    int customerCount;
    double totalBalance;
    
    Branch() : customerCount(0), totalBalance(0) {}
    
    Branch(string code, string name, string loc) 
        : branchCode(code), branchName(name), location(loc), customerCount(0), totalBalance(0) {}
};

class BranchManager {
private:
    vector<Branch> branches;
    
public:
    BranchManager() {
        // Initialize with 3 branches
        branches.push_back(Branch("JHB", "Johannesburg Central", "Johannesburg"));
        branches.push_back(Branch("CPT", "Cape Town Central", "Cape Town"));
        branches.push_back(Branch("DBN", "Durban Central", "Durban"));
    }
    
    void addBranch(string code, string name, string location) {
        branches.push_back(Branch(code, name, location));
    }
    
    void viewAllBranches() {
        cout << "\n=== All Branches ===\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < branches.size(); i++) {
            cout << "Branch " << (i+1) << ":\n";
            cout << "  Code: " << branches[i].branchCode << endl;
            cout << "  Name: " << branches[i].branchName << endl;
            cout << "  Location: " << branches[i].location << endl;
            cout << "  Customers: " << branches[i].customerCount << endl;
            cout << "  Total Balance: R" << branches[i].totalBalance << endl;
            cout << "----------------------------------------\n";
        }
    }
    
    void viewBranchDetails(string code) {
        for (auto &b : branches) {
            if (b.branchCode == code) {
                cout << "\n=== Branch Details ===\n";
                cout << "Code: " << b.branchCode << endl;
                cout << "Name: " << b.branchName << endl;
                cout << "Location: " << b.location << endl;
                cout << "Customers: " << b.customerCount << endl;
                cout << "Total Balance: R" << b.totalBalance << endl;
                return;
            }
        }
        cout << "Branch not found!\n";
    }
    
    void interBranchComparison() {
        cout << "\n=== Inter-Branch Comparison ===\n";
        cout << "----------------------------------------\n";
        
        Branch *maxCust = &branches[0];
        Branch *maxBal = &branches[0];
        
        for (auto &b : branches) {
            if (b.customerCount > maxCust->customerCount) maxCust = &b;
            if (b.totalBalance > maxBal->totalBalance) maxBal = &b;
        }
        
        cout << "Highest Customers: " << maxCust->branchName 
             << " (" << maxCust->customerCount << " customers)\n";
        cout << "Highest Balance: " << maxBal->branchName 
             << " (R" << maxBal->totalBalance << ")\n";
        cout << "----------------------------------------\n";
    }
    
    Branch* getBranch(string code) {
        for (auto &b : branches) {
            if (b.branchCode == code) return &b;
        }
        return NULL;
    }
    
    vector<Branch>& getBranches() { return branches; }
};

// ============================================================
// 1.3 Transaction Authentication & Types
// ============================================================

struct Transaction {
    char accNum[25];
    char type[20];  // Deposit, Withdraw, Transfer
    double amount;
    char date[20];
    char status[10]; // Success, Failed
};

class TransactionManager {
private:
    vector<Transaction> transactions;
    
public:
    void recordTransaction(string accNum, string type, double amount, string status) {
        Transaction t;
        strcpy(t.accNum, accNum.c_str());
        strcpy(t.type, type.c_str());
        t.amount = amount;
        
        // Get current date/time
        time_t now = time(0);
        char *dt = ctime(&now);
        strcpy(t.date, dt);
        strcpy(t.status, status.c_str());
        
        transactions.push_back(t);
        
        // Save to file
        saveTransactionToFile(t);
    }
    
    void saveTransactionToFile(Transaction &t) {
        ofstream file("transactions.dat", ios::binary | ios::app);
        file.write((char*)&t, sizeof(t));
        file.close();
    }
    
    void viewTransactionHistory(string accNum) {
        ifstream file("transactions.dat", ios::binary);
        Transaction t;
        bool found = false;
        
        cout << "\n=== Transaction History ===\n";
        while (file.read((char*)&t, sizeof(t))) {
            if (accNum == t.accNum) {
                cout << "Type: " << t.type << " | Amount: R" << t.amount 
                     << " | Date: " << t.date << " | Status: " << t.status;
                found = true;
            }
        }
        file.close();
        
        if (!found) {
            cout << "No transactions found!\n";
        }
    }
    
    void dailyTransactionReport() {
        ifstream file("transactions.dat", ios::binary);
        Transaction t;
        int count = 0;
        double total = 0;
        
        cout << "\n=== Daily Transaction Report ===\n";
        while (file.read((char*)&t, sizeof(t))) {
            count++;
            total += t.amount;
            cout << count << ". " << t.type << " | R" << t.amount << " | " << t.status;
        }
        cout << "----------------------------------------\n";
        cout << "Total Transactions: " << count << endl;
        cout << "Total Amount: R" << total << endl;
        file.close();
    }
    
    void branchPerformanceReport(BranchManager &bm) {
        ifstream file("transactions.dat", ios::binary);
        Transaction t;
        map<string, double> branchTotals;
        
        cout << "\n=== Branch Performance Report ===\n";
        while (file.read((char*)&t, sizeof(t))) {
            string accNum = t.accNum;
            if (accNum.length() >= 8) {
                string branch = accNum.substr(4, 3);
                branchTotals[branch] += t.amount;
            }
        }
        
        for (auto &bt : branchTotals) {
            cout << "Branch " << bt.first << ": R" << bt.second << endl;
        }
        file.close();
    }
};

// Global instances
BranchManager branchManager;
TransactionManager transactionManager;

// ============================================================
// 1.5.2 Customer Search and Filtering
// ============================================================

class CustomerSearch {
public:
    // Linear search by account number
    int linearSearchByAccount(vector<Customer> &customers, string accNum) {
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].accountNumber == accNum) {
                return i;
            }
        }
        return -1;
    }
    
    // Linear search by name
    vector<int> linearSearchByName(vector<Customer> &customers, string name) {
        vector<int> results;
        for (int i = 0; i < customers.size(); i++) {
            string fullName = string(customers[i].firstName) + " " + string(customers[i].surname);
            if (fullName.find(name) != string::npos) {
                results.push_back(i);
            }
        }
        return results;
    }
    
    // Filter by account type
    vector<int> filterByAccountType(vector<Customer> &customers, string type) {
        vector<int> results;
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].accountType == type) {
                results.push_back(i);
            }
        }
        return results;
    }
    
    // Filter by branch
    vector<int> filterByBranch(vector<Customer> &customers, string branch) {
        vector<int> results;
        for (int i = 0; i < customers.size(); i++) {
            if (customers[i].branchCode == branch) {
                results.push_back(i);
            }
        }
        return results;
    }
};

// ============================================================
// 1.5.1 Interest Calculation
// ============================================================

void calculateInterestForAllAccounts(vector<Customer> &customers) {
    cout << "\n=== Interest Calculation ===\n";
    for (auto &c : customers) {
        double interest = 0;
        string accType = c.accountType;
        
        if (accType == "Savings") {
            interest = c.balance * 0.04;
            cout << c.accountNumber << " (Savings): R" << interest << " interest\n";
        } else if (accType == "Fixed Deposit") {
            interest = c.balance * 0.08;
            cout << c.accountNumber << " (Fixed Deposit): R" << interest << " interest\n";
        } else if (accType == "Cheque") {
            interest = c.balance * 0.02;
            cout << c.accountNumber << " (Cheque): R" << interest << " interest\n";
        }
    }
}

// ============================================================
// 1.7 File Handling - Backup and Export
// ============================================================

void backupData() {
    // Backup customers.dat
    ifstream src("customers.dat", ios::binary);
    ofstream dst("customers_backup.dat", ios::binary);
    
    char buffer[1024];
    while (src.read(buffer, sizeof(buffer))) {
        dst.write(buffer, src.gcount());
    }
    
    src.close();
    dst.close();
    cout << "Backup created successfully!\n";
}

void exportToCSV() {
    ifstream in("customers.dat", ios::binary);
    ofstream out("customers.csv");
    
    out << "AccountNumber,FirstName,Surname,IDNumber,Contact,Email,Address,DOB,AccountType,Branch,Balance\n";
    
    Customer c;
    while (in.read((char*)&c, sizeof(c))) {
        out << c.accountNumber << "," << c.firstName << "," << c.surname << ","
            << c.idNumber << "," << c.contact << "," << c.email << ","
            << c.address << "," << c.dob << "," << c.accountType << ","
            << c.branchCode << "," << c.balance << "\n";
    }
    
    in.close();
    out.close();
    cout << "Exported to CSV successfully!\n";
}

void exportToText() {
    ifstream in("customers.dat", ios::binary);
    ofstream out("customers.txt");
    
    Customer c;
    while (in.read((char*)&c, sizeof(c))) {
        out << "=====================================\n";
        out << "Account: " << c.accountNumber << "\n";
        out << "Name: " << c.firstName << " " << c.surname << "\n";
        out << "ID: " << c.idNumber << "\n";
        out << "Contact: " << c.contact << "\n";
        out << "Email: " << c.email << "\n";
        out << "Address: " << c.address << "\n";
        out << "DOB: " << c.dob << "\n";
        out << "Type: " << c.accountType << "\n";
        out << "Branch: " << c.branchCode << "\n";
        out << "Balance: R" << c.balance << "\n";
        out << "=====================================\n\n";
    }
    
    in.close();
    out.close();
    cout << "Exported to Text successfully!\n";
}

// ============================================================
// 1.6 Reporting and Analytics
// ============================================================

void customerAccountSummary() {
    ifstream file("customers.dat", ios::binary);
    Customer c;
    int count = 0;
    double total = 0;
    
    cout << "\n=== Customer Account Summary ===\n";
    while (file.read((char*)&c, sizeof(c))) {
        count++;
        total += c.balance;
        cout << count << ". " << c.accountNumber << " | " 
             << c.firstName << " " << c.surname << " | R" << c.balance << "\n";
    }
    cout << "----------------------------------------\n";
    cout << "Total Customers: " << count << endl;
    cout << "Total Balance: R" << total << endl;
    file.close();
}


// Forward declaration for updateCustomer
void updateCustomer(Customer &c, int position);


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
        cout << "1. Register New Customer Account\n";
        cout << "2. View Customer Details\n";
        cout << "3. Process Transactions\n";
        cout << "4. Generate Reports\n";
        cout << "5. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Register new customer account
                Customer newCust;
                newCust.registerCustomer(branch);
                break;
            }
            case 2: {
                // View customer details
                ifstream file("customers.dat", ios::binary);
                string searchAcc;
                cout << "Enter Account Number to search: ";
                cin >> searchAcc;
                
                Customer c;
                bool found = false;
                while (file.read((char*)&c, sizeof(c))) {
                    if (strcmp(c.getAccountNumber(), searchAcc.c_str()) == 0) {
                        c.displayDetails();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Customer not found!\n";
                }
                file.close();
                break;
            }
            case 3: {
                // Process transactions on behalf of customers
                ifstream file("customers.dat", ios::binary);
                string searchAcc;
                int transType;
                double amount;
                
                cout << "Enter Customer Account Number: ";
                cin >> searchAcc;
                
                Customer c;
                int pos = 0;
                bool found = false;
                
                while (file.read((char*)&c, sizeof(c))) {
                    if (strcmp(c.getAccountNumber(), searchAcc.c_str()) == 0) {
                        cout << "\n--- Process Transaction ---\n";
                        cout << "1. Deposit\n2. Withdrawal\n";
                        cout << "Enter transaction type: ";
                        cin >> transType;
                        cout << "Enter amount: R";
                        cin >> amount;
                        
                        if (transType == 1) {
                            c.deposit(amount);
                            cout << "Deposit successful! New balance: R" << amount << endl;
                        } else if (transType == 2) {
                            if (c.withdraw(amount)) {
                                cout << "Withdrawal successful!\n";
                            }
                        }
                        
                        updateCustomer(c, pos);
                        found = true;
                        break;
                    }
                    pos++;
                }
                if (!found) {
                    cout << "Customer not found!\n";
                }
                file.close();
                break;
            }
            case 4: {
                // Generate reports for their branch
                ifstream file("customers.dat", ios::binary);
                cout << "\n--- Branch Report ---\n";
                cout << "Branch: " << branch << endl;
                cout << "----------------------------------------\n";
                
                Customer c;
                int count = 0;
                double totalBalance = 0;
                
                while (file.read((char*)&c, sizeof(c))) {
                    string accNum = c.getAccountNumber();
                    // Check if account belongs to this branch
                    if (accNum.find(branch) != string::npos) {
                        cout << "Account: " << accNum << endl;
                        c.displayBalance();
                        cout << "----------------------------------------\n";
                        count++;
                    }
                }
                cout << "Total customers in branch " << branch << ": " << count << endl;
                file.close();
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
 // End of question 1.1.1


//  Login with attempt limit
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
        cout << "4. Transfer\n";
        cout << "5. View Account Statement\n";
        cout << "6. Change PIN\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                c.displayBalance();
                break;

            case 2:
                cout << "Enter amount: R";
                cin >> amount;
                c.deposit(amount);
                updateCustomer(c, position);
                cout << "Deposit successful!\n";
                break;

            case 3:
                cout << "Enter amount: R";
                cin >> amount;
                if (c.withdraw(amount)) {
                    updateCustomer(c, position);
                    cout << "Withdrawal successful!\n";
                }
                break;

            case 4: {
                // Transfer to another account
                ifstream inFile("customers.dat", ios::binary);
                string targetAcc;
                double transferAmount;
                
                cout << "Enter target Account Number: ";
                cin >> targetAcc;
                cout << "Enter amount to transfer: R";
                cin >> transferAmount;
                
                if (transferAmount > 0 && c.withdraw(transferAmount)) {
                    // Find and update target account
                    Customer target;
                    int targetPos = 0;
                    bool found = false;
                    
                    while (inFile.read((char*)&target, sizeof(target))) {
                        if (strcmp(target.getAccountNumber(), targetAcc.c_str()) == 0) {
                            target.deposit(transferAmount);
                            updateCustomer(target, targetPos);
                            found = true;
                            break;
                        }
                        targetPos++;
                    }
                    inFile.close();
                    
                    if (found) {
                        updateCustomer(c, position);
                        cout << "Transfer of R" << transferAmount << " to " << targetAcc << " successful!\n";
                    } else {
                        // Rollback - deposit back
                        c.deposit(transferAmount);
                        cout << "Target account not found! Transfer cancelled.\n";
                    }
                } else {
                    cout << "Transfer failed! Insufficient funds or invalid amount.\n";
                }
                break;
            }

            case 5: {
                // View Account Statement
                cout << "\n--- Account Statement ---\n";
                cout << "Account Number: " << c.getAccountNumber() << endl;
                c.displayBalance();
                cout << "----------------------------------------\n";
                cout << "Statement: Account is active.\n";
                cout << "Date: " << __DATE__ << "\n";
                cout << "----------------------------------------\n";
                break;
            }

            case 6: {
                string newPIN;
                cout << "Enter new 5-digit PIN: ";
                cin >> newPIN;

                if (newPIN.length() == 5) {
                    // Validate PIN is all digits
                    bool validPIN = true;
                    for (int i = 0; i < newPIN.length(); i++) {
                        if (!isdigit(newPIN[i])) {
                            validPIN = false;
                            break;
                        }
                    }
                    
                    if (validPIN) {
                        c.changePIN(newPIN);
                        updateCustomer(c, position);
                        cout << "PIN changed successfully!\n";
                    } else {
                        cout << "Invalid PIN! Must contain only digits.\n";
                    }
                } else {
                    cout << "Invalid PIN format! Must be exactly 5 digits.\n";
                }
                break;
            }

            case 7:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 7);
}

// End of question 1.1.2


// 🔹 Main system
int main() {
    srand(time(0));
    
    int mainOption;

    do {
        cout << "\n========================================\n";
        cout << "       BANKING SYSTEM MAIN MENU        \n";
        cout << "========================================\n";
        cout << "1. Add Teller (Admin)\n";
        cout << "2. Teller Login\n";
        cout << "3. Customer Login\n";
        cout << "4. Branch Management\n";
        cout << "5. Reports & Analytics\n";
        cout << "6. Data Backup & Export\n";
        cout << "7. Exit\n";
        cout << "Choose option: ";
        cin >> mainOption;

        switch (mainOption) {
            case 1:
                addTeller();
                break;
            case 2: {
                string branch;
                if (login(branch)) {
                    tellerMenu(branch);
                }
                break;
            }
            case 3: {
                // Customer Login
                Customer loggedIn;
                int pos;
                
                if (loginCustomer(loggedIn, pos)) {
                    customerMenu(loggedIn, pos);
                }
                break;
            }
            case 4: {
                // Branch Management
                int branchChoice;
                do {
                    cout << "\n=== Branch Management ===\n";
                    cout << "1. View All Branches\n";
                    cout << "2. View Branch Details\n";
                    cout << "3. Inter-Branch Comparison\n";
                    cout << "4. Back to Main\n";
                    cin >> branchChoice;
                    
                    switch (branchChoice) {
                        case 1:
                            branchManager.viewAllBranches();
                            break;
                        case 2: {
                            string code;
                            cout << "Enter Branch Code (JHB/CPT/DBN): ";
                            cin >> code;
                            branchManager.viewBranchDetails(code);
                            break;
                        }
                        case 3:
                            branchManager.interBranchComparison();
                            break;
                    }
                } while (branchChoice != 4);
                break;
            }
            case 5: {
                // Reports & Analytics
                int reportChoice;
                do {
                    cout << "\n=== Reports & Analytics ===\n";
                    cout << "1. Daily Transaction Report\n";
                    cout << "2. Customer Account Summary\n";
                    cout << "3. Branch Performance Report\n";
                    cout << "4. Calculate Interest\n";
                    cout << "5. Back to Main\n";
                    cin >> reportChoice;
                    
                    switch (reportChoice) {
                        case 1:
                            transactionManager.dailyTransactionReport();
                            break;
                        case 2:
                            customerAccountSummary();
                            break;
                        case 3:
                            transactionManager.branchPerformanceReport(branchManager);
                            break;
                        case 4: {
                            // Load customers and calculate interest
                            ifstream file("customers.dat", ios::binary);
                            vector<Customer> customers;
                            Customer c;
                            while (file.read((char*)&c, sizeof(c))) {
                                customers.push_back(c);
                            }
                            file.close();
                            calculateInterestForAllAccounts(customers);
                            break;
                        }
                    }
                } while (reportChoice != 5);
                break;
            }
            case 6: {
                // Data Backup & Export
                int exportChoice;
                do {
                    cout << "\n=== Data Backup & Export ===\n";
                    cout << "1. Backup Data\n";
                    cout << "2. Export to CSV\n";
                    cout << "3. Export to Text\n";
                    cout << "4. Back to Main\n";
                    cin >> exportChoice;
                    
                    switch (exportChoice) {
                        case 1:
                            backupData();
                            break;
                        case 2:
                            exportToCSV();
                            break;
                        case 3:
                            exportToText();
                            break;
                    }
                } while (exportChoice != 4);
                break;
            }
            case 7:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }

    } while (mainOption != 7);

    return 0;
}