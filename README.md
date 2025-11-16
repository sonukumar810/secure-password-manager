# 🛡️ SecurePass Manager

A secure and modular password manager built in **C++**, implementing **bcrypt hashing**, **MySQL storage**, and **OOP principles** for maintainability and scalability.

---

## 📌 About the Project

SecurePass Manager is a security-focused password management system developed in C++. It uses **object-oriented design**, **bcrypt hashing**, and **persistent MySQL storage** to securely manage user credentials.

The project emphasizes:

* Separation of login & authentication logic
* Strong password hashing using bcrypt
* Clean OOP structure for scalability
* Secure and efficient database operations using C++ MySQL Connector

---

## ⭐ Features

* 🔐 **Secure Password Hashing**

  * Uses **bcrypt** to hash and verify passwords.
  * Includes random salts for enhanced security.

* 🧩 **Modular OOP Architecture**

  * Separate classes for authentication, database operations, and user interactions.
  * Easy to extend and maintain.

* 🗄️ **MySQL Integration**

  * Uses **C++ MySQL Connector** for database communication.
  * Stores salted, hashed credentials securely.
  * Designed for scalability.

* 🧑‍💻 **Robust Input Handling**

  * Validates user inputs to ensure safe operations.

---

## 🏗️ Tech Stack

| Component    | Technology                            |
| ------------ | ------------------------------------- |
| Language     | **C++**                               |
| Database     | **MySQL**                             |
| Security     | **bcrypt** (hashing)                  |
| Architecture | **Object-Oriented Programming (OOP)** |
| DB Connector | **C++ MySQL Connector**               |

---

## 📂 Project Structure

```
secure-password-manager/
│── src/
│   ├── main.cpp
│   ├── auth.cpp / auth.h
│   ├── database.cpp / database.h
│   └── utils.cpp / utils.h
│── include/
│── README.md
│── CMakeLists.txt (optional)
```

---

## ⚙️ Setup & Installation

### 1. Clone the Repository

```bash
git clone https://github.com/sonukumar810/secure-password-manager.git
cd secure-password-manager
```

### 2. Install MySQL Connector for C++

Download and configure from MySQL official site.

### 3. Configure Database

Create a database and table:

```sql
CREATE DATABASE securepass;

USE securepass;

CREATE TABLE users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  username VARCHAR(255) UNIQUE NOT NULL,
  password_hash VARCHAR(255) NOT NULL
);
```

### 4. Build the Program

Using g++ (example):

```bash
g++ src/*.cpp -lmysqlcppconn -o securepass
```

---

## ▶️ Usage

Run the application:

```bash
./securepass
```

You can:

* Register a user
* Store hashed passwords
* Login using bcrypt verification

---

## 🔒 Security Notes

* Passwords are **never stored in plain text**.
* All stored credentials use **salted bcrypt hashes**.
* MySQL ensures persistent and structured storage.

---

## 📁 GitHub Repository

🔗 https://github.com/sonukumar810/secure-password-manager

---
