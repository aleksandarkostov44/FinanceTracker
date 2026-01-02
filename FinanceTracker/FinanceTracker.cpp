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

void runApplication(double profile[ACCOUNT_ROWS][MONTHS], int activeMonths) {

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

    while (true) {
        std::cout << "Welcome! Type 'setup' to begin or 'exit' to quit: ";
        std::cin.getline(command, MAX_STR);

        if (areEqual(command, "exit")) {
            break;
        }

        if (areEqual(command, "setup")) {
            setupAccount(profile);
            break;
        }
        else if (command[0] != '\0') {
            std::cout << "Error: You must create a profile first using 'setup'!" << std::endl;
        }
    }

    return 0;
}