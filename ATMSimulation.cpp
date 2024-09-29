#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h> 

using namespace std;

// Structure to represent an ATM account
struct ATMCard {
    int accountNumber;
    string accountName;
    string birthday;
    string contactNumber;
    double balance;
    int pinCode;
};

struct Transaction {
    string description;
    double amount;
};

int generateRandomAccountNumber() {
    // Generate a random 5-digit account number
    return 10000 + rand() % 90000;
}

// Function to save accounts to a file
void saveAccounts(const vector<ATMCard>& accounts) {
    ofstream fileptr("D:/Accounts.txt");
    if (fileptr.is_open()) {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        struct tm* timeinfo;
        timeinfo = localtime(&now);
        char timestamp[80];
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

        // Generate a random 6-digit trace number
        int traceNumber = rand() % 900000 + 100000;

        for (const ATMCard& account : accounts) {
            fileptr << "Date&Time: " << timestamp << " \nLocation: Your ATM Location" << " \nAcc No.: *****" << account.accountNumber % 10000 << " \nBalance: Php. " << account.balance << " \nTrace No: " << traceNumber << endl;
        }
        fileptr.close();
    } else {
        cout << "Error: Unable to save the accounts." << endl;
    }
}

void loadAccounts(vector<ATMCard>& accounts) {
    ifstream fileptr("D:/Accounts.txt");
    if (!fileptr) {
        return; // File doesn't exist, or an error occurred.
    }

    ATMCard account;
    while (fileptr >> account.accountNumber >> account.balance) {
        accounts.push_back(account);
    }
    fileptr.close();
}

// Function to create a new account
void registerAccount(vector<ATMCard>& accounts) {
    system("cls");
    ATMCard newAccount;

    newAccount.accountNumber = generateRandomAccountNumber(); // Generate a random account number
    cout << "Generated Account Number: " << newAccount.accountNumber << endl;
    cout << "Enter Account Name: ";
    cin >> newAccount.accountName;
    cout << "MM/D/YYYY" << "\n" << "Enter Birthday: ";
    cin >> newAccount.birthday;
    cout << "Enter Contact Number: ";
    cin >> newAccount.contactNumber;
    cout << "Enter Initial Deposit (Min. 5000): ";
    cin >> newAccount.balance;

    while (newAccount.balance < 5000) {
        cout << "The minimum initial deposit is 5000" << endl;
        cout << "Enter Initial Deposit (Min. 5000): ";
        cin >> newAccount.balance;
    }

    cout << "Enter PIN Code (MAX 6 digits): ";
    char pinBuffer[7]; // To store and display the masked PIN
    for (int i = 0; i < 6; i++) {
        char c = _getch(); // Read a character without displaying it
        if (c == '\r' || c == '\n') {
            break;
        } else if (c == '\b' && i > 0) {
            // Handle backspace
            cout << "\b \b"; // Clear the character from the console
            i -= 2; // Go back two positions (one for the backspace and one for the character to be erased)
        } else {
            cout << '*' ; // Display an asterisk
            pinBuffer[i] = c; // Store the actual PIN character
        }
    }
    pinBuffer[6] = '\0'; // Null-terminate the PIN buffer
    newAccount.pinCode = atoi(pinBuffer); // Convert the masked PIN to an integer

    while (newAccount.pinCode < 1000 || newAccount.pinCode > 999999) {
        cout<<endl << "Please enter a 4 to 6-digit PIN code" << endl;
        cout << "Enter PIN Code (MAX 6 digits): ";
        for (int i = 0; i < 6; i++) {
            char c = _getch();
            if (c == '\r' || c == '\n') {
                break;
            } else if (c == '\b' && i > 0) {
                cout << "\b \b";
                i -= 2;
            } else {
                cout << '*';
                pinBuffer[i] = c;
            }
        }
        pinBuffer[6] = '\0';
        newAccount.pinCode = atoi(pinBuffer);
    }

    // Add the new account to the list
    accounts.push_back(newAccount);
    saveAccounts(accounts); // Save accounts after registration
    cout <<endl<< "You have successfully created an account" << endl;
    system("pause");
}

// Function to authenticate a user
bool authenticateUser(const vector<ATMCard>& accounts, int accountNumber, int pinCode) {
    for (const ATMCard& account : accounts) {
        if (account.accountNumber == accountNumber && account.pinCode == pinCode) {
            return true;
        }
    }
    return false;
}

// Function to deposit (multiple of 100)
void deposit(vector<ATMCard>& accounts, int accountNumber, int pinCode) {
    // Authentication code (similar to what's already in the code)

    for (ATMCard& account : accounts) {
        if (account.accountNumber == accountNumber && account.pinCode == pinCode) {
            cout <<endl<< "Enter the deposit amount: ";
            double amount;
            cin >> amount;
            if (amount > 0 && (int)amount % 100 == 0) {
                account.balance += amount;
                cout << "Deposit successful. New balance: " << account.balance << endl;
                saveAccounts(accounts);  // Save the updated account data
            } else {
                cout << "Invalid deposit amount. The deposit must be a multiple of 100." << endl;
            }
            return;
        }
    }
    cout <<endl<< "Authentication failed. Access denied." << endl;
}


// Function to withdraw (multiple of 100)
void withdraw(vector<ATMCard>& accounts, int accountNumber, int pinCode) {
    // Authentication code (similar to what's already in the code)
    if (authenticateUser(accounts, accountNumber, pinCode))
    {
        for (ATMCard& account : accounts)
        {
            if (account.accountNumber == accountNumber && account.pinCode == pinCode)
            {
                cout <<endl<< "Enter the withdrawal amount: ";
                double amount;
                cin >> amount;
                if ((int)amount % 100 == 0 && amount <= account.balance) // Corrected this line
                {
                    account.balance -= amount;
                    cout << "Withdrawal successful. New balance: " << account.balance << endl;
                    saveAccounts(accounts);  // Save the updated account data
                }
                else
                {
                    cout << "Invalid withdrawal amount or insufficient funds. The withdrawal must be a multiple of 100." << endl;
                }
                return;
            }
        }
    }
    else
    {
        cout<<endl << "Authentication failed. Access denied." << endl;
    }
}

// Function to change PIN code
void changePin(vector<ATMCard>& accounts, int accountNumber, int oldPin) {
    // Authentication code (similar to what's already in the code)
    if (authenticateUser(accounts, accountNumber, oldPin))
    {
        for (ATMCard& account : accounts) {
            if (account.accountNumber == accountNumber && account.pinCode == oldPin) {
                cout <<endl<< "Enter your new PIN code: ";
                char newPinBuffer[7]; // To store and display the masked new PIN
                for (int i = 0; i < 6; i++) {
                    char c = _getch(); // Read a character without displaying it
                    if (c == '\r' || c == '\n') {
                        break;
                    } else if (c == '\b' && i > 0) {
                        // Handle backspace
                        cout << "\b \b"; // Clear the character from the console
                        i -= 1; // Go back one position
                    } else {
                        cout << '*'; // Display an asterisk
                        newPinBuffer[i] = c; // Store the actual new PIN character
                    }
                }
                newPinBuffer[6] = '\0'; // Null-terminate the new PIN buffer
                int newPin = atoi(newPinBuffer); // Convert the masked new PIN to an integer

                // Update the account's PIN here
                account.pinCode = newPin;

                cout<<endl << "PIN code changed successfully." << endl;
                system("pause");
                return;
            }
        }
        }else{
        cout<<endl << "Authentication failed. Access denied." << endl;
        }
    }



int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator with current time
    vector<ATMCard> accounts;

    // Load existing accounts from the file
    loadAccounts(accounts);

    bool flashDriveInserted = false;

    while (!flashDriveInserted) {
        cout << "Please insert the flash drive (Drive D) to continue." << endl;

        // Specify the drive letter for your flash drive
        char flashDriveLetter = 'D';

        // Loop to repeatedly check for the presence of the drive
        while (true) {
            // Check if the drive is inserted
            if (GetLogicalDrives() & (1 << (flashDriveLetter - 'A'))) {
                flashDriveInserted = true;
                break; // Break out of the loop when the drive is detected
            }

            // If the drive is not detected, wait for a moment and check again
            this_thread::sleep_for(chrono::seconds(1));
        }

        if (flashDriveInserted) {
            cout << "Flash drive detected. ATM system is now active." << endl;
        }
        system("pause");
    }

    int choice;
    int accountNumber;
    int pinCode;
    char pinBuffer[7]; // Declare pinBuffer once at the beginning of the main function

    do {
        system("cls");
        cout << "ATM Menu:" << endl;
        cout << "1. Register Account" << endl;
        cout << "2. Balance Inquiry" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Deposit" << endl;
        cout << "5. Change PIN Code" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                registerAccount(accounts);
                saveAccounts(accounts); // Save accounts after registration
                break;
                }
            case 2: {
                system("cls");
                cout << "Enter your account number: ";
                cin >> accountNumber;
                cout << "Enter your PIN code: ";
                for (int i = 0; i < 6; i++) {
                    char c = _getch(); // Read a character without displaying it
                    if (c == '\r' || c == '\n') {
                        break;
                    } else if (c == '\b' && i > 0) {
                        // Handle backspace
                        cout << "\b \b"; // Clear the character from the console
                        i -= 2; // Go back two positions (one for the backspace and one for the character to be erased)
                    } else {
                        cout << '*'; // Display an asterisk
                        pinBuffer[i] = c; // Store the actual PIN character
                    }
                }
                pinBuffer[6] = '\0'; // Null-terminate the PIN buffer
                pinCode = atoi(pinBuffer); // Convert the masked PIN to an integer

                if (authenticateUser(accounts, accountNumber, pinCode)) {
                    for (const ATMCard& account : accounts) {
                        if (account.accountNumber == accountNumber) {
                            cout <<endl<< "Account Number: " << account.accountNumber << endl;
                            cout << "Account Name: " << account.accountName << endl;
                            cout << "Balance: " << account.balance << endl;
                            break;
                        }
                    }
                } else {
                    cout<<endl << "Authentication failed. Access denied." << endl;
                }
                system("pause");
                break;
                }
            case 3: {
                system("cls");
                // Use pinBuffer without redeclaration
                cout << "Enter your account number: ";
                cin >> accountNumber;
                cout << "Enter your PIN code: ";


                for (int i = 0; i < 6; i++) {
                    char c= _getch(); // Read a character without displaying it
                    if (c == '\r' || c == '\n') {
                        break;
                    } else if (c == '\b' && i > 0) {
                        // Handle backspace
                        cout << "\b \b"; // Clear the character from the console
                        i -= 2; // Go back two positions (one for the backspace and one for the character to be erased)
                    } else {
                        cout << '*'; // Display an asterisk
                        pinBuffer[i] = c; // Store the actual PIN character
                    }
                }


                pinBuffer[6] = '\0'; // Null-terminate the PIN buffer
                pinCode = atoi(pinBuffer); // Convert the masked PIN to an integer
                withdraw(accounts, accountNumber, pinCode);  // Call the withdrawal function
                system("pause");
                break;
                }
            case 4: {
                system("cls");
                cout << "Enter your account number: ";
                cin >> accountNumber;
                cout << "Enter your PIN code: ";

                for (int i = 0; i < 6; i++) {
                    char c= _getch(); // Read a character without displaying it
                    if (c == '\r' || c == '\n') {
                        break;
                    } else if (c == '\b' && i > 0) {
                        // Handle backspace
                        cout << "\b \b"; // Clear the character from the console
                        i -= 2; // Go back two positions (one for the backspace and one for the character to be erased)
                    } else {
                        cout << '*'; // Display an asterisk
                        pinBuffer[i] = c; // Store the actual PIN character
                    }
                }
                pinBuffer[6] = '\0'; // Null-terminate the PIN buffer
                pinCode = atoi(pinBuffer); // Convert the masked PIN to an integer;

                deposit(accounts, accountNumber, pinCode);  // Call the deposit function
                system("pause");
                break;
                }
            case 5: {
                char c;
                system("cls");
                cout << "Enter your account number: ";
                cin >> accountNumber;

                // Enter the old PIN
                cout << "Enter your PIN code: ";
                char pinBuffer[7]; // To store and display the masked old PIN
                for (int i = 0; i < 6; i++) {
                    c = _getch(); // Read a character without displaying it
                    if (c == '\r' || c == '\n') {
                        break;
                    } else if (c == '\b' && i > 0) {
                        // Handle backspace
                        cout << "\b \b"; // Clear the character from the console
                        i -= 1; // Go back one position
                    } else {
                        cout << '*'; // Display an asterisk
                        pinBuffer[i] = c; // Store the actual old PIN character
                    }
                }
                pinBuffer[6] = '\0'; // Null-terminate the old PIN buffer
                int oldPin = atoi(pinBuffer); // Convert the masked old PIN to an integer

                changePin(accounts, accountNumber, oldPin);  // Call the change PIN function
                system("pause");
                break;

            }
            case 0: {
                cout << "Thank you for using the ATM. Goodbye!" << endl;
                break;
                }
            default:{
                cout << "Invalid choice. Please try again." << endl;
                system("pause");
            }
        }
        if (choice != 0) {
            system("pause");
        }
    } while (choice != 0);

    //return 0;
}
