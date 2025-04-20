Tab Manager — Doubly Linked List & Stack Simulation

This project simulates a basic tab manager similar to a web browser.

Each tab is tracked using a doubly linked list, and each tab maintains a history of visited pages using a stack (LIFO). Pages can be opened, navigated back, or closed entirely, and all tabs are kept sorted by page count and tab ID.

Features

- Open Tab: Create a new tab or open a new page in an existing tab
- Back Navigation: Go back to the previous page in a tab
- Close Tab: Remove a tab and display its page history
- Display: Show all tabs and page counts (from head to tail and tail to head)
- Quit: Gracefully closes all tabs and displays removed pages

Technologies

- Language: C++
- Data Structures:
  - Custom stack for page history (DynPageStack)
  - Custom doubly linked list for managing tabs (TabsDLL)
- No STL containers used (completely manual memory management)

File Structure

| File             | Purpose                                  |
|------------------|------------------------------------------|
| HW3main.cpp      | Main program – command interpreter       |
| TabsDLL.h/cpp    | Tab manager with doubly linked list logic|
| DynPageStack.h/cpp | Page history stack implementation      |

Run Instructions

1. Compile:

   g++ HW3main.cpp TabsDLL.cpp DynPageStack.cpp -o tab_manager

2. Execute:

   ./tab_manager

3. Input:

   When prompted, enter the name of a text file with valid tab commands (e.g., commands.txt).

Example Input

open 1 google.com  
open 2 youtube.com  
open 1 github.com  
back 1  
display  
quit

Output Example

COMMAND: open 1 google.com  
Created new tab 1 with page: google.com  

COMMAND: back 1  
Removing from tab with ID: 1  
Removed page: github.com. Remaining number of pages: 1  

COMMAND: display  
Displaying tabs from head to tail:  
Tab 2 has 1 pages open.  
Tab 1 has 1 pages open.  

Displaying tabs from tail to head:  
Tab 1 has 1 pages open.  
Tab 2 has 1 pages open.  
