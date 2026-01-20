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
    <img src="https://img.shields.io/badge/Team-4_Members-blue?style=for-the-badge&logo=microsoft-teams&logoColor=white" alt="Team" />
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

**SwiftEx Pakistan Logistics System** is a robust console-based application designed to simulate and manage real-world courier operations. It demonstrates the practical application of advanced algorithms to handle parcel sorting, route optimization, and tracking across a network of major Pakistani cities.

The system ensures efficiency through **Intelligent Routing** (Dijkstra's Algorithm) and **Priority Processing** (Heaps), ensuring critical deliveries like "Overnight" packages are handled first.

---

### 📦 Core Modules

The system is divided into four distinct operational modules:

#### 1. Intelligent Parcel Sorting
* **Logic:** Automatically sorts parcels based on urgency (Overnight, 2-Day, Normal) and weight.
* **Mechanism:** Uses **Min-Heap Priority Queues** to ensure high-priority packages are processed before standard ones.

#### 2. Parcel Routing (Network Optimization)
* **Logic:** Calculates the optimal delivery path between cities using **Dijkstra’s Algorithm** ($O(V^2)$).
* **Coverage:** Includes major hubs: Lahore (Punjab), Karachi (Sindh), Peshawar (KPK), and Quetta (Balochistan).
* **Dynamic:** Supports road closures (blocking/unblocking paths) in real-time.

#### 3. Real-Time Tracking
* **Logic:** Provides instant status updates and history logs for any shipment.
* **Efficiency:** Uses a **Hash Table** for $O(1)$ constant time lookup of tracking IDs (e.g., `SWX1000`).

#### 4. Courier Operations Pipeline
* **Flow:** Simulates the physical movement of packages through three stages:
    1.  **Pickup Queue** (Batch of 5)
    2.  **Warehouse Queue** (Sorting/Loading)
    3.  **Transit Queue** (Out for Delivery)

---

### 🧩 Data Structures Implemented

We implemented custom data structures from scratch to maximize performance and demonstrate core CS concepts.

| Data Structure | Implementation Details | Usage in Project |
| :--- | :--- | :--- |
| **🕸️ Graph** | Adjacency List with Weights | Models the map of Pakistani cities and calculates shortest paths. |
| **⚡ Priority Queue** | Min-Heap Implementation | Manages "Overnight" and "2-Day" delivery queues based on priority scores. |
| **🔑 Hash Table** | Polynomial Rolling Hash | Stores and retrieves Parcel objects by ID with $O(1)$ access. Handles collisions via Linear Probing. |
| **🔄 Queue** | Singly Linked List (FIFO) | Manages standard parcel flow (Pickup $\to$ Warehouse $\to$ Transit). |
| **📦 Dynamic Array** | Resizable Array (2x Growth) | Stores operation logs and status history with $O(1)$ access. |

---

### 👥 Team Members

We are a team of four dedicated developers working on this project.

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/2-UmairArshad">
        <img src="https://cdn-icons-png.flaticon.com/512/4140/4140048.png" width="80px;" alt="Umair Arshad"/><br />
      </a>
      <sub><b><a href="https://github.com/2-UmairArshad">Umair Arshad</a></b></sub><br />
      <br />
      <span>💻 Developer</span>
    </td>
    <td align="center">
      <a href="https://www.linkedin.com/in/hussain-nawaz-b835453a2">
        <img src="https://cdn-icons-png.flaticon.com/512/4140/4140037.png" width="80px;" alt="Hussain Nawaz"/><br />
      </a>
      <sub><b><a href="https://www.linkedin.com/in/hussain-nawaz-b835453a2">Hussain Nawaz</a></b></sub><br />
      <br />
      <span>🔄 Developer</span>
    </td>
    <td align="center">
      <a href="https://www.linkedin.com/in/shaheer-hassan-khan-2567a6385/">
        <img src="https://cdn-icons-png.flaticon.com/512/4140/4140061.png" width="80px;" alt="Shaheer Hassan"/><br />
      </a>
      <sub><b><a href="https://www.linkedin.com/in/shaheer-hassan-khan-2567a6385/">Shaheer Hassan</a></b></sub><br />
      <br />
      <span>🛠️ Developer</span>
    </td>
    <td align="center">
      <a href="https://github.com/Irfan-Bajwa">
        <img src="https://cdn-icons-png.flaticon.com/512/4140/4140042.png" width="80px;" alt="Muhammad Irfan"/><br />
      </a>
      <sub><b><a href="https://github.com/Irfan-Bajwa">Muhammad Irfan</a></b></sub><br />
      <br />
      <span>🚀 Developer</span>
    </td>
  </tr>
</table>

---

### 💻 Tech Stack

* **Language:** C++ (MINGW Compiler)
* **Libraries:** `<iostream>`, `<string>`
* **Tools:** Visual Studio Code, Git

---

### 📅 Roadmap

- [x] **Project Initiation** (Sept 15, 2025)
- [x] **Requirement Analysis**
- [x] **Module Implementation**
- [x] **Unit & Integration Testing**
- [x] **System Testing**
- [x] **Final Release** (January 1, 2026)

---

<div align="center">
  <p>Made with ❤️ by the SwiftEx Team</p>
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:00599C,100:00BFFF&height=100&section=footer" width="100%">
</div>