#include "file_op_header.h"

/*
function to load stock data from csv file
this function reads stock.csv and stores data into product database
*/
void load_stock()
{
    // open stock file in read mode 
    FILE *fp = fopen("Stock.csv","r");

    // return if file not found 
    if(!fp) return;

    // buffer to store each line 
    char line[256];

    // skip header line 
    fgets(line,sizeof(line),fp);

    // initialize database size 
    db_size = 0;

    // read file line by line 
    while(fgets(line,sizeof(line),fp))
    {
        // parse csv data and store into database 
        if(sscanf(line,"%[^,],%[^,],%d,%f",db[db_size].product_name,db[db_size].product_id,
                                &db[db_size].quantity,&db[db_size].price)==4)
        {
            // increment database size 
            db_size++;
        }
    }

    // close file 
    fclose(fp);
}

/*
function to load bank data from csv file
this function reads bank.csv and stores data into users database
*/
void load_bank()
{
    // open bank file in read mode */
    FILE *fp = fopen("Bank.csv","r");

    // return if file not found 
    if(!fp) return;

    // buffer to store each line 
    char line[256];

    // skip header line 
    fgets(line,sizeof(line),fp);

    // read file line by line 
    while(fgets(line,sizeof(line),fp))
    {
        // parse csv data and store into users database 
        sscanf(line,"%[^,],%[^,],%[^,],%[^,],%[^,],%d,%f",users[user_size].place,users[user_size].ifsc,
                        users[user_size].bank,users[user_size].name,users[user_size].cardnumber,&users[user_size].pin,
            &users[user_size].balance);

        // increment user size 
        user_size++;
    }

    // close file 
    fclose(fp);
}

/*
function to update stock file
this function writes current product database into stock.csv
*/
void update_stock_file()
{
    // open stock file in write mode
    FILE *fp = fopen("Stock.csv","w");

    // return if file not opened
    if(!fp) return;

    // write header line
    fprintf(fp,"ItemName,CardID,Qty,Price\n");

    // loop through database
    for(int i=0;i<db_size;i++)
    {
        // write each product data
        fprintf(fp,"%s,%s,%d,%0.2f\n",db[i].product_name,db[i].product_id,db[i].quantity,db[i].price);
    }

    // close file
    fclose(fp);
}

/*
function to update bank file
this function writes current users data into bank.csv
*/
void update_bank_file()
{
    // open bank file in write mode
    FILE *fp = fopen("Bank.csv","w");

    // return if file not opened
    if(!fp) return;

    // write header line
    fprintf(fp,"place,ifsc,bank,name,cardnumber,pin,balance\n");

    // loop through users
    for(int i=0;i<user_size;i++)
    {
        // write each user data
        fprintf(fp,"%s,%s,%s,%s,%s,%d,%.2f\n",users[i].place,users[i].ifsc,users[i].bank,
                        users[i].name,users[i].cardnumber,users[i].pin,users[i].balance);
    }

    // close file
    fclose(fp);
}

/*
function to add bill details into file
this function appends transaction details with timestamp
*/
void add_bill_to_file(float cash, char *mode)
{
    // open file in append mode
    FILE *fp = fopen("cash.csv","a");

    // return if file not opened
    if(!fp) return;

    // buffer to store date and time
    char time_date[30];

    // get current time
    time_t t = time(NULL);

    // convert time to local format
    struct tm *tm_info = localtime(&t);

    // format time into string
    strftime(time_date,sizeof(time_date),"%d-%m-%Y %H:%M:%S",tm_info);

    // write bill details
    fprintf(fp,"%f,%s,%s\n",cash,time_date,mode);

    // close file
    fclose(fp);
}