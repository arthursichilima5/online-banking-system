#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_NAME "bank.txt"

struct Account {
    int accNo;
    char name[30];
    float balance;
};

/* Create a new account */
void createAccount() {
    struct Account acc;
    FILE *fp = fopen(FILE_NAME, "a");

    printf("\n--- Create Account ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc.accNo);

    printf("Enter Name: ");
    scanf("%s", acc.name);

    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    fprintf(fp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);
    fclose(fp);

    printf("Account created successfully!\n");
}

/* Find account in file */
int findAccount(int accNo, struct Account *acc) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) return 0;

    while (fscanf(fp, "%d %s %f", &acc->accNo, acc->name, &acc->balance) != EOF) {
        if (acc->accNo == accNo) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* Update file after deposit or withdraw */
void updateAccount(struct Account updatedAcc) {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Account acc;

    while (fscanf(fp, "%d %s %f", &acc.accNo, acc.name, &acc.balance) != EOF) {
        if (acc.accNo == updatedAcc.accNo) {
            fprintf(temp, "%d %s %.2f\n", updatedAcc.accNo, updatedAcc.name, updatedAcc.balance);
        } else {
            fprintf(temp, "%d %s %.2f\n", acc.accNo, acc.name, acc.balance);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}

/* Deposit money */
void deposit() {
    int accNo;
    float amount;
    struct Account acc;

    printf("\n--- Deposit ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    if (findAccount(accNo, &acc)) {
        printf("Enter Amount: ");
        scanf("%f", &amount);

        acc.balance += amount;
        updateAccount(acc);

        printf("Deposit successful! New balance: %.2f\n", acc.balance);
    } else {
        printf("Account not found!\n");
    }
}

/* Withdraw money */
void withdraw() {
    int accNo;
    float amount;
    struct Account acc;

    printf("\n--- Withdraw ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    if (findAccount(accNo, &acc)) {
        printf("Enter Amount: ");
        scanf("%f", &amount);

        if (amount > acc.balance) {
            printf("Insufficient funds!\n");
        } else {
            acc.balance -= amount;
            updateAccount(acc);
            printf("Withdrawal successful! New balance: %.2f\n", acc.balance);
        }
    } else {
        printf("Account not found!\n");
    }
}

/* Check balance */
void checkBalance() {
    int accNo;
    struct Account acc;

    printf("\n--- Check Balance ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    if (findAccount(accNo, &acc)) {
        printf("\nAccount Number: %d\n", acc.accNo);
        printf("Name: %s\n", acc.name);
        printf("Balance: %.2f\n", acc.balance);
    } else {
        printf("Account not found!\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n=== Simple Banking System ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: exit(0);
            default: printf("Invalid option!\n");
        }
    }
    return 0;
}
