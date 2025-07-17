# 🚌 Bus Reservation System in C

A terminal-based **Bus Reservation System** developed in **C language**. This project simulates a basic bus ticket booking system with **user authentication**, **seat availability**, **admin access**, and **ticket pricing**. It is suitable for academic purposes and beginner-level system projects.

---

## 🎯 Objective

To create a simple and user-friendly bus ticket reservation system where users can:
- ✅ User Sign Up & Sign In with Phone & PIN
- 🎟 Ticket Booking with Available Seat Display
- 🕒 Fixed Departure Times: 6 AM, 12 PM, 6 PM
- 🌍 Locations: Dhaka, Barishal, Chittagong, Faridpur, Kurigram
- 💵 Ticket Price Display and File Storage
- 📂 Ticket Saved to File (`ticket.txt`)
- 🔐 Admin Panel for Monitoring
- 🎨 Colored UI for Sign In/Up Screens
- 🚫 Input Validations (Phone: 11-digit, PIN Retry, Exit Option)
- 🆔 Unique Ticket ID Generating (e.g., TRIP0001) for each booking

---
## 🔍 Features in Detail
### 👤 User Authentication
- **Sign Up**: Register using phone number and PIN (saved in file `signup.txt`)
- **Sign In**: Log in with registered phone number and PIN (PIN validation included)
- Input validation: 
  - Phone number must be **exactly 11 digits**
  - If PIN is wrong, the user is asked to retry

---

### 🧾 Ticket Booking
- Once logged in, users can:
  - Select **departure** and **destination** locations from the following:
    - Dhaka
    - Barishal
    - Chittagong
    - Faridpur
    - Kurigram
  - Select one of the fixed **departure times**:
    - 6 AM
    - 12 PM
    - 6 PM
  - See **available seats**
  - Book tickets (enter number of seats)
  - **Ticket price** is calculated and shown (price depends on route)
  - Ticket is saved in `ticket.txt`

---
### 💵 Ticket Pricing
- Pricing varies based on destination and route
- Displayed before final booking confirmation
- Included in `ticket.txt`

---
### 🆔 Ticket ID

Every ticket you book gets a unique **Ticket ID** (e.g., `TKT1234`)  
This helps users and admins to identify and track individual tickets easily.
---

### 🧑‍💼 Admin Panel
- Accessible through Sign In (with specific admin credentials)
- Admin can view system activity or reserved tickets (future extension possible)

---

### 🎨 UI Enhancements
- Colored Sign In/Sign Up screens using console color functions
- Clear screen and proper UI flow in terminal
- Exit option included in main menu

---

## 🛠 Technologies Used

- Language: **C**
- Compiler: `gcc`
- Platform: Terminal-based (Linux/Windows)
- File I/O: Used to store users (`signup.txt`) and tickets (`ticket.txt`)

---

## 📂 File Structure

```
BusReservationSystem/
├── Bus_reservasion_V1.c        # Main source code
├── README.md                   # Project documentation
├── LICENSE                     # MIT License
├── .gitignore                  # Git ignored files
└── sample_output.txt           # Sample terminal output
```

---

## 🖥 How to Compile and Run

Open terminal in this folder and run:

```bash
gcc Bus_reservasion_V1.c -o bus_app
./bus_app
```

---

## 📷 Sample Output

See `sample_output.txt` for a sample run of the system.

---

## 👨‍🎓 Author

- **Anoy Khan**
- 2nd Semester Student, BUBT
- 🔗 [Portfolio](https://anoykhan.github.io/Portfolio_2nd/)

---

## 📄 License

This project is licensed under the **MIT License**. See [LICENSE](LICENSE) for details.

---

⭐ **If you found this project useful, please give it a star on GitHub!**
