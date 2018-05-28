#include<stdio.h>
#include<stdlib.h>
#include "string.h"

typedef struct user{
    int m_account_number;
    char m_phone_number[12];
    char m_date[10];
    char m_address[100];
    char m_type_account[50];
    char m_name[100];
    int m_age;
    char m_country[50];
    int m_id[9];
}user_t;

typedef struct node{
    int m_account_num;
    float m_money;
    char m_date_creation[10];
    user_t *person;
    struct node *next;
}node_t;
node_t* search_in_list(node_t** head, int account_number);

int menu()
{
    int user_selection;
    printf("CUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n");
    printf("*************** WELCOME TO THE MAIN MENU *************************\n");
    printf("\n");
    printf("1.Create new account\n2.Update information of existing account\n 3.For transactions\n4.Check the details of existing account\n5.Removing existing account\n6.View customer's list\n7.Exit\n\n\n Enter your choice:");
    scanf("%d",&user_selection);
    return user_selection;
}

void CreateNewAcount( node_t** head)
{
    user_t *person = NULL;
    person = malloc(sizeof(user_t));
    if (person == NULL)
        return;
    float money_to_seposit;
    char* date_creation;
    printf("Enter today's date(mm/dd/yyyy):");
    scanf("%s",&date_creation);
    printf("\nEnter the account number:");
    scanf("%d",&(person->m_account_number));
    printf("\nEnter the name:");
    scanf("%s",person->m_name);
    printf("\nEnter the date of birth(mm/dd/yyyy):");
    scanf("%s",person->m_date);
    printf("\nEnter the age:");
    scanf("%d",&person->m_age);
    printf("\nEnter the address:");
    scanf("%s",person->m_address);
    printf("\nEnter the ID number:");
    scanf("%d",&person->m_id);
    printf("Enter amount of money you want to deposit:");
    scanf("%f",&money_to_seposit);
    printf("\nEnter the phone number: ");
    scanf("%s",person->m_phone_number);
    push(head,person,&date_creation,money_to_seposit);

}
void UpdateAcountInfo(node_t** head)
{
    int account_num,user_selection;
    printf("Enter the account no. of the customer whose info you want to change:\n");
    scanf("%d",&account_num);
    node_t* account_to_edit = search_in_list(head,account_num);
    if (account_to_edit == NULL)
    {
        printf("There is no account with this number - back to menu\n");
        return;
    }

    printf("\nWhich information do you want to change?\n1.Address\n2.Phone\n\nEnter your choice(1 for address and 2 for phone):");
    scanf("%d",&user_selection);
    switch (user_selection)
    {
        case 1:
        {
            printf("Enter the new address:");
            scanf("%s",account_to_edit->person->m_address);
            printf("Changes saved!");
            break;
        }
        case 2:
        {
            printf("Enter the new phone number:");
            scanf("%s",&account_to_edit->person->m_phone_number);
            printf("Changes saved!");
            break;
        }
        default:
        {
            printf("there is no such option in menu, try again..:)");
            break;
        }
    }

}

node_t* GetUserInput(node_t** head)
{
    int account_num;
    printf("Enter the account no. of the customer:");
    scanf("%d",&account_num);
    node_t* account_to_edit = search_in_list(head,account_num);
    if (account_to_edit == NULL)
        printf("There is no account with this number\n");
    return account_to_edit;
}

void WithdrawORDepostingMoney(node_t** head)
{
    int amount;
    int user_selection;
    node_t* account = GetUserInput(head);
    if (account == NULL)
        return;
    printf("Do you want to\n1.Deposit\n2.Withdraw?\n\nEnter your choice(1 for deposit and 2 for withdraw):");
    scanf("%d",&user_selection);
    switch (user_selection)
    {
        case 1:{
            printf("Enter the amount you want to deposit:$ ");
            scanf("%f",&amount);
            account->m_money += amount;
            printf("your money has been deposited into your bank acount");
            break;
        }
        case 2:{
            printf("Enter the amount you want to withdraw:$ ");
            scanf("%f",&amount);
            account->m_money -= amount;
            if(account->m_money < 0)
                printf("your account is in debit balance");
            else
                printf("Money Withdrawal was successful");
            break;
        }
        default:
            printf("there is no such option in menu, try again..:)");
            break;

    }

}
void DeleteAcount(node_t** head)
{
    int account_num;
    printf("Enter the account no. of the customer:");
    scanf("%d",&account_num);
    Delete_node(head,account_num);
}


void ShowAcountTypeInfo(node_t** head)
{
    node_t* user_account = GetUserInput(head);
    if (user_account == NULL)
    {
        return;
    }
    printf("Account Number: %d\n",user_account->m_account_num);
    printf("Name: %s\n",user_account->person->m_name);
    printf("Address: %s\n",user_account->person->m_address);
    printf("Phone Number: %s\n",user_account->person->m_phone_number);
}

/***********************************************************************
*Function Name:push
*Function input:ptr to head of linked list, ptr to user struct
*Function output:none
*Function Action:the function push a new account to list.To iterate over
 * the linked list, we use a pointer "current" and set it to start from
 * the head and then in each step, we advance the pointer to the next
 * item in the list, until we reach the last item.
***********************************************************************/
void push(node_t** head,  user_t* m_user, char* date, float money) {
    //user_t *usr=m_user;
    node_t *new_node= (node_t*)malloc(sizeof(node_t));
    new_node->m_account_num=m_user->m_account_number;
    new_node->person=m_user;
    new_node->m_money=money;

    new_node->next=NULL;
    strcpy(new_node->m_date_creation,date);

    if(*head == NULL)
    {
        *head=new_node;
        return;
    }
    node_t* current = *head;

        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next=new_node;
    return;
}

void PopNode(node_t** head)
{
    node_t* new_head=NULL;
    if (*head == NULL)
    {
        printf("The list is empty\n");
        return;
    }
    new_head = (*head)->next;
    free(*head);
    *head=new_head;
}

void Delete_node(node_t** head, int account_num)
{
    node_t* current = *head;
    node_t* temp_node=NULL;
    if ((*head)->m_account_num == account_num)
    {
        PopNode(head);
        return;
    }
    while (current->next->m_account_num != account_num && current->next !=NULL)
    {
        current=current->next;
    }
    if(current->next == NULL)
    {
        printf("there is no account number\n");
        return;
    }
    temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);


}

node_t* search_in_list(node_t** head, int account_number)
{
    node_t* current = *head;
    while (current != NULL)
    {
        if(current->m_account_num == account_number)
        {
            return current;
        }
        current=current->next;
    }
    return current;
}

void Free_List(node_t** head)
{
    node_t* temp_node=NULL;
    node_t* current = *head;
    while (current !=NULL)
    {
        temp_node = current;
        current=current->next;
        free(temp_node);
    }
    *head=NULL;
}


int main()
{
    int user_selection=menu();
    node_t *head=NULL;

    while (user_selection != 7)
    {
        switch (user_selection)
        {
            case 1:
                CreateNewAcount(&head);
                break;

            case 2:
                UpdateAcountInfo(&head);
                break;
            case 3:
                WithdrawORDepostingMoney(&head);
                break;
            case 4:
                ShowAcountTypeInfo(&head);
                break;
            case 5:
                DeleteAcount(&head);
                break;
            default:
                break;
        }
        user_selection = menu();
    }
    Free_List(&head);

    return 0;
}
