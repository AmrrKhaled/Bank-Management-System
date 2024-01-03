#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct
{
    int month;
    int year;
} date;
typedef struct
{
    char *account_number;
    char *name;
    char *email;
    char *number;
    float balance;
    date CustomerDate;
} account;
account *customer;

int savevalid(char *);
int isvalid(char *);
void print(int);
void Login(void);
void load(void);
void add(void);
void delete(void);
void menu(void);
void advSearch(void);
void modify(void);
void transfer(void);
void search(void);
void deposit(void);
void quit(void);
void withdraw(void);
int checkemail(char *email);
int checkname(char *name);
int checknumber(char *number);
int checkacc(char *account_number);
void convert(int month, char *result);
void sortbyname(account arr[]);
void sortbydate(account arr[]);
void sortbybalance(account arr[]);
void Save(void);
void minimenu(void);

FILE *users;
FILE *accounts;
char accounts_paths[] = "accounts.txt";
char users_paths[] = "users.txt";
int customer_count = 0;
int flagvr = 0;

int isvalid(char deposit[])
{
    int valid_1 = 0, valid_2 = 0;
    for (int i = 0; deposit[i] != '\0'; i++)
    {
        if (deposit[i] == '.')
        {
            if (valid_1)
            {
                return 0;
            }
            valid_1 = 1;
        }
    }
    if (valid_1)
    {

        for (int i = 0; deposit[i] != '\0'; i++)
        {
            if (deposit[i] >= '0' && deposit[i] <= '9')
            {
                valid_2++;
            }
        }
        if (strlen(deposit) - 1 == valid_2 && valid_1)
        {
            return 1;
        }
    }
    else
    {
        for (int i = 0; deposit[i] != '\0'; i++)
        {
            if (deposit[i] >= '0' && deposit[i] <= '9')
            {
                valid_2++;
            }
        }
        if (strlen(deposit) == valid_2)
        {
            return 1;
        }
    }
    return 0;
}
int isvalid_2(char str[])
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        count++;
    }
    if (count > 1)
    {
        return 4;
    }
    if (str[0] == '1')
    {
        return 1;
    }
    else if (str[0] == '2')
    {
        return 2;
    }
    else if (str[0] == '3')
    {
        return 3;
    }
    return 4;
}
int savevalid(char str[])
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        count++;
    }
    if (count > 1)
    {
        return 2;
    }
    if (str[0] == '0')
    {
        return 0;
    }
    else if (str[0] == '1')
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
void Login(void)
{
    char cmp1[50], user[50], password[20];
    char delimter[] = " \n";
    int flag1 = 1, flag2 = 1;
    do
    {
        users = fopen(users_paths, "r");
        printf("Please enter your username : ");
        scanf("%s", user);
        printf("Please enter your password : ");
        scanf("%s", password);
        if (users_paths != NULL)
        {
            while (fgets(cmp1, 50, users_paths))
            {
                char *tok = strtok(cmp1, delimter);
                flag1 = strcmp(tok, user);
                if (!flag1)
                {
                    tok = strtok(NULL, delimter);
                    if (!(strcmp(password, tok)))
                    {
                        printf("User found . How can I help you ?\n");
                        flag2 = 0;
                        load();
                        break;
                    }
                }
            }
            if (flag1 || flag2)
            {
                printf("Invalid username or password .\n");
                getchar();
                minimenu();
            }
        }
        fclose(users_paths);
    } while (flag2 || flag1);
    menu();
}
void load(void)
{
    char userCredentials[100];
    char delimiter[] = "',','-'";
    customer_count = 0;
    accounts = fopen(accounts_paths, "r");
    int j = 0;
    while (fgets(userCredentials, sizeof(userCredentials), accounts))
    {
        customer_count++;
    }
    fclose(accounts);
    accounts = fopen(accounts_paths, "r");
    customer = malloc(sizeof(account) * customer_count);
    while (fgets(userCredentials, sizeof(userCredentials), accounts))
    {
        char *token = strtok(userCredentials, delimiter);
        int i = 0;
        while (token != NULL)
        {
            switch (i)
            {
            case 0:
                customer[j].account_number = strdup(token);
                break;
            case 1:
                customer[j].name = strdup(token);
                break;
            case 2:
                customer[j].email = strdup(token);
                break;
            case 3:
                sscanf(token, "%f", &customer[j].balance);
                break;
            case 4:
                customer[j].number = strdup(token);
                break;
            case 5:
                sscanf(token, "%d", &customer[j].CustomerDate.month);
                break;
            case 6:
                sscanf(token, "%d", &customer[j].CustomerDate.year);
                break;
            }
            token = strtok(NULL, delimiter);
            i++;
        }
        j++;
    }
}
int checkname(char *name)
{
    int y = strlen(name), x = 1;
    int alphas = 0, spaces = 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        if ((name[i] >= 97 && name[i] <= 122) || (name[i] >= 65 && name[i] <= 90) || name[i] == ' ')
        {
            alphas++;
        }
    }
    while (name[spaces] == ' ')
    {
        spaces++;
    }
    if (spaces > 0)
    {
        for (int k = 0; k < y; k++)
        {
            name[k] = name[k + spaces];
        }
    }
    if (name[0] >= 97 && name[0] <= 122)
    {
        name[0] -= 32;
    }
    for (int z = 0; z < y; z++)
    {
        if (name[z] == ' ' && name[z + 1] >= 97 && name[z + 1] <= 122)
        {
            name[z + 1] -= 32;
        }
    }
    while (name[x] != ' ')
    {
        if (name[x] >= 65 && name[x] <= 90)
            name[x] += 32;
        x++;
    }
    x += 2;
    while (name[x] != '\0')
    {
        if (name[x] >= 65 && name[x] <= 90)
            name[x] += 32;
        x++;
    }

    if (y == alphas)
    {
        return 0;
    }
    return 1;
}
int checkacc(char *account_number)
{
    int digits = 0;
    for (int i = 0; account_number[i] != '\0'; i++)
    {
        if (account_number[i] >= '0' && account_number[i] <= '9')
        {
            digits++;
        }
    }
    if (digits == 10)
    {
        return 0;
    }
    return 1;
}
int checknumber(char *number)
{
    int digits = 0;
    for (int i = 0; number[i] != '\0'; i++)
    {
        if (number[i] >= '0' && number[i] <= '9')
        {
            digits++;
        }
    }
    if (digits == 11)
    {
        return 0;
    }
    return 1;
}
int checkemail(char *email)
{
    int x = strlen(email);
    int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
    int i = 0;
    char temp[50];
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == 64)
        {
            temp3 = 1;
            break;
        }
    }
    if (!temp3)
    {
        return 1;
    }
    strcpy(temp, email);
    char *token = strtok(temp, "@");
    for (int i = 0; token[i] != '\0'; i++)
    {
        if ((token[i] >= 65 && token[i] <= 90) || (token[i] >= 97 && token[i] <= 122))
        {
            temp4 = 1;
            break;
        }
    }

    if (token != NULL)
    {
        token = strtok(NULL, ".");
        if (token != NULL)
        {
            temp1 = 1;
        }
    }
    token = strtok(NULL, "\0");
    if (token != NULL)
    {
        temp2 = 1;
    }
    if (temp1 && temp2 && temp3 && temp4)
    {
        return 0;
    }
    return 1;
}
void convert(int month, char *result)
{
    char months[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    for (int i = 0; i < 12; i++)
    {
        if (month == i + 1)
        {
            strcpy(result, months[i]);
            return;
        }
    }
}
void search(void)
{
    int i, flag = 0;
    char account1[50];
    printf("please enter account Number : ");
    getchar();
    gets(account1);
    for (i = 0; i < customer_count; i++)
    {
        if (strcmp(customer[i].account_number, account1) == 0)
        {
            print(i);
            flag = 1;
            break;
        }
    }
    if (!flag)
        printf("Account not found .\n");
    menu();
}
void advSearch(void)
{
    char target[50], info[50];
    int i, flag = 0;
    printf("Please enter the name required to be searched : ");
    scanf("%s", target);
    char *tok1, *tok2;
    for (i = 0; i < customer_count; i++)
    {
        strcpy(info, customer[i].name);
        if ((strstr(info, target)))
        {
            print(i);
            printf("\n");
            flag = 1;
        }
    }
    if (!flag)
        printf("No matches found .\n");
    getchar();
    menu();
}
void add(void)
{
    int temp = 1, sav;
    char save[20];
    time_t currenttime;
    struct tm *localTime;
    char newacc[20], name[50], email[50], mob[50];
    int flag = 1, currentmonth, currentyear;
    printf("Please enter the new account number : ");
    scanf("%s", newacc);
    if (checkacc(newacc))
    {
        printf("Invalid account number .\n");
        menu();
    }
    for (int i = 0; i < customer_count; i++)
    {
        if (!(strcmp(customer[i].account_number, newacc)))
        {
            printf("This account number is already used .\n");
            flag = 0;
            menu();
        }
    }
    while (1)
    {
        if (flag)
        {
            printf("Please enter the name of the user : ");
            getchar();
            gets(name);
            if (checkname(name))
            {
                printf("Invalid name .\n");
                temp = 0;
                menu();
            }
            else
            {
                printf("Please enter your email : ");
                scanf("%s", email);
            }
            if (checkemail(email))
            {
                printf("Invalid email .\n");
                temp = 0;
                menu();
            }
            else
            {
                printf("Please enter the mobile number : ");
                getchar();
                scanf("%s", mob);
            }
            if (checknumber(mob))
            {
                printf("Invalid mobile number .\n");
                temp = 0;
                menu();
            }
            break;
        }
        else
            menu();
    }
    time(&currenttime);
    localTime = localtime(&currenttime);
    currentmonth = localTime->tm_mon + 1;
    currentyear = localTime->tm_year + 1900;
    if (temp)
    {

        do
        {
            printf("1.Save modification .\n0.Discard changes .\n");
            scanf("%s", save);
            if (savevalid(save) <= 1)
            {
                sav = atoi(save);
                flag = 0;
            }
            else
            {
                printf("Invalid Entry .\n");
                sav = atoi(save);
                flag = 1;
            }
        } while (flag);
    }
    if (sav && temp)
    {
        customer_count++;
        customer = realloc(customer, sizeof(account) * customer_count);
        customer[customer_count - 1].account_number = strdup(newacc);
        customer[customer_count - 1].name = strdup(name);
        customer[customer_count - 1].email = strdup(email);
        customer[customer_count - 1].number = strdup(mob);
        customer[customer_count - 1].balance = 0.0;
        customer[customer_count - 1].CustomerDate.month = currentmonth;
        customer[customer_count - 1].CustomerDate.year = currentyear;
        printf("Account is added successfully .\n");
        Save();
        strcat(newacc, ".txt");
        FILE *file = fopen(newacc, "a");
        fclose(file);
    }
    menu();
}
void report()
{
    char acc[20];
    int flag = 0;
    printf("Please enter the account number : ");
    scanf("%s", acc);
    while (checkacc(acc))
    {
        printf("Invalid account number .\n");
        getchar();
        menu();
        break;
    }
    for (int i = 0; i < customer_count; i++)
    {
        if (!(strcmp(acc, customer[i].account_number)))
        {
            flag = 1;
        }
    }
    if (flag)
    {
        strcat(acc, ".txt");
        FILE *file = fopen(acc, "r");
        char userCredentials[100];
        int i = 0, temp = 0;
        while (fgets(userCredentials, sizeof(userCredentials), file))
        {
            temp++;
        }
        fclose(file);
        file = fopen(acc, "r");
        if (temp >= 5)
        {
            while (fgets(userCredentials, sizeof(userCredentials), file))
            {

                if (i >= temp - 5)
                {
                    printf("%s", userCredentials);
                }
                i++;
            }
        }
        else if (temp < 5 && temp > 0)
        {
            while (fgets(userCredentials, sizeof(userCredentials), file))
                printf("%s", userCredentials);
            getchar();
        }

        else if (temp == 0 || file == NULL)
        {
            printf("No transactions for this account number .\n");
            getchar();
        }
        menu();
    }
    else
    {
        printf("Account deleted or not found .");
        menu();
    }
}
void modify(void)
{
    char name[50], mob_number[50], email[50], email1[50];
    char mod_num[11], temp[20], save[20];
    int modified = -1, temp1, c, flag = 1, sav;
    int x1 = 1, x2 = 1, x3 = 1;
    printf("Please enter the account number : ");
    scanf("%s", mod_num);
    for (int i = 0; i < customer_count; i++)
    {
        if (!(strcmp(mod_num, customer[i].account_number)))
        {
            modified = i;
            break;
        }
    }
    if (modified < 0)
    {
        printf("Account not found .\n");
        menu();
    }

    do
    {
        printf("Please choose the data you want to modify :\n1.NAME\n2.MOBILE NUMBER\n3.EMAIL ADDRES\n");
        scanf("%s", temp);
        if (isvalid_2(temp) <= 3)
        {
            temp1 = atof(temp);
        }
        if (temp1 == 1 || temp1 == 2 || temp1 == 3)
        {
            flag = 0;
        }

    } while (flag);

    while ((c = getchar()) != '\n' && c != EOF)
        ;
    do
    {
        switch (temp1)
        {
        case 1:
            printf("Please enter new name : ");
            gets(name);
            name[strlen(name) + 1] = '\0';
            x1 = checkname(name);
            if (x1)
            {
                printf("Invalid name .\n");
                break;
            }
            x2 = 0;
            x3 = 0;
            printf("1.Save modification .\n0.Discard changes .\n");
            scanf("%s", save);
            if (savevalid(save) <= 1)
            {
                sav = atof(save);
            }
            else
            {
                menu();
            }
            if (sav)
            {
                strcpy(customer[modified].name, name);
                printf("The new modified name is : %s for this account number : %s\n", customer[modified].name, customer[modified].account_number);
                Save();
                break;
            }
        case 2:
            printf("Please enter new phone number : ");
            gets(mob_number);
            mob_number[strlen(mob_number) + 1] = '\0';
            x2 = checknumber(mob_number);
            if (x2)
            {
                printf("Invalid mobile number .\n");
                break;
            }
            x1 = 0;
            x3 = 0;
            printf("1.Save modification .\n0.Discard changes .\n");
            scanf("%s", save);
            if (savevalid(save) <= 1)
            {
                sav = atof(save);
            }
            else
            {
                menu();
            }
            if (sav)
            {
                strcpy(customer[modified].number, mob_number);
                printf("The new modified mobile number is : %s for this account number : %s\n", customer[modified].number, customer[modified].account_number);
                Save();
                break;
            }
        case 3:
            printf("Please enter new email : ");
            gets(email);
            email[strlen(email) + 1] = '\0';
            strcpy(email1, email);
            x3 = checkemail(email);
            if (x3)
            {
                printf("Invalid email .\n");
                break;
            }
            x1 = 0;
            x2 = 0;
            printf("1.Save modification .\n0.Discard changes .\n");
            scanf("%s", save);
            if (savevalid(save) <= 1)
            {
                sav = atof(save);
            }
            else
            {
                menu();
            }
            if (sav)
            {
                strcpy(customer[modified].email, email1);
                printf("The new modified email is : %s for this account number : %s\n", customer[modified].email, customer[modified].account_number);
                Save();
                break;
            }
        }
    } while (x1 && x2 && x3);
    menu();
}
void Save(void)
{
    accounts = fopen(accounts_paths, "w");
    for (int i = 0; i < customer_count; i++)
    {
        fprintf(accounts, "%s,", customer[i].account_number);
        fprintf(accounts, "%s,", customer[i].name);
        fprintf(accounts, "%s,", customer[i].email);
        fprintf(accounts, "%.2f,", customer[i].balance);
        fprintf(accounts, "%s,", customer[i].number);
        fprintf(accounts, "%d-", customer[i].CustomerDate.month);
        fprintf(accounts, "%d", customer[i].CustomerDate.year);
        fprintf(accounts, "\n");
    }
    fclose(accounts);
}
void transfer(void)
{
    char accs[11], accr[11], trans[20];
    char save[20];
    int i, j, check1 = 1, check2 = 1, flag = 1, sav;
    float tranx;
    printf("Please enter the account number of the sender : ");
    scanf("%s", accs);
    for (i = 0; i < customer_count; i++)
    {
        if (!(strcmp(customer[i].account_number, accs)))
        {

            check1 = 0;
            printf("Please enter the account number of the receiver : ");
            scanf("%s", accr);
            for (j = 0; j < customer_count; j++)
            {
                if (!(strcmp(customer[j].account_number, accr)))
                {
                    if (!strcmp(accr, accs))
                    {
                        printf("You can not transfer to the same account .\n");
                        menu();
                    }
                    check2 = 0;
                    printf("Please enter the amount of money you want to transfer : ");
                    scanf("%s", trans);
                    if (isvalid(trans))
                    {
                        tranx = atof(trans);
                    }
                    else
                    {
                        printf("Invalid Entry .\n");
                        menu();
                    }
                    if (tranx <= customer[i].balance)
                    {
                        do
                        {
                            printf("1.Save modification .\n0.Discard changes .\n");
                            scanf("%s", save);
                            if (savevalid(save) <= 1)
                            {
                                sav = atof(save);
                                sav = atoi(save);
                                flag = 0;
                            }
                            else
                            {
                                printf("Invalid Entry . \n");

                                flag = 1;
                            }
                        } while (flag);
                    }
                    else
                    {
                        printf("Insufficient balance .\n");
                        menu();
                    }
                    if (sav)
                    {
                        customer[i].balance -= tranx;
                        customer[j].balance += tranx;
                        printf("Successful transfer . \n");
                        Save();
                        break;
                    }
                }
            }
        }
        if (!(check1 && check2))
            break;
    }
    if (check1)
    {
        printf("Invalid sender account .\n");
        menu();
    }
    if (check2)
    {
        printf("Invalid reciever account .\n");
        menu();
    }
    if (sav)
    {
        strcat(accs, ".txt");
        FILE *files = fopen(accs, "a");
        fprintf(files, "%0.2f are transfered from the account. The updated balance is %0.2f\n", tranx, customer[i].balance);
        fclose(files);
        strcat(accr, ".txt");
        FILE *filer = fopen(accr, "a");
        fprintf(filer, "%0.2f are transfered to the account. The updated balance is %0.2f\n", tranx, customer[j].balance);
        fclose(filer);
    }
    menu();
}
void deposit(void)
{
    int k, sav, flag = 0, flags = 0;
    char num[11], save[20];
    char depo[20];
    float dep;
    printf("Please enter account number : ");
    scanf("%s", num);
    for (k = 0; k < customer_count; k++)
    {
        if (!strcmp(num, customer[k].account_number))
        {
            printf("Please enter amount of money to be deposited : ");
            scanf("%s", depo);
            if (isvalid(depo))
            {
                dep = atof(depo);
            }
            else
            {
                printf("Invalid Entry .\n");
                menu();
            }
            flag = 1;
            if (dep < 0 || dep > 10000)
            {
                printf("Exceeded deposit limit .\n");
                menu();
            }
            do
            {
                printf("1.Save modification .\n0.Discard changes .\n");
                scanf("%s", save);
                if (savevalid(save) <= 1)
                {
                    sav = atoi(save);
                    flags = 0;
                }
                else
                {
                    printf("Invalid Entry .\n");
                    sav = atoi(save);
                    flags = 1;
                }
            } while (flags);
            if (sav)
            {
                customer[k].balance += dep;
                printf("Successful transaction . \n");
                Save();
                break;
            }
            else
                continue;
        }
    }
    if (!flag)
        printf("Invalid account number .\n");
    if (flag && sav)
    {
        strcat(num, ".txt");
        FILE *file = fopen(num, "a");
        fprintf(file, "%.2f are deposited. The updated balance is %.2f\n", dep, customer[k].balance);
        fclose(file);
    }
    menu();
}
void delete(void)
{
    char target[20], save[20];
    int i, j, flag = 0, sav = 0, balance, flags;
    printf("Please enter account number : ");
    scanf("%s", target);
    for (i = 0; i < customer_count; i++)
    {
        if (!(strcmp(target, customer[i].account_number)))
        {
            balance = (customer[i].balance == 0);
            flag = 1;
            break;
        }
    }
    if (flag && balance)
    {
        do
        {
            printf("1.Save modification .\n0.Discard changes .\n");
            scanf("%s", save);
            if (savevalid(save) <= 1)
            {
                sav = atoi(save);
                flags = 0;
            }
            else
            {
                printf("Invalid Entry .\n");
                sav = atoi(save);
                flags = 1;
            }
        } while (flags);
        if (sav)
        {
            for (j = i; j < customer_count - 1; j++)
            {
                strcpy(customer[j].account_number, customer[j + 1].account_number);
                strcpy(customer[j].name, customer[j + 1].name);
                strcpy(customer[j].email, customer[j + 1].email);
                strcpy(customer[j].number, customer[j + 1].number);
                customer[j].balance = customer[j + 1].balance;
                customer[j].CustomerDate.month = customer[j + 1].CustomerDate.month;
                customer[j].CustomerDate.year = customer[j + 1].CustomerDate.year;
            }
            customer[customer_count - 1].name = NULL;
            customer[customer_count - 1].account_number = NULL;
            customer[customer_count - 1].email = NULL;
            customer[customer_count - 1].balance = 0.0;
            customer[customer_count - 1].CustomerDate.month = 1;
            customer[customer_count - 1].CustomerDate.year = 1;
            customer[customer_count - 1].number = NULL;
            customer_count--;
            printf("Succesful deletion .\n");
            Save();
        }
    }
    if (!flag)
        printf("Acccount not found .\n");
    if (!balance)
        printf("Balance is not 0.0 . Deletion couldn't be done .\n");
    menu();
}
void withdraw(void)
{
    float amount;
    char target[20], with[20], save[20];
    int index, flag = 0, sav, flags;
    float withx;
    printf("Please enter account number : ");
    scanf("%s", target);
    if (checkacc(target))
    {
        printf("Invalid account number .\n");
        menu();
    }
    printf("Please enter the amount to be withdrawn : ");
    scanf("%s", with);
    if (isvalid(with))
    {
        withx = atof(with);
    }
    else
    {
        printf("Invalid Entry .\n");
        menu();
    }
    for (int i = 0; i < customer_count; i++)
    {
        if (!(strcmp(customer[i].account_number, target)) && withx <= customer[i].balance)
        {
            flag = 1;
            index = i;
            break;
        }
    }
    if (withx > customer[index].balance)
    {
        printf("Insufficient balance .\n");
        menu();
    }
    if (flag)
    {
        do
        {
            printf("1.Save modification .\n0.Discard changes .\n");
            scanf("%s", save);
            if (savevalid(save) <= 1)
            {
                sav = atof(save);
                flags = 0;
            }
            else
            {
                printf("Invalid Entry .\n");
                flags = 1;
            }
        } while (flags);
        if (withx > 10000)
            printf("Exceeded withdrawal limit .\n");
        else if (withx <= customer[index].balance && sav)
        {
            customer[index].balance -= withx;
            printf("Successful transaction .\n");
            Save();
        }
    }
    else
        printf("Invalid account number .\n");
    if (flag && sav)
    {
        strcat(target, ".txt");
        FILE *file = fopen(target, "a");
        fprintf(file, "%.2f are withdrew. The updated balance is %.2f\n", withx, customer[index].balance);
        fclose(file);
    }
    menu();
}
void sortbybalance(account arr[])
{
    account hold;
    for (int i = 0; i < customer_count - 1; i++)
    {
        for (int j = 0; j < customer_count - i - 1; j++)
        {
            if (customer[j].balance > customer[j + 1].balance)
            {
                hold = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = hold;
            }
        }
    }
    for (int i = 0; i < customer_count; i++)
    {
        print(i);
        printf("\n");
    }
    menu();
}
void sortbyname(account arr[])
{
    account hold;
    for (int i = 0; i < customer_count - 1; i++)
    {
        for (int j = 0; j < customer_count - i - 1; j++)
        {
            if (strcmp(customer[j].name, customer[j + 1].name) == 1)
            {
                hold = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = hold;
            }
        }
    }
    for (int i = 0; i < customer_count; i++)
    {
        print(i);
        printf("\n");
    }
    menu();
}
void sortbydate(account arr[])
{
    account temp;
    for (int i = 0; i < customer_count - 1; i++)
    {
        for (int j = 0; j < customer_count - i - 1; j++)
        {
            if (customer[j].CustomerDate.year > customer[j + 1].CustomerDate.year)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            else if (customer[j].CustomerDate.year == customer[j + 1].CustomerDate.year && customer[j].CustomerDate.month > customer[j + 1].CustomerDate.month)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < customer_count; i++)
    {
        print(i);
        printf("\n");
    }
    menu();
}
void printsort(void)
{
    char x[20];
    printf("How would you like the data sorted ?\n");
    printf("1.NAME based\n2.BALANCE based\n3.DATE based\n");
    getchar();
    gets(x);
    int z = atoi(x);
    switch (z)
    {
    case 1:
        sortbyname(customer);
        break;
    case 2:
        sortbybalance(customer);
        break;
    case 3:
        sortbydate(customer);
        break;
    default:
    {
        printf("Invalid entry .\n");
        menu();
    }
    }
}
void quit(void)
{
    exit(0);
}
void menu(void)
{
    char in[20];
    printf("1.ADD\n2.DELETE\n3.MODIFY\n4.SEARCH\n5.ADVANCED SEARCH\n6.WITHDRAW\n7.DEPOSIT\n8.TRANSFER\n9.REPORT\n10.PRINT\n11.QUIT\n");
    scanf("%s", in);
    int a = atoi(in);
    switch (a)
    {
    case 1:
        add();
        break;
    case 2:
        delete ();
        break;
    case 3:
        modify();
        break;
    case 4:
        search();
        break;
    case 5:
        advSearch();
        break;
    case 6:
        withdraw();
        break;
    case 7:
        deposit();
        break;
    case 8:
        transfer();
        break;
    case 9:
        report();
        break;
    case 10:
        printsort();
        break;
    case 11:
        quit();
    default:
        flagvr = 1;
        printf("Invalid entry .\n");
        menu();
    }
}
void minimenu(void)
{
    char x[20];
    printf("1.LOGIN\n");
    printf("2.QUIT\n");
    gets(x);
    int y = atoi(x);
    if (y == 1)
    {
        Login();
    }
    else if (y == 2)
        quit();
    else
    {
        minimenu();
    }
}
void print(int index)
{
    char result[10];
    printf("Account Number : %s\n", customer[index].account_number);
    printf("Name : %s\n", customer[index].name);
    printf("Email : %s\n", customer[index].email);
    printf("Number : %s\n", customer[index].number);
    printf("Balance : %.2f EGP\n", customer[index].balance);
    convert(customer[index].CustomerDate.month, result);
    printf("Date : %s %d\n", result, customer[index].CustomerDate.year);
}
int main(void)
{
    minimenu();
    return 0;
}
