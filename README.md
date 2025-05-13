# 📦 Product Inventory Management System

> **Course:** Data Structures and Algorithms – Semester 2 (2023–2024)  
> **University:** HCMC University of Technology – VNU-HCM  
> **Faculty:** Computer Science and Engineering

Welcome to the official GitHub repository for the semester-long project on **Product Inventory Management**. This project was developed as part of two major assignments focused on implementing core data structures and applying them in real-world scenarios using modern C++ (C++17).

---

## 📁 Repository Structure


---

## 🧩 Assignment 1 – Inventory Management

### 🎯 Objectives

- Develop foundational list data structures:
  - `XArrayList` – Array-based list
  - `DLinkedList` – Doubly linked list
- Build inventory-related classes:
  - `List1D` – A one-dimensional list for storing generic values
  - `List2D` – A matrix structure for storing product attributes
  - `InventoryManager` – Core class managing names, attributes, and quantities

### 📝 Grading Breakdown

| Component              | Weight |
|------------------------|--------|
| List Implementations   | 60%    |
| Application Classes    | 40%    |

---

## 🔐 Assignment 2 – Huffman-Based Inventory Compression

### 🎯 Objectives

- Implement advanced data structures:
  - `xMap` – Custom Hash Table
  - `Heap` – Generic Heap (min/max support)
- Develop practical applications:
  - `HuffmanTree` – K-ary Huffman encoding tree
  - `InventoryCompressor` – Compress inventory using Huffman encoding

### 📝 Grading Breakdown

| Component                       | Weight |
|---------------------------------|--------|
| `xMap.h` (Hash Table)           | 40%    |
| `Heap.h` (Heap)                 | 20%    |
| Application Code (Compressor)  | 40%    |

---

## ⚙️ Build & Run

Ensure you have `g++` installed and configured for C++17:

```bash
g++ -std=c++17 -I./include main.cpp -o inventory_app
./inventory_app
```

## NOTE
You can refer the source code in branch Assignment_1 and Assignment_2
