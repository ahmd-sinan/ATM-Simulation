#include <stdio.h>
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define RESET "\033[0m"

typedef struct {
    char name[50];
    int pin;
    float balance;
    float transactions[1000];
    int transactionCount;
} Account;

void checkBalance(Account *user) {
    printf(BOLD "Balance: $%.2f\n" RESET, user->balance);
    printf(BOLD YELLOW"--------------------------------\n" RESET);
    if (user->balance <= 0) {
        printf(BOLD RED "NOT ENOUGH BALANCE!\n" RESET);
        printf(BOLD YELLOW"--------------------------------\n" RESET);
        return;
    }
}
void deposit(Account *user) {
    float deposit;
    printf(BOLD "Enter deposit amount: " RESET);
    scanf("%f", &deposit);
    if (deposit <= 0) {
        printf(BOLD RED "INVALID AMOUNT!\nEnter a Valid Amount\n" RESET);
        printf(BOLD YELLOW"--------------------------------\n" RESET);
        return;
    }
    user->balance = user->balance + deposit;
    printf(BOLD GREEN "You deposited $%.2f\n" RESET, deposit);
    printf("Updated Balance: $%.2f\n", user->balance);
    printf(BOLD YELLOW"--------------------------------\n" RESET);

    user->transactions[user->transactionCount] = deposit;
    user->transactionCount++;


}
void withdraw(Account *user) {
    float withdraw;
    printf(BOLD "Enter withdraw amount: " RESET);
    scanf("%f", &withdraw);
    if (withdraw <= 0) {
        printf(BOLD RED "INVALID AMOUNT!\nPlease Enter a Valid Amount\n" RESET);
        printf(BOLD YELLOW"--------------------------------\n" RESET);
        return;
    }
    if (withdraw > user->balance) {
        printf(BOLD RED "NOT ENOUGH BALANCE!\n" RESET);
        printf(BOLD YELLOW"--------------------------------\n" RESET);
        return;
    }
    user->balance = user->balance - withdraw;
    printf(BOLD GREEN "You withdrew $%.2f\n" RESET, withdraw);
    printf("Updated Balance: $%.2f\n", user->balance);
    printf(BOLD YELLOW"--------------------------------\n" RESET);

    user->transactions[user->transactionCount] = -withdraw;
    user->transactionCount++;
}

void transactions(Account *user) {
    if (user->transactionCount == 0) {
        printf(BOLD RED "No Transactions Yet!\n" RESET);
        printf(BOLD YELLOW"--------------------------------\n" RESET);
        return; 
    }
    printf(BOLD YELLOW "--------------------------------\n" RESET);
    printf(BOLD YELLOW "      TRANSACTION HISTORY\n\n" RESET);
    for (int i = 0; i < user->transactionCount; i++) {
        if (user->transactions[i] > 0) {
            printf(BOLD GREEN "%d. Deposit: $%.2f\n" RESET, i+1,  user->transactions[i]);
        }
        else {
            printf(BOLD RED "%d. Withdraw: $%.2f\n" RESET, i+1, -user->transactions[i]);
        }
    }
    printf(BOLD YELLOW "\n--------------------------------\n" RESET);
    printf(BOLD YELLOW "Current Balance: $%.2f\n" RESET, user->balance);
    printf(BOLD YELLOW "--------------------------------\n" RESET);
}

int main() {
    Account users[3] = {
                    {"John Doe", 1234, 1000.00},
                    {"Jane Smith", 5678, 2000.00},
                    {"Abu", 2468, 1500.00}
    };
    int pin;
    int attempts = 0;
    int currentUser = -1;
    int valid;


    printf(BOLD YELLOW"      WELCOME TO THE ATM\n" RESET);
    printf(BOLD YELLOW"--------------------------------\n\n" RESET);
    while (attempts < 3) {
        valid = 0;
        printf("\nEnter your PIN: ");
        scanf("%d", &pin);

        for (int i = 0; i < 3; i++) {
            if (pin == users[i].pin) {
                valid = 1;
                currentUser = i;
                printf(BOLD GREEN "LOGIN SUCCESSFUL!\n" RESET);
                printf(BOLD YELLOW "Welcome, %s!\n" RESET, users[i].name);
                break;
            }
        }

        if (valid == 1) {
            break;
        }
        else {
            attempts++;
            printf(BOLD RED "WRONG PIN!\n" RESET);
        }
    }
    if (attempts == 3) {
        printf(BOLD RED"Too Many Failed Attempts, Please Try Again Later!\n" RESET);
        return 1;
    }

    int choice;
    while (1) {
        printf("\n");
        printf(BOLD YELLOW "1. Check Balance\n" RESET);
        printf(BOLD YELLOW "2. Deposit\n" RESET);
        printf(BOLD YELLOW "3. Withdraw\n" RESET);
        printf(BOLD YELLOW "4. View Transactions\n" RESET);
        printf(BOLD RED"5. Exit\n" RESET);
        printf(BOLD"\nPlease Select Your Choice: " RESET);
        scanf("%d", &choice);

        if (choice < 1 || choice > 5) {
            printf(BOLD RED "Invalid Entry!\n" RESET);
            printf(BOLD YELLOW"--------------------------------\n" RESET);
            continue;
        }
        if (choice == 1) checkBalance(&users[currentUser]);
        if (choice == 2) deposit(&users[currentUser]);
        if (choice == 3) withdraw(&users[currentUser]);
        if (choice == 4) transactions(&users[currentUser]);
        if (choice == 5) {
            printf(BOLD GREEN "Thank You For Using Our ATM, Goodbye!\n" RESET);
            break;
        }
    }
    return 0;
}