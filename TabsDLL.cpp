#include "TabsDLL.h"
using namespace std;


TabsDLL::TabsDLL() : head(nullptr), tail(nullptr) {}

TabsDLL::~TabsDLL() {
    TabNode* current = head;
    while (current) {
        TabNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

bool TabsDLL::tabExists(int TabID) {
    TabNode* current = head;
    while (current) {
        if (current->tab_id == TabID) {
            return true;
        }
        current = current->next;
    }
    return false;
}

string TabsDLL::newTab(int TabID, string pageURL) {
    if (tabExists(TabID)) {
        cout << "Error: Tab " << TabID << " already exists.\n";
        return "";
    }

    TabNode* newNode = new TabNode;
    newNode->tab_id = TabID;
    newNode->count_of_open_pages = 1;
    newNode->page_stack.push(pageURL);
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        insertSorted(); // Sort the list after adding a new tab
    }

    return pageURL;
}

string TabsDLL::update(int TabID, string pageURL) {
    TabNode* current = head;
    while (current) {
        if (current->tab_id == TabID) {
            // Push the new page onto the stack
            current->page_stack.push(pageURL);
            current->count_of_open_pages++;

            // Retrieve the new top page
            string topPage;
            if (current->page_stack.pop(topPage)) {
                current->page_stack.push(topPage); // Push it back to restore the stack
            }

            // Sort the list after updating the tab
            insertSorted();

            return topPage; // Return the new top page
        }
        current = current->next;
    }
    cout << "Error: Tab " << TabID << " not found.\n";
    return "";
}

void TabsDLL::backTab(int TabID) {
    TabNode* current = head;
    while (current) {
        if (current->tab_id == TabID) {
            if (current->count_of_open_pages > 1) {
                string poppedPage;
                current->page_stack.pop(poppedPage);
                current->count_of_open_pages--;

                insertSorted(); // Sort the list after removing a page
                cout << "Removing from tab with ID: " << TabID << "\n";
                cout << "Removed page: " << poppedPage << ". Remaining number of pages: " << current->count_of_open_pages << "\n";
            } else {
                string poppedPage;
                current->page_stack.pop(poppedPage);

                cout << "Removing from tab with ID: " << TabID << "\n";
                cout << "Removed page: " << poppedPage << ". Stack is now empty. Deleting tab.\n";

                // Remove the tab from the list
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;

                delete current;
            }
            return;
        }
        current = current->next;
    }
    cout << "Error: Tab " << TabID << " not found.\n";
}

void TabsDLL::closeTab(int TabID) {
    TabNode* current = head;
    while (current) {
        if (current->tab_id == TabID) {
            cout << "Closing tab " << TabID << " and removing all pages:\n";

            while (!current->page_stack.isEmpty()) {
                string poppedPage;
                current->page_stack.pop(poppedPage);
                cout << "Removed page: " << poppedPage << "\n";
            }

            // Remove the tab from the list
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == head) head = current->next;
            if (current == tail) tail = current->prev;

            delete current;
            return;
        }
        current = current->next;
    }
    cout << "Error: Tab " << TabID << " not found.\n";
}

void TabsDLL::display() {
    cout << "Displaying tabs from head to tail:\n";
    TabNode* current = head;
    while (current) {
        cout << "Tab " << current->tab_id << " has " << current->count_of_open_pages << " pages open.\n";
        current = current->next;
    }

    cout << "Displaying tabs from tail to head:\n";
    TabNode* currentTail = tail;
    while (currentTail) {
        cout << "Tab " << currentTail->tab_id << " has " << currentTail->count_of_open_pages << " pages open.\n";
        currentTail = currentTail->prev;
    }
}

void TabsDLL::quitAndDisplay() {
    cout << "Closing all tabs:\n";
    while (head) {
        closeTab(head->tab_id);
    }
}

void TabsDLL::insertSorted() {
    if (!head || !head->next) return;

    bool ischanged;
    do {
        ischanged = false;
        TabNode* current = head;

        while (current->next != nullptr) {
            if (current->count_of_open_pages > current->next->count_of_open_pages || (current->count_of_open_pages == current->next->count_of_open_pages && current->tab_id > current->next->tab_id)) {

                TabNode* temp = current->next;

                if (current->prev) current->prev->next = temp;
                if (temp->next) temp->next->prev = current;

                current->next = temp->next;
                temp->prev = current->prev;
                temp->next = current;
                current->prev = temp;

                if (head == current) head = temp;
                if (tail == temp) tail = current;

                ischanged = true;
            } else {
                current = current->next;
            }
        }
    } while (ischanged);
}

//Yigit Narci
