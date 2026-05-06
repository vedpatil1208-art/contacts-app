# Contacts App Backend using Linked Lists

## Overview

This project is a **Contacts App Backend** developed as part of a **Data Structures and Algorithms case study**.

The application manages contacts using **three different types of linked lists**:

* **Singly Linked List** — main contact storage
* **Doubly Linked List** — forward and backward traversal
* **Circular Linked List** — recent contacts carousel

The goal of the project is to demonstrate how different linked list structures are suited for different operations in a practical backend system.

---

## Problem Statement

Build a contacts application backend where users can:

* add contacts
* delete contacts
* search contacts
* sort contacts
* traverse contacts
* manage recently accessed contacts

The project uses multiple linked list implementations to show the advantages of each data structure.

---

## Data Structures Used

### Singly Linked List

Used for storing the main contacts database.

**Why used**

* simple structure
* efficient insertion
* efficient deletion through pointer manipulation

---

### Doubly Linked List

Used for forward and backward traversal.

**Why used**

* supports traversal in both directions
* useful for navigation

---

### Circular Linked List

Used for recent contacts.

**Why used**

* naturally supports carousel-style traversal
* useful for recent access history

---

## Features Implemented

### Core Features

* Add contact
* Delete contact by name
* Search contact by name
* Display all contacts
* Forward traversal
* Backward traversal
* Recent contacts carousel (last 5 contacts)
* Sort contacts alphabetically using merge sort

---

## Additional Features

* Auto-generated contact ID
* Phone number validation (exactly 10 digits)
* Duplicate phone number protection
* Update contact information
* Merge two contact lists
* File-based persistent storage using `contacts.txt`

---

## Contact Details Stored

Each contact stores:

* Contact ID
* Name
* Phone Number
* Email Address

---

## File Storage

Contacts are stored in:

```text
contacts.txt
```

The program:

* loads contacts from file when it starts
* saves updated contacts automatically after add, delete, update, sort, and merge operations

This allows data to persist between runs.

---

## Project Structure

```text
contacts-app/
├── main.cpp
├── contacts.txt
└── README.md
```

---

## Team Members (3 Member Group)

### Member 1 — Core Contact Management

* Singly linked list
* Add contact
* Delete contact
* Update contact
* File storage

### Member 2 — Navigation Structures

* Doubly linked list
* Forward traversal
* Backward traversal
* Circular linked list
* Recent contacts

### Member 3 — Algorithms and Validation

* Merge sort
* Linear search
* Merge lists
* Auto-generated ID
* Validation logic

---

## How to Compile and Run

### Compile

```bash
g++ main.cpp -o contacts
```

### Run

```bash
./contacts
```

---

## Sample Menu

```text
===== CONTACTS APP =====
1. Add Contact
2. Delete Contact
3. Display Contacts
4. Search Contact
5. Sort Contacts
6. Recent Contacts
7. Forward & Backward Traversal
8. Update Contact
9. Merge Another List
0. Exit
```

---

## Concepts Demonstrated

* Linked list implementation
* Pointer manipulation
* Merge sort on linked lists
* Linear search
* File handling in C++
* Input validation
* Practical backend design

---

## Conclusion

This project demonstrates how multiple linked list structures can be used together in a practical application.

Each linked list serves a different purpose:

* **Singly linked list** for core storage
* **Doubly linked list** for navigation
* **Circular linked list** for recent access history

The result is a structured and functional contacts management backend built using fundamental data structures.
