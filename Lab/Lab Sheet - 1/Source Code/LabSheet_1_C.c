/**
 * Lab Sheet - 1, Authentication Keys for the given Users.
 * Title: Authentication key representation for the multiple Users in CPP.
 * Aim: Utilization of Union/Structure/Enum type representation using inheritance.
 * author: Santa Basnet
 * Everest Engineering College.
 */

#include<stdio.h>
#include<string.h>

#define MAX 5

/**
 * Boolean Type.
 */
enum Boolean {
    FALSE, TRUE
};

/**
 * All the available User types in the table.
 */
enum UserType {
    INDIVIDUAL, CORPORATE
};

/**
 * Data type representation of Individual User.
 */
struct IndividualUser {
    int id;
    char name[32];
    char licenseKey[5];
    int price;
};

/**
 * Data type representation of Corporate User.
 */
struct CorporateUser {
    int id;
    char name[32];
    char licenseKeys[25][5];
    int price;
    int noOfKeys;
};

/**
 * Representation of type Software User.
 */
typedef struct {
    union {
        struct IndividualUser iUser;
        struct CorporateUser cUser;
    } user;
    enum UserType userType;
} SoftwareUser;

/**
 * Declare all the users as a global variable.
 */
SoftwareUser allSoftwareUsers[MAX];

/**
 * Initialize All the users.
 */
void initialize() {
    /**
     * 1. User id = 1
     */
    struct IndividualUser iUser1 = {1, "ram", "aXz5", 5000};
    allSoftwareUsers[0].user.iUser = iUser1;
    allSoftwareUsers[0].userType = INDIVIDUAL;

    /**
     * 1. User id = 2
     */
    struct CorporateUser cUser1 = {2, "eec", {"by3K", "66Y2", "4Uee", "oQ5r"}, 15000, 4};
    allSoftwareUsers[1].user.cUser = cUser1;
    allSoftwareUsers[1].userType = CORPORATE;

    /**
     * 1. User id = 3
     */
    struct CorporateUser cUser2 = {3, "pec", {"Lrc4", "rc8K", "22Y8"}, 10000, 3};
    allSoftwareUsers[2].user.cUser = cUser2;
    allSoftwareUsers[2].userType = CORPORATE;

    /**
     * 1. User id = 4
     */
    struct CorporateUser cUser3 = {4, "kec", {"8tW2", "uU5e", "pPi0", "eR71", "Tup4", "v9Bg"}, 25000, 6};
    allSoftwareUsers[3].user.cUser = cUser3;
    allSoftwareUsers[3].userType = CORPORATE;

    /**
     * 1. User id = 5
     */
    struct IndividualUser iUser2 = {5, "sam", "bB39", 5000};
    allSoftwareUsers[4].user.iUser = iUser2;
    allSoftwareUsers[4].userType = INDIVIDUAL;
}

void printLicenseKeys(SoftwareUser sUser) {
    for (int i = 0; i < sUser.user.cUser.noOfKeys; i++) {
        printf("%s, ", sUser.user.cUser.licenseKeys[i]);
    }
    printf("\t");
}

void displayUser(SoftwareUser sUser) {
    switch (sUser.userType) {
        case INDIVIDUAL:
            printf("\n");
            printf("%d\t", sUser.user.iUser.id);
            printf("%s\t", sUser.user.iUser.name);
            printf("INDIVIDUAL\t");
            printf("%s\t", sUser.user.iUser.licenseKey);
            printf("%d\t", sUser.user.iUser.price);
            break;
        case CORPORATE:
            printf("\n");
            printf("%d\t", sUser.user.cUser.id);
            printf("%s\t", sUser.user.cUser.name);
            printf("CORPORATE\t");
            printLicenseKeys(sUser);
            printf("%d\t", sUser.user.cUser.price);
            break;
    }
}

/**
 * Display All Users.
 */
void displayAllUsers() {
    printf("\n1. All the listed Users : ");
    for (int i = 0; i < MAX; i++) {
        displayUser(allSoftwareUsers[i]);
    }
    printf("\n");
}

/**
 * Compute amount paid by the given User name.
 * @param userName
 * @return calculatedAmount
 */
int amountOf(char *userName) {
    for (int i = 0; i < MAX; i++) {
        switch (allSoftwareUsers[i].userType) {
            case INDIVIDUAL:
                if (strcmp(allSoftwareUsers[i].user.iUser.name, userName) == 0)
                    return allSoftwareUsers[i].user.iUser.price;
                break;
            case CORPORATE:
                if (strcmp(allSoftwareUsers[i].user.cUser.name, userName) == 0)
                    return allSoftwareUsers[i].user.cUser.price;
                break;
        }
    }
    return 0;
}

/**
 * Find the user type of the given user name.
 * @param userName
 * @return userType
 */
const char *userTypeOf(char *userName) {
    for (int i = 0; i < MAX; i++) {
        switch (allSoftwareUsers[i].userType) {
            case INDIVIDUAL:
                if (strcmp(allSoftwareUsers[i].user.iUser.name, userName) == 0)
                    return "INDIVIDUAL";
                break;
            case CORPORATE:
                if (strcmp(allSoftwareUsers[i].user.cUser.name, userName) == 0)
                    return "CORPORATE";
                break;
        }
    }
    return "Not Found !";
}

/**
 * Identify if the given user name with the license key has access in the system or not.
 * @param userName
 * @param licenseKey
 * @return accessMessage
 */
const char *findAccessOf(char *userName, char *licenseKey) {
    enum Boolean result = FALSE;
    for (int i = 0; i < MAX; i++) {
        if (result == TRUE) break;
        switch (allSoftwareUsers[i].userType) {
            case INDIVIDUAL:
                if (strcmp(allSoftwareUsers[i].user.iUser.name, userName) == 0 &&
                    strcmp(allSoftwareUsers[i].user.iUser.licenseKey, licenseKey) == 0)
                    result = TRUE;
                break;
            case CORPORATE:
                if (strcmp(allSoftwareUsers[i].user.cUser.name, userName) == 0) {
                    for (int cnt = 0; cnt < allSoftwareUsers[i].user.cUser.noOfKeys; cnt++) {
                        if (strcmp(allSoftwareUsers[i].user.cUser.licenseKeys[cnt], licenseKey) == 0)
                            result = TRUE;
                    }
                }
                break;
        }
    }
    if (result == TRUE) return "Access Granted.";
    else return "Access Denied !";
}

/**
 * Display Summary.
 */
void displaySummary() {
    int noOfUsers = 0;
    int noOfLicenses = 0;
    int totalAmountCollected = 0;
    for (int i = 0; i < MAX; i++) {
        noOfUsers++;
        allSoftwareUsers[i].userType == CORPORATE

        ? noOfLicenses += allSoftwareUsers[i].user.cUser.noOfKeys
        : noOfLicenses++;

        allSoftwareUsers[i].userType == CORPORATE
        ? (totalAmountCollected += allSoftwareUsers[i].user.cUser.price)
        : (totalAmountCollected += allSoftwareUsers[i].user.iUser.price);
    }
    printf("\n5. Summaries\n");
    printf("\tNo. of Users: %d\n", noOfUsers);
    printf("\tNo. of Licenses Given: %d\n", noOfLicenses);
    printf("\tTotal Amount Collected: %d\n", totalAmountCollected);
}

/**
 * Program entry point.
 * @return 0 for successful operation.
 */
int main() {
    /**
     * 1. Initialize the table data.
     */
    initialize();

    /**
     * 1. Display all the initialized data.
     */
    displayAllUsers();

    /**
     * 2. Find the price paid by the user name.
     */
    char userName[] = "kec";
    printf("\n2. Price paid by the user : %d\n", amountOf(userName));

    /**
     * 3. Find the user type by the user name.
     */
    printf("\n3. User type of: %s\n", userTypeOf(userName));

    /**
     * 4. Find the access key by given the user name and the user key.
     */
    char licenseKey[] = "pPi0";
    printf("\n4. License key response: %s\n", findAccessOf(userName, licenseKey));

    /**
     * 5. Display Summary.
     */
    displaySummary();

    return 0;
}