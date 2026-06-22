#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct expense
{
    char date[15];
    char category[100];
    int amt;
    char description[500];
}expenses[1000];
int count = 0 ;
void saveExpense()
{
    FILE *fp = fopen("expenses.txt", "w");
    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    for(int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %s %d %s\n", expenses[i].date, expenses[i].category, expenses[i].amt, expenses[i].description);
    }
    fclose(fp);
}
void loadExpense()
{
    FILE *fp = fopen("expenses.txt", "r");
    
    count = 0;
    while(fscanf(fp, "%s %s %d %s", expenses[count].date, expenses[count].category, &expenses[count].amt, expenses[count].description) == 4)
    {
        count++;
    }
    fclose(fp);
}
void addExpense()
{
    printf("Enter date (dd/mm/yyyy): ");
    scanf("%s", expenses[count].date);
    getchar();   // remove newline left by scanf

    printf("Enter category: ");
    fgets(expenses[count].category,
          sizeof(expenses[count].category),
          stdin);
    expenses[count].category[strcspn(expenses[count].category, "\n")] = '\0';

    printf("Enter amount: ");
    scanf("%d", &expenses[count].amt);
    getchar();   // remove newline left by scanf

    printf("Enter description: ");
    fgets(expenses[count].description,
          sizeof(expenses[count].description),
          stdin);
    expenses[count].description[strcspn(expenses[count].description, "\n")] = '\0';

    count++;

    printf("Expense added successfully!\n");
}
void viewExpense()
{
    if(count == 0)
    {
        printf("No expenses to display.\n");
        return;
    }

    printf("\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("%-5s %-15s %-20s %-10s %-30s\n",
           "ID", "Date", "Category", "Amount", "Description");
    printf("--------------------------------------------------------------------------------------------------\n");

    for(int i = 0; i < count; i++)
    {
        printf("%-5d %-15s %-20s %-10d %-30s\n",
               i + 1,
               expenses[i].date,
               expenses[i].category,
               expenses[i].amt,
               expenses[i].description);
    }

    printf("--------------------------------------------------------------------------------------------------\n");
}
void editExpense()
{
    if(count == 0)
    {
        printf("No expenses to edit.\n");
        return;
    }
    printf("Enter the Expense ID to edit: ");
    int index;
    scanf("%d", &index);
    if(index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }
    printf("\nCurrent Details:\n");
    printf("Date: %s\n", expenses[index].date);
    printf("Category: %s\n", expenses[index].category);
    printf("Amount: %d\n", expenses[index].amt);
    printf("Description: %s\n", expenses[index].description);

    printf("Enter new date (dd/mm/yyyy): ");
    scanf("%s", expenses[index].date);
    getchar();   // remove newline left by scanf

    printf("Enter new category: ");
    fgets(expenses[index].category,
          sizeof(expenses[index].category),
          stdin);
    expenses[index].category[strcspn(expenses[index].category, "\n")] = '\0';

    printf("Enter new amount: ");
    scanf("%d", &expenses[index].amt);
    getchar();   // remove newline left by scanf

    printf("Enter new description: ");
    fgets(expenses[index].description,
          sizeof(expenses[index].description),
          stdin);
    expenses[index].description[strcspn(expenses[index].description, "\n")] = '\0';

    printf("Expense updated successfully!\n");
}
void deleteExpense()
{
    if(count == 0)
    {
        printf("No expenses to delete.\n");
        return;
    }
    printf("Enter the index of the expense to delete: ");
    int index;
    scanf("%d", &index);
    if(index < 0 || index >= count)
    {
        printf("Invalid index.\n");
        return;
    }
    for(int i = index; i < count - 1; i++)
    {
        expenses[i] = expenses[i + 1];
    }
    count--;
}
void searchExpense()
{
    if(count == 0)
    {
        printf("No expenses to search.\n");
        return;
    }
    printf("Enter the category to search: ");
    char category[100];
    scanf("%s", category);
    int found = 0;
    for(int i = 0; i < count; i++)
    {
        if(strcmp(expenses[i].category, category) == 0)
        {
            printf("Date: %s\n", expenses[i].date);
            printf("Category: %s\n", expenses[i].category);
            printf("Amount: %d\n", expenses[i].amt);
            printf("Description: %s\n", expenses[i].description);
            printf("-----------------------------\n");
            found = 1;
        }
    }
    if(!found)
    {
        printf("No expenses found in the specified category.\n");
    }
}
void sortExpense()
{
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(expenses[j].amt > expenses[j + 1].amt)
            {
                struct expense temp = expenses[j];
                expenses[j] = expenses[j + 1];
                expenses[j + 1] = temp;
            }
        }
    }
    printf("Expenses sorted successfully.\n");
}
int main()
{
    loadExpense();
    while(1)
    {
        printf("==========Expense Tracker==========\n");
        printf("1.Add Expense\n");
        printf("2.View Expenses\n");
        printf("3.Edit Expense\n");
        printf("4.Delete Expenses\n");
        printf("5.Search Expenses\n");
        printf("6.Sort Expenses\n");
        printf("7.Exit\n");
        printf("===================================\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                addExpense();
                saveExpense();
                break;
            case 2:
                viewExpense();
                break;
            case 3:
                editExpense();
                saveExpense();
                break;
            case 4:
                deleteExpense();
                saveExpense();
                break;
            case 5:
                searchExpense();
                break;
            case 6:
                sortExpense();
                saveExpense();
                break;
            case 7:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
    }
    return 0;
}