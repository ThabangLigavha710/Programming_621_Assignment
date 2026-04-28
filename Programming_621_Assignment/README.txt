# Banking System README

## How to Compile and Run the System

### Compilation (Windows with g++):
```
g++ -o bank_system main.cpp
```

### Running the System:
```
./bank_system
```

---

## Default Teller Login Credentials

The system comes with one default teller account:

| Username | Password | Role |
|----------|----------|------|
| admin    | admin123 | Manager/Teller |

**Note:** On first run, you can log in with these credentials to access teller functions.

---

## How to Create Customer Accounts and View Generated PINs

### As a Teller:
1. Log in with teller credentials (admin / admin123)
2. Select option to create new customer account
3. Enter customer details when prompted:
   - First name
   - Surname
   - ID Number
   - Contact number
   - Email address
   - Physical address
   - Date of birth
   - Account type (Savings, Fixed Deposit, or Cheque)
   - Branch code
   - Initial deposit amount

4. **System automatically generates a 4-digit PIN** for the customer
5. The PIN is displayed on screen and saved to the customer record

### Viewing Customer PINs:
- Tellers can view customer PINs through the "View Customer" option
- PINs are shown masked (e.g., "****") for security
- Full PIN only displayed at time of account creation

---

## How Customers Log In and Perform Transactions

### Customer Login:
1. Select "Customer Login" from main menu
2. Enter account number (provided by teller)
3. Enter 4-digit PIN (given at account creation)
4. If credentials valid, access customer menu

### Available Customer Transactions:
1. **Check Balance** - View current account balance
2. **Deposit Money** - Add funds to account
3. **Withdraw Money** - Remove funds (if sufficient balance)
4. **Transfer Money** - Send funds to another account
5. **View Account Details** - See personal information
6. **Change PIN** - Update security PIN
7. **Exit** - Log out of account

### Transaction Limits:
- Minimum withdrawal: R10
- Maximum withdrawal: R50,000 per transaction
- Minimum deposit: R10

---

## Code Organization

The system is organized into logical modules:

### 1. Customer Class (`Customer`)
- Stores all customer data (account details, balance, PIN)
- Provides getter/setter methods for encapsulation
- Handles deposit and withdrawal operations

### 2. Customer Search (`CustomerSearch`)
- Linear search by account number
- Search by name (partial match)
- Filter by account type
- Filter by branch

### 3. Interest Calculation
- Savings accounts: 4% interest
- Fixed Deposit accounts: 8% interest
- Cheque accounts: 2% interest

### 4. Export Functions
- Export to CSV format
- Export to text format

### 5. Teller Functions
- Create customer accounts
- View all customers
- Search customers
- Generate account reports

---

## File Structure

```
Programming_621_Assignment/
├── main.cpp          # Main program source code
├── customers.dat    # Binary file storing customer records
├── customers.csv    # Exported customer data (CSV format)
├── customers.txt    # Exported customer data (text format)
└── README.txt       # This file
```

---

## Troubleshooting

### Common Issues:
1. **"Cannot open customers.dat"** - File doesn't exist yet; this is normal on first run
2. **"Invalid PIN"** - Check account number and PIN; contact teller for help
3. **"Insufficient funds"** - Withdrawal amount exceeds balance
4. **"Account not found"** - Verify account number with teller

### Getting Help:
- Contact system administrator
- Refer to teller manual
- Check system logs for error details

---

## Security Notes

- Change default teller password after first login
- Keep customer PINs confidential
- Log out of teller account when leaving workstation
- Customer data is stored in binary format for security

---

*Last Updated: April 2026*
*Banking System v1.0*