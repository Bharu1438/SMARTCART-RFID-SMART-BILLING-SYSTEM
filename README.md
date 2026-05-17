# 🛒 SMARTCART: RFID SMART BILLING SYSTEM

This project is an embedded system developed using a **microcontroller-based design** that enables automatic billing using **RFID technology**.  
It simplifies shopping by eliminating manual billing and reducing checkout time.

## ✨ Features

- RFID-based product identification  
- Automatic cart billing system  
- Real-time total price calculation  
- Manager mode for updating products  
- Product add/remove functionality  
- LCD display for user interaction  
- Keypad-based input for payment  
- Secure card payment with PIN verification  
- UART communication to display data on PC  

## 💻 Hardware Used

- Microcontroller (ARM / Embedded Controller)  
- RFID Reader & RFID Tags  
- 16x2 LCD Display  
- Keypad  
- Buzzer  
- UART (Serial Communication Interface)  
- PC for product monitoring  

## ⏳ How It Works

1. System starts and displays a welcome message.  
2. User scans RFID card (Manager/Product).  
3. Manager can update product details in database.  
4. User scans product tags to add items to cart.  
5. System displays product price and updates total bill.  
6. User can delete items using RFID scan.  
7. Cart details are sent to PC via UART.  
8. User selects payment mode using keypad.  
9. For card payment, user enters PIN.  
10. If PIN is correct → transaction successful.  
11. System displays “Thank You” message.  

---

## 🌄 Project Images

### ⏺️ Block Diagram
![Block Diagram](Images/Image_0.png)

This diagram shows the overall architecture of the system, including the LPC2148 microcontroller connected with RFID reader, LCD, keypad, switches, and PC via UART.

---

### 🔌 Circuit Schematic
![Circuit Schematic](Images/Image_1.jpeg)

This schematic represents the complete hardware connections of the system, including power supply, LCD interfacing, RFID module, keypad, and serial communication.

---

### ▶️ Welcome Screen
![Welcome](Images/Image1.png)

This screen appears when the system is powered on, displaying a welcome message to the user.

---

### 🔍 Scan Selection (Manager/Product)
![Scan](Images/Image2.png)

The system prompts the user to scan an RFID card, identifying whether it is a manager card or a product card.

---

### ⚙️ Manager Updating Products
![Manager Update](Images/Image3.png)

This screen is displayed when the manager is updating product details such as price or product information.

---

### ✅ Product Update Success
![Update Success](Images/Image4.png)

Indicates that the product information has been successfully updated in the system database.

---

### 💰 Product Price & Total Bill
![Billing](Images/Image5.png)

Displays the scanned product price along with the updated total cart value.

---

### 🖥️ Product List on PC
![PC Display](Images/Image6.png)

Shows the list of products and billing details on the PC through UART communication.

---

### ❌ Scan to Delete Product
![Delete Scan](Images/Image7.png)

Prompts the user to scan a product card to remove it from the cart.

---

### 💸 Updated Price After Deletion
![Delete Price](Images/Image8.png)

Displays the updated total after removing a product from the cart.

---

### 🖥️ Updated Product List on PC
![PC Updated](Images/Image9.png)


Shows the updated cart details on the PC after deletion of a product.

---

### 💳 Payment Mode Selection
![Payment Mode](Images/Image10.png)

Allows the user to choose a payment method using the keypad.

---

### 🔢 Enter Amount
![Enter Amount](Images/Image11.png)

Prompts the user to enter the payment amount via keypad.

---

### 💳 Swipe Card
![Swipe](Images/Image12.png)

Requests the user to swipe their card to proceed with payment.

---

### ❗ Wrong PIN
![Wrong PIN](Images/Image13.png)

Displays an error message if the entered PIN is incorrect.

---

### 🎉 Transaction Success
![Thank You](Images/Image14.png)

Displays thank you message if the transaction is successful.

---

## 👨🏻‍💻 Author

**J Bhargava Satish**
