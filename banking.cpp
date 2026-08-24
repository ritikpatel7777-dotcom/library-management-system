#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <ctime>

using namespace std;

// =====================================================
// HELPER FUNCTION
// =====================================================

string getCurrentDateTime() {
    time_t now = time(nullptr);
    tm *localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_mday << "/"
       << setw(2) << localTime->tm_mon + 1 << "/"
       << localTime->tm_year + 1900
       << " "
       << setw(2) << localTime->tm_hour << ":"
       << setw(2) << localTime->tm_min;

    return ss.str();
}


// =====================================================
// TRANSACTION CLASS
// =====================================================

class Transaction {

private:
    int transactionId;
    long long accountNumber;
    string type;
    double amount;
    string details;
    string date;

public:

    Transaction() {
        transactionId = 0;
        accountNumber = 0;
        amount = 0;
    }

    Transaction(
        int id,
        long long accNo,
        string t,
        double a,
        string d,
        string dt
    ) {
        transactionId = id;
        accountNumber = accNo;
        type = t;
        amount = a;
        details = d;
        date = dt;
    }

    int getId() const {
        return transactionId;
    }

    long long getAccountNumber() const {
        return accountNumber;
    }

    string getType() const {
        return type;
    }

    double getAmount() const {
        return amount;
    }

    string getDetails() const {
        return details;
    }

    string getDate() const {
        return date;
    }

    void display() const {

        cout << "\n----------------------------------------";
        cout << "\nTransaction ID : " << transactionId;
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nType           : " << type;
        cout << "\nAmount         : Rs. "
             << fixed << setprecision(2)
             << amount;
        cout << "\nDetails        : " << details;
        cout << "\nDate           : " << date;
        cout << "\n----------------------------------------\n";
    }
};


// =====================================================
// ACCOUNT CLASS
// =====================================================

class Account {

private:

    long long accountNumber;
    string name;
    string phone;
    string pin;
    double balance;

public:

    Account() {
        accountNumber = 0;
        balance = 0;
    }

    Account(
        long long accNo,
        string n,
        string ph,
        string p,
        double bal
    ) {
        accountNumber = accNo;
        name = n;
        phone = ph;
        pin = p;
        balance = bal;
    }

    long long getAccountNumber() const {
        return accountNumber;
    }

    string getName() const {
        return name;
    }

    string getPhone() const {
        return phone;
    }

    string getPin() const {
        return pin;
    }

    double getBalance() const {
        return balance;
    }

    bool verifyPIN(string enteredPin) const {
        return pin == enteredPin;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {

        if (amount <= 0 || amount > balance) {
            return false;
        }

        balance -= amount;

        return true;
    }

    void displayAccount() const {

        cout << "\n========================================";
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nName           : " << name;
        cout << "\nPhone          : " << phone;
        cout << "\nBalance        : Rs. "
             << fixed << setprecision(2)
             << balance;
        cout << "\n========================================\n";
    }
};


// =====================================================
// BANK CLASS
// =====================================================

class Bank {

private:

    vector<Account> accounts;
    vector<Transaction> transactions;

    long long nextAccountNumber;
    int nextTransactionId;

public:

    Bank() {

        nextAccountNumber = 100001;
        nextTransactionId = 1;

        loadAccounts();
        loadTransactions();
    }


    // =================================================
    // SAVE ACCOUNTS
    // =================================================

    void saveAccounts() {

        ofstream file("accounts.txt");

        if (!file) {
            cout << "\nError opening accounts file!\n";
            return;
        }

        for (const auto &account : accounts) {

            file << account.getAccountNumber() << "|"
                 << account.getName() << "|"
                 << account.getPhone() << "|"
                 << account.getPin() << "|"
                 << fixed << setprecision(2)
                 << account.getBalance()
                 << "\n";
        }

        file.close();
    }


    // =================================================
    // LOAD ACCOUNTS
    // =================================================

    void loadAccounts() {

        ifstream file("accounts.txt");

        if (!file) {
            return;
        }

        string line;

        while (getline(file, line)) {

            stringstream ss(line);

            string accNo;
            string name;
            string phone;
            string pin;
            string balance;

            getline(ss, accNo, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, pin, '|');
            getline(ss, balance, '|');

            if (!accNo.empty()) {

                long long number = stoll(accNo);
                double bal = stod(balance);

                accounts.push_back(
                    Account(
                        number,
                        name,
                        phone,
                        pin,
                        bal
                    )
                );

                if (number >= nextAccountNumber) {
                    nextAccountNumber = number + 1;
                }
            }
        }

        file.close();
    }


    // =================================================
    // SAVE TRANSACTIONS
    // =================================================

    void saveTransactions() {

        ofstream file("transactions.txt");

        if (!file) {
            cout << "\nError opening transaction file!\n";
            return;
        }

        for (const auto &transaction : transactions) {

            file << transaction.getId() << "|"
                 << transaction.getAccountNumber() << "|"
                 << transaction.getType() << "|"
                 << transaction.getAmount() << "|"
                 << transaction.getDetails() << "|"
                 << transaction.getDate()
                 << "\n";
        }

        file.close();
    }


    // =================================================
    // LOAD TRANSACTIONS
    // =================================================

    void loadTransactions() {

        ifstream file("transactions.txt");

        if (!file) {
            return;
        }

        string line;

        while (getline(file, line)) {

            stringstream ss(line);

            string id;
            string accountNumber;
            string type;
            string amount;
            string details;
            string date;

            getline(ss, id, '|');
            getline(ss, accountNumber, '|');
            getline(ss, type, '|');
            getline(ss, amount, '|');
            getline(ss, details, '|');
            getline(ss, date, '|');

            if (!id.empty()) {

                int transactionId = stoi(id);
                long long accNo = stoll(accountNumber);
                double transactionAmount = stod(amount);

                transactions.push_back(
                    Transaction(
                        transactionId,
                        accNo,
                        type,
                        transactionAmount,
                        details,
                        date
                    )
                );

                if (transactionId >= nextTransactionId) {
                    nextTransactionId =
                        transactionId + 1;
                }
            }
        }

        file.close();
    }


    // =================================================
    // FIND ACCOUNT
    // =================================================

    Account* findAccount(long long accountNumber) {

        for (auto &account : accounts) {

            if (
                account.getAccountNumber()
                == accountNumber
            ) {
                return &account;
            }
        }

        return nullptr;
    }


    // =================================================
    // CREATE ACCOUNT
    // =================================================

    void createAccount() {

        string name;
        string phone;
        string pin;

        double initialDeposit;

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        cout << "\n========== CREATE ACCOUNT ==========\n";

        cout << "Enter Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "\nName cannot be empty!\n";
            return;
        }

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        if (phone.empty()) {
            cout << "\nPhone number cannot be empty!\n";
            return;
        }

        cout << "Create 4-digit PIN: ";
        cin >> pin;

        if (pin.length() != 4) {
            cout << "\nPIN must contain exactly 4 digits!\n";
            return;
        }

        for (char c : pin) {

            if (!isdigit(c)) {

                cout << "\nPIN must contain only digits!\n";
                return;
            }
        }

        cout << "Enter Initial Deposit: ";
        cin >> initialDeposit;

        if (initialDeposit < 0) {

            cout << "\nInvalid deposit amount!\n";
            return;
        }

        long long accountNumber =
            nextAccountNumber++;

        accounts.push_back(
            Account(
                accountNumber,
                name,
                phone,
                pin,
                initialDeposit
            )
        );

        saveAccounts();

        cout << "\n========================================";
        cout << "\n       ACCOUNT CREATED SUCCESSFULLY";
        cout << "\n========================================";
        cout << "\nAccount Number : "
             << accountNumber;
        cout << "\nName           : "
             << name;
        cout << "\nBalance        : Rs. "
             << fixed << setprecision(2)
             << initialDeposit;
        cout << "\n========================================\n";
    }


    // =================================================
    // LOGIN
    // =================================================

    Account* customerLogin() {

        long long accountNumber;
        string pin;

        cout << "\n========== CUSTOMER LOGIN ==========\n";

        cout << "Account Number: ";
        cin >> accountNumber;

        cout << "PIN: ";
        cin >> pin;

        Account *account =
            findAccount(accountNumber);

        if (account == nullptr) {

            cout << "\nAccount not found!\n";
            return nullptr;
        }

        if (!account->verifyPIN(pin)) {

            cout << "\nIncorrect PIN!\n";
            return nullptr;
        }

        cout << "\nLogin successful!\n";

        return account;
    }


    // =================================================
    // ADD TRANSACTION
    // =================================================

    void addTransaction(
        long long accountNumber,
        string type,
        double amount,
        string details
    ) {

        transactions.push_back(
            Transaction(
                nextTransactionId++,
                accountNumber,
                type,
                amount,
                details,
                getCurrentDateTime()
            )
        );

        saveTransactions();
    }


    // =================================================
    // BALANCE
    // =================================================

    void balanceInquiry(Account *account) {

        cout << "\n========== BALANCE INQUIRY ==========\n";

        cout << "Account Number : "
             << account->getAccountNumber();

        cout << "\nAccount Holder : "
             << account->getName();

        cout << "\nAvailable Balance : Rs. "
             << fixed << setprecision(2)
             << account->getBalance()
             << "\n";
    }


    // =================================================
    // DEPOSIT
    // =================================================

    void deposit(Account *account) {

        double amount;

        cout << "\nEnter deposit amount: ";
        cin >> amount;

        if (amount <= 0) {

            cout << "\nAmount must be greater than zero!\n";
            return;
        }

        account->deposit(amount);

        addTransaction(
            account->getAccountNumber(),
            "DEPOSIT",
            amount,
            "Cash deposited"
        );

        saveAccounts();

        cout << "\nDeposit successful!";
        cout << "\nAmount : Rs. "
             << fixed << setprecision(2)
             << amount;
        cout << "\nBalance: Rs. "
             << account->getBalance()
             << "\n";
    }


    // =================================================
    // WITHDRAW
    // =================================================

    void withdraw(Account *account) {

        double amount;

        cout << "\nEnter withdrawal amount: ";
        cin >> amount;

        if (amount <= 0) {

            cout << "\nInvalid amount!\n";
            return;
        }

        if (
            account->getBalance()
            < amount
        ) {

            cout << "\nInsufficient balance!\n";
            return;
        }

        account->withdraw(amount);

        addTransaction(
            account->getAccountNumber(),
            "WITHDRAW",
            amount,
            "Cash withdrawn"
        );

        saveAccounts();

        cout << "\nWithdrawal successful!";
        cout << "\nAmount : Rs. "
             << fixed << setprecision(2)
             << amount;
        cout << "\nBalance: Rs. "
             << account->getBalance()
             << "\n";
    }


    // =================================================
    // FUND TRANSFER
    // =================================================

    void transfer(Account *sender) {

        long long receiverNumber;
        double amount;

        cout << "\nEnter Receiver Account Number: ";
        cin >> receiverNumber;

        if (
            receiverNumber
            == sender->getAccountNumber()
        ) {

            cout << "\nCannot transfer to your own account!\n";
            return;
        }

        Account *receiver =
            findAccount(receiverNumber);

        if (receiver == nullptr) {

            cout << "\nReceiver account not found!\n";
            return;
        }

        cout << "Enter Transfer Amount: ";
        cin >> amount;

        if (amount <= 0) {

            cout << "\nInvalid amount!\n";
            return;
        }

        if (
            sender->getBalance()
            < amount
        ) {

            cout << "\nInsufficient balance!\n";
            return;
        }

        sender->withdraw(amount);
        receiver->deposit(amount);

        string senderDetails =
            "Transfer to Account " +
            to_string(receiverNumber);

        string receiverDetails =
            "Transfer received from Account " +
            to_string(
                sender->getAccountNumber()
            );

        addTransaction(
            sender->getAccountNumber(),
            "TRANSFER_SENT",
            amount,
            senderDetails
        );

        addTransaction(
            receiver->getAccountNumber(),
            "TRANSFER_RECEIVED",
            amount,
            receiverDetails
        );

        saveAccounts();

        cout << "\n========================================";
        cout << "\n       TRANSFER SUCCESSFUL";
        cout << "\n========================================";
        cout << "\nAmount : Rs. "
             << fixed << setprecision(2)
             << amount;
        cout << "\nTo     : "
             << receiverNumber;
        cout << "\nBalance: Rs. "
             << sender->getBalance();
        cout << "\n========================================\n";
    }


    // =================================================
    // TRANSACTION HISTORY
    // =================================================

    void transactionHistory(Account *account) {

        bool found = false;

        cout << "\n========== TRANSACTION HISTORY ==========\n";

        for (const auto &transaction : transactions) {

            if (
                transaction.getAccountNumber()
                == account->getAccountNumber()
            ) {

                transaction.display();

                found = true;
            }
        }

        if (!found) {

            cout << "\nNo transactions found.\n";
        }
    }


    // =================================================
    // RECEIPT GENERATION
    // =================================================

    void generateReceipt(
        Account *account,
        string operation,
        double amount
    ) {

        ofstream file(
            "receipts.txt",
            ios::app
        );

        if (!file) {

            cout << "\nUnable to generate receipt!\n";
            return;
        }

        file << "\n========================================\n";
        file << "          BANK TRANSACTION RECEIPT\n";
        file << "========================================\n";

        file << "Date           : "
             << getCurrentDateTime()
             << "\n";

        file << "Account Number : "
             << account->getAccountNumber()
             << "\n";

        file << "Account Holder : "
             << account->getName()
             << "\n";

        file << "Operation      : "
             << operation
             << "\n";

        file << "Amount         : Rs. "
             << fixed << setprecision(2)
             << amount
             << "\n";

        file << "Balance        : Rs. "
             << account->getBalance()
             << "\n";

        file << "========================================\n";

        file.close();

        cout << "\nReceipt generated successfully!";
        cout << "\nSaved in: receipts.txt\n";
    }


    // =================================================
    // INTEREST CALCULATION
    // =================================================

    void calculateInterest(Account *account) {

        double annualRate;

        cout << "\nEnter annual interest rate (%): ";
        cin >> annualRate;

        if (annualRate < 0) {

            cout << "\nInvalid interest rate!\n";
            return;
        }

        double interest =
            account->getBalance()
            * annualRate
            / 100.0;

        cout << "\n========== INTEREST CALCULATION ==========\n";

        cout << "Current Balance : Rs. "
             << fixed << setprecision(2)
             << account->getBalance();

        cout << "\nInterest Rate   : "
             << annualRate << "%";

        cout << "\nEstimated Interest: Rs. "
             << interest;

        cout << "\nEstimated Amount : Rs. "
             << account->getBalance()
                + interest
             << "\n";
    }


    // =================================================
    // ATM SIMULATION
    // =================================================

    void atmSimulation(Account *account) {

        int choice;

        do {

            cout << "\n========================================";
            cout << "\n              ATM SIMULATION";
            cout << "\n========================================";

            cout << "\n1. Check Balance";
            cout << "\n2. Withdraw Cash";
            cout << "\n3. Deposit Cash";
            cout << "\n4. Mini Statement";
            cout << "\n5. Exit ATM";

            cout << "\n\nEnter choice: ";
            cin >> choice;

            switch (choice) {

            case 1:
                balanceInquiry(account);
                break;

            case 2:
                withdraw(account);
                break;

            case 3:
                deposit(account);
                break;

            case 4:
                transactionHistory(account);
                break;

            case 5:
                cout << "\nExiting ATM...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
            }

        } while (choice != 5);
    }


    // =================================================
    // USER MENU
    // =================================================

    void userMenu(Account *account) {

        int choice;

        do {

            cout << "\n========================================";
            cout << "\n             CUSTOMER DASHBOARD";
            cout << "\n========================================";

            cout << "\n1. Account Details";
            cout << "\n2. Balance Inquiry";
            cout << "\n3. Deposit";
            cout << "\n4. Withdraw";
            cout << "\n5. Fund Transfer";
            cout << "\n6. Transaction History";
            cout << "\n7. Generate Receipt";
            cout << "\n8. Calculate Interest";
            cout << "\n9. ATM Simulation";
            cout << "\n10. Logout";

            cout << "\n\nEnter choice: ";
            cin >> choice;

            switch (choice) {

            case 1:
                account->displayAccount();
                break;

            case 2:
                balanceInquiry(account);
                break;

            case 3: {

                double oldBalance =
                    account->getBalance();

                deposit(account);

                if (
                    account->getBalance()
                    > oldBalance
                ) {

                    generateReceipt(
                        account,
                        "DEPOSIT",
                        account->getBalance()
                        - oldBalance
                    );
                }

                break;
            }

            case 4: {

                double oldBalance =
                    account->getBalance();

                withdraw(account);

                if (
                    account->getBalance()
                    < oldBalance
                ) {

                    generateReceipt(
                        account,
                        "WITHDRAW",
                        oldBalance
                        - account->getBalance()
                    );
                }

                break;
            }

            case 5:
                transfer(account);
                break;

            case 6:
                transactionHistory(account);
                break;

            case 7: {

                double amount;

                cout << "\nEnter receipt amount: ";
                cin >> amount;

                if (amount > 0) {

                    generateReceipt(
                        account,
                        "GENERAL TRANSACTION",
                        amount
                    );
                }

                break;
            }

            case 8:
                calculateInterest(account);
                break;

            case 9:
                atmSimulation(account);
                break;

            case 10:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
            }

        } while (choice != 10);
    }


    // =================================================
    // ADMIN LOGIN
    // =================================================

    bool adminLogin() {

        string username;
        string password;

        cout << "\n========== ADMIN LOGIN ==========\n";

        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        return (
            username == "admin"
            &&
            password == "admin123"
        );
    }


    // =================================================
    // VIEW ALL ACCOUNTS
    // =================================================

    void viewAllAccounts() const {

        if (accounts.empty()) {

            cout << "\nNo accounts available.\n";
            return;
        }

        cout << "\n========== ALL ACCOUNTS ==========\n";

        for (const auto &account : accounts) {

            account.displayAccount();
        }
    }


    // =================================================
    // VIEW ALL TRANSACTIONS
    // =================================================

    void viewAllTransactions() const {

        if (transactions.empty()) {

            cout << "\nNo transactions available.\n";
            return;
        }

        cout << "\n========== ALL TRANSACTIONS ==========\n";

        for (const auto &transaction : transactions) {

            transaction.display();
        }
    }


    // =================================================
    // TOTAL BANK BALANCE
    // =================================================

    void totalBankBalance() const {

        double total = 0;

        for (const auto &account : accounts) {

            total += account.getBalance();
        }

        cout << "\nTotal Bank Balance: Rs. "
             << fixed << setprecision(2)
             << total
             << "\n";
    }


    // =================================================
    // ADMIN MENU
    // =================================================

    void adminMenu() {

        int choice;

        do {

            cout << "\n========================================";
            cout << "\n             ADMIN DASHBOARD";
            cout << "\n========================================";

            cout << "\n1. View All Accounts";
            cout << "\n2. View All Transactions";
            cout << "\n3. Total Bank Balance";
            cout << "\n4. Logout";

            cout << "\n\nEnter choice: ";
            cin >> choice;

            switch (choice) {

            case 1:
                viewAllAccounts();
                break;

            case 2:
                viewAllTransactions();
                break;

            case 3:
                totalBankBalance();
                break;

            case 4:
                cout << "\nLogging out...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
            }

        } while (choice != 4);
    }
};


// =====================================================
// MAIN FUNCTION
// =====================================================

int main() {

    Bank bank;

    int choice;

    do {

        cout << "\n\n============================================";
        cout << "\n        BANKING MANAGEMENT SYSTEM";
        cout << "\n============================================";

        cout << "\n1. Create Account";
        cout << "\n2. Customer Login";
        cout << "\n3. Admin Login";
        cout << "\n4. Exit";

        cout << "\n\nEnter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:

            bank.createAccount();

            break;


        case 2: {

            Account *account =
                bank.customerLogin();

            if (account != nullptr) {

                bank.userMenu(account);
            }

            break;
        }


        case 3:

            if (bank.adminLogin()) {

                cout << "\nAdmin login successful!\n";

                bank.adminMenu();

            } else {

                cout << "\nInvalid admin credentials!\n";
            }

            break;


        case 4:

            cout << "\nThank you for using "
                 << "Banking Management System!\n";

            break;  


        default:

            cout << "\nInvalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}