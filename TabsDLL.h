#ifndef TABSDLL_H
#define TABSDLL_H

#include <iostream>
#include "DynPageStack.h"
#include <string>

class TabsDLL{
private:
    struct TabNode
    {
    int tab_id;
    DynPageStack page_stack;
    int count_of_open_pages;
    TabNode* next;
    TabNode* prev;
    };
    
    TabNode* head;
    TabNode* tail;
    
    void insertSorted();

public:
    TabsDLL();
    ~TabsDLL();
    
    bool tabExists(int TabID);
    string newTab(int TabID, string pageURL);
    string update(int TabID, string pageURL);
    void backTab(int TabID);
    void closeTab(int TabID);
    void display();
    void quitAndDisplay();
};

#endif // TABSDLL_H
