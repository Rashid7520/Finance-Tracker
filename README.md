# 💰 Finance Tracker (C++ + MySQL)

A **Personal Finance & Budget Management System** built in **C++** with a **MySQL database**. This terminal-based application helps you track expenses, manage monthly budgets, and view financial summaries with a simple CLI interface.

---

## 📌 Features

- 🧾 User Registration & Login  
- 💸 Add Income and Expense Transactions  
- 📊 Set and View Monthly Budgets by Category  
- 📆 View Monthly Financial Summary  
- 🗃️ Category-Based Transaction Grouping  
- 🔐 Secure and personalized user access  
- 💽 MySQL Database Backend  

---

## 🧠 How It Works

1. **User Login/Register**  
   Each user gets a personalized dashboard.

2. **Add Transactions**  
   Income or expense is logged by category, type, date, and description.

3. **Set Budget**  
   Allocate a monthly budget for specific categories.

4. **View Budget**  
   See how much you've allocated in different categories each month.

5. **View Summary**  
   Monthly summary of income, expenses, and remaining balance.

---

## 🖥️ Technology Stack

- **Language:** C++  
- **Database:** MySQL  
- **Connector:** MySQL Connector/C++  
- **Build Tool:** g++  
- **Platform:** Linux (Tested on Ubuntu via WSL)  

---

## 🚀 Setup Instructions (Step-by-Step)

### 📌 Prerequisites

- C++ compiler (e.g., `g++`)  
- MySQL Server  
- MySQL Connector/C++ (`libmysqlcppconn-dev`)  
- Git  

### 📁 Clone the Project

```bash
git clone https://github.com/Rashid7520/Finance-Tracker.git
cd Finance-Tracker
```

### ⚙️ Database Setup

1. **Open MySQL**
   ```bash
   mysql -u root -p
   ```

2. **Create database and tables:**
   ```bash
   CREATE DATABASE finance;
   USE finance;

   CREATE TABLE users (
       user_id INT AUTO_INCREMENT PRIMARY KEY,
       name VARCHAR(50),
       email VARCHAR(100) UNIQUE,
       password VARCHAR(100)
   );

   CREATE TABLE categories (
       category_id INT AUTO_INCREMENT PRIMARY KEY,
       name VARCHAR(50)
   );

   CREATE TABLE transactions (
       txn_id INT AUTO_INCREMENT PRIMARY KEY,
       user_id INT,
       category_id INT,
       amount DOUBLE,
       type VARCHAR(20),
       txn_date DATE,
       description TEXT,
       created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
       FOREIGN KEY (user_id) REFERENCES users(user_id),
       FOREIGN KEY (category_id) REFERENCES categories(category_id)
   );

   CREATE TABLE budget (
       budget_id INT AUTO_INCREMENT PRIMARY KEY,
       user_id INT,
       category_id INT,
       month VARCHAR(7),
       amount DOUBLE,
       FOREIGN KEY (user_id) REFERENCES users(user_id),
       FOREIGN KEY (category_id) REFERENCES categories(category_id)
   );
   
   -- Insert sample categories
   INSERT INTO categories(name) VALUES ('Food'), ('Transport'), ('Health'), ('Shopping'), ('Salary'), ('Bills');
   ```

### 🧱 Build the Project

   ```bash
   g++ main.cpp users.cpp transaction.cpp budget.cpp summary.cpp utils.cpp -o finance_tracker -lmysqlcppconn -lssl -lcrypto
   ```

### 🏃 Run the App

   ```bash
   ./finance_tracker
   ```

---
### 🙌 Contribution

 **Contributions, bug reports, and suggestions are welcome!**

- **Fork the repository**
- **Create a new branch**
- **Commit your changes**
- **Push to your fork**
- **Open a Pull Request**

---
### 📧 Contact

- Created by:- Rashid Khan
- Email: mdrashid7520@gmail.com

---
### 🚀 Made with ❤️ in C++

Let me know if you need any additional sections or modifications!
