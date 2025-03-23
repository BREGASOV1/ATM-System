# ATM System (C++ Console Application)

A console-based ATM simulator that handles financial transactions and user authentication, with persistent data storage in text files.

## Features 🏦
- User authentication (Account Number + PIN)
- Quick withdrawals (predefined amounts)
- Normal withdrawals (custom multiples of 5)
- Deposit functionality
- Balance checking
- Persistent data storage (`Clients.txt`)
- Interactive console menus
- Input validation

## Installation & Usage 💻

### Requirements
- C++ compiler (GCC, Clang, or MSVC)
- Terminal/Command Prompt

### Quick Start
1. Compile the code:
   ```bash
   g++ main.cpp -o atm

 #Run the executable:

./atm  # Linux/Mac
atm.exe  # Windows

Data File Format (Clients.txt)
Store client records in this format:


AccountNumber#//#PIN#//#Name#//#Phone#//#Balance
Example:
123456#//#7890#//#John Doe#//#555-1234#//#5000.00
Key Functions 🛠️
Login System: Secure PIN-based authentication

Quick Withdraw: Instant access to common amounts (20, 50, 100, etc.)

Custom Withdraw: Any amount divisible by 5

Deposits: Add funds to account

Balance Check: Real-time account balance

Data Persistence: All changes saved to Clients.txt

Transaction Flow 🔄
Login Screen → Main Menu → Transaction Type

Perform operation (Withdraw/Deposit/Check Balance)

Automatic balance updates

Persistent data storage

Code Structure 📚
Struct: stClientData (stores user information)

File Operations: Read/write to Clients.txt

Menu System:

ATM Main Menu

Quick/Normal Withdrawal screens

Deposit screen

Balance screen

Development Notes 📝
Input validation for all user entries

Error handling for insufficient funds

Clean console interface with ASCII art

Modular functions for easy maintenance


