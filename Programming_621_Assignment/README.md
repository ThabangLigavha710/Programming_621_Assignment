# Banking System

> A comprehensive C++ banking system with teller management, customer accounts, and transaction processing.

## Table of Contents

- [How to Compile and Run the System](#how-to-compile-and-run-the-system)
- [Default Teller Login Credentials](#default-teller-login-credentials)
- [How to Create Customer Accounts and View Generated PINs](#how-to-create-customer-accounts-and-view-generated-pins)
- [How Customers Log In and Perform Transactions](#how-customers-log-in-and-perform-transactions)
- [Code Organization](#code-organization)
- [File Structure](#file-structure)
- [Troubleshooting](#troubleshooting)
- [Security Notes](#security-notes)

---

## How to Compile and Run the System

### Compilation (Windows with g++)

```bash
g++ -o bank_system main.cpp
```

### Running the System

```bash
./bank_system.exe
```

Or simply:

```bash
./bank_system
```

---

## Default Teller Login Credentials

The system comes with one default teller account:

| Username | Password | Role |
|----------|----------|------|
| admin    | admin123 | Manager/Teller |

> **Note:** On first run, you can log in with these credentials to access teller functions.

---

## How to Create Customer Accounts and View Generated PINs

### As a Teller

1. Log in with teller credentials (`admin` / `admin123`)
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

### Viewing Customer PINs

- Tellers can view customer PINs through the "View Customer" option
- PINs are shown masked (e.g., `****`) for security
- Full PIN only displayed at time of account creation

---

## How Customers Log In and Perform Transactions

### Customer Login

1. Select "Customer Login" from main menu
2. Enter account number (provided by teller)
3. Enter 4-digit PIN (given at account creation)
4. If credentials valid, access customer menu

### Available Customer Transactions

| Option | Transaction | Description |
|--------|-------------|-------------|
| 1 | Check Balance | View current account balance |
| 2 | Deposit Money | Add funds to account |
| 3 | Withdraw Money | Remove funds (if sufficient balance) |
| 4 | Transfer Money | Send funds to another account |
| 5 | View Account Details | See personal information |
| 6 | Change PIN | Update security PIN |
| 7 | Exit | Log out of account |

### Transaction Limits

- **Minimum withdrawal:** R10
- **Maximum withdrawal:** R50,000 per transaction
- **Minimum deposit:** R10

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

| Account Type | Interest Rate |
|--------------|---------------|
| Savings | 4% |
| Fixed Deposit | 8% |
| Cheque | 2% |

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
├── main.cpp              # Main program source code
├── customers.dat         # Binary file storing customer records
├── customers.csv         # Exported customer data (CSV format)
├── customers.txt         # Exported customer data (text format)
├── tellers.dat           # Binary file storing teller records
├── transactions.dat     # Binary file storing transaction history
├── README.md             # This file (Markdown format)
└── README.txt            # Original README (Text format)
```

---

## Troubleshooting

### Common Issues

| Error Message | Cause | Solution |
|---------------|-------|----------|
| `Cannot open customers.dat` | File doesn't exist yet | Normal on first run; will be created when first customer is added |
| `Invalid PIN` | Wrong account number or PIN | Check credentials; contact teller for help |
| `Insufficient funds` | Withdrawal amount exceeds balance | Reduce withdrawal amount |
| `Account not found` | Invalid account number | Verify account number with teller |

### Getting Help

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