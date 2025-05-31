#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()
#include <map>
#include <iomanip>

using namespace std;

// Variabel global
string registeredUsername = "";
string registeredPassword = "";
double walletBalance = 0.0;
vector<string> transactionHistory;  // Save transaction history
map<string, double> expenseCategories; // Save categories and total expenses
vector<pair<string, double> > expenseHistory; // Save expense history (categories and amounts)
map<string, double> budgetCategories; // Save categories and monthly budget
map<string, double> spendingCategories; // Save expenses per category to compare with budget
double monthlyExpenses[12][5] = {
    {0, 0, 0, 0, 0}, // Januari
    {0, 0, 0, 0, 0}, // Februari
    {0, 0, 0, 0, 0}, // Maret
    {0, 0, 0, 0, 0}, // April
    {0, 0, 0, 0, 0}, // Mei
    {0, 0, 0, 0, 0}, // Juni
    {0, 0, 0, 0, 0}, // Juli
    {0, 0, 0, 0, 0}, // Agustus
    {0, 0, 0, 0, 0}, // September
    {0, 0, 0, 0, 0}, // Oktober
    {0, 0, 0, 0, 0}, // November
    {0, 0, 0, 0, 0}  // Desember
};
string categories[] = {"Food", "Entertainment", "Transport", "Utilities", "Others"};
// Subscription Management Constants
const int MAX_USERS = 100;
const int MAX_SUBSCRIPTIONS = 10;

// Array untuk menyimpan informasi pengguna
string users[MAX_USERS][2]; // [username, password]
map<string, int> usernameToUserID;

string subscriptions[MAX_USERS][MAX_SUBSCRIPTIONS][3]; // [name, cost, category]

// function for sign up
void signUp() {
    cout << "===== SIGN UP =====" << endl;
    if (usernameToUserID.size() >= MAX_USERS) {
        cout << "Maximum number of users reached. Cannot register more users." << endl;
        return;
    }

    string username, password;
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    int userID = usernameToUserID.size();
    users[userID][0] = username;
    users[userID][1] = password;
    usernameToUserID[username] = userID;

    cout << "Registration successful!" << endl;
    cout << "Please login." << endl << endl;
}

// Function for login
bool login(int &loggedInUserID) {
    string username, password;

    cout << "===== LOGIN =====" << endl;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (usernameToUserID.find(username) != usernameToUserID.end()) {
        int userID = usernameToUserID[username];
        if (users[userID][1] == password) {
            cout << "Login successful! Welcome, " << username << "!" << endl;
            loggedInUserID = userID;
            return true;
        }
    }

    cout << "Invalid username or password. Please try again." << endl;
    return false;
}

// Function to add funds to the wallet
void addFunds(double amount, int fundOption) {
    string source = (fundOption == 1) ? "Debit Card" : "Credit Card";
    walletBalance += amount;
    transactionHistory.push_back("Added $" + to_string(amount) + " from " + source);
    cout << "Funds added successfully from " << source << ". New Balance: $" << walletBalance << endl;
}

// Function to withdraw funds from the wallet
void withdrawFunds(double amount) {
    if (amount <= walletBalance) {
        walletBalance -= amount;
        transactionHistory.push_back("Withdrew $" + to_string(amount));
        cout << "Withdraw successful. New Balance: $" << walletBalance << endl;
    } else {
        cout << "Insufficient balance. Please try again." << endl;
    }
}

// Function for Wallet Management
void walletManagement() {
    int option;
    do {
        cout << "\n===== WALLET MANAGEMENT =====" << endl;
        cout << "1. View Balance" << endl;
        cout << "2. Add Funds" << endl;
        cout << "3. Withdraw Funds" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1) {
            // Password protection for "View Balance"
            string confirmPassword;
            cout << "Enter your password to view balance: ";
            cin >> confirmPassword;
            if (confirmPassword == registeredPassword) {
                cout << "Current Balance: $" << walletBalance << endl;
            } else {
                cout << "Incorrect password. Access denied." << endl;
            }
        } else if (option == 2) {
            // The process for "Add Funds" without password protection at the beginning
            int fundOption;
            cout << "Select funding source:" << endl;
            cout << "1. Debit Card" << endl;
            cout << "2. Credit Card" << endl;
            cout << "Enter your choice: ";
            cin >> fundOption;

            if (fundOption == 1 || fundOption == 2) {
                double amount;
                cout << "Enter amount to add: $";
                cin >> amount;
                if (amount > 0) {
                    // Password protection before transactions
                    string confirmPassword;
                    cout << "Enter your password to confirm transaction: ";
                    cin >> confirmPassword;
                    if (confirmPassword == registeredPassword) {
                        addFunds(amount, fundOption); // Call the function to add funds
                    } else {
                        cout << "Incorrect password. Transaction canceled." << endl;
                    }
                } else {
                    cout << "Invalid amount. Please try again." << endl;
                }
            } else {
                cout << "Invalid funding source. Please try again." << endl;
            }
        } else if (option == 3) {
            // The process for "Withdraw Funds" without password protection at the beginning
            double amount;
            cout << "Enter amount to withdraw: $";
            cin >> amount;
            if (amount > 0) {
                // Password protection before transactions
                string confirmPassword;
                cout << "Enter your password to confirm transaction: ";
                cin >> confirmPassword;
                if (confirmPassword == registeredPassword) {
                    withdrawFunds(amount); // Call the function to withdraw funds
                } else {
                    cout << "Incorrect password. Transaction canceled." << endl;
                }
            } else {
                cout << "Invalid amount. Please try again." << endl;
            }
        } else if (option == 4) {
            cout << "Returning to the main menu..." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 4);
}

void viewMonthlyTransactionHistory() {
    cout << "\n--- Monthly Transaction History ---" << endl;
    cout << "Month    ";
    for (const auto& category : categories) {
        cout << category << "   ";
    }
    cout << endl;

    for (int month = 0; month < 12; ++month) {
        cout << month + 1 << "        ";
        for (int category = 0; category < 5; ++category) {
            cout << monthlyExpenses[month][category] << "      ";
        }
        cout << endl;
    }
}


// Function for Transaction History
void transactionHistoryMenu() {
    int option;
    do {
        cout << "\n===== TRANSACTION HISTORY =====" << endl;
        cout << "1. View Transactions" << endl;
        cout << "2. Filter by Date" << endl;
        cout << "3. Download Transaction History" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1) {
            string confirmPassword;
            cout << "Enter your password to view transactions: ";
            cin >> confirmPassword;

            if (confirmPassword == registeredPassword) {
                cout << "\n--- Transaction History ---" << endl;
                if (transactionHistory.empty()) {
                    cout << "No transactions available." << endl;
                } else {
                    for (const auto& transaction : transactionHistory) {
                        cout << transaction << endl;
                    }
                }

                // Call the function to view monthly transaction history
                viewMonthlyTransactionHistory();
            } else {
                cout << "Password incorrect. Access denied." << endl;
            }
        } else if (option == 2) {
            cout << "Filtering by date not yet implemented." << endl;
        } else if (option == 3) {
            cout << "Transaction history downloaded (simulated)." << endl;
        } else if (option == 4) {
            cout << "Returning to the main menu..." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 4);
}

// Function for Payment Systems
void paymentSystemMenu() {
    int option;
    do {
        cout << "\n===== PAYMENT SYSTEM =====" << endl;
        cout << "1. Send Money" << endl;
        cout << "2. Receive Money" << endl;
        cout << "3. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1) {
            string recipientName;
            string confirmPassword;
            double amount;

            cout << "Enter recipient's name: ";
            cin >> recipientName;
            cout << "Enter amount to send: $";
            cin >> amount;
            cout << "Enter your password to confirm: ";
            cin >> confirmPassword;

            if (confirmPassword == registeredPassword) {
                if (amount > 0 && amount <= walletBalance) {
                    walletBalance -= amount;
                    transactionHistory.push_back("Sent $" + to_string(amount) + " to " + recipientName);
                    cout << "Money sent to " << recipientName << " successfully. New Balance: $" << walletBalance << endl;
                } else {
                    cout << "Invalid amount or insufficient balance. Please try again." << endl;
                }
            } else {
                cout << "Password incorrect. Transaction canceled." << endl;
            }

        } else if (option == 2) {
            string senderName;
            double amount;

            cout << "Enter sender's name: ";
            cin >> senderName;
            cout << "Enter amount to receive: $";
            cin >> amount;
            cout << "Enter sender's password to confirm the transfer: ";
            string senderPassword;
            cin >> senderPassword;  // Simulation of sending sender password input without verification

            if (amount > 0) {
                walletBalance += amount;
                transactionHistory.push_back("Received $" + to_string(amount) + " from " + senderName);
                cout << "Money received from " << senderName << " successfully. New Balance: $" << walletBalance << endl;
            } else {
                cout << "Invalid amount. Please try again." << endl;
            }

        } else if (option == 3) {
            cout << "Returning to the main menu..." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 3);
}

// Function to add expenses to the budget planner
void addExpenseToBudget(const string& category, double amount) {
    // Simple logic for adding expenses to the budget planner
    cout << "Expense of $" << amount << " added to budget for category: " << category << endl;
}

// Function to add expenses
void addExpense() {
    string category;
    double amount;
    int month;

    cout << "Enter expense category (e.g., Food, Entertainment, Transport, Utilities, Others): ";
    cin >> category;
    cout << "Enter amount: $";
    cin >> amount;
    cout << "Enter month (1-12): ";
    cin >> month;

    // Input validation for amount and month
    if (amount > 0 && month >= 1 && month <= 12) {
        expenseCategories[category] += amount;
        expenseHistory.push_back(std::make_pair(category, amount));
        addExpenseToBudget(category, amount);

        // Update monthly expenses array
        for (int i = 0; i < 5; ++i) {
            if (categories[i] == category) {
                monthlyExpenses[month - 1][i] += amount;
                break;
            }
        }

        cout << "Expense added successfully!" << endl;
    } else {
        cout << "Invalid amount or month. Please try again." << endl;
    }
}

// Function for expense analytics
void viewAnalytics() {
    double totalExpense = 0;
    int totalTransactions = expenseHistory.size();

    // Calculate total expenses
    for (const auto& entry : expenseHistory) {
        totalExpense += entry.second;
    }

    cout << "\n--- Expense Analytics ---" << endl;
    cout << "Total Expense: $" << totalExpense << endl;

    if (totalTransactions > 0) {
        double averageExpense = totalExpense / totalTransactions;
        cout << "Average Expense: $" << averageExpense << endl;
    } else {
        cout << "No transactions to analyze." << endl;
    }
}

// Function for Expense Tracking and Analytics Menu
void viewMonthlyReport() {
    cout << "Displaying Monthly Report..." << endl; // Detailed logic to display monthly reports
}

void expenseTrackingAndAnalyticsMenu() {
    int option;
    do {
        cout << "\n===== EXPENSE TRACKING AND ANALYTICS =====" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. View Monthly Report" << endl;
        cout << "3. View Analytics" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1) {
            addExpense();
        } else if (option == 2) {
            viewMonthlyReport();
        } else if (option == 3) {
            viewAnalytics();
        } else if (option == 4) {
            cout << "Returning to main menu..." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 4);
}

// Function to set a monthly budget
void setMonthlyBudget() {
    string category;
    double amount;

    cout << "Enter budget category (e.g., Food, Entertainment, Transport): ";
    cin >> category;
    cout << "Enter monthly budget amount for " << category << ": $";
    cin >> amount;

    if (amount > 0) {
        budgetCategories[category] = amount;
        cout << "Budget set successfully for " << category << " with an amount of $" << amount << endl;
    } else {
        cout << "Invalid amount. Please try again." << endl;
    }
}

// Function to view the current budget and expenses
void viewCurrentBudgetAndSpending() {
    cout << "\n--- Current Budget and Spending ---" << endl;
    if (budgetCategories.empty()) {
        cout << "No budget set. Please set a budget first." << endl;
        return;
    }

    for (const auto& entry : budgetCategories) {
        string category = entry.first;
        double budget = entry.second;
        double spent = spendingCategories[category];
        cout << "Category: " << category
             << ", Budget: $" << budget
             << ", Spent: $" << spent
             << ", Remaining: $" << (budget - spent) << endl;
    }
}

// Function to analyze budget usage
void analyzeBudgetUsage() {
    cout << "\n--- Budget Usage Analysis ---" << endl;
    if (budgetCategories.empty()) {
        cout << "No budget set. Please set a budget first." << endl;
        return;
    }

    for (const auto& entry : budgetCategories) {
        string category = entry.first;
        double budget = entry.second;
        double spent = spendingCategories[category];
        double usagePercent = (spent / budget) * 100;

        cout << "Category: " << category
             << ", Budget Usage: " << usagePercent << "%";

        if (usagePercent > 100) {
            cout << " (Over Budget)";
        }
        cout << endl;
    }
}

// Function to display the Budget Planner menu
void budgetPlannerMenu() {
    int option;
    do {
        cout << "\n===== BUDGET PLANNER =====" << endl;
        cout << "1. Set Monthly Budget" << endl;
        cout << "2. View Current Budget and Spending" << endl;
        cout << "3. Analyze Budget Usage" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1) {
            setMonthlyBudget();
        } else if (option == 2) {
            viewCurrentBudgetAndSpending();
        } else if (option == 3) {
            analyzeBudgetUsage();
        } else if (option == 4) {
            cout << "Returning to the main menu..." << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 4);
}

// Function to add new subscriptions
void addSubscription(int userID) {
    int subscriptionID = -1;

    cout << "\n=== Add New Subscription for User " << users[userID][0] << " ===\n";

    // Find an empty slot
    for (int i = 0; i < MAX_SUBSCRIPTIONS; i++) {
        if (subscriptions[userID][i][0].empty()) {
            subscriptionID = i;
            break;
        }
    }

    if (subscriptionID == -1) {
        cout << "Sorry, the maximum number of subscriptions has been reached for this user.\n";
        return;
    }

    // Input subscription data
    cout << "Enter subscription name (e.g., Netflix, Spotify): ";
    cin.ignore(); // Remove the buffer 
    getline(cin, subscriptions[userID][subscriptionID][0]);

    cout << "Enter monthly cost: ";
    cin >> subscriptions[userID][subscriptionID][1];
    cin.ignore(); // Remove the buffer after entering numbers

    cout << "Enter subscription category (e.g., Entertainment, Music, Education): ";
    getline(cin, subscriptions[userID][subscriptionID][2]);

    cout << "Subscription " << subscriptions[userID][subscriptionID][0]
         << " added successfully with a monthly cost of "
         << subscriptions[userID][subscriptionID][1] << ".\n";
}

// Function to display all subscriptions
void displaySubscriptions(int userID) {
    cout << "\n=== Subscription List for User " << users[userID][0] << " ===\n";

    bool hasSubscriptions = false;
    double totalCost = 0;

    for (int i = 0; i < MAX_SUBSCRIPTIONS; i++) {
        if (!subscriptions[userID][i][0].empty()) {
            hasSubscriptions = true;
            cout << i + 1 << ". Name: " << subscriptions[userID][i][0]
                 << ", Monthly Cost: " << subscriptions[userID][i][1]
                 << ", Category: " << subscriptions[userID][i][2] << endl;

            // Add the monthly fee to the total
            totalCost += stod(subscriptions[userID][i][1]);
        }
    }

    if (!hasSubscriptions) {
        cout << "No subscriptions registered yet.\n";
    } else {
        cout << fixed << setprecision(2);
        cout << "Total monthly subscription cost: " << totalCost << endl;
    }
}

// Function to delete service
void deleteSubscription(int userID) {
    cout << "\n=== Delete Subscription for User " << users[userID][0] << " ===\n";
    displaySubscriptions(userID);

    int subID;
    cout << "Enter the subscription number to delete (or 0 to cancel): ";
    cin >> subID;

    if (subID == 0) {
        cout << "Cancellation confirmed. Returning to menu.\n";
        return;
    }

    if (subID < 1 || subID > MAX_SUBSCRIPTIONS || subscriptions[userID][subID - 1][0].empty()) {
        cout << "Invalid subscription number.\n";
        return;
    }

    // Empty slot 
    subscriptions[userID][subID - 1][0].clear();
    subscriptions[userID][subID - 1][1].clear();
    subscriptions[userID][subID - 1][2].clear();

    cout << "Subscription deleted successfully.\n";
}

// Function to manage subscriptions
void subscriptionsManager(int userID) {
    int option;
    do {
        cout << "\n=== SUBSCRIPTIONS MANAGER ===\n";
        cout << "1. Add New Subscription\n";
        cout << "2. View All Subscriptions\n";
        cout << "3. Delete Subscription\n";
        cout << "4. Back to Main Menu\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1:
                addSubscription(userID);
                break;
            case 2:
                displaySubscriptions(userID);
                break;
            case 3:
                deleteSubscription(userID);
                break;
            case 4:
                cout << "Returning to the main menu.\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (option != 4);
}

// Function to display menu after login
void postLoginMenu(int userID) {
    int option;
    do {
        cout << "\n===== POST-LOGIN MENU =====" << endl;
        cout << "1. Wallet Management" << endl;
        cout << "2. Transaction History" << endl;
        cout << "3. Payment System" << endl;
        cout << "4. Expense Tracking and Analytics" << endl;
        cout << "5. Budget Planner" << endl;
        cout << "6. Subscriptions Manager" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1:
                walletManagement();
                break;
            case 2:
                transactionHistoryMenu();
                break;
            case 3:
                paymentSystemMenu();
                break;
            case 4:
                expenseTrackingAndAnalyticsMenu();
                break;
            case 5:
                budgetPlannerMenu();
                break;
            case 6:
                subscriptionsManager(userID);
                break;
            case 7:
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (option != 7);
}

// Main function (Main Menu)
int main() {
    int loggedInUserID = -1;
    srand(time(0));

    int choice;
    bool loginSuccess = false;

    do {
        cout << "\n===== USER REGISTRATION =====" << endl;
        cout << "1. Sign Up" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                signUp();
                break;
            case 2:
                loginSuccess = login(loggedInUserID);
                if(loginSuccess) {
                    postLoginMenu(loggedInUserID);
                }
                break;
            case 3:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
