# Playlist-Management-System
The provided C++ program implements a playlist management system using a doubly linked list and a hash table. Here's a detailed description:

1. **Header Files:**
   - `#include<iostream>`: Standard input/output stream functions.
   - `#include<string.h>` and `#include<cstring>`: String manipulation functions.
   - `#include<stdlib.h>`: General-purpose functions involving memory allocation, rand function, etc.
   - `#include<stdio.h>`: Standard input/output functions.
   - `#include<fstream>`: File stream functions for reading/writing to files.

2. **Constants and Structures:**
   - `const int TABLE_SIZE = 10;`: Constant defining the size of the hash table.
   - `struct node`: Definition of a node structure for the doubly linked list with a `char` array to store the song name, and pointers to the next and previous nodes.

3. **Global Variables:**
   - `node* top, *temp, *top1;`: Global pointers for the linked list operations.

4. **Function Prototypes:**
   - `void tofile(char a[])`: Function to write a song name to a file named "playlist.txt".
   - `class Stack`: Definition of a stack class for maintaining search and play history.
     - `bool isEmpty()`: Check if the stack is empty.
     - `void push(const char* newSong)`: Push a new song onto the stack.
     - `string top()`: Return the top element of the stack.
     - `void pop()`: Pop the top element from the stack.
     - `void display()`: Display the contents of the stack.
     - `~Stack()`: Destructor to deallocate memory.

   - `class HashTable`: Definition of a hash table class for maintaining unique songs.
     - `int hashFunction(const char* key)`: Hash function to determine the index in the hash table.
     - `void insert(const char* key)`: Insert a song into the hash table.
     - `void display()`: Display the contents of the hash table.
     - `bool search(const char* key)`: Search for a song in the hash table.

5. **Linked List Operations:**
   - `void add_node(struct node* first)`: Add a new node (song) to the end of the linked list.
   - `void add_node_file(struct node* first, string a)`: Add a node with a song name from a file.
   - `void delete_file(char a[])`: Delete a song from the file "playlist.txt."
   - `void del_node(struct node* first)`: Delete the last node from the linked list.
   - `void printlist(struct node* first)`: Print the list of songs in the playlist.
   - `void count_nodes(struct node* first)`: Count the total number of songs in the playlist.
   - `struct node* del_pos(struct node* &pointer, int pos)`: Delete a node at a specified position.

6. **Search and Play Operations:**
   - `void search1(struct node* first)`: Search for a song in the playlist and update the search history.
   - `void create()`, `void push(char data[])`, `void display()`: Operations for maintaining a recently played songs list.
   - `void play(struct node* first)`: Play a selected song from the playlist and update the recently played list.
   - `void recent()`, `void topelement()`: Display the recently played songs and the last played song.
   - `void sort(struct node* start)`: Sort the playlist in ascending order.

7. **File Operations:**
   - `void addplaylist(struct node* start)`: Add songs to the playlist from a file.
   - `void del_search(struct node* &start)`: Delete a song from the playlist based on user input.

8. **Play Modes:**
   - `void playloop(struct node* &start)`: Play songs in a loop.
   - `void shuffleplay(struct node* &start)`: Play songs in a shuffled order.
   - `void loop(struct node* &start)`: Choose between regular and shuffled play modes.

9. **Delete Menu:**
   - `void deletemenu(struct node* &start)`: Display a menu for deleting songs (by search or position).

10. **Main Function:**
    - Initialization of variables and the main program loop allowing users to perform various operations on the playlist.

Note: The program seems to be a console-based music playlist management system with features such as adding, deleting, searching, and playing songs. It maintains a playlist using a doubly linked list, stores songs in a hash table for uniqueness, and keeps track of play and search history using a stack. Users can also choose between regular and shuffled play modes.
