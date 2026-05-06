#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

/* =========================
   CONTACT
========================= */

struct Contact {
    int id;
    string name;
    string phone;
    string email;
};

/* =========================
   GLOBAL AUTO ID
========================= */

int nextId = 1001;

int generateId() {
    return nextId++;
}

/* =========================
   PHONE VALIDATION
========================= */

bool isValidPhone(const string& phone) {
    if (phone.length() != 10)
        return false;

    for (char ch : phone) {
        if (!isdigit(ch))
            return false;
    }

    return true;
}

/* =========================
   SINGLY LINKED LIST
========================= */

struct SNode {
    Contact data;
    SNode* next;

    SNode(Contact c) {
        data = c;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    SNode* head;

    SNode* merge(SNode* left, SNode* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data.name < right->data.name) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

    void split(SNode* source, SNode** front, SNode** back) {
        SNode* slow = source;
        SNode* fast = source->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    SNode* mergeSortUtil(SNode* node) {
        if (!node || !node->next)
            return node;

        SNode* a;
        SNode* b;

        split(node, &a, &b);

        a = mergeSortUtil(a);
        b = mergeSortUtil(b);

        return merge(a, b);
    }

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    SNode* getHead() {
        return head;
    }

    bool phoneExists(const string& phone) {
        SNode* temp = head;

        while (temp) {
            if (temp->data.phone == phone)
                return true;

            temp = temp->next;
        }

        return false;
    }

    bool addContact(Contact c) {
        if (phoneExists(c.phone))
            return false;

        SNode* newNode = new SNode(c);

        if (!head) {
            head = newNode;
            return true;
        }

        SNode* temp = head;

        while (temp->next)
            temp = temp->next;

        temp->next = newNode;
        return true;
    }

    bool deleteContact(string name) {
        if (!head)
            return false;

        if (head->data.name == name) {
            SNode* del = head;
            head = head->next;
            delete del;
            return true;
        }

        SNode* prev = head;
        SNode* curr = head->next;

        while (curr) {
            if (curr->data.name == name) {
                prev->next = curr->next;
                delete curr;
                return true;
            }

            prev = curr;
            curr = curr->next;
        }

        return false;
    }

    Contact* search(string name) {
        SNode* temp = head;

        while (temp) {
            if (temp->data.name == name)
                return &(temp->data);

            temp = temp->next;
        }

        return nullptr;
    }

    bool updateContact(string name, string phone, string email) {
        SNode* temp = head;

        while (temp) {
            if (temp->data.name == name) {
                if (temp->data.phone != phone && phoneExists(phone))
                    return false;

                temp->data.phone = phone;
                temp->data.email = email;
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    void display() {
        if (!head) {
            cout << "No contacts available.\n";
            return;
        }

        SNode* temp = head;

        while (temp) {
            cout << "ID: " << temp->data.id
                 << " | Name: " << temp->data.name
                 << " | Phone: " << temp->data.phone
                 << " | Email: " << temp->data.email << "\n";

            temp = temp->next;
        }
    }

    void sortContacts() {
        head = mergeSortUtil(head);
    }

    void mergeList(SinglyLinkedList& other) {
        SNode* temp = other.head;

        while (temp) {
            addContact(temp->data);
            temp = temp->next;
        }

        sortContacts();
    }

    void saveToFile() {
        ofstream file("contacts.txt");

        SNode* temp = head;

        while (temp) {
            file << temp->data.id << "|"
                 << temp->data.name << "|"
                 << temp->data.phone << "|"
                 << temp->data.email << "\n";

            temp = temp->next;
        }

        file.close();
    }

    void loadFromFile() {
        ifstream file("contacts.txt");

        if (!file.is_open())
            return;

        string line;
        int maxId = 1000;

        while (getline(file, line)) {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr, name, phone, email;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, email);

            Contact c;
            c.id = stoi(idStr);
            c.name = name;
            c.phone = phone;
            c.email = email;

            if (c.id > maxId)
                maxId = c.id;

            addContact(c);
        }

        nextId = maxId + 1;

        file.close();
    }
};

/* =========================
   DOUBLY LINKED LIST
========================= */

struct DNode {
    Contact data;
    DNode* prev;
    DNode* next;

    DNode(Contact c) {
        data = c;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void buildFromSingly(SNode* sHead) {
        head = nullptr;
        tail = nullptr;

        while (sHead) {
            DNode* node = new DNode(sHead->data);

            if (!head) {
                head = tail = node;
            } else {
                tail->next = node;
                node->prev = tail;
                tail = node;
            }

            sHead = sHead->next;
        }
    }

    void traverseForward() {
        DNode* temp = head;

        while (temp) {
            cout << temp->data.name << " ";
            temp = temp->next;
        }

        cout << "\n";
    }

    void traverseBackward() {
        DNode* temp = tail;

        while (temp) {
            cout << temp->data.name << " ";
            temp = temp->prev;
        }

        cout << "\n";
    }
};

/* =========================
   CIRCULAR LINKED LIST
========================= */

struct CNode {
    Contact data;
    CNode* next;

    CNode(Contact c) {
        data = c;
        next = nullptr;
    }
};

class CircularLinkedList {
private:
    CNode* tail;
    int size;
    const int MAX_SIZE = 5;

public:
    CircularLinkedList() {
        tail = nullptr;
        size = 0;
    }

    void addRecent(Contact c) {
        CNode* newNode = new CNode(c);

        if (!tail) {
            tail = newNode;
            tail->next = tail;
            size = 1;
            return;
        }

        if (size == MAX_SIZE) {
            CNode* oldHead = tail->next;
            tail->next = oldHead->next;
            delete oldHead;
            size--;
        }

        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
        size++;
    }

    void display() {
        if (!tail) {
            cout << "No recent contacts.\n";
            return;
        }

        CNode* temp = tail->next;

        do {
            cout << temp->data.name << " ";
            temp = temp->next;
        } while (temp != tail->next);

        cout << "\n";
    }
};

/* =========================
   MAIN
========================= */

int main() {
    SinglyLinkedList contacts;
    CircularLinkedList recent;
    DoublyLinkedList doubly;

    contacts.loadFromFile();

    int choice;

    do {
        cout << "\n===== CONTACTS APP =====\n";
        cout << "1. Add Contact\n";
        cout << "2. Delete Contact\n";
        cout << "3. Display Contacts\n";
        cout << "4. Search Contact\n";
        cout << "5. Sort Contacts\n";
        cout << "6. Recent Contacts\n";
        cout << "7. Forward & Backward Traversal\n";
        cout << "8. Update Contact\n";
        cout << "9. Merge Another List\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Contact c;

            cout << "Enter name: ";
            getline(cin, c.name);

            do {
                cout << "Enter 10-digit phone number: ";
                getline(cin, c.phone);

                if (!isValidPhone(c.phone))
                    cout << "Invalid phone number. Must contain exactly 10 digits.\n";

            } while (!isValidPhone(c.phone));

            if (contacts.phoneExists(c.phone)) {
                cout << "Phone number already exists.\n";
                continue;
            }

            cout << "Enter email: ";
            getline(cin, c.email);

            c.id = generateId();

            contacts.addContact(c);
            contacts.saveToFile();

            cout << "Contact added successfully. Generated ID: " << c.id << "\n";
        }

        else if (choice == 2) {
            string name;

            cout << "Enter name to delete: ";
            getline(cin, name);

            if (contacts.deleteContact(name)) {
                contacts.saveToFile();
                cout << "Contact deleted.\n";
            } else {
                cout << "Contact not found.\n";
            }
        }

        else if (choice == 3) {
            contacts.display();
        }

        else if (choice == 4) {
            string name;

            cout << "Enter name to search: ";
            getline(cin, name);

            Contact* found = contacts.search(name);

            if (found) {
                cout << "ID: " << found->id
                     << " | Name: " << found->name
                     << " | Phone: " << found->phone
                     << " | Email: " << found->email << "\n";

                recent.addRecent(*found);
            } else {
                cout << "Contact not found.\n";
            }
        }

        else if (choice == 5) {
            contacts.sortContacts();
            contacts.saveToFile();
            cout << "Contacts sorted alphabetically.\n";
        }

        else if (choice == 6) {
            recent.display();
        }

        else if (choice == 7) {
            doubly.buildFromSingly(contacts.getHead());

            cout << "Forward: ";
            doubly.traverseForward();

            cout << "Backward: ";
            doubly.traverseBackward();
        }

        else if (choice == 8) {
            string name, phone, email;

            cout << "Enter name: ";
            getline(cin, name);

            do {
                cout << "Enter new 10-digit phone number: ";
                getline(cin, phone);

                if (!isValidPhone(phone))
                    cout << "Invalid phone number. Must contain exactly 10 digits.\n";

            } while (!isValidPhone(phone));

            cout << "Enter new email: ";
            getline(cin, email);

            if (contacts.updateContact(name, phone, email)) {
                contacts.saveToFile();
                cout << "Contact updated.\n";
            } else {
                cout << "Update failed. Phone may already exist or contact not found.\n";
            }
        }

        else if (choice == 9) {
            SinglyLinkedList other;
            int n;

            cout << "How many contacts in second list? ";
            cin >> n;
            cin.ignore();

            for (int i = 0; i < n; i++) {
                Contact c;

                cout << "\nEnter name: ";
                getline(cin, c.name);

                do {
                    cout << "Enter 10-digit phone number: ";
                    getline(cin, c.phone);

                    if (!isValidPhone(c.phone))
                        cout << "Invalid phone number. Must contain exactly 10 digits.\n";

                } while (!isValidPhone(c.phone));

                if (contacts.phoneExists(c.phone) || other.phoneExists(c.phone)) {
                    cout << "Phone number already exists. Skipping this contact.\n";
                    continue;
                }

                cout << "Enter email: ";
                getline(cin, c.email);

                c.id = generateId();

                other.addContact(c);
            }

            contacts.mergeList(other);
            contacts.saveToFile();

            cout << "Lists merged successfully.\n";
        }

    } while (choice != 0);

    return 0;
}