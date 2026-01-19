<div align="center">

  <img src="https://cdn-icons-png.flaticon.com/512/9561/9561688.png" alt="Logo" width="100" height="100">

  <h1 align="center">SwiftEx Courier System</h1>

  <p align="center">
    <strong>Advanced Logistics & Courier Management Solution</strong>
    <br />
    A sophisticated C++ application for parcel sorting, route optimization, and real-time tracking across Pakistan.
    <br />
    <br />
    <a href="#-demo">View Demo</a>
    ·
    <a href="#-report-bug">Report Bug</a>
    ·
    <a href="#-request-feature">Request Feature</a>
  </p>
  
  <p align="center">
    <img src="https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++" />
    <img src="https://img.shields.io/badge/Status-Completed-success?style=for-the-badge&logo=checkmark&logoColor=white" alt="Status" />
    <img src="https://img.shields.io/badge/Course-Data_Structures-orange?style=for-the-badge&logo=book&logoColor=white" alt="Course" />
  </p>
</div>

<br />

<details>
  <summary><strong>📚 Table of Contents</strong></summary>
  <ol>
    <li><a href="#-about-the-project">About The Project</a></li>
    <li><a href="#-core-modules">Core Modules</a></li>
    <li><a href="#-data-structures-implemented">Data Structures Implemented</a></li>
    <li><a href="#-team-members">Team Members</a></li>
    <li><a href="#-tech-stack">Tech Stack</a></li>
    <li><a href="#-roadmap">Roadmap</a></li>
  </ol>
</details>

<br />

---

### 🚀 About The Project

[cite_start]**SwiftEx Pakistan Logistics System** is a robust console-based application designed to simulate and manage real-world courier operations[cite: 32]. [cite_start]It demonstrates the practical application of advanced algorithms to handle parcel sorting, route optimization, and tracking across a network of major Pakistani cities[cite: 33].

[cite_start]The system ensures efficiency through **Intelligent Routing** (Dijkstra's Algorithm) and **Priority Processing** (Heaps), ensuring critical deliveries like "Overnight" packages are handled first[cite: 35, 722].

---

### 📦 Core Modules

[cite_start]The system is divided into four distinct operational modules:

#### 1. Intelligent Parcel Sorting
* [cite_start]**Logic:** Automatically sorts parcels based on urgency (Overnight, 2-Day, Normal) and weight[cite: 141].
* [cite_start]**Mechanism:** Uses **Min-Heap Priority Queues** to ensure high-priority packages are processed before standard ones[cite: 143].

#### 2. Parcel Routing (Network Optimization)
* [cite_start]**Logic:** Calculates the optimal delivery path between cities using **Dijkstra’s Algorithm** ($O(V^2)$)[cite: 168, 304].
* [cite_start]**Coverage:** Includes major hubs: Lahore (Punjab), Karachi (Sindh), Peshawar (KPK), and Quetta (Balochistan)[cite: 351].
* [cite_start]**Dynamic:** Supports road closures (blocking/unblocking paths) in real-time[cite: 172].

#### 3. Real-Time Tracking
* [cite_start]**Logic:** Provides instant status updates and history logs for any shipment[cite: 213].
* [cite_start]**Efficiency:** Uses a **Hash Table** for $O(1)$ constant time lookup of tracking IDs (e.g., `SWX1000`)[cite: 215].

#### 4. Courier Operations Pipeline
* **Flow:** Simulates the physical movement of packages through three stages:
    1.  [cite_start]**Pickup Queue** (Batch of 5) [cite: 250]
    2.  [cite_start]**Warehouse Queue** (Sorting/Loading) [cite: 256]
    3.  [cite_start]**Transit Queue** (Out for Delivery) [cite: 261]

---

### 🧩 Data Structures Implemented

[cite_start]We implemented custom data structures from scratch to maximize performance and demonstrate core CS concepts[cite: 45].

| Data Structure | Implementation Details | Usage in Project |
| :--- | :--- | :--- |
| **🕸️ Graph** | Adjacency List with Weights | [cite_start]Models the map of Pakistani cities and calculates shortest paths[cite: 116, 123]. |
| **⚡ Priority Queue** | Min-Heap Implementation | [cite_start]Manages "Overnight" and "2-Day" delivery queues based on priority scores[cite: 64, 80]. |
| **🔑 Hash Table** | Polynomial Rolling Hash | Stores and retrieves Parcel objects by ID with $O(1)$ access. [cite_start]Handles collisions via Linear Probing[cite: 99, 107]. |
| **🔄 Queue** | Singly Linked List (FIFO) | [cite_start]Manages standard parcel flow (Pickup $\to$ Warehouse $\to$ Transit)[cite: 83, 91]. |
| **📦 Dynamic Array** | Resizable Array (2x Growth) | [cite_start]Stores operation logs and status history with $O(1)$ access[cite: 46, 55]. |

---

### 👥 Team Members

We are a team of three working on System, Integration, and Unit testing.

<table>
  <tr>
    <td align="center">
      <img src="https://cdn-icons-png.flaticon.com/512/4140/4140048.png" width="80px;" alt=""/><br />
      <sub><b>Umair</b></sub><br />
      <br />
      <span title="System Testing">💻 System Level Testing</span>
    </td>
    <td align="center">
      <img src="https://cdn-icons-png.flaticon.com/512/4140/4140037.png" width="80px;" alt=""/><br />
      <sub><b>Usman</b></sub><br />
      <br />
      <span title="Integration Testing">🔄 Integration Level Testing</span>
    </td>
    <td align="center">
      <img src="https://cdn-icons-png.flaticon.com/512/4140/4140051.png" width="80px;" alt=""/><br />
      <sub><b>Abdul Muiz</b></sub><br />
      <br />
      <span title="Unit Testing">🛠️ Unit Level Testing</span>
    </td>
  </tr>
</table>

---

### 💻 Tech Stack

* [cite_start]**Language:** C++ (MINGW Compiler) [cite: 443]
* [cite_start]**Libraries:** `<iostream>`, `<string>`, `<vector>` (only where allowed) [cite: 445]
* **Tools:** Visual Studio Code, Git

---

### 📅 Roadmap

- [x] **Project Initiation** (Sept 15, 2025)
- [x] **Requirement Analysis**
- [x] **Module Implementation**
- [x] **Unit & Integration Testing**
- [x] **System Testing**
- [x] **Final Release** (May 15, 2026)

---

<div align="center">
  <p>Made with ❤️ by the SwiftEx Team</p>
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:00599C,100:00BFFF&height=100&section=footer" width="100%">
</div>