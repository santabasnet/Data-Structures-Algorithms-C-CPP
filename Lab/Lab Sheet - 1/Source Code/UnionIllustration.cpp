/**
 * Example to demonstrate the use of Union in C language.
 *
 * This program illustrates the three types of account in a typical
 * commercial bank which shares multiple structures in a Union type.
 * Union is all about shared memory, representation of variable sizes
 * of data.
 *
 * Everest Engineering College.
 * By: Santa Basnet.
 * Date: Nov 17, 2021.
 */

/**
 * Header files.
 */
#include <stdio.h>
#include <string.h>

/**
 * Account type literals.
 */
const int FIXED = 0;
const int SAVING = 1;
const int CURRENT = 2;

/**
 * Saving account: demo attributes.
 * Saving account provides interest but does not have mature date.
 */
struct Saving {
    float interestRate;
    double balance;
};

/**
 * Current account: demo attributes.
 * Current account does not provide interests to their clients.
 */
struct Current {
    double balance;
};

/**
 * Fixed account: demo attributes.
 * Fixed account has certain interest rate and mature date.
 */
struct Fixed {
    float interestRate;
    double balance;
    long matureDate;
};

/**
 * Account type definitions with the help of Union.
 */
struct Account {
    char name[64];
    int type;
    union {
        struct Saving saving;
        struct Current current;
        struct Fixed fixed;
    } accountDetails;
};

/**
 * Converts the account type to string literals.
 * @param type
 * @return accountTypeName
 */
const char *accountTypeLiteral(int type) {
    switch (type) {
        case FIXED:
            return "FIXED";
        case CURRENT:
            return "CURRENT";
        case SAVING:
            return "SAVING";
    }
}

/**
 * Display the formatted output for fixed account.
 * @param account
 */
void displayFixed(struct Account account) {
    printf("\nAccount Details: ");
    printf("\n-----------------------------------------------");
    printf("\n\tName:           %s", account.name);
    printf("\n\tAccount Type:   %s", accountTypeLiteral(account.type));
    printf("\n\tBalance:        %.2f", account.accountDetails.fixed.balance);
    printf("\n\tMature Date:    %.2ld", account.accountDetails.fixed.matureDate);
    printf("\n\tInterest Rate:  %.2f", account.accountDetails.fixed.interestRate);
    printf("\n------------------------------------------------");
}

/**
 * Display the formatted output for current account.
 * @param account
 */
void displayCurrent(struct Account account) {
    printf("\nAccount Details: ");
    printf("\n------------------------------------------------");
    printf("\n\tName:       %s", account.name);
    printf("\n\tBalance:    %.2f", account.accountDetails.current.balance);
    printf("\n------------------------------------------------");
}

/**
 * Display the formatted output for saving account.
 * @param account
 */
void displaySaving(struct Account account) {
    printf("\nAccount Details: ");
    printf("\n------------------------------------------------");
    printf("\n\tName:           %s", account.name);
    printf("\n\tBalance:        %.2f", account.accountDetails.saving.balance);
    printf("\n\tInterest Rate:  %.2f", account.accountDetails.saving.interestRate);
    printf("\n------------------------------------------------");
}

/**
 * Display account data.
 */
void display(struct Account account) {
    switch (account.type) {
        case FIXED:
            displayFixed(account);
            break;
        case CURRENT:
            displayCurrent(account);
            break;
        case SAVING:
            displaySaving(account);
            break;
    }
}

/**
 * Main function starts here.
 * @return
 */
int main() {
    struct Account account;
    /**
     * Initialization.
     */
    strcpy(account.name, "Everest Engineering College");
    account.type = FIXED;
    account.accountDetails.fixed.balance = 100000.9f;
    account.accountDetails.fixed.matureDate = 1637159100239l;
    account.accountDetails.fixed.interestRate = 0.12f;
    /**
     * Display the initialized data.
     */
    display(account);
    return 0;
}