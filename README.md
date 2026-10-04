# 🐾 Pet Care Management System

A modular **C++ console-based Pet Care Management System** designed to manage pet owners, pets, appointments, user accounts, authentication, and related records through a structured role-based system.

The project started as a university software development project and is being further developed as a practical portfolio project, with a focus on modular design, maintainability, user experience, and future scalability.

---

## 📌 Overview

The **Pet Care Management System** provides a simple centralized system for managing information related to pet care operations.

The application uses a **role-based menu system** where different users can access functions according to their responsibilities.

Currently, the system supports:

- User authentication
- Role-based access
- Pet owner management
- Pet management
- Appointment management
- Search functionality
- Input validation
- Automatic ID generation
- File-based data storage
- Modular C++ source structure

The project currently uses **text files for local data storage**. A database-based version is planned as a future improvement.

---

## ✨ Features

### 🔐 Authentication & User Management

- User login and authentication
- Role-based access control
- Administrator user management
- Create new user accounts
- View registered users
- Support for different user roles:
  - Administrator
  - Receptionist
  - Vet Staff Member

---

### 👤 Pet Owner Management

- Register new pet owners
- Automatically generate Owner IDs
- Update owner information
- View owner records
- Search owners by:
  - Owner ID
  - Mobile number

- Duplicate mobile number detection
- Input validation for important fields

---

### 🐶 Pet Management

- Register pets under existing owners
- Automatically generate Pet IDs
- View registered pets
- View pets belonging to a specific owner
- Store information including:
  - Pet name
  - Pet type
  - Breed
  - Age
  - Gender
  - Special notes

---

### 📅 Appointment Management

- Create new appointments
- Automatically generate Appointment IDs
- Link appointments to registered pets
- Update appointment information
- View appointment details
- Search appointments by:
  - Appointment ID
  - Pet ID

- View appointments related to a pet
- Track appointment status:
  - Pending
  - Completed

- Store treatment notes and symptoms
- Track the last updated date

---

### 🔎 Search & Record Management

The system provides search functionality across different types of records.

Examples include:

- Search owner by Owner ID
- Search owner by mobile number
- Search appointments by Appointment ID
- Search appointments by Pet ID
- Search appointments belonging to an owner

---

### ✅ Input Validation

The application includes reusable input validation functions for common user inputs.

Current validation includes:

- Empty input validation
- Whitespace-only input validation
- Numeric menu validation
- Mobile number validation
- Age validation
- Date format validation
- Menu choice validation
- Gender selection validation
- Duplicate mobile number checking

---

## 🏗️ Project Structure

```text
Pet Care Management System/
│
├── main.cpp
│
├── include/
│   ├── models.h
│   ├── input.h
│   ├── parser.h
│   ├── id_generator.h
│   ├── config.h
│   ├── auth.h
│   ├── owner.h
│   ├── pet.h
│   ├── appointment.h
│   ├── search.h
│   └── user.h
│
├── src/
│   ├── input.cpp
│   ├── parser.cpp
│   ├── id_generator.cpp
│   ├── auth.cpp
│   ├── owner.cpp
│   ├── pet.cpp
│   ├── appointment.cpp
│   ├── search.cpp
│   └── user.cpp
│
├── data/
│   ├── owners.txt
│   ├── pets.txt
│   ├── appointments.txt
│   ├── users.txt
│   ├── temp1.txt
│   └── temp2.txt
│
├── .gitignore
└── README.md
```

---

## 🧩 Architecture

The project follows a **modular structure** by separating declarations, implementations, data models, input handling, parsing, authentication, and individual management modules.

### Main Components

| Component        | Responsibility                      |
| ---------------- | ----------------------------------- |
| `main.cpp`       | Application flow and menus          |
| `models.h`       | Data structures                     |
| `input.*`        | Input handling and validation       |
| `parser.*`       | Convert stored data into structures |
| `id_generator.*` | Generate record IDs                 |
| `auth.*`         | Authentication and role handling    |
| `owner.*`        | Owner management                    |
| `pet.*`          | Pet management                      |
| `appointment.*`  | Appointment management              |
| `search.*`       | Search operations                   |
| `user.*`         | User account management             |
| `config.h`       | File path configuration             |

This separation makes the project easier to understand, maintain, debug, and extend.

---

## 💾 Data Storage

The current version uses **local text files** for data persistence.

```text
data/
├── owners.txt
├── pets.txt
├── appointments.txt
└── users.txt
```

Temporary files are also used when updating stored records.

The current file-based approach keeps the project simple and easy to run without requiring an external database server.

> **Note:** The data files included in this repository are intended for demonstration/testing purposes.

---

## 🛠️ Technologies Used

- **C++**
- Standard C++ Library
- File I/O
- Modular programming
- Structures
- Functions
- Header/source separation
- Text-file data persistence
- Console-based user interface

---

## ▶️ How to Run

### 1. Clone the repository

```bash
git clone https://github.com/thisum-gamage/Pet-Care-Management-System.git
```

### 2. Open the project directory

```bash
cd Pet-Care-Management-System
```

### 3. Compile the project

Using `g++`:

```bash
g++ main.cpp src/input.cpp src/parser.cpp src/id_generator.cpp src/auth.cpp src/owner.cpp src/pet.cpp src/appointment.cpp src/search.cpp src/user.cpp -o main
```

### 4. Run the application

On Windows:

```powershell
.\main
```

---

## 🖥️ Application Workflow

A typical workflow looks like this:

```text
        Start Application
               │
               ▼
             Login
               │
               ▼
         Role-based Menu
               │
   ┌───────────┼──────────────┐
   ▼           ▼              ▼
 Owner        Pet        Appointment
Manage       Manage        Manage
   │           │              │
   └───────────┴──────────────┘
               │
               ▼
        Search / Reports
```

---

## 📋 Current Status

**Current Version:** Stable Modular Version

The core management system is functional and organized into separate modules.

The project is currently being developed further as a **portfolio project**, with future improvements focused on functionality, usability, architecture, and data management.

---

## 🚀 Future Improvements

The following features are planned for future versions:

- 📊 Dashboard with system statistics
- 📈 Improved reports and analytics
- 🐕 Detailed pet profiles
- 📅 Appointment history and timeline
- 🔎 More advanced search and filtering
- 🎨 Improved terminal user interface
- 💾 Backup and restore functionality
- 🧱 Object-Oriented Programming refactor
- 🗄️ Database integration
- ⚡ SQLite-based data storage
- 🔐 Improved authentication and password security
- 🧪 Expanded testing
- 📦 Improved project documentation

These features will be introduced progressively as the project evolves.

---

## 📸 Screenshots

Screenshots of the application interface will be added in future updates.

---

## 🎯 Project Goals

The long-term goal of this project is to evolve a simple console-based university project into a more complete software application while continuously improving:

- Software architecture
- C++ programming skills
- Data management
- Problem-solving
- User experience
- Code organization
- Real-world software development practices

---

## 📄 License

This project currently does not specify an open-source license.
