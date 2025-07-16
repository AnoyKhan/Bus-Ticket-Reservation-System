# 📘 User Manual – Bus Reservation System in C

Welcome to the **Bus Reservation System** developed in C. This manual will guide you through each part of using the system – from logging in to booking your ticket. Designed for easy navigation and a beginner-friendly experience.

---

## 🖥 1. Starting the Program

To start the program, open your terminal in the project folder and type:

```bash
gcc Bus_reservasion_V1.c -o bus_app
./bus_app
```
---
## 🔐 2. Main Menu
Once launched, you will see:
```
===== Welcome to the Bus Reservation System =====

1. Sign In
2. Sign Up
3. Exit

```
Choose an option by entering the corresponding number.

---

## 🧾 3. Sign Up (New User)
- Choose option 2 (Sign Up)
- Enter:
  - Your phone number (must be 11 digits, e.g., 01712345678)
  - A secure PIN
- Your credentials will be saved in signup.txt

You can now log in using this phone and PIN.

---

## 🔑 4. Sign In (Existing User)
- Choose option 1 (Sign In)
- Enter your:
  - Phone number 
  - PIN
- If incorrect, the system will prompt you to retry without exiting
- If correct, you will enter the booking system
---
## 🚍 5. Booking a Ticket
Once signed in:
1. Select departure and destination from:
   - Dhaka 
   - Barishal 
   - Chittagong
   - Faridpur
   - Kurigram
2. Choose a departure time:
   - 6 AM
   - 12 PM
   - 6 PM
3. Choose a departure time:
  - Available seats
  - Ticket price (based on route)
4. Enter number of tickets to book
5. Confirmation message:
   - Total price shown
   - Ticket is saved to ticket.txt
---
### 🆔 Ticket ID
Every ticket you book gets a unique **Ticket ID** (e.g., `TKT1234`)  
This helps users and admins to identify and track individual tickets easily.
---

## 🧑‍💼 6. Admin Panel
- Admin can log in using predefined credentials (admin phone & pin)
- Admin can view/manage booking data (future extension)
---
## 💡 7. Input Validation & Exit Option
- Phone number must be 11 digits
- PIN must match existing user
- Option to exit the system any time from main menu
---
## 📁 Output Files
- accounts.txt → Stores user credentials
- ticket.txt → Stores all booked ticket information
---
## 📌 Notes
- Ensure proper use of input (e.g., exact format for phone number)
- Only valid selections are accepted
- Console text may appear with colors for better readability
---
## For any issue, contact the author: Anoy Khan
- 📧 Email: anoykhan14@gmail.com
- 🌐 Portfolio: https://anoykhan.github.io/Portfolio_2nd/