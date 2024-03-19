#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
void main(){
    struct CreateAccount{
        long int currAccNum;
        char name[20];
        char email[30];
        char phonenum[29];
        char password[20];
        int balance;
        int mpin;
    };
    int mpin1=0, mpin2=0;
    struct CreateAccount account;

    account.balance = 0;
    printf("Enter your name: ");
    scanf("%s", account.name);
    printf("Enter your email: ");
    scanf("%s", account.email);
    printf("Enter your phone number: ");
    scanf("%s", &account.phonenum);
    printf("Enter your password: ");
    scanf("%s", account.password);
    printf("Enter your MPIN - 4 digit: ");
    scanf("%d", &mpin1);
    printf("Confirm You MPIN: ");
    scanf("%d", &mpin2);

    if(mpin1 == mpin2){
        account.mpin = mpin1;
    }
    else{
        printf("MPIN didn't matched");
        exit(1);
    }

    FILE *file;
    FILE *fp;

    file = fopen("acnum.txt", "r");
    fscanf(file, "%d", &account.currAccNum);
    fclose(file);

    fp = fopen("temp.txt", "a");
    fprintf(fp, "%d", account.currAccNum+1);
    fclose(fp);

    remove("acnum.txt");
    rename("temp.txt", "acnum.txt");


    char filename[20];
    sprintf(filename, "%s.txt", account.phonenum);

    if (access(filename, F_OK) != -1) {
        printf("Account already exists. Account creation aborted.\n");
        exit(1);
    }

    fp = fopen(filename, "a");
    fprintf(fp, "%ld %s %s %s %s %d %d\n", account.currAccNum, account.name, account.email, account.phonenum, account.password, account.balance, account.mpin);



    printf("Your account number is %ld", account.currAccNum);

    getch();
}
