#include <iostream>
#include <string>
using namespace std;

// Struktur untuk Node dalam doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;

    // Constructor
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

// Kelas untuk Doubly Linked List
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor untuk membersihkan memory
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }

    // Menambahkan node di awal linked list
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);

        // Jika list kosong
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }

        // Menambahkan di awal list
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    // Menambahkan node di akhir linked list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);

        // Jika list kosong
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
            return;
        }

        // Menambahkan di akhir list
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // Mencetak semua elemen dari depan ke belakang
    void printForward() {
        Node* current = head;

        // Traversal dari head ke tail
        while (current != nullptr) {
            cout << current->data;

            // Tambahkan spasi jika bukan node terakhir
            if (current->next != nullptr) {
                cout << " ";
            }

            current = current->next;
        }
        cout << endl;
    }

    // Mencetak semua elemen dari belakang ke depan
    void printBackward() {
        Node* current = tail;

        // Traversal dari tail ke head
        while (current != nullptr) {
            cout << current->data;

            // Tambahkan spasi jika bukan node pertama
            if (current->prev != nullptr) {
                cout << " ";
            }

            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    int N;
    cin >> N;

    DoublyLinkedList list;

    // Membaca dan memproses N operasi
    for (int i = 0; i < N; i++) {
        string operation;
        cin >> operation;

        if (operation == "insertFirst") {
            int value;
            cin >> value;
            list.insertAtBeginning(value);
        }
        else if (operation == "insertLast") {
            int value;
            cin >> value;
            list.insertAtEnd(value);
        }
        else if (operation == "printForward") {
            list.printForward();
        }
        else if (operation == "printBackward") {
            list.printBackward();
        }
    }

    return 0;
}
