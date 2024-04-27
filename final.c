#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

// Function to save password
void savePassword()
{
    char site[100], password[100];
    printf("Enter site name: ");
    scanf("%s", site);
    printf("Enter password: ");
    scanf("%s", password);
    FILE *file = fopen("passwords.txt", "a");
    fprintf(file, "%s %s\n", site, password);
    fclose(file);
}

// Function to display saved passwords
void displayPasswords()
{
    FILE *file = fopen("passwords.txt", "r");
    char site[100], password[100];
    while (fscanf(file, "%s %s", site, password) != EOF)
    {
        printf("Site: %s, Password: %s\n", site, password);
    }
    fclose(file);
}

// Function to change password
void changePassword()
{
    char site[100], password[100];
    printf("Enter site name: ");
    scanf("%s", site);
    printf("Enter new password: ");
    scanf("%s", password);
    FILE *file = fopen("passwords.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    char tempSite[100], tempPassword[100];
    while (fscanf(file, "%s %s", tempSite, tempPassword) != EOF)
    {
        if (strcmp(site, tempSite) == 0)
        {
            fprintf(tempFile, "%s %s\n", site, password);
        }
        else
        {
            fprintf(tempFile, "%s %s\n", tempSite, tempPassword);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("passwords.txt");
    rename("temp.txt", "passwords.txt");
}

// Function to delete password entry
void deletePassword()
{
    char site[100];
    printf("Enter site name to delete: ");
    scanf("%s", site);
    FILE *file = fopen("passwords.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    char tempSite[100], tempPassword[100];
    bool found = false;
    while (fscanf(file, "%s %s", tempSite, tempPassword) != EOF)
    {
        if (strcmp(site, tempSite) == 0)
        {
            found = true;
            continue; // Skip writing this entry
        }
        fprintf(tempFile, "%s %s\n", tempSite, tempPassword);
    }
    fclose(file);
    fclose(tempFile);
    if (found)
    {
        remove("passwords.txt");
        rename("temp.txt", "passwords.txt");
        printf("Password entry deleted successfully.\n");
    }
    else
    {
        remove("temp.txt"); // Remove temp file if no entry was deleted
        printf("Site not found in the password manager.\n");
    }
}

// Function to generate a random password
void generatePassword(char password[] ,int length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+";
    const int charsetLength = strlen(charset);

    srand(time(NULL));

    for (int i = 0; i < length; ++i)
    {
        password[i] = charset[rand() % charsetLength];
    }
    password[length] = '\0';

    printf("Generated password: %s\n", password);
}

int main()
{
    char adminPassword[] = "admin";
    char password[100];
    int attempts = 0;
    const int maxAttempts = 3;
    char email[100];
    bool emailVerified = false;

    // while (!emailVerified && attempts < maxAttempts)
    while (!emailVerified)
    {
        printf("Enter admin password: ");
        // scanf("%s", password);
        int k = 0;
        char ch, pass[100];
        while ((ch = _getch()) != 13)
        {
            pass[k] = ch;
            k++;
            printf("*");
        }
        if (strcmp(password, adminPassword) == 0)
        {
            int choice;
            while (1)
            {
                printf("\n1. Save password\n");
                printf("2. Display passwords\n");
                printf("3. Change password\n");
                printf("4. Delete password\n");
                printf("5. Generate password\n");
                printf("6. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    savePassword();
                    break;
                case 2:
                    displayPasswords();
                    break;
                case 3:
                    changePassword();
                    break;
                case 4:
                    deletePassword();
                    break;
                case 5:
                {
                    int length;
                    printf("Enter length of the password: ");
                    scanf("%d", &length);
                    generatePassword(length);
                    break;
                }
                case 6:
                    return 0;
                default:
                    printf("Invalid choice\n");
                }
            }
        }
        else
        {
            attempts++;
            printf("Invalid password. Attempts left: %d\n", maxAttempts - attempts);
        }
    }
    if (attempts == maxAttempts)
    {
        printf("Maximum attempts reached. Check your mail to reset your password\n");
        char command[100] = "python main.py -email isangautam@gmail.com -password ";
        char password[10] = generatePassword(9);
        strcat(command, password);
    }

    return 0;
}
