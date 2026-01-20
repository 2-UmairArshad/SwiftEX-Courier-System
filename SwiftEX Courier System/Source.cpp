#include <iostream>
#include <string>
using namespace std;

/*
 * DynamicArray<T>
 * Time Complexity:
 *   - push(): O(1), O(n) when resizing
 *   - operator[]: O(1)
 *   - removeAt(): O(n) shifting elements
 *   - clear(): O(1)
 * Space Complexity: O(n)
 */
template <typename T>
class DynamicArray {
private:
    T* arr;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    DynamicArray() : capacity(10), size(0) {
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void push(const T& item) {
        if (size == capacity) resize();
        arr[size++] = item;
    }

    T& operator[](int index) {
        return arr[index];
    }

    const T& operator[](int index) const {
        return arr[index];
    }

    int getSize() const { return size; }

    void clear() { size = 0; }

    void removeAt(int index) {
        if (index < 0 || index >= size) return;
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }
};

/*
 * Parcel Class
 * Time Complexity:
 *   - Constructor: O(1)
 *   - updateStatus(): O(1)
 *   - displayDetails(): O(h) where h is the size of status history
 *   - All getters: O(1)
 * Space Complexity: O(h) where h is the number of status updates
 */
class Parcel {
private:
    string trackingId;
    string sender;
    string receiver;
    string destination;
    int weight;
    string priority;
    bool isFragile;
    string status;
    string assignedRider;
    DynamicArray<string> statusHistory;

public:
    Parcel() : weight(0), isFragile(false), status("Created"), assignedRider("None") {}

    Parcel(string id, string send, string recv, string dest, int w, string pri, bool frag)
        : trackingId(id), sender(send), receiver(recv), destination(dest),
        weight(w), priority(pri), isFragile(frag), status("Created"), assignedRider("None") {
        statusHistory.push("Status: Created");
    }

    string getTrackingId() const { return trackingId; }
    string getDestination() const { return destination; }
    int getWeight() const { return weight; }
    string getPriority() const { return priority; }
    bool getFragile() const { return isFragile; }
    string getStatus() const { return status; }
    string getSender() const { return sender; }
    string getReceiver() const { return receiver; }
    string getAssignedRider() const { return assignedRider; }

    void setAssignedRider(string riderId) {
        assignedRider = riderId;
        statusHistory.push("Assigned to Rider: " + riderId);
    }

    void updateStatus(string newStatus) {
        status = newStatus;
        statusHistory.push("Status: " + newStatus);
    }

    void displayDetails() const {
        cout << "\n========== PARCEL DETAILS ==========\n";
        cout << "Tracking ID: " << trackingId << endl;
        cout << "Sender: " << sender << endl;
        cout << "Receiver: " << receiver << endl;
        cout << "Destination: " << destination << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Priority: " << priority << endl;
        cout << "Fragile: " << (isFragile ? "Yes" : "No") << endl;
        cout << "Current Status: " << status << endl;
        cout << "Assigned Rider: " << assignedRider << endl;
        cout << "\n--- Status History ---\n";
        for (int i = 0; i < statusHistory.getSize(); i++) {
            cout << (i + 1) << ". " << statusHistory[i] << endl;
        }
        cout << "====================================\n";
    }
};

/*
 * Rider Class
 * Time Complexity:
 *   - Constructor: O(1)
 *   - All operations: O(1) or O(n) for parcel list operations
 * Space Complexity: O(p) where p is the number of assigned parcels
 */
class Rider {
private:
    string riderId;
    string name;
    string phoneNumber;
    string vehicleType;
    int maxCapacity;
    int currentLoad;
    string currentLocation;
    bool isAvailable;
    DynamicArray<string> assignedParcels;
    DynamicArray<string> deliveryHistory;

public:
    Rider() : maxCapacity(0), currentLoad(0), isAvailable(true) {}

    Rider(string id, string n, string phone, string vehicle, int capacity, string location)
        : riderId(id), name(n), phoneNumber(phone), vehicleType(vehicle),
        maxCapacity(capacity), currentLoad(0), currentLocation(location), isAvailable(true) {
    }

    string getRiderId() const { return riderId; }
    string getName() const { return name; }
    string getPhoneNumber() const { return phoneNumber; }
    string getVehicleType() const { return vehicleType; }
    int getMaxCapacity() const { return maxCapacity; }
    int getCurrentLoad() const { return currentLoad; }
    string getCurrentLocation() const { return currentLocation; }
    bool getAvailability() const { return isAvailable; }
    int getRemainingCapacity() const { return maxCapacity - currentLoad; }

    void setAvailability(bool status) { isAvailable = status; }
    void setCurrentLocation(string location) { currentLocation = location; }

    bool canCarry(int weight) const {
        return isAvailable && (currentLoad + weight <= maxCapacity);
    }

    bool assignParcel(string parcelId, int weight) {
        if (!canCarry(weight)) {
            return false;
        }
        assignedParcels.push(parcelId);
        currentLoad += weight;
        return true;
    }

    void completeDelivery(string parcelId, int weight) {
        for (int i = 0; i < assignedParcels.getSize(); i++) {
            if (assignedParcels[i] == parcelId) {
                assignedParcels.removeAt(i);
                currentLoad -= weight;
                deliveryHistory.push("Delivered: " + parcelId);
                break;
            }
        }
    }

    void removeParcel(string parcelId, int weight) {
        for (int i = 0; i < assignedParcels.getSize(); i++) {
            if (assignedParcels[i] == parcelId) {
                assignedParcels.removeAt(i);
                currentLoad -= weight;
                break;
            }
        }
    }

    void displayDetails() const {
        cout << "\n========== RIDER DETAILS ==========\n";
        cout << "Rider ID: " << riderId << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phoneNumber << endl;
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "Max Capacity: " << maxCapacity << " kg" << endl;
        cout << "Current Load: " << currentLoad << " kg" << endl;
        cout << "Remaining Capacity: " << getRemainingCapacity() << " kg" << endl;
        cout << "Current Location: " << currentLocation << endl;
        cout << "Status: " << (isAvailable ? "Available" : "Unavailable") << endl;

        cout << "\n--- Assigned Parcels (" << assignedParcels.getSize() << ") ---\n";
        if (assignedParcels.getSize() == 0) {
            cout << "No parcels assigned\n";
        }
        else {
            for (int i = 0; i < assignedParcels.getSize(); i++) {
                cout << (i + 1) << ". " << assignedParcels[i] << endl;
            }
        }

        cout << "\n--- Delivery History (Last 10) ---\n";
        if (deliveryHistory.getSize() == 0) {
            cout << "No deliveries yet\n";
        }
        else {
            int start = (deliveryHistory.getSize() > 10) ? deliveryHistory.getSize() - 10 : 0;
            for (int i = start; i < deliveryHistory.getSize(); i++) {
                cout << (i + 1) << ". " << deliveryHistory[i] << endl;
            }
        }
        cout << "===================================\n";
    }

    void displaySummary() const {
        cout << riderId << " | " << name << " | " << vehicleType
            << " | Load: " << currentLoad << "/" << maxCapacity << " kg"
            << " | Parcels: " << assignedParcels.getSize()
            << " | " << (isAvailable ? "Available" : "Unavailable") << endl;
    }
};

/*
 * PriorityQueue<T>
 * Time Complexity:
 *   - enqueue(): O(log n)
 *   - dequeue(): O(log n)
 *   - isEmpty(): O(1)
 *   - size(): O(1)
 * Space Complexity: O(n)
 */
template <typename T>
class PriorityQueue {
private:
    class Node {
    public:
        T data;
        int priority;
        Node() : data(nullptr), priority(0) {}
        Node(T d, int p) : data(d), priority(p) {}
    };

    DynamicArray<Node> heap;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)].priority > heap[index].priority) {
            Node temp = heap[index];
            heap[index] = heap[parent(index)];
            heap[parent(index)] = temp;
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int size = heap.getSize();
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < size && heap[left].priority < heap[smallest].priority)
            smallest = left;
        if (right < size && heap[right].priority < heap[smallest].priority)
            smallest = right;

        if (smallest != index) {
            Node temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            heapifyDown(smallest);
        }
    }

public:
    void enqueue(T data, int priority) {
        heap.push(Node(data, priority));
        heapifyUp(heap.getSize() - 1);
    }

    T dequeue() {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        T result = heap[0].data;
        heap[0] = heap[heap.getSize() - 1];
        heap.removeAt(heap.getSize() - 1);
        if (!isEmpty()) {
            heapifyDown(0);
        }
        return result;
    }

    bool isEmpty() const {
        return heap.getSize() == 0;
    }

    int size() const {
        return heap.getSize();
    }
};

/*
 * Queue
 * Time Complexity:
 *   - enqueue(): O(1)
 *   - dequeue(): O(1)
 *   - peek(): O(1)
 *   - isEmpty(): O(1)
 *   - size(): O(1)
 * Space Complexity: O(n)
 */
template <typename T>
class Queue {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        Node* temp = front;
        T data = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        count--;
        return data;
    }

    T peek() {
        if (isEmpty()) {
            throw "Queue is empty";
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int size() const {
        return count;
    }
};

/*
 * HashTable
 * Time Complexity:
 *   - insert(): O(1) average, O(n) worst case
 *   - search(): O(1) average, O(n) worst case
 *   - remove(): O(1) average, O(n) worst case
 * Space Complexity: O(n)
 */
template <typename K, typename V>
class HashTable {
private:
    class Entry {
    public:
        K key;
        V value;
        bool occupied;
        Entry() : key(), value(), occupied(false) {}
        Entry(K k, V v) : key(k), value(v), occupied(true) {}
    };

    Entry* table;
    int capacity;
    int size;

    int hashFunction(const string& key) {
        int hash = 0;
        for (int i = 0; i < key.length(); i++) {
            hash = (hash * 31 + key[i]) % capacity;
        }
        return hash;
    }

    void resize() {
        Entry* oldTable = table;
        int oldCapacity = capacity;
        capacity *= 2;
        table = new Entry[capacity];
        size = 0;

        for (int i = 0; i < oldCapacity; i++) {
            if (oldTable[i].occupied) {
                insert(oldTable[i].key, oldTable[i].value);
            }
        }
        delete[] oldTable;
    }

public:
    HashTable() : capacity(100), size(0) {
        table = new Entry[capacity];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(K key, V value) {
        if (size >= capacity * 0.7) {
            resize();
        }

        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].occupied && table[index].key != key) {
            index = (index + 1) % capacity;
            if (index == originalIndex) {
                resize();
                insert(key, value);
                return;
            }
        }

        if (!table[index].occupied) {
            size++;
        }
        table[index] = Entry(key, value);
    }

    V* search(K key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].occupied) {
            if (table[index].key == key) {
                return &table[index].value;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) break;
        }
        return nullptr;
    }

    bool remove(K key) {
        int index = hashFunction(key);
        int originalIndex = index;

        while (table[index].occupied) {
            if (table[index].key == key) {
                table[index].occupied = false;
                size--;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) break;
        }
        return false;
    }
};

/*
 * Graph
 * Time Complexity:
 *   - addVertex(): O(1)
 *   - addEdge(): O(1)
 *   - findShortestPath(): O(V^2) V is number of vertices
 *   - blockPath()/unblockPath(): O(E) where E is edges from a vertex
 *   - displayGraph(): O(V + E)
 * Space Complexity: O(V + E)
 */
class Graph {
private:
    class Edge {
    public:
        string destination;
        int weight;
        bool blocked;
        Edge* next;
        Edge(string dest, int w) : destination(dest), weight(w), blocked(false), next(nullptr) {}
    };

    class Vertex {
    public:
        string name;
        Edge* edges;
        Vertex() : edges(nullptr) {}
    };

    HashTable<string, int> vertexIndex;
    DynamicArray<Vertex> vertices;
    int vertexCount;

public:
    Graph() : vertexCount(0) {}

    void addVertex(string name) {
        int* existing = vertexIndex.search(name);
        if (existing == nullptr) {
            Vertex v;
            v.name = name;
            vertices.push(v);
            vertexIndex.insert(name, vertexCount);
            vertexCount++;
        }
    }

    void addEdge(string from, string to, int weight) {
        int* fromIdx = vertexIndex.search(from);
        if (fromIdx == nullptr) {
            addVertex(from);
            fromIdx = vertexIndex.search(from);
        }

        int* toIdx = vertexIndex.search(to);
        if (toIdx == nullptr) {
            addVertex(to);
        }

        Edge* newEdge = new Edge(to, weight);
        newEdge->next = vertices[*fromIdx].edges;
        vertices[*fromIdx].edges = newEdge;
    }

    bool cityExists(string cityName) {
        int* idx = vertexIndex.search(cityName);
        return (idx != nullptr);
    }

    void blockPath(string from, string to) {
        int* fromIdx = vertexIndex.search(from);
        if (fromIdx != nullptr) {
            Edge* current = vertices[*fromIdx].edges;
            while (current != nullptr) {
                if (current->destination == to) {
                    current->blocked = true;
                    cout << "Path from " << from << " to " << to << " has been blocked.\n";
                    return;
                }
                current = current->next;
            }
        }
        cout << "Path from " << from << " to " << to << " does not exist.\n";
    }

    void unblockPath(string from, string to) {
        int* fromIdx = vertexIndex.search(from);
        if (fromIdx != nullptr) {
            Edge* current = vertices[*fromIdx].edges;
            while (current != nullptr) {
                if (current->destination == to) {
                    current->blocked = false;
                    cout << "Path from " << from << " to " << to << " has been unblocked.\n";
                    return;
                }
                current = current->next;
            }
        }
        cout << "Path from " << from << " to " << to << " does not exist.\n";
    }

    DynamicArray<string> findShortestPath(string start, string end, int& totalDistance) {
        DynamicArray<string> path;
        totalDistance = 0;

        int* startIdx = vertexIndex.search(start);
        int* endIdx = vertexIndex.search(end);

        if (startIdx == nullptr) {
            cout << "\nError: Source city '" << start << "' not found in network!\n";
            return path;
        }

        if (endIdx == nullptr) {
            cout << "\nError: Destination city '" << end << "' not found in network!\n";
            return path;
        }

        DynamicArray<int> distances;
        DynamicArray<int> previous;
        DynamicArray<bool> visited;

        const int INFINITY_VALUE = 999999;

        for (int i = 0; i < vertexCount; i++) {
            distances.push(INFINITY_VALUE);
            previous.push(-1);
            visited.push(false);
        }

        distances[*startIdx] = 0;

        for (int count = 0; count < vertexCount; count++) {
            int minDist = INFINITY_VALUE;
            int u = -1;

            for (int j = 0; j < vertexCount; j++) {
                if (!visited[j] && distances[j] < minDist) {
                    minDist = distances[j];
                    u = j;
                }
            }

            if (u == -1 || minDist == INFINITY_VALUE) break;

            visited[u] = true;

            Edge* edge = vertices[u].edges;
            while (edge != nullptr) {
                if (!edge->blocked) {
                    int* vIdx = vertexIndex.search(edge->destination);
                    if (vIdx != nullptr) {
                        int v = *vIdx;
                        if (!visited[v]) {
                            int alt = distances[u] + edge->weight;
                            if (alt < distances[v]) {
                                distances[v] = alt;
                                previous[v] = u;
                            }
                        }
                    }
                }
                edge = edge->next;
            }
        }

        if (distances[*endIdx] == INFINITY_VALUE) {
            cout << "\nNo route available from " << start << " to " << end << "!\n";
            cout << "The cities exist but are not connected in the network.\n";
            return path;
        }

        DynamicArray<string> reversePath;
        int current = *endIdx;
        while (current != -1) {
            reversePath.push(vertices[current].name);
            current = previous[current];
        }

        for (int i = reversePath.getSize() - 1; i >= 0; i--) {
            path.push(reversePath[i]);
        }

        totalDistance = distances[*endIdx];

        return path;
    }

    void displayGraph() {
        cout << "\n========== PAKISTAN NETWORK GRAPH ==========\n";
        for (int i = 0; i < vertexCount; i++) {
            cout << vertices[i].name << " -> ";
            Edge* edge = vertices[i].edges;
            if (edge == nullptr) {
                cout << "No connections";
            }
            while (edge != nullptr) {
                cout << edge->destination << "(" << edge->weight << "km";
                if (edge->blocked) cout << ", BLOCKED";
                cout << ")";
                if (edge->next != nullptr) cout << ", ";
                edge = edge->next;
            }
            cout << endl;
        }
        cout << "============================================\n";
    }

    DynamicArray<string> getAllCities() {
        DynamicArray<string> cities;
        for (int i = 0; i < vertexCount; i++) {
            cities.push(vertices[i].name);
        }
        return cities;
    }
};

class CourierLogisticsSystem {
private:
    PriorityQueue<Parcel*> overnightQueue;
    PriorityQueue<Parcel*> twoDayQueue;
    Queue<Parcel*> normalQueue;

    Graph routingNetwork;

    HashTable<string, Parcel*> trackingSystem;
    DynamicArray<Parcel*> allParcels;

    HashTable<string, Rider*> riderSystem;
    DynamicArray<Rider*> allRiders;

    Queue<Parcel*> pickupQueue;
    Queue<Parcel*> warehouseQueue;
    Queue<Parcel*> transitQueue;
    DynamicArray<string> operationLog;

    int parcelCounter;
    int riderCounter;

    int getPriorityValue(string priority) {
        if (priority == "overnight") return 1;
        if (priority == "2-day") return 2;
        return 3;
    }

    void initializeNetwork() {
        routingNetwork.addEdge("Lahore", "Islamabad", 375);
        routingNetwork.addEdge("Lahore", "Faisalabad", 135);
        routingNetwork.addEdge("Lahore", "Multan", 340);
        routingNetwork.addEdge("Lahore", "Rawalpindi", 380);
        routingNetwork.addEdge("Lahore", "Gujranwala", 80);
        routingNetwork.addEdge("Lahore", "Sialkot", 125);

        routingNetwork.addEdge("Lahore", "Karachi", 1200);
        routingNetwork.addEdge("Karachi", "Hyderabad", 165);
        routingNetwork.addEdge("Karachi", "Sukkur", 470);
        routingNetwork.addEdge("Karachi", "Larkana", 475);
        routingNetwork.addEdge("Hyderabad", "Sukkur", 320);

        routingNetwork.addEdge("Islamabad", "Peshawar", 180);
        routingNetwork.addEdge("Peshawar", "Mardan", 55);
        routingNetwork.addEdge("Peshawar", "Abbottabad", 120);
        routingNetwork.addEdge("Islamabad", "Abbottabad", 50);

        routingNetwork.addEdge("Multan", "Quetta", 675);
        routingNetwork.addEdge("Karachi", "Quetta", 715);
        routingNetwork.addEdge("Quetta", "Gwadar", 635);

        routingNetwork.addEdge("Faisalabad", "Multan", 225);
        routingNetwork.addEdge("Faisalabad", "Sargodha", 70);
        routingNetwork.addEdge("Rawalpindi", "Islamabad", 15);
        routingNetwork.addEdge("Gujranwala", "Sialkot", 65);

        routingNetwork.addEdge("Multan", "Sukkur", 395);
        routingNetwork.addEdge("Islamabad", "Faisalabad", 245);

        routingNetwork.addEdge("Lahore", "Islamabad-M2", 355);
        routingNetwork.addEdge("Islamabad-M2", "Islamabad", 10);

        cout << "\nNetwork initialized with Pakistani cities:\n";
        cout << "- Punjab: Lahore (Hub), Islamabad, Faisalabad, Multan, Rawalpindi, Gujranwala, Sialkot, Sargodha\n";
        cout << "- Sindh: Karachi (Hub), Hyderabad, Sukkur, Larkana\n";
        cout << "- KPK: Peshawar (Hub), Mardan, Abbottabad\n";
        cout << "- Balochistan: Quetta (Hub), Gwadar\n";
    }

public:
    CourierLogisticsSystem() : parcelCounter(1000), riderCounter(100) {
        initializeNetwork();
        cout << "\n========================================\n";
        cout << "   SwiftEx Pakistan Logistics System\n";
        cout << "========================================\n";
    }

    ~CourierLogisticsSystem() {
        for (int i = 0; i < allParcels.getSize(); i++) {
            delete allParcels[i];
        }
        for (int i = 0; i < allRiders.getSize(); i++) {
            delete allRiders[i];
        }
    }

    void addRider() {
        cout << "\n========== ADD NEW RIDER ==========\n";
        string name, phone, vehicle, location;
        int capacity;

        cout << "Enter Rider Name: ";
        getline(cin, name);
        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "\nVehicle Types:\n";
        cout << "1. Motorcycle (up to 20 kg)\n";
        cout << "2. Car (up to 50 kg)\n";
        cout << "3. Van (up to 100 kg)\n";
        cout << "4. Truck (up to 500 kg)\n";
        cout << "5. Custom\n";
        cout << "Select Vehicle Type (1-5): ";

        string vehicleInput;
        getline(cin, vehicleInput);
        int vehicleChoice = (vehicleInput.empty() ? 0 : stoi(vehicleInput));

        switch (vehicleChoice) {
        case 1:
            vehicle = "Motorcycle";
            capacity = 20;
            break;
        case 2:
            vehicle = "Car";
            capacity = 50;
            break;
        case 3:
            vehicle = "Van";
            capacity = 100;
            break;
        case 4:
            vehicle = "Truck";
            capacity = 500;
            break;
        case 5: {
            cout << "Enter Vehicle Type: ";
            getline(cin, vehicle);
            cout << "Enter Max Capacity (kg): ";
            string capStr;
            getline(cin, capStr);
            capacity = stoi(capStr);
            break;
        }
        default:
            cout << "Invalid choice! Defaulting to Motorcycle.\n";
            vehicle = "Motorcycle";
            capacity = 20;
            break;
        }

        cout << "\nAvailable Locations:\n";
        cout << "Lahore, Karachi, Islamabad, Faisalabad, Multan, Peshawar, Quetta, etc.\n";
        cout << "Enter Current Location: ";
        getline(cin, location);

        string riderId = "R" + to_string(riderCounter++);
        Rider* rider = new Rider(riderId, name, phone, vehicle, capacity, location);

        allRiders.push(rider);
        riderSystem.insert(riderId, rider);

        operationLog.push("New rider added: " + riderId + " - " + name);

        cout << "\n========================================\n";
        cout << "     RIDER ADDED SUCCESSFULLY!\n";
        cout << "========================================\n";
        cout << "Rider ID: " << riderId << endl;
        cout << "Name: " << name << endl;
        cout << "Vehicle: " << vehicle << endl;
        cout << "Capacity: " << capacity << " kg" << endl;
        cout << "Location: " << location << endl;
        cout << "========================================\n";
    }

    void removeRider() {
        cout << "\n========== REMOVE RIDER ==========\n";
        string riderId;
        cout << "Enter Rider ID to remove: ";
        getline(cin, riderId);

        Rider** rider = riderSystem.search(riderId);
        if (rider == nullptr || *rider == nullptr) {
            cout << "Rider not found!\n";
            return;
        }

        if ((*rider)->getCurrentLoad() > 0) {
            cout << "\nWarning: This rider has " << (*rider)->getCurrentLoad()
                << " kg of parcels assigned!\n";
            cout << "Please reassign parcels before removing rider.\n";
            string confirmStr;
            cout << "Force remove anyway? (y/n): ";
            getline(cin, confirmStr);
            if (confirmStr != "y" && confirmStr != "Y") {
                cout << "Removal cancelled.\n";
                return;
            }
        }

        string riderName = (*rider)->getName();

        for (int i = 0; i < allRiders.getSize(); i++) {
            if (allRiders[i]->getRiderId() == riderId) {
                delete allRiders[i];
                allRiders.removeAt(i);
                break;
            }
        }

        riderSystem.remove(riderId);
        operationLog.push("Rider removed: " + riderId + " - " + riderName);

        cout << "\n========================================\n";
        cout << "Rider " << riderId << " removed successfully!\n";
        cout << "========================================\n";
    }

    void displayAllRiders() {
        cout << "\n========== ALL RIDERS ==========\n";
        if (allRiders.getSize() == 0) {
            cout << "No riders in system.\n";
            return;
        }

        cout << "Total Riders: " << allRiders.getSize() << "\n\n";
        for (int i = 0; i < allRiders.getSize(); i++) {
            cout << (i + 1) << ". ";
            allRiders[i]->displaySummary();
        }
        cout << "================================\n";
    }

    void viewRiderDetails() {
        cout << "\n========== RIDER DETAILS ==========\n";
        string riderId;
        cout << "Enter Rider ID: ";
        getline(cin, riderId);

        Rider** rider = riderSystem.search(riderId);
        if (rider == nullptr || *rider == nullptr) {
            cout << "Rider not found!\n";
            return;
        }

        (*rider)->displayDetails();
    }

    void assignParcelToRider() {
        cout << "\n========== ASSIGN PARCEL TO RIDER ==========\n";
        string parcelId, riderId;

        cout << "Enter Parcel Tracking ID: ";
        getline(cin, parcelId);

        Parcel** parcel = trackingSystem.search(parcelId);
        if (parcel == nullptr || *parcel == nullptr) {
            cout << "Parcel not found!\n";
            return;
        }

        if ((*parcel)->getAssignedRider() != "None") {
            cout << "\nWarning: Parcel is already assigned to rider: "
                << (*parcel)->getAssignedRider() << endl;
            string confirmStr;
            cout << "Reassign to different rider? (y/n): ";
            getline(cin, confirmStr);
            if (confirmStr != "y" && confirmStr != "Y") {
                cout << "Assignment cancelled.\n";
                return;
            }

            Rider** oldRider = riderSystem.search((*parcel)->getAssignedRider());
            if (oldRider != nullptr && *oldRider != nullptr) {
                (*oldRider)->removeParcel(parcelId, (*parcel)->getWeight());
            }
        }

        cout << "\n--- Parcel Details ---\n";
        cout << "Weight: " << (*parcel)->getWeight() << " kg\n";
        cout << "Destination: " << (*parcel)->getDestination() << endl;
        cout << "Priority: " << (*parcel)->getPriority() << endl;

        cout << "\n--- Available Riders ---\n";
        bool hasAvailable = false;
        for (int i = 0; i < allRiders.getSize(); i++) {
            if (allRiders[i]->canCarry((*parcel)->getWeight())) {
                cout << (i + 1) << ". ";
                allRiders[i]->displaySummary();
                hasAvailable = true;
            }
        }

        if (!hasAvailable) {
            cout << "No riders available with sufficient capacity!\n";
            return;
        }

        cout << "\nEnter Rider ID to assign: ";
        getline(cin, riderId);

        Rider** rider = riderSystem.search(riderId);
        if (rider == nullptr || *rider == nullptr) {
            cout << "Rider not found!\n";
            return;
        }

        if (!(*rider)->canCarry((*parcel)->getWeight())) {
            cout << "\nError: Rider cannot carry this parcel!\n";
            cout << "Rider capacity: " << (*rider)->getRemainingCapacity() << " kg\n";
            cout << "Parcel weight: " << (*parcel)->getWeight() << " kg\n";
            return;
        }

        if ((*rider)->assignParcel(parcelId, (*parcel)->getWeight())) {
            (*parcel)->setAssignedRider(riderId);
            (*parcel)->updateStatus("Assigned to Rider " + riderId);
            operationLog.push("Parcel " + parcelId + " assigned to rider " + riderId);

            cout << "\n========================================\n";
            cout << "   ASSIGNMENT SUCCESSFUL!\n";
            cout << "========================================\n";
            cout << "Parcel: " << parcelId << endl;
            cout << "Assigned to: " << (*rider)->getName() << " (" << riderId << ")" << endl;
            cout << "Rider Load: " << (*rider)->getCurrentLoad() << "/"
                << (*rider)->getMaxCapacity() << " kg" << endl;
            cout << "========================================\n";
        }
        else {
            cout << "Assignment failed!\n";
        }
    }

    void autoAssignParcels() {
        cout << "\n========== AUTO-ASSIGN PARCELS ==========\n";

        if (allParcels.getSize() == 0) {
            cout << "No parcels to assign!\n";
            return;
        }

        if (allRiders.getSize() == 0) {
            cout << "No riders available!\n";
            return;
        }

        int assignedCount = 0;
        int failedCount = 0;

        for (int i = 0; i < allParcels.getSize(); i++) {
            Parcel* parcel = allParcels[i];

            if (parcel->getAssignedRider() != "None" ||
                parcel->getStatus() == "Delivered") {
                continue;
            }

            Rider* bestRider = nullptr;
            int minRemainingCapacity = 999999;

            for (int j = 0; j < allRiders.getSize(); j++) {
                if (allRiders[j]->canCarry(parcel->getWeight())) {
                    int remaining = allRiders[j]->getRemainingCapacity() - parcel->getWeight();
                    if (remaining < minRemainingCapacity) {
                        minRemainingCapacity = remaining;
                        bestRider = allRiders[j];
                    }
                }
            }

            if (bestRider != nullptr) {
                if (bestRider->assignParcel(parcel->getTrackingId(), parcel->getWeight())) {
                    parcel->setAssignedRider(bestRider->getRiderId());
                    parcel->updateStatus("Auto-assigned to Rider " + bestRider->getRiderId());
                    cout << "* " << parcel->getTrackingId() << " -> "
                        << bestRider->getRiderId() << " (" << bestRider->getName() << ")\n";
                    assignedCount++;
                }
            }
            else {
                cout << "x " << parcel->getTrackingId() << " - No suitable rider\n";
                failedCount++;
            }
        }

        operationLog.push("Auto-assigned " + to_string(assignedCount) + " parcels");

        cout << "\n========================================\n";
        cout << "Successfully assigned: " << assignedCount << " parcels\n";
        cout << "Failed to assign: " << failedCount << " parcels\n";
        cout << "========================================\n";
    }

    void completeDelivery() {
        cout << "\n========== COMPLETE DELIVERY ==========\n";
        string parcelId;
        cout << "Enter Parcel Tracking ID: ";
        getline(cin, parcelId);

        Parcel** parcel = trackingSystem.search(parcelId);
        if (parcel == nullptr || *parcel == nullptr) {
            cout << "Parcel not found!\n";
            return;
        }

        if ((*parcel)->getAssignedRider() == "None") {
            cout << "This parcel is not assigned to any rider!\n";
            return;
        }

        string riderId = (*parcel)->getAssignedRider();
        Rider** rider = riderSystem.search(riderId);

        if (rider != nullptr && *rider != nullptr) {
            (*rider)->completeDelivery(parcelId, (*parcel)->getWeight());
        }

        (*parcel)->updateStatus("Delivered");
        operationLog.push("Delivery completed: " + parcelId + " by rider " + riderId);

        cout << "\n========================================\n";
        cout << "   DELIVERY COMPLETED!\n";
        cout << "========================================\n";
        cout << "Parcel: " << parcelId << endl;
        cout << "Delivered by: " << riderId << endl;
        cout << "========================================\n";
    }

    void updateRiderAvailability() {
        cout << "\n========== UPDATE RIDER AVAILABILITY ==========\n";
        string riderId;
        cout << "Enter Rider ID: ";
        getline(cin, riderId);

        Rider** rider = riderSystem.search(riderId);
        if (rider == nullptr || *rider == nullptr) {
            cout << "Rider not found!\n";
            return;
        }

        cout << "\nCurrent Status: " << ((*rider)->getAvailability() ? "Available" : "Unavailable") << endl;
        cout << "\n1. Set Available\n";
        cout << "2. Set Unavailable\n";
        cout << "Enter choice: ";

        string choiceStr;
        getline(cin, choiceStr);
        int choice = (choiceStr.empty() ? 0 : stoi(choiceStr));

        bool newStatus = (choice == 1);
        (*rider)->setAvailability(newStatus);

        operationLog.push("Rider " + riderId + " status: " +
            (newStatus ? "Available" : "Unavailable"));

        cout << "\nRider status updated to: " << (newStatus ? "Available" : "Unavailable") << endl;
    }

    void updateRiderLocation() {
        cout << "\n========== UPDATE RIDER LOCATION ==========\n";
        string riderId, newLocation;

        cout << "Enter Rider ID: ";
        getline(cin, riderId);

        Rider** rider = riderSystem.search(riderId);
        if (rider == nullptr || *rider == nullptr) {
            cout << "Rider not found!\n";
            return;
        }

        cout << "Current Location: " << (*rider)->getCurrentLocation() << endl;

        cout << "Enter New Location: ";
        getline(cin, newLocation);

        (*rider)->setCurrentLocation(newLocation);
        operationLog.push("Rider " + riderId + " moved to " + newLocation);

        cout << "\nLocation updated successfully!\n";
    }

    void viewRidersByLocation() {
        cout << "\n========== RIDERS BY LOCATION ==========\n";
        string location;

        cout << "Enter Location: ";
        getline(cin, location);

        bool found = false;
        for (int i = 0; i < allRiders.getSize(); i++) {
            if (allRiders[i]->getCurrentLocation() == location) {
                if (!found) {
                    cout << "\nRiders in " << location << ":\n";
                    found = true;
                }
                cout << (i + 1) << ". ";
                allRiders[i]->displaySummary();
            }
        }

        if (!found) {
            cout << "No riders found in " << location << endl;
        }
        cout << "========================================\n";
    }

    void addNewRoute() {
        cout << "\n========== ADD NEW ROUTE ==========\n";
        string from, to;
        int distance;

        cout << "Enter Source City: ";
        cin.ignore();
        getline(cin, from);
        cout << "Enter Destination City: ";
        getline(cin, to);
        cout << "Enter Distance (km): ";
        cin >> distance;

        if (distance <= 0) {
            cout << "Invalid distance! Distance must be positive.\n";
            return;
        }

        routingNetwork.addEdge(from, to, distance);
        routingNetwork.addEdge(to, from, distance);

        cout << "\nRoute added successfully!\n";
        cout << from << " <-> " << to << " (" << distance << " km)\n";
        operationLog.push("Route added: " + from + " <-> " + to + " (" + to_string(distance) + " km)");
    }

    void addParcel() {
        cout << "\n========== ADD NEW PARCEL ==========\n";
        string sender, receiver, source, destination, priority;
        int weight;
        char fragileInput;

        cout << "Enter Sender Name: ";
        cin.ignore();
        getline(cin, sender);
        cout << "Enter Receiver Name: ";
        getline(cin, receiver);

        cout << "\nAvailable Cities:\n";
        cout << "Punjab: Lahore, Islamabad, Faisalabad, Multan, Rawalpindi, Gujranwala, Sialkot, Sargodha\n";
        cout << "Sindh: Karachi, Hyderabad, Sukkur, Larkana\n";
        cout << "KPK: Peshawar, Mardan, Abbottabad\n";
        cout << "Balochistan: Quetta, Gwadar\n\n";

        cout << "Enter Source City: ";
        getline(cin, source);
        cout << "Enter Destination City: ";
        getline(cin, destination);

        if (!routingNetwork.cityExists(source)) {
            cout << "\nWarning: Source city '" << source << "' is not in the network!\n";
            char addCity;
            cout << "Would you like to add this city to the network? (y/n): ";
            cin >> addCity;
            if (addCity == 'y' || addCity == 'Y') {
                routingNetwork.addVertex(source);
                cout << "City '" << source << "' added to network.\n";
                cout << "Note: You'll need to add routes connecting this city.\n";
            }
            else {
                cout << "Parcel creation cancelled.\n";
                return;
            }
        }

        if (!routingNetwork.cityExists(destination)) {
            cout << "\nWarning: Destination city '" << destination << "' is not in the network!\n";
            char addCity;
            cout << "Would you like to add this city to the network? (y/n): ";
            cin >> addCity;
            if (addCity == 'y' || addCity == 'Y') {
                routingNetwork.addVertex(destination);
                cout << "City '" << destination << "' added to network.\n";
                cout << "Note: You'll need to add routes connecting this city.\n";
            }
            else {
                cout << "Parcel creation cancelled.\n";
                return;
            }
        }

        int totalDist;
        DynamicArray<string> testPath = routingNetwork.findShortestPath(source, destination, totalDist);

        if (testPath.getSize() == 0) {
            cout << "\n=============================================\n";
            cout << "ERROR: No route exists between " << source << " and " << destination << "!\n";
            cout << "=============================================\n";
            char addRoute;
            cout << "\nWould you like to add a route? (y/n): ";
            cin >> addRoute;
            if (addRoute == 'y' || addRoute == 'Y') {
                cout << "\nYou can either:\n";
                cout << "1. Add a direct route between these cities\n";
                cout << "2. Add routes to connect them through other cities\n";
                cout << "3. Return to main menu (Option 4 to add routes)\n\n";

                char choice;
                cout << "Add a direct route now? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    int distance;
                    cout << "Enter distance from " << source << " to " << destination << " (km): ";
                    cin >> distance;
                    routingNetwork.addEdge(source, destination, distance);
                    routingNetwork.addEdge(destination, source, distance);
                    cout << "\nDirect route added! You can now create the parcel.\n";
                }
                else {
                    cout << "\nPlease add necessary routes from the main menu and try again.\n";
                    return;
                }
            }
            else {
                cout << "\nParcel creation cancelled. Please add routes first.\n";
                return;
            }
        }

        cout << "\nEnter Weight (kg): ";
        cin >> weight;
        cout << "Enter Priority (overnight/2-day/normal): ";
        cin >> priority;
        cout << "Is Fragile? (y/n): ";
        cin >> fragileInput;

        bool isFragile = (fragileInput == 'y' || fragileInput == 'Y');

        string trackingId = "SWX" + to_string(parcelCounter++);
        Parcel* parcel = new Parcel(trackingId, sender, receiver, destination, weight, priority, isFragile);

        allParcels.push(parcel);
        trackingSystem.insert(trackingId, parcel);

        int priorityValue = getPriorityValue(priority);
        int weightPriority = priorityValue * 100 + weight;

        if (priority == "overnight") {
            overnightQueue.enqueue(parcel, weightPriority);
        }
        else if (priority == "2-day") {
            twoDayQueue.enqueue(parcel, weightPriority);
        }
        else {
            normalQueue.enqueue(parcel);
        }

        pickupQueue.enqueue(parcel);
        parcel->updateStatus("Added to Pickup Queue");

        operationLog.push("Parcel " + trackingId + " created and sorted");

        cout << "\n=============================================\n";
        cout << "       PARCEL CREATED SUCCESSFULLY!\n";
        cout << "=============================================\n";
        cout << "Tracking ID: " << trackingId << endl;
        cout << "Route: " << source << " -> " << destination << endl;
        cout << "Distance: " << totalDist << " km\n";
        cout << "Priority: " << priority << endl;
        cout << "Weight: " << weight << " kg\n";
        cout << "Status: Sorted into " << priority << " queue\n";
        cout << "=============================================\n";
    }

    void displaySortedParcels() {
        cout << "\n========== SORTED PARCELS ==========\n";
        cout << "Overnight Queue Size: " << overnightQueue.size() << endl;
        cout << "2-Day Queue Size: " << twoDayQueue.size() << endl;
        cout << "Normal Queue Size: " << normalQueue.size() << endl;
        cout << "Pickup Queue Size: " << pickupQueue.size() << endl;
        cout << "Warehouse Queue Size: " << warehouseQueue.size() << endl;
        cout << "Transit Queue Size: " << transitQueue.size() << endl;
        cout << "====================================\n";
    }

    void findRoute() {
        cout << "\n========== FIND ROUTE ==========\n";
        string trackingId;
        cout << "Enter Tracking ID: ";
        cin >> trackingId;

        Parcel** parcel = trackingSystem.search(trackingId);
        if (parcel == nullptr || *parcel == nullptr) {
            cout << "Parcel not found!\n";
            return;
        }

        string destination = (*parcel)->getDestination();
        int totalDistance = 0;
        DynamicArray<string> path = routingNetwork.findShortestPath("Lahore", destination, totalDistance);

        if (path.getSize() == 0) {
            cout << "\n=============================================\n";
            cout << "ERROR: No route available to " << destination << "!\n";
            cout << "=============================================\n";
            cout << "Please add routes to connect Lahore to " << destination << endl;
            return;
        }

        cout << "\n========================================\n";
        cout << "   OPTIMAL ROUTE (DIJKSTRA'S ALGORITHM)\n";
        cout << "========================================\n";
        cout << "Parcel ID: " << trackingId << endl;
        cout << "Destination: " << destination << endl;
        cout << "Total Distance: " << totalDistance << " km\n";
        cout << "\nRoute Path:\n";
        for (int i = 0; i < path.getSize(); i++) {
            cout << "  " << (i + 1) << ". " << path[i];
            if (i < path.getSize() - 1) cout << " ->";
            cout << endl;
        }
        cout << "\nTotal Stops: " << (path.getSize() - 1) << endl;
        cout << "========================================\n";
    }

    void blockPath() {
        cout << "\n========== BLOCK PATH ==========\n";
        string from, to;
        cout << "Enter Source City: ";
        cin >> from;
        cout << "Enter Destination City: ";
        cin >> to;
        routingNetwork.blockPath(from, to);
        operationLog.push("Path blocked: " + from + " to " + to);
    }

    void unblockPath() {
        cout << "\n========== UNBLOCK PATH ==========\n";
        string from, to;
        cout << "Enter Source City: ";
        cin >> from;
        cout << "Enter Destination City: ";
        cin >> to;
        routingNetwork.unblockPath(from, to);
        operationLog.push("Path unblocked: " + from + " to " + to);
    }

    void displayNetwork() {
        routingNetwork.displayGraph();
    }

    void trackParcel() {
        cout << "\n========== TRACK PARCEL ==========\n";
        string trackingId;
        cout << "Enter Tracking ID: ";
        cin >> trackingId;

        Parcel** parcel = trackingSystem.search(trackingId);
        if (parcel == nullptr || *parcel == nullptr) {
            cout << "Parcel not found!\n";
            return;
        }

        (*parcel)->displayDetails();
    }

    void updateParcelStatus() {
        cout << "\n========== UPDATE PARCEL STATUS ==========\n";
        string trackingId;
        cout << "Enter Tracking ID: ";
        cin >> trackingId;

        Parcel** parcel = trackingSystem.search(trackingId);
        if (parcel == nullptr || *parcel == nullptr) {
            cout << "Parcel not found!\n";
            return;
        }

        cout << "\n--- Current Status: " << (*parcel)->getStatus() << " ---\n";
        cout << "\nStatus Options:\n";
        cout << "1. Dispatched\n";
        cout << "2. In Transit\n";
        cout << "3. Out for Delivery\n";
        cout << "4. Lost\n";
        cout << "5. Failed Delivery Attempt\n";
        cout << "6. Return to Sender\n";
        cout << "7. Held at Customs\n";
        cout << "8. At Distribution Center\n";
        cout << "9. Custom Status\n";
        cout << "0. Cancel\n";
        cout << "\nEnter your choice (1-9): ";

        int choice;
        cin >> choice;

        string newStatus;

        switch (choice) {
        case 1:
            newStatus = "Dispatched";
            break;
        case 2:
            newStatus = "In Transit";
            break;
        case 3:
            newStatus = "Out for Delivery";
            break;
        case 4:
            newStatus = "Lost";
            break;
        case 5:
            newStatus = "Failed Delivery Attempt";
            break;
        case 6:
            newStatus = "Return to Sender";
            break;
        case 7:
            newStatus = "Held at Customs";
            break;
        case 8:
            newStatus = "At Distribution Center";
            break;
        case 9:
            cout << "Enter custom status: ";
            cin.ignore();
            getline(cin, newStatus);
            break;
        case 0:
            cout << "Update cancelled.\n";
            return;
        default:
            cout << "Invalid choice! Update cancelled.\n";
            return;
        }

        (*parcel)->updateStatus(newStatus);
        operationLog.push("Status updated for " + trackingId + ": " + newStatus);

        cout << "\n========================================\n";
        cout << "Status updated successfully!\n";
        cout << "New Status: " << newStatus << endl;
        cout << "========================================\n";
    }

    void processPickupQueue() {
        cout << "\n========== PROCESS PICKUP QUEUE ==========\n";
        if (pickupQueue.isEmpty()) {
            cout << "No parcels in pickup queue.\n";
            return;
        }

        int count = 0;
        while (!pickupQueue.isEmpty() && count < 5) {
            Parcel* parcel = pickupQueue.dequeue();
            parcel->updateStatus("Picked up - Moving to Warehouse");
            warehouseQueue.enqueue(parcel);
            cout << "Processed: " << parcel->getTrackingId() << endl;
            operationLog.push("Pickup processed: " + parcel->getTrackingId());
            count++;
        }
        cout << "\nProcessed " << count << " parcels from pickup queue.\n";
    }

    void processWarehouseQueue() {
        cout << "\n========== PROCESS WAREHOUSE QUEUE ==========\n";
        if (warehouseQueue.isEmpty()) {
            cout << "No parcels in warehouse queue.\n";
            return;
        }

        int count = 0;
        while (!warehouseQueue.isEmpty() && count < 5) {
            Parcel* parcel = warehouseQueue.dequeue();
            parcel->updateStatus("Loaded - In Transit");
            transitQueue.enqueue(parcel);
            cout << "Processed: " << parcel->getTrackingId() << endl;
            operationLog.push("Warehouse processed: " + parcel->getTrackingId());
            count++;
        }
        cout << "\nProcessed " << count << " parcels from warehouse queue.\n";
    }

    void processTransitQueue() {
        cout << "\n========== PROCESS TRANSIT QUEUE ==========\n";
        if (transitQueue.isEmpty()) {
            cout << "No parcels in transit queue.\n";
            return;
        }

        int count = 0;
        while (!transitQueue.isEmpty() && count < 3) {
            Parcel* parcel = transitQueue.dequeue();
            parcel->updateStatus("Out for Delivery");
            cout << "Processed: " << parcel->getTrackingId() << " - Out for Delivery\n";
            operationLog.push("Transit completed: " + parcel->getTrackingId());
            count++;
        }
        cout << "\nProcessed " << count << " parcels from transit queue.\n";
    }

    void displayOperationLog() {
        cout << "\n========== OPERATION LOG ==========\n";
        if (operationLog.getSize() == 0) {
            cout << "No operations logged yet.\n";
            return;
        }

        int start = (operationLog.getSize() > 20) ? operationLog.getSize() - 20 : 0;
        for (int i = start; i < operationLog.getSize(); i++) {
            cout << (i + 1) << ". " << operationLog[i] << endl;
        }
        cout << "===================================\n";
    }

    void displayAllParcels() {
        cout << "\n========== ALL PARCELS ==========\n";
        if (allParcels.getSize() == 0) {
            cout << "No parcels in system.\n";
            return;
        }

        for (int i = 0; i < allParcels.getSize(); i++) {
            cout << "\n" << (i + 1) << ". Tracking ID: " << allParcels[i]->getTrackingId();
            cout << " | Status: " << allParcels[i]->getStatus();
            cout << " | Priority: " << allParcels[i]->getPriority();
            cout << " | Destination: " << allParcels[i]->getDestination();
            cout << " | Rider: " << allParcels[i]->getAssignedRider() << endl;
        }
        cout << "=================================\n";
    }
};

int main() {
    CourierLogisticsSystem system;
    string choice;

    do {
        cout << "\n\n";
        cout << "========================================\n";
        cout << "   SWIFTEX PAKISTAN LOGISTICS SYSTEM\n";
        cout << "========================================\n\n";

        cout << "MODULE 1: INTELLIGENT PARCEL SORTING\n";
        cout << "1.  Add New Parcel\n";
        cout << "2.  Display Sorted Queues Status\n\n";

        cout << "MODULE 2: PARCEL ROUTING\n";
        cout << "3.  Find Optimal Route for Parcel\n";
        cout << "4.  Add New Route to Network\n";
        cout << "5.  Block / Close Path\n";
        cout << "6.  Unblock / Open Path\n";
        cout << "7.  Display Network Graph\n\n";

        cout << "MODULE 3: PARCEL TRACKING\n";
        cout << "8.  Track Parcel by ID\n";
        cout << "9.  Update Parcel Status\n";
        cout << "10. Display All Parcels\n\n";

        cout << "MODULE 4: COURIER OPERATIONS\n";
        cout << "11. Process Pickup Queue\n";
        cout << "12. Process Warehouse Queue\n";
        cout << "13. Process Transit Queue\n";
        cout << "14. Display Operation Log\n\n";

        cout << "MODULE 5: RIDER MANAGEMENT\n";
        cout << "15. Add New Rider\n";
        cout << "16. Remove Rider\n";
        cout << "17. Display All Riders\n";
        cout << "18. View Rider Details\n";
        cout << "19. Assign Parcel to Rider\n";
        cout << "20. Auto-Assign Parcels to Riders\n";
        cout << "21. Complete Delivery\n";
        cout << "22. Update Rider Availability\n";
        cout << "23. Update Rider Location\n";
        cout << "24. View Riders by Location\n\n";

        cout << "0.  Exit System\n";
        cout << "----------------------------------------\n";
        cout << "Enter your choice: ";

        getline(cin, choice);

        if (choice == "1") {
            system.addParcel();
        }
        else if (choice == "2") {
            system.displaySortedParcels();
        }
        else if (choice == "3") {
            system.findRoute();
        }
        else if (choice == "4") {
            system.addNewRoute();
        }
        else if (choice == "5") {
            system.blockPath();
        }
        else if (choice == "6") {
            system.unblockPath();
        }
        else if (choice == "7") {
            system.displayNetwork();
        }
        else if (choice == "8") {
            system.trackParcel();
        }
        else if (choice == "9") {
            system.updateParcelStatus();
        }
        else if (choice == "10") {
            system.displayAllParcels();
        }
        else if (choice == "11") {
            system.processPickupQueue();
        }
        else if (choice == "12") {
            system.processWarehouseQueue();
        }
        else if (choice == "13") {
            system.processTransitQueue();
        }
        else if (choice == "14") {
            system.displayOperationLog();
        }
        else if (choice == "15") {
            system.addRider();
        }
        else if (choice == "16") {
            system.removeRider();
        }
        else if (choice == "17") {
            system.displayAllRiders();
        }
        else if (choice == "18") {
            system.viewRiderDetails();
        }
        else if (choice == "19") {
            system.assignParcelToRider();
        }
        else if (choice == "20") {
            system.autoAssignParcels();
        }
        else if (choice == "21") {
            system.completeDelivery();
        }
        else if (choice == "22") {
            system.updateRiderAvailability();
        }
        else if (choice == "23") {
            system.updateRiderLocation();
        }
        else if (choice == "24") {
            system.viewRidersByLocation();
        }
        else if (choice == "0") {
            cout << "\n========================================\n";
            cout << "   Thank you for using SwiftEx System\n";
            cout << "========================================\n";
        }
        else {
            cout << "\nInvalid choice! Please try again.\n";
        }

        if (choice != "0") {
            cout << "\nPress Enter to continue...";
            string dummy;
            getline(cin, dummy);
        }

    } while (choice != "0");

    return 0;
}
