/**
 * Title:   Lab 4 - BookList class implementation.
 * Purpose: ** implement a BookList class that will be used to create new linked list, add and delete elements**
 * Class:   CSC 2430 Winter 2022
 * Author:  ** Kaddijatou Baldeh **
 */
#include "booklist.h"

#include <sstream>
#include <string>
#include <iostream>
using std::string;
using std::stringstream;
using std::ostream;
using std::istream;
using std::endl;

/**
 * Copy Constructor of the Book List
 * You don't need to implement this method.
 * @param other the original BookList that is going to be copied.
 */
BookList::BookList(const BookList &other) {

}
/**
 * Copy Assignment operator of the Book List
 * You don't need to implement this method.
 * @param rhs The right hand side operand of the assignment.
 * @return a reference to the caller object
 */
BookList &BookList::operator=(const BookList &rhs) {
    return *this;
}
/**
 * Default constructor
 * Initializing _head to null pointer and setting initial size to zero
 */
BookList::BookList() {
    // set head to null and size to zero
    _head = nullptr;
    _size = 0;
}
/**
 * Destructor
 * deallocate the memory allocated for the linklist and book
 */
BookList::~BookList() {
    // deallocate memory
    if(_head != nullptr){
        //set a temporary node to head
        Node* temp = _head;
        // node that should be deleted
        Node* toDelete;
        //a loop to that checks if the head that temp is pointing to is not null
        while (temp != nullptr){
            toDelete = temp;
            temp = temp->next;
            toDelete->next = nullptr;
            delete toDelete->book;// deallocate memory for the book first
            delete toDelete;
        }
    }

}
/**Adds a book at the beginning of the list.
 * @param book to be added to the new node
 * @return always returns true
 */
bool BookList::AddBook(const Book &book) {
    //create a new node with a book
    Node* neo = new Node(book);
    // if the book list is empty
    if( _head == nullptr){
        _head = neo;
    }
        //if the list is not empty, add a new book
    else{
        neo->next = _head;
        _head = neo;
    }
    _size++;// increase size
    return true;
}
/**
 * Creates a book using the parameters, then adds the book at the beginning of the list.
 * @param name of the book
 * @param isbn of the book
 * @param year of publication
 * @return always returns true
 */
bool BookList::AddBook(const string &name, const string &isbn, unsigned int year) {
    // create a new node and a book for that node
    Node* neo = new Node;
    neo->book = new Book(name,isbn,year);
    // if the book list is empty
    if(_head == nullptr){
        _head = neo;
    }
        //if the list is not empty, add a new book
    else{
        neo->next = _head;
        _head = neo;
    }
    // increase size
    _size++;
    return true;
}
/**
 * Creates a book using the parameters, then adds the book at the beginning of the list.
 * @param name of the book
 * @param year of publication
 * @return always returns true
 */
bool BookList::AddBook(const string &name, unsigned int year) {
    // create a new node and a book for that node
    Node* neo = new Node;
    neo->book = new Book(name,year);

    if(_head == nullptr){
        _head = neo;
    }
        //if the list is not empty, add a new book
    else{
        neo->next = _head;
        _head = neo;
    }
    // increase size
    _size++;
    return true;
}
/**
 * Find a book with the given isbn
 * @param isbn the isbn of the book the user is searching for
 * @return position of the book in the list if found, -1 otherwise
 */
int BookList::IndexOf(const string &isbn) const {
    // initialize position to start loop through list
    size_t start = 0;
    //if the position to start is not within list
    if (start >= _size){
        return -1;
    }
    //creat temp to point where head point to
    Node* temp = _head;
    //loop through to find index with the isbn
    for (int i = start; i < _size; ++i) {
        if (temp->book->GetISBN() == isbn)
            // return index of the position of the book
            return i;
        temp = temp->next;
    }
    //return -1 otherwise
    return -1;
}
/**
 * Returns the pointer to the book that is located at the given position
 * Returns the pointer to the book that is located at the given position. If the position is not valid it returns nullptr
 * @param position
 * @return
 */
const Book *BookList::Get(unsigned int position) const {
    // Add your code
    size_t cur = 0;
    //if the position is not within list
    if(position >= _size){
        return nullptr;
    }
    //loop through to find index with the isbn
    for (Node* temp = _head; temp != nullptr; temp = temp->next) {
        if (cur == position) {
            return temp->book;
        }
        cur++;
    }
    //return null otherwise
    return nullptr;
}
/**
 * Removes the book located in the given position
 * @param position that is to be removed
 * @return true if position is removed, false otherwise
 */
bool BookList::Remove(unsigned int position) {
    //if the position to remove does not exist in the list
    if(position >= _size){
        return false;
    }
    Node * toRemove;
    // if the size is one and _head does not equal a null pointer
    if(0 == position){
        toRemove = _head;
        _head = _head->next;

    }else{
        Node* temp = _head;
        if(temp == nullptr || temp->next == nullptr){
            return false;
        }
        //loop through to find the position
        for(int i = 0; i < position; i++){
            temp = temp->next;
        }
        toRemove = temp->next;
        temp->next = toRemove->next;
    }
    //delete book element and node
    delete toRemove->book;
    delete toRemove;
    _size--; //reduce size

    return true;
}
/**
 * Returns a string representation of the list.
 * Format for string to be returned:
 * [Book1Name.Book1ISBN.Book1Year, Book2Name.Book2ISBN, Book2Year, ...]
 * @return the string created to string
 */
string BookList::ToString() const {
    stringstream ss;
    ss << "[";
    //loop through book list
    for (Node* temp = _head; temp != nullptr && _size > 0; temp = temp->next){
        //place a comma between each book information
        if(temp != _head){
            ss << ", ";
        }
        //used the book ToString method to add a period between book information fields
        ss << temp->book->ToString();
    }
    ss << "]";

    return ss.str();
}
/**
 * Reads from an input stream, each book will be stored in the stream in a single line.
 * @param input stream to read from
 * @return input to allow stream chaining
 */

istream &BookList::Read(istream &input) {
    //loop through input to add new books
    while(input){
        Node * neo = new Node;
        // create a default book to copy new book information
        neo->book = new Book("default","default",1);
        //calls the book read method of the book class to get input
        neo->book->Read(input);
        // after the information is copied, if the book list is empty
        if(_head == nullptr){
            _head = neo;
        }
        else{ //if the list is not empty, add a new book to the top of the list
            neo->next = _head;
            _head = neo;
        }
        _size++;// increase size
    }
    //check if a book has not been copied correctly to delete
    Node* temp = _head;
    if(temp->book->GetName() == "default"){
        _head = temp->next;
        delete temp->book;
        delete temp;
        _size--;
    }
    return input;
}
/**
 * Writes to the output stream, each book should be stored in a single line.
 * @param output
 * @return output to allow stream chaining
 */
ostream &BookList::Write(ostream &output) const {
    // loop through book to write
    for (Node* temp = _head; temp != nullptr && _size > 0; temp = temp->next) {
        output << temp->book->GetName() << "." << temp->book->GetISBN() << "." << temp->book->GetYear() << "\n";
    }
    return output;
}
/**
 * Clears the whole list. It frees all the allocated memory for the elements of the list
 * sets _head to nullptr and _size to zero.
 * @param none
 * @return none
 */
void BookList::Clear() {
    Node* temp = _head;
    Node* toClear;
    // continue to remove while head is not null
    while(temp != nullptr && _size > 0 ){
        toClear = temp;
        temp = temp->next;
        delete toClear->book; // delete book stored
        delete toClear;
        _size--;//reduces size
    }
    //set head to null
    _head = nullptr;
}
/**
 * adds quotation marks and title to each book info field
 * @param none
 * @return output stream
 */
string BookList::ToJSON() const {
    stringstream ss;
    ss << "[";
    for (Node* temp = _head; temp != nullptr && _size > 0; temp = temp->next){
        if(temp != _head){
            ss << ", ";
        }
        ss << temp->book->ToJSON();
    }
    ss << "]";

    return ss.str();
}
/**
 * The number of elements of the list.
 * @return the number of elements of the list.
 */
unsigned int BookList::Size() const {
    return _size;
}
/**
 * Creates a dynamically allocated
 * @param book
 */
BookList::Node::Node(const Book &book) {
    this->book = new Book(book);
    next = nullptr;
}

/**
 * initializes book and next to nullptr
 * @param none
 */
BookList::Node::Node() {
    book = nullptr;
    next = nullptr;
}