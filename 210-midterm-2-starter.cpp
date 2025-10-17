#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

// --------
// Constants
// --------
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const string FILENAME = "/Users/andrewtai/Desktop/COMSC_210/midterm2/names.txt";

// --------
// Prototypes
// --------
void printVector(const vector<string>& v);

// --------
// DLL class
// --------
class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // Printers
    void printHead() {
        cout << head->data;
    }
    void printTail() {
        cout << tail->data;
    }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " " << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

// --------
// Main
// --------
int main() {
    // Coffee queue implemented as a doubly linked list

    // Set seed
    srand(time(0));

    // Open file of names; store in vector
    ifstream names;
    names.open("names.txt");
    if (!names) {       // Check if file good
        cout << "Error opening file." << endl;
        return 1;
    }
    vector<string> nameList;
    string name;
    while (names >> name)  // Read names into vector
        nameList.push_back(name);
    names.close();

    const int nNames = nameList.size();
    printVector(nameList); // For debugging

    // Initialize coffeeLine with 5 random names
    cout << "Store opens:" << endl;
    DoublyLinkedList coffeeLine;
    for (int i = 0; i < 5; i++) {
        int r = rand() % nNames;
        coffeeLine.push_back(nameList[r]);
        cout << nameList[r] << " joins the line" << endl;
    }
    cout << "Resulting line: " << endl;
    coffeeLine.print();

    // Simulate 20 rounds
    for (int t=0; t<20; t++) {
        cout << "Time step #" << t+1 << endl;

        // Calculate probability
        int prob = rand() % 100 + 1;

        // 1. Front of line is served
        if (prob <= 40) {
            coffeeLine.printHead();
            cout << " is served" << endl;
            coffeeLine.pop_front();
        }

        // 2. New customer joins end
        if (prob <= 60) {
            int r = rand() % nNames;
            cout << nameList[r] << " joined the line" << endl;
            coffeeLine.push_back(nameList[r]);
        }
    }

    return 0;
}


// --------
// Programmer functions
// --------
void printVector(const vector<string>& v) {
    // For debugging: print vector contents
    for (const string& i : v)
        cout << i << " ";
    cout << endl;
}
