# 🏦 Bank Management System + Currency Exchange — Full OOP C++

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=flat-square&logo=cplusplus)
![OOP](https://img.shields.io/badge/Paradigm-OOP%20%2B%20Inheritance-blueviolet?style=flat-square)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=flat-square&logo=windows)
![Architecture](https://img.shields.io/badge/Architecture-Layered%20%2F%20MVC--like-orange?style=flat-square)
![Version](https://img.shields.io/badge/Version-Final%20Extended-gold?style=flat-square)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)

The final and most complete version of the Bank Management System — all previous features plus a full **Currency Exchange Module** with real-time rate updates, multi-currency conversion, and a built-in currency calculator. Built entirely with **Object-Oriented C++** using inheritance, encapsulation, and a clean layered architecture.

> 🔗 **Previous versions:**
> [v1 - Client CRUD](https://github.com/YourUsername/Bank-Client-Management-v1) · [v2 - Transactions](https://github.com/YourUsername/Bank-Client-Management-v2) · [v3 - Login & Permissions](https://github.com/YourUsername/Bank-Client-Management-v3)

---

## 📸 Preview

```
                    -------------------------------------------
                                    Main Screen
                    -------------------------------------------
                    User : admin
                    Date : 23/04/2026
                    -------------------------------------------

                    =================================================
                                    Main Menue
                    =================================================
                            [1]  Show Client List.
                            [2]  Add New Client.
                            [3]  Delete Client.
                            [4]  Update Client Info.
                            [5]  Find Client.
                            [6]  Transactions.
                            [7]  Manage Users.
                            [8]  Login Register.
                            [9]  Currency Exchange.     ← NEW
                            [10] Logout.
                    =================================================

                    =================================================
                            Currency Exchange Menue
                    =================================================
                            [1] List Currencies.
                            [2] Find Currency.
                            [3] Update Rate.
                            [4] Currency Calculator.
                            [5] Main Menue.
                    =================================================
```

---

## ✨ What's New — Currency Exchange Module

| Feature | Description |
|---|---|
| 📋 **List Currencies** | View all supported currencies with country, code, name, and rate |
| 🔍 **Find Currency** | Search by currency code (e.g. `USD`) or by country name |
| ✏️ **Update Rate** | Update the exchange rate of any currency (with 3-attempt limit) |
| 🧮 **Currency Calculator** | Convert any amount between two currencies via USD as base |

### How Conversion Works

```
Amount in Currency A
    → ÷ Rate(A) → Amount in USD
        → × Rate(B) → Amount in Currency B
```

All rates are stored relative to **1 USD** in `Currencies.txt`.

---

## ✨ Full Feature List

### 🏦 Client Management
- List, Add, Delete, Update, Find clients

### 💰 Transactions
- Deposit, Withdraw (with overdraft protection)
- Transfer between accounts with full audit trail
- View total balances

### 👥 User Management
- Full CRUD on system users
- Bitwise role-based permission system (9 permissions)
- Login with username + password

### 📝 Audit Logs
- Login Register — tracks every login with timestamp
- Transfer Log — records every transfer with source, destination, amounts, and user

### 💱 Currency Exchange ← NEW
- List all currencies
- Find by code or country
- Update exchange rate (with 3-attempt security limit)
- Currency Calculator (multi-currency conversion via USD)

---

## 🗂️ Project Structure

```
BankProject/
│
├── ConsoleApplication1.cpp          # Entry point
├── Global.h                         # Global CurrentUser session
│
├── clsPerson.h                      # Base class: name, email, phone
├── clsBankClient.h                  # Client: CRUD, Deposit, Withdraw, Transfer
├── clsUser.h                        # User: CRUD, permissions, login log
├── clsCurrency.h                    # Currency: Find, UpdateRate, Convert   ← NEW
│
├── clsString.h                      # String utility class
├── clsDate.h                        # Date/time utility class
├── clsInputValidate.h               # Safe typed input reading
├── clsUtil.h                        # General utilities
├── clsPeriod.h                      # Date period utility
│
├── clsScreen.h                      # Base screen (header, access check)
├── clsMainScreen.h                  # Main menu (10 options)
├── clsLoginScreen.h                 # Login screen
│
├── clsClientListScreen.h            # List clients
├── clsAddNewClientScreen.h          # Add client
├── clsDeleteClientScreen.h          # Delete client
├── clsUpdateClientScreen.h          # Update client
├── clsFindClientScreen.h            # Find client
│
├── clsTransactionsScreen.h          # Transactions sub-menu
├── clsDepositScreen.h               # Deposit
├── clsWithdrawScreen.h              # Withdraw
├── clsTransferScreen.h              # Transfer between accounts
├── clsTotalBalancesScreen.h         # Total balances
├── clsTransferLogScreen.h           # Transfer history log
│
├── clsManageUsers.h                 # Manage users sub-menu
├── clsUsersListScreen.h             # List users
├── clsAddNewUserScreen.h            # Add user
├── clsDeleteUserScreen.h            # Delete user
├── clsUpdateUserScreen.h            # Update user
├── clsFindUserScreen.h              # Find user
│
├── clsLoginRegisterScreen.h         # Login audit log
│
├── clsCurrencyExchangeMenue.h       # Currency Exchange sub-menu     ← NEW
├── clsCurreniesListScreen.h         # List all currencies            ← NEW
├── clsFindCurrencyScreen.h          # Find by code or country        ← NEW
├── clsUpdateCurrencyRateScreen.h    # Update exchange rate           ← NEW
├── clsCurrencyCalculatorScreen.h    # Currency calculator            ← NEW
│
├── Clients.txt                      # Clients data
├── Users.txt                        # Users data
├── Currencies.txt                   # Currencies & rates             ← NEW
├── TransferLog.txt                  # Transfer audit log
└── LoginRegister.txt                # Login audit log
```

---

## 🧱 Architecture

```
┌──────────────────────────────────────────────────────┐
│                  PRESENTATION LAYER                  │
│   clsScreen (base) → All Screen & Menu classes       │
└────────────────────────┬─────────────────────────────┘
                         │ uses
┌────────────────────────▼─────────────────────────────┐
│                   BUSINESS LAYER                     │
│   clsPerson (base)                                   │
│     ├── clsBankClient  (Deposit, Withdraw, Transfer) │
│     └── clsUser        (Permissions, LoginRegister)  │
│   clsCurrency          (Find, UpdateRate, Convert)   │
└────────────────────────┬─────────────────────────────┘
                         │ uses
┌────────────────────────▼─────────────────────────────┐
│                    DATA LAYER                        │
│   Clients.txt · Users.txt · Currencies.txt           │
│   TransferLog.txt · LoginRegister.txt                │
└──────────────────────────────────────────────────────┘
```

### Inheritance Hierarchy

```
clsPerson  (Base)
├── clsBankClient
└── clsUser

clsScreen  (Base)
├── clsMainScreen
├── clsCurrencyExchangeMenue
├── clsTransactionsScreen
├── clsManageUsers
└── All other screen classes
```

---

## 🔐 Permission System (Bitwise)

| Permission | Value |
|---|---|
| `pShowClientList` | 1 |
| `pAddNewClient` | 2 |
| `pDeleteClient` | 4 |
| `pUpdateClient` | 8 |
| `pFindClient` | 16 |
| `pTransactions` | 32 |
| `pManageUsers` | 64 |
| `pLoginRegister` | 128 |
| `pAll` (full access) | -1 |

---

## 💾 File Formats

**Clients.txt:**
```
Mohammed#//#El Amrani#//#m@email.com#//#0612345678#//#A1001#//#1234#//#15000.000000
```

**Users.txt:**
```
Admin#//#User#//#admin@bank.com#//#0600000000#//#admin#//#1234#//#-1
```

**Currencies.txt:** ← NEW
```
United States#//#USD#//#US Dollar#//#1.000000
European Union#//#EUR#//#Euro#//#0.920000
Morocco#//#MAD#//#Moroccan Dirham#//#10.050000
```

**TransferLog.txt:**
```
23/04/2026 14:32:00#//#A1001#//#A1002#//#500.000000#//#14500.000000#//#9000.500000#//#admin
```

---

## 🚀 Getting Started

### Prerequisites
- **Visual Studio 2019+** (uses `__declspec(property)`)
- Windows OS

### Run in Visual Studio
1. Open `ConsoleApplication1.vcxproj`
2. Press `Ctrl + F5`

### First Run Setup

**Users.txt:**
```
Admin#//#User#//#admin@bank.com#//#0600000000#//#admin#//#1234#//#-1
```

**Currencies.txt** (sample):
```
United States#//#USD#//#US Dollar#//#1.000000
European Union#//#EUR#//#Euro#//#0.920000
Morocco#//#MAD#//#Moroccan Dirham#//#10.050000
Saudi Arabia#//#SAR#//#Saudi Riyal#//#3.750000
```

---

## 🛠️ Technologies Used

- **Language:** C++
- **Libraries:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`, `<ctime>`
- **Concepts:** OOP, Inheritance, Encapsulation, File I/O, Bitwise RBAC, Layered Architecture, Audit Logging, Currency Conversion

---

## 🔮 Possible Improvements

- [ ] Fetch live exchange rates from an API
- [ ] Add currency conversion history log
- [ ] Hash stored passwords
- [ ] Export reports to CSV
- [ ] Cross-platform support (remove `system()` / `__declspec`)
- [ ] Migrate storage to SQLite

---

## 👨‍💻 Author

> Built with ❤️ as the final extension of a full C++ banking system series.

Feel free to fork, star ⭐, or contribute!

---

## 📄 License

This project is licensed under the **MIT License** — free to use and modify.
