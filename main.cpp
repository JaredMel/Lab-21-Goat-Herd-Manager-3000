#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Goat {
    private:
        int age;
        string name;
        string color;
        string names[15] = {"Senior", "Godlike", "Old", "Mature", "Teen", "Simon", "Simone", "Simons", "Simones", "Tyler", "The John", "John", "Bloofer", "Mities", "Gorlac"};
        string colors[15] = {"Red", "Yellow", "Blue", "White", "Gold", "Silver", "Mauve", "Orange", "Green", "Yellow-Orange", "Purple", "Grey", "Black", "Pink", "Brown"};
    public:
        Goat() {
            int randnum = rand() % 15;
            age = rand() % 19 + 1;
            name = names[randnum];
            randnum = rand() % 15;
            color = colors[randnum];
        }
        Goat(int a, string n, string c) {age = a; name = n; color = c;};

        void printGoat(Goat g) 
        {
            cout << g.name << " (" << g.color << ", " << g.age << ")" << endl;
        }
};

class DoublyLinkedList {
    private:
        struct Node {
            Goat data;
            Node* prev;
            Node* next;
            Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
                data = val;
                prev = p;
                next = n;
            }
        };

    Node* head;
    Node* tail;
    public:
        // constructor
        DoublyLinkedList() { head = nullptr; tail = nullptr; }

        void push_back(Goat value) {
            Node* newNode = new Node(value);
            if (!tail) // if there's no tail, the list is empty
                head = tail = newNode;
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        void push_front(Goat value) {
            Node* newNode = new Node(value);
            if (!head) // if there's no head, the list is empty
                head = tail = newNode;
            else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        }

        void insert_after(Goat value, int position) {
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
                tail = newNode; // Inserting at the end
                temp->next = newNode;
        }

        /*void delete_node(Goat value) {
            if (!head) return; // Empty list

            Node* temp = head;
            while (temp && temp->data != value)
                temp = temp->next;

            if (!temp) return; // Value not found

            if (temp->prev) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next; // Deleting the head
            }

            if (temp->next) {
                temp->next->prev = temp->prev;
            } else {
                tail = temp->prev; // Deleting the tail
            }

            delete temp;
        }*/

        void print() {
            Node* current = head;
            if (!current) return;
            while (current) {
                current->data.printGoat(current->data);
                current = current->next;
            }
            cout << endl;
        }

        void print_reverse() {
            Node* current = tail;
            if (!current) return;
            while (current) {
                current->data.printGoat(current->data);
                current = current->prev;
            }
            cout << endl;
        }

        ~DoublyLinkedList() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};

// Driver program
int main() {
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS; //Tried to use srand(time(0)) but for some reason wouldn't allow me.

    for (size_t i = 0; i < size; i++)
    {
        Goat temp = Goat();
        list.push_back(temp);
    }
    
    cout << "List forward: " << endl;
    list.print();

    cout << "List backward: " << endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}