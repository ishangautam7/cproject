#include<stdio.h>

void main(){
    struct CreateAccount{
        long int currAccNum;
        char name[20];
        char email[30];
        long int phonenum;
        char password[20];
    };

    struct CreateAccount account;

    printf("Enter your name: ");
    scanf("%s", account.name);
    printf("Enter your email: ");
    scanf("%s", account.email);
    printf("Enter your phone number: ");
    scanf("%ld", &account.phonenum);
    printf("Enter your password: ");
    scanf("%s", account.password);


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



    fp = fopen(account.phonenum, "a");
    fprintf(fp, "%ld %s %s %ld %s\n", account.currAccNum, account.name, account.email, account.phonenum, account.password);



    printf("Your account number is %ld", account.currAccNum);

    getch();
}
