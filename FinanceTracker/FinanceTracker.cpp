/**
*
* Solution to course project # 3
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Aleksandar Kostov
* @idnumber 8MI0600611
* @compiler VC
*
* <file with helper functions>
*
*/


#include <iostream>
const int MONTHS = 12;
const int ACCOUNT_ROWS = 2;
const int INCOME_INDEX = 0;
const int EXPENSE_INDEX = 1;
const int MAX_STR = 64;
const double EMPTY = -1.0;

const char* MONTH_NAMES[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

void invalidateProfile(double profile[ACCOUNT_ROWS][MONTHS]) {
    for (int i = 0; i < ACCOUNT_ROWS; i++) {
        for (int j = 0; j < MONTHS; j++) {
            profile[i][j] = EMPTY;
        }
    }
}

bool areEqual(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

void printMenu() {
    std::cout << "\nAvailable commands: add, report, search <month>, sort <type>, forecast <monthsAhead>, chart, exit" << std::endl;
}
void addEntry(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {
    int month;
    std::cout << "Month: ";
    std::cin >> month;

    if (month < 1 || month > activeMonths) {
        std::cout << "Invalid month number! Please use 1 to " << activeMonths << "." << std::endl;
        std::cin.ignore(1000, '\n');
        return;
    }


    int idx = month - 1;
    double inputIncome, inputExpense;

    std::cout << "Enter income: ";
    std::cin >> inputIncome;
    std::cout << "Enter expense: ";
    std::cin >> inputExpense;
    std::cin.ignore(1000, '\n');

    if (profile[INCOME_INDEX][idx] == EMPTY) {
        profile[INCOME_INDEX][idx] = 0;
        profile[EXPENSE_INDEX][idx] = 0;
    }

    profile[INCOME_INDEX][idx] += inputIncome;
    profile[EXPENSE_INDEX][idx] += inputExpense;

    double currentIncome = profile[INCOME_INDEX][idx];
    double currentExpense = profile[EXPENSE_INDEX][idx];
    double balance = currentIncome - currentExpense;

    std::cout << "Result: Balance for " << MONTH_NAMES[idx] << " = ";
    if (balance > 0) std::cout << "+";
    std::cout << balance << std::endl;
}

void showReport(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {

    std::cout << "\nMonth | Income | Expense | Balance" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    double totalIncome = 0;
    double totalExpense = 0;
    int monthsWithData = 0;

    for (int i = 0; i < activeMonths; i++) {
        if (profile[INCOME_INDEX][i] != EMPTY) {
            double income = profile[INCOME_INDEX][i];
            double expense = profile[EXPENSE_INDEX][i];
            double balance = income - expense;

            totalIncome += income;
            totalExpense += expense;
            monthsWithData++;

            std::cout << MONTH_NAMES[i] << " | " << income << " | " << expense << " | ";
            if (balance > 0) std::cout << "+";
            std::cout << balance << std::endl;
        }
    }

    if (monthsWithData == 0) {
        std::cout << "No data recorded yet." << std::endl;
        return;
    }

    double totalBalance = totalIncome - totalExpense;
    double averageBalance = totalBalance / monthsWithData;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Total income: " << totalIncome << std::endl;
    std::cout << "Total expense: " << totalExpense << std::endl;
    std::cout << "Average balance: ";
        if (averageBalance > 0) std::cout << "+";
    std::cout << averageBalance << std::endl;
}

void runApplication(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {
    char command[MAX_STR];

    while (true) {
        printMenu();
        std::cout << "> ";
        std::cin.getline(command, MAX_STR);

        if (areEqual(command, "exit")) {
            return;
        }
        if (areEqual(command, "add")) {
            addEntry(profile, activeMonths);
        }
        else if (areEqual(command, "report")) {
            showReport(profile, activeMonths);
        }
        else if (areEqual(command, "search")) {

        }
        else if (areEqual(command, "sort")) {

        }
        else if (areEqual(command, "forecast")) {

        }
        else if (areEqual(command, "chart")) {

        }
        else if (command[0] != '\0') {
            std::cout << "Unknown command." << std::endl;
        }
    }
}

void setupAccount(double profile[ACCOUNT_ROWS][MONTHS]) {
    int n;
    std::cout << "Enter number of months: ";
    std::cin >> n;
    std::cin.ignore();

    if (n > 0 && n <= MONTHS) {
        invalidateProfile(profile);
        std::cout << "Profile created for " << n << " months." << std::endl;
        runApplication(profile, n);
    }
    else {
        std::cout << "Invalid range (1-12)." << std::endl;
    }
}

int main() {
    double profile[ACCOUNT_ROWS][MONTHS];
    char command[MAX_STR];
    bool shouldExit = false;

    while (!shouldExit) 
    {
        std::cout << "Enter 'setup' to start or 'exit' to quit: ";
        std::cin.getline(command, MAX_STR);

        if (areEqual(command, "exit")) 
        {
            shouldExit = true;
        }
        else if (areEqual(command, "setup")) 
        {
            int n;
            std::cout << "Enter number of months: ";
            std::cin >> n;
            std::cin.ignore();

            if (n > 0 && n <= MONTHS) 
            {
                invalidateProfile(profile);
                std::cout << "Profile created successfully." << std::endl;
                runApplication(profile, n);
            }
            else 
            {
                std::cout << "Invalid months (1-12)." << std::endl;
            }
        }
        else if (command[0] != '\0') 
        {
            std::cout << "Error: You must run 'setup' first!" << std::endl;
        }
    }
    return 0;
}