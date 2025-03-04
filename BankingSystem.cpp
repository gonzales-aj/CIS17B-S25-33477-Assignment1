#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class BankAccount{
    private:
        string accountHolderName;
        int accountNumber;
        double balance;

    public:
    BankAccount(string name, double initialBalance) {
        accountHolderName = name;
        balance = (initialBalance >= 0) ? initialBalance : 0;
        accountNumber = 1;
    }

    void deposit(double amount) {
        try {
            if (amount <=0) {
                throw invalid_argument("Deposit must be at least $1");
            }
            balance += amount;
            cout << "Deposit successful. New balance: $" << balance << "\n";
        } catch (const exception &e){
            cout << "Error: " << e.what() << "\n";
        }
    }

    void withdraw(double amount){
        try {
            if (amount <=0) {
                throw invalid_argument("You must withdraw at least $1");
            }
            if (amount > balance) {
                throw invalid_argument("Not enough funds");
            }
            balance -= amount;
            cout << "Withdrawal successful. New balance: $" << balance << "\n";
        } catch (const exception &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    void displayAccount() const {
        cout << "\nAccount holder name: " << accountHolderName;
        cout << "\nAccount number: " << accountNumber;
        cout << "\nAccount balance: $" << balance << "\n";
    }
};

void clearInputBuffer() {           // Handle invalid user input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void handleDeposit(BankAccount &account) {
    double amount;
    cout << "\nEnter deposit amount: ";
    if (!(cin >> amount)) {
        cout << "Invalid input.\n";
        clearInputBuffer();
        return;
    }
    account.deposit(amount);
}

void handleWithdrawal(BankAccount &account) {
    double amount;
    cout << "Enter withdrawal amount: ";
    if (!(cin >> amount)) {
        cout << "Invalid input.\n";
        clearInputBuffer();
        return;
    }
    account.withdraw(amount);
}

int main() {
    BankAccount *account = nullptr;
    int choice;
    string name;
    double initialBalance;

    do {        
        cout << "\nBank System:\n";
        cout << "1. Create account\n";
        cout << "2. Deposit money\n";
        cout << "3. Withdraw money\n";
        cout << "4. View account\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) { 
            cout << "Invalid input.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice) {
        case 1:             // Create account
            if (account) {
                cout << "An account already exists.\n";
            } else {
                cout << "Enter the account holder name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your initial balance: ";
                if (!(cin >> initialBalance) || initialBalance < 0) {
                        cout << "Invalid initial balance. Setting balance to $0.\n";
                        initialBalance = 0;
                        clearInputBuffer();
            }
            account = new BankAccount(name, initialBalance);
            cout << "Account created successfully.\n";
            }  break;
        case 2:             // Deposit money
            if (account) handleDeposit(*account);
            else cout << "Please create an account first.";
            break;
        case 3:             // Withdraw money
            if (account) handleWithdrawal(*account);
            else cout << "Please create an account first.";
            break;
        case 4:             // Display account
            if (account) account->displayAccount();
            else cout << "Please create an account first.";
            break;
        case 5:             // Close program
            cout << "Closing the bank system.";
            break;
        default:
            cout << "Invalid choice. Please select options 1-5.";
    } 
} while (choice != 5);

    delete account; // Clear memory
    return 0;
}