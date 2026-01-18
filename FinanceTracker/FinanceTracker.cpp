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
    for (int i = 0; i < ACCOUNT_ROWS; i++) 
    {
        for (int j = 0; j < MONTHS; j++) 
        {
            profile[i][j] = EMPTY;
        }
    }
}

bool areEqual(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) 
    {
        s1++;
        s2++;
    }
    return *s1 == *s2;
}

const char* getArgument(const char* fullString, int commandLen) {
    return fullString + commandLen + 1;
}

bool startsWith(const char* fullString, const char* prefix) {
    while (*prefix) 
    {
        if (*fullString != *prefix) 
        {
            return false;
        }
        fullString++;
        prefix++;
    }
    return true;
}

void printMenu() {
    std::cout << "\nAvailable commands: add, report, search <monthName>, sort <type>, forecast <monthsAhead>, chart, exit" << std::endl;
}

int findMonthIndex(const char* name) {
    for (int i = 0; i < MONTHS; i++) 
    {
        if (areEqual(name, MONTH_NAMES[i])) 
        {
            return i;
        }
    }
    return -1;
}

int getDigitFromChar(const char* str) {
    int res = 0;
    while (*str >= '0' && *str <= '9') 
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res;
}

double getSortValue(double profile[ACCOUNT_ROWS][MONTHS], int monthIdx, const char* type) {
    if (areEqual(type, "income")) 
    {
        return profile[INCOME_INDEX][monthIdx];
    }
    if (areEqual(type, "expense")) 
    {
        return profile[EXPENSE_INDEX][monthIdx];
    }
    return profile[INCOME_INDEX][monthIdx] - profile[EXPENSE_INDEX][monthIdx];
}

void printShortMonth(int index) {
    if (index < 0 || index >= MONTHS)
    {
        return;
    }

    const char* name = MONTH_NAMES[index];

    for (int i = 0; i < 3 && name[i] != '\0'; i++) 
    {
        std::cout << name[i];
    }
}

double findMaxIncome(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {
    double maxVal = 0;
    for (int i = 0; i < activeMonths; i++) 
    {
        if (profile[INCOME_INDEX][i] > maxVal) 
        {
            maxVal = profile[INCOME_INDEX][i];
        }
    }
    return maxVal;
}

bool hasInputError() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Error: Invalid input. Please enter a number." << std::endl;
        return true;
    }
    return false;
}

void addEntry(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {
    int month;
    while (true) {
        std::cout << "Month: ";
        std::cin >> month;
        if (hasInputError()) continue;

        if (month < 1 || month > activeMonths) {
            std::cout << "Invalid month number! Please use 1 to " << activeMonths << "." << std::endl;
            continue;
        }
        break;
    }

    int idx = month - 1;
    double inputIncome, inputExpense;
    while (true) {
        std::cout << "Enter income: ";
        std::cin >> inputIncome;
        if (hasInputError()) continue;
        break;
    }

    while (true) {
        std::cout << "Enter expense: ";
        std::cin >> inputExpense;
        if (hasInputError()) continue;
        break;
    }

    std::cin.ignore(1000, '\n');

    if (profile[INCOME_INDEX][idx] == EMPTY) 
    {
        profile[INCOME_INDEX][idx] = 0;
        profile[EXPENSE_INDEX][idx] = 0;
    }

    profile[INCOME_INDEX][idx] += inputIncome;
    profile[EXPENSE_INDEX][idx] += inputExpense;

    double currentIncome = profile[INCOME_INDEX][idx];
    double currentExpense = profile[EXPENSE_INDEX][idx];
    double balance = currentIncome - currentExpense;

    std::cout << "Result: Balance for " << MONTH_NAMES[idx] << " = ";
    if (balance > 0)
    {
        std::cout << "+";
    }
    std::cout << balance << std::endl;
}

void showReport(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {
    std::cout << "\nMonth | Income | Expense | Balance" << std::endl;
    std::cout << "----------------------------------" << std::endl;

    double totalIncome = 0;
    double totalExpense = 0;
    int monthsWithData = 0;

    for (int i = 0; i < activeMonths; i++) 
    {
        if (profile[INCOME_INDEX][i] != EMPTY) 
        {
            double income = profile[INCOME_INDEX][i];
            double expense = profile[EXPENSE_INDEX][i];
            double balance = income - expense;

            totalIncome += income;
            totalExpense += expense;
            monthsWithData++;

            printShortMonth(i);
            std::cout << " | " << income << " | " << expense << " | ";
            if (balance > 0)
            {
                std::cout << "+";
            }
            std::cout << balance << std::endl;
        }
    }

    if (monthsWithData == 0) 
    {
        std::cout << "No data recorded yet." << std::endl;
        return;
    }

    double totalBalance = totalIncome - totalExpense;
    double averageBalance = totalBalance / monthsWithData;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Total income: " << totalIncome << std::endl;
    std::cout << "Total expense: " << totalExpense << std::endl;
    std::cout << "Average balance: ";
    if (averageBalance > 0)
    {
        std::cout << "+";
    }
    std::cout << averageBalance << std::endl;
}

void searchMonth(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths, const char* monthName) {
    int idx = findMonthIndex(monthName);

    if (idx == -1 || idx >= activeMonths) 
    {
        std::cout << "Invalid month name or month not in active range." << std::endl;
        return;
    }

    if (profile[INCOME_INDEX][idx] == EMPTY) 
    {
        std::cout << "No data recorded for " << monthName << "." << std::endl;
        return;
    }

    double income = profile[INCOME_INDEX][idx];
    double expense = profile[EXPENSE_INDEX][idx];
    double balance = income - expense;

        std::cout << "Income: " << income << std::endl;
        std::cout << "Expense: " << expense << std::endl;
        std::cout << "Balance: " << (balance > 0 ? "+" : "") << balance << std::endl;

        if (income > 0) 
        {
            double ratio = (expense / income) * 100.0;
            std::cout << "Expense ratio: " << ratio << "%" << std::endl;
        }
        else if (income == 0 && expense > 0) 
        {
            std::cout << "Expense ratio: 100% (No income)" << std::endl;
        }
        else 
        {
            std::cout << "Expense ratio: 0%" << std::endl;
        }
}

void sortByType(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths, const char* type) {
    int validIndices[MONTHS];
    int count = 0;

    for (int i = 0; i < activeMonths; i++) {
        if (profile[INCOME_INDEX][i] != EMPTY) {
            validIndices[count++] = i;
        }
    }

    if (count == 0) {
        std::cout << "No data recorded yet for sorting." << std::endl;
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        int maxPos = i;
        for (int j = i + 1; j < count; j++) 
        {
            double val1 = getSortValue(profile, validIndices[maxPos], type);
            double val2 = getSortValue(profile, validIndices[j], type);

            if (val2 > val1) 
            {
                maxPos = j;
            }
        }
        int temp = validIndices[i];
        validIndices[i] = validIndices[maxPos];
        validIndices[maxPos] = temp;
    }

    std::cout << "Sorted by monthly " << type << " (descending):" << std::endl;
    int topLimit = (count < 3) ? count : 3;

    for (int i = 0; i < topLimit; i++) {
        int mIdx = validIndices[i];
        double val = getSortValue(profile, mIdx, type);

        std::cout << i + 1 << ". ";
        printShortMonth(mIdx);
        std::cout << ": " << (val > 0 ? "+" : "") << val << std::endl;
    }
}

void calculateForecast(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths, const char* monthsAheadStr) {
    int n = getDigitFromChar(monthsAheadStr);
    if (n <= 0) 
    {
        std::cout << "Invalid number of months for forecast." << std::endl;
        return;
    }

    double totalSavings = 0;
    int monthsWithData = 0;

    for (int i = 0; i < activeMonths; i++) 
    {
        if (profile[INCOME_INDEX][i] != EMPTY) 
        {
            totalSavings += (profile[INCOME_INDEX][i] - profile[EXPENSE_INDEX][i]);
            monthsWithData++;
        }
    }

    if (monthsWithData == 0) 
    {
        std::cout << "No data available to make a forecast." << std::endl;
        return;
    }

    double delta = totalSavings / monthsWithData;

    std::cout << "Current savings: " << totalSavings << std::endl;
    std::cout << "Average monthly change: " << (delta > 0 ? "+" : "") << delta << std::endl;

    if (delta > 0) 
    {
        double predicted = totalSavings + n * delta;
        std::cout << "Predicted savings after " << n << " months: " << predicted << std::endl;
    }
    else 
    {
        std::cout << "You are out of money!" << std::endl;
    }
}

void drawChart(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {
    double max = findMaxIncome(profile, activeMonths);
    if (max <= 0) 
    {
        std::cout << "No income data to display chart." << std::endl;
        return;
    }
    std::cout << "\n=== YEARLY FINANCIAL CHART ===" << std::endl;
    int startY = ((int)max / 500 + (max > 0 ? 1 : 0)) * 500;
    for (int y = startY; y >= 500; y -= 500) 
    {
        std::cout << (y < 1000 ? " " : "") << y << " | ";
        for (int i = 0; i < activeMonths; i++) 
        {
            if (profile[INCOME_INDEX][i] >= y)
            {
                std::cout << " #  ";
            }
            else
            {
                std::cout << "    ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "     --------------------------------------------" << std::endl;
    std::cout << "      ";
    for (int i = 0; i < activeMonths; i++) 
    {
        printShortMonth(i);
        std::cout << " ";
    }
    std::cout << std::endl;
}

void setupMenu(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {
    char command[MAX_STR];

    while (true) 
    {
        printMenu();
        std::cout << "> ";
        std::cin.getline(command, MAX_STR);

        if (areEqual(command, "exit")) 
        {
            std::cout << "\n--- FINAL FINANCIAL REPORT ---" << std::endl;
            showReport(profile, activeMonths);
            return;
        }
        if (areEqual(command, "add")) 
        {
            addEntry(profile, activeMonths);
        }
        else if (areEqual(command, "report")) 
        {
            showReport(profile, activeMonths);
        }
        else if (startsWith(command, "search ")) 
        {
            const char* monthName = getArgument(command, 6);
            searchMonth(profile, activeMonths, monthName);
        }
        else if (startsWith(command, "sort ")) 
        {
            const char* type = getArgument(command, 4);
            sortByType(profile, activeMonths, type);
        }
        else if (startsWith(command, "forecast ")) 
        {
            const char* stepsStr = getArgument(command, 8);
            calculateForecast(profile, activeMonths, stepsStr);
        }
        else if (areEqual(command, "chart")) 
        {
            drawChart(profile, activeMonths);
        }
        else if (command[0] != '\0') 
        {
            std::cout << "Unknown command." << std::endl;
        }
    }
}

void runApplication(double profile[ACCOUNT_ROWS][MONTHS]) {
    char command[MAX_STR];

    while (true) 
    {
        std::cout << "Enter 'setup' to start or 'exit' to quit: ";
        std::cin.getline(command, MAX_STR);

        if (areEqual(command, "exit")) 
        {
            break;
        }
        else if (areEqual(command, "setup")) 
        {
            int n;
            while (true) {
                std::cout << "Enter number of months (1-12): ";
                std::cin >> n;

                if (hasInputError()) {
                    continue;
                }

                std::cin.ignore(1000, '\n');

                if (n > 0 && n <= MONTHS) {
                    invalidateProfile(profile);
                    std::cout << "Profile created successfully." << std::endl;
                    setupMenu(profile, n);
                    break;
                }
                else {
                    std::cout << "Invalid months (1-12)." << std::endl;
                }
            }
        }
        else if (command[0] != '\0') 
        {
            std::cout << "Error: You must run 'setup' first to create an account!" << std::endl;
        }
    }
}

int main() 
{
    double profile[ACCOUNT_ROWS][MONTHS];
    runApplication(profile);
    return 0;
}