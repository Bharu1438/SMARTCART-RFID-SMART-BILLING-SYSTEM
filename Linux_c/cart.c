#include "cart.h"

/*
function to update stock details
this function continuously takes product input from user
if product exists it updates quantity and price
if product not exists it adds new product to database
loop stops when user enters "completed"
*/
void update_stock()
{
    // infinite loop to continuously take input
    while (1)
    {
        // array to store product name
        char name[50];

        // index to track product position
        int ind = -1, quantity;

        // buffer for input values
        char buffer[50];

        // prompt user
        printf("\n(Enter completed to stop)\nEnter product name: ");

        // read product name
        fgets(name, sizeof(name), stdin);

        // remove newline character
        name[strcspn(name, "\n")] = '\0';

        // check for exit condition
        if (strcmp(name, "completed") == 0)
        {
#ifdef USE_USB
            // send completed message via uart
            write(uart_fd, "completed$", 10);
#else
            // print success message
            printf("success\n");
#endif
            // update stock file
            update_stock_file();

            // reset flag
            flag = 0;

            // exit loop
            break;
        }

        // search product in database
        for (int i = 0; i < db_size; i++)
        {
            // compare product names
            if (strcmp(name, db[i].product_name) == 0)
            {
                // store index if found
                ind = i;

                // break loop
                break;
            }
        }

        // if product not found
        if (ind == -1)
        {
            // copy product name
            strcpy(db[db_size].product_name, name);

            // take product id
            printf("Enter Product ID: ");
            fgets(buffer, sizeof(buffer), stdin);

            // remove newline
            buffer[strcspn(buffer, "\n")] = '\0';

            // store product id
            strcpy(db[db_size].product_id, buffer);

            // take quantity
            printf("Enter Quantity: ");
            fgets(buffer, sizeof(buffer), stdin);

            // convert and store quantity
            db[db_size].quantity = atoi(buffer);

            // take price
            printf("Enter Price: ");
            fgets(buffer, sizeof(buffer), stdin);

            // convert and store price
            db[db_size].price = atof(buffer);

            // increase database size
            db_size++;
        }
        else
        {
            // take quantity
            printf("Enter Quantity: ");
            fgets(buffer, sizeof(buffer), stdin);

            // convert quantity
            quantity = atoi(buffer);

            // update quantity
            db[ind].quantity += quantity;

            // take price
            printf("Enter Price: ");
            fgets(buffer, sizeof(buffer), stdin);

            // update price
            db[ind].price = atof(buffer);

            // print update message
            printf("%s updated\n", db[ind].product_name);
        }
    }
}

/*
function to add product into cart
this function checks product availability using id
if product exists it adds to cart or increments quantity
also updates total bill and sends data via uart or prints
*/
void add_to_cart(char *id)
{
    // variable to store total price
    float price;

    // buffers for formatted price
    char price_buff[20], product_price_buff[20];

    // find product index
    int ind = find_product(id);

    // return if product not found
    if (ind == -1) return;

    // check stock availability
    if (db[ind].quantity <= 0)
    {
        // print out of stock
        printf("Out of stock\n");

        // return
        return;
    }

    // loop through cart
    for (int i = 0; i < cart_size; i++)
    {
        // check if product already exists in cart
        if (strcmp(cart[i].product_name, db[ind].product_name) == 0)
        {
            // increase cart quantity
            cart[i].quantity++;

            // decrease stock
            db[ind].quantity--;

            // calculate total bill
            price = total_bill();

            // format total price
            sprintf(price_buff, "%.2f$", price);

            // format product price
            sprintf(product_price_buff, "%.2f$", db[ind].price);

#ifdef USE_USB
            // send product price
            write(uart_fd, product_price_buff, strlen(product_price_buff));

            // send total price
            write(uart_fd, price_buff, strlen(price_buff));
#else
            // print product price
            printf("product Price : %s\n", product_price_buff);

            // print total price
            printf("total price : %s\n", price_buff);
#endif
            // return after update
            return;
        }
    }

    // copy product name to cart
    strcpy(cart[cart_size].product_name, db[ind].product_name);

    // set quantity
    cart[cart_size].quantity = 1;

    // set price
    cart[cart_size].price = db[ind].price;

    // decrease stock
    db[ind].quantity--;

    // increase cart size
    cart_size++;

    // calculate total bill
    price = total_bill();

    // format total price
    sprintf(price_buff, "%.2f$", price);

    // format product price
    sprintf(product_price_buff, "%.2f$", db[ind].price);

#ifdef USE_USB
    // send product price
    write(uart_fd, product_price_buff, strlen(product_price_buff));

    // send total price
    write(uart_fd, price_buff, strlen(price_buff));
#else
    // print product price
    printf("product Price : %s\n", product_price_buff);

    // print total price
    printf("total price : %s\n", price_buff);
#endif
}

/*
function to delete product from cart
this function reduces quantity or removes product from cart
also updates stock and recalculates total bill
*/
void delete_product(char *id)
{
    // initialize total price
    float price = 0.0;

    // buffers for formatted price
    char price_buff[20], product_price_buff[20];

    // check if cart is empty
    if (cart_size == 0)
    {
        // set total price to zero
        sprintf(price_buff, "%.2f$", 0.00);

        // set product price to zero
        sprintf(product_price_buff, "%.2f$", 0.00);

#ifdef USE_USB
        // send total price
        write(uart_fd, price_buff, strlen(price_buff));

        // send product price
        write(uart_fd, product_price_buff, strlen(product_price_buff));
#else
        // print price
        printf("price : %s\n", price_buff);

        // print total price
        printf("total price : %s\n", product_price_buff);
#endif
        // clear screen
        printf("\033[2J\033[H");

        // print message
        printf("cart is empty\n");

        // delay
        sleep(1);

        // clear screen again
        printf("\033[2J\033[H");

        // return
        return;
    }

    // find product index
    int ind = find_product(id);

    // if not found
    if (ind == -1)
    {
#ifdef USE_USB
        // send error message
        write(uart_fd, "product notfound$", 17);

        // send zero price
        write(uart_fd, "0.00$", 5);
#endif
        // print error
        printf("Product not found\n");

        // return
        return;
    }

    // loop through cart
    for (int i = 0; i < cart_size; i++)
    {
        // match product
        if (strcmp(db[ind].product_name, cart[i].product_name) == 0)
        {
            // decrease cart quantity
            cart[i].quantity--;

            // increase stock
            db[ind].quantity++;

            // if quantity becomes zero
            if (cart[i].quantity == 0)
            {
                // shift elements
                for (int j = i; j < cart_size - 1; j++)
                    cart[j] = cart[j + 1];

                // decrease cart size
                cart_size--;

                // clear screen
                printf("\033[2J\033[H");

                // print header
                printf("--------------------Harika Mart--------------------\n");
            }

            // calculate total bill
            price = total_bill();

            // format total price
            sprintf(price_buff, "%.2f$", price);

            // format product price
            sprintf(product_price_buff, "%.2f$", db[ind].price);

#ifdef USE_USB
            // send product price
            write(uart_fd, product_price_buff, strlen(product_price_buff));

            // send total price
            write(uart_fd, price_buff, strlen(price_buff));
#else
            // print product price
            printf("product Price : %s\n", product_price_buff);

            // print total price
            printf("total price : %s\n", price_buff);
#endif
            // return after deletion
            return;
        }
    }

    // print if product not in cart
    printf("Product not in cart\n");
}

