#include <stdio.h>
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BOLD "\033[1m"
#define RESET "\033[0m"


float balance = 1000.0;

void checkBalance() {
    printf(BOLD "Balance: $%.2f\n" RESET, balance);
    if (balance <= 0) {
        printf(BOLD RED "NOT ENOUGH BALANCE!\n" RESET);
        return;
    }
}
void deposit() {
    float deposit;
    printf(BOLD "Enter deposit amount: " RESET);
    scanf("%f", &deposit);
    if (deposit <= 0) {
        printf(BOLD RED "INVALID AMOUNT!\nEnter a Valid Amount\n" RESET);
        return;
    }
    balance = balance + deposit;
    printf(BOLD GREEN "You deposited $%.2f\n" RESET, deposit);
    printf("Updated Balance: $%.2f\n", balance);

}
void withdraw() {
    float withdraw;
    printf(BOLD "Enter withdraw amount: " RESET);
    scanf("%f", &withdraw);
    if (withdraw <= 0) {
        printf(BOLD RED "INVALID AMOUNT!\nPlease Enter a Valid Amount\n" RESET);
        return;
    }
    if (withdraw > balance) {
        printf(BOLD RED "NOT ENOUGH BALANCE!\n" RESET);
        return;
    }
    balance = balance - withdraw;
    printf(BOLD GREEN "You withdrew $%.2f\n" RESET, withdraw);
    printf("Updated Balance: $%.2f\n", balance);
}

int main() {
    int pin;
    int storedPin[] = {1234, 5678, 2468};
    int users = 3;
    int attempts = 0;
    int valid;

    printf(BOLD YELLOW"      WELCOME TO THE ATM\n" RESET);
    printf(BOLD YELLOW"--------------------------------\n\n" RESET);
    while (attempts < 3) {
        valid = 0;
        printf("\nEnter your PIN: ");
        scanf("%d", &pin);

        for (int i = 0; i < users; i++) {
            if (pin == storedPin[i]) {
                valid = 1;
                break;
            }
        }

        if (valid == 1) {
            printf(BOLD GREEN "LOGIN SUCCESSFUL!\n" RESET);
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
        printf(BOLD RED"4. Exit\n" RESET);
        printf(BOLD"\nPlease Select Your Choice: " RESET);
        scanf("%d", &choice);

        if (choice < 1 || choice > 4) {
            printf(BOLD RED "Invalid Entry!\n" RESET);
            continue;
        }
        if (choice == 1) checkBalance();
        if (choice == 2) deposit();
        if (choice == 3) withdraw();
        if (choice == 4) {
            printf(BOLD GREEN "Thank You For Using Our ATM, Goodbye!\n" RESET);
            break;
        }
    }
    return 0;
}