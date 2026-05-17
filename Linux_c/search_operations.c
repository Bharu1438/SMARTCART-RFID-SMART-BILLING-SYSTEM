/*
include header file which contains function declarations and required dependencies
*/
#include "search_op_header.h"

/*
this function searches for a product in database using product id
it returns index of product if found otherwise returns -1
*/
int find_product(char *id)
{
    for(int i=0;i<db_size;i++)
    if(strncmp(db[i].product_id+1,id,8)==0)
    return i;
    return -1;
}

/*
this function searches for a user account using card id
it returns index of user if found otherwise returns -1
*/
int find_account(char *id)
{
    for(int i=0;i<user_size;i++)
    if(strncmp(users[i].cardnumber+1,id+1,8)==0)
    return i;
    return -1;
}

/*
this function calculates total bill amount from all items in cart
it also displays cart details on screen
*/
float total_bill()
{
    float total = 0;

#ifdef USE_USB
    printf("\033[2J\033[H");
#endif

    printf("\n------------------ Hari Mart ------------------\n");
    printf("%-20s %-7s %-7s\n","Item","Qty","Price");
    printf("------------------------------------------------\n");

    for(int i=0;i<cart_size;i++)
    {
        printf("%-20s %-7d %-7.2f\n",cart[i].product_name,cart[i].quantity,cart[i].price);
        total += cart[i].quantity * cart[i].price;
    }

    printf("------------------------------------------------\n");
    printf("%30s : %.2f\n","Total",total);
    return total;
}

/*
this function checks whether given card id belongs to manager
it reads manager card data from file and compares
returns 'M' if manager card otherwise returns 'C'
*/
char find_manager_card(char *id)
{
    char card_buffer[20];
    FILE *fp = fopen("Manager_card.csv", "r");
    if(fp == NULL)
    return '\0';
    id[strcspn(id, "$")] = '\0';
    while(fgets(card_buffer, sizeof(card_buffer), fp))
    {
        card_buffer[strcspn(card_buffer, "$")] = '\0';
        if(strcmp(card_buffer + 1, id) == 0)
        {
            fclose(fp);
            return 'M';
        }
    }
    fclose(fp);
    return 'C';
}
