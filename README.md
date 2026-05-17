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
![Block Diagram](images/image_0.jpg)

---

### 🔌 Circuit Schematic
![Circuit Schematic](images/image_1.jpg)

---

### ▶️ Welcome Screen
![Welcome](images/image1.jpg)

---

### 🔍 Scan Selection (Manager/Product)
![Scan](images/image2.jpg)

---

### ⚙️ Manager Updating Products
![Manager Update](images/image3.jpg)

---

### ✅ Product Update Success
![Update Success](images/image4.jpg)

---

### 💰 Product Price & Total Bill
![Billing](images/image5.jpg)

---

### 🖥️ Product List on PC
![PC Display](images/image6.jpg)

---

### ❌ Scan to Delete Product
![Delete Scan](images/image7.jpg)

---

### 💸 Updated Price After Deletion
![Delete Price](images/image8.jpg)

---

### 🖥️ Updated Product List on PC
![PC Updated](images/image9.jpg)

---

### 💳 Payment Mode Selection
![Payment Mode](images/image10.jpg)

---

### 🔢 Enter Amount
![Enter Amount](images/image11.jpg)

---

### 💳 Swipe Card
![Swipe](images/image12.jpg)

---

### ❗ Wrong PIN
![Wrong PIN](images/image13.jpg)

---

### 🎉 Transaction Success
![Thank You](images/image14.jpg)

---

## 👨🏻‍💻 Author

**J Bhargava Satish**
