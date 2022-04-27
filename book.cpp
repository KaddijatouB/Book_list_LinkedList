/**
 * Title:   Lab 4 - Book class implementation
 * Purpose: ** Implement a book class that can be used to get a book informations**
 * Class:   CSC 2430 Winter 2022
 * Author:  ** Kaddijatou Baldeh **
 */
#include "book.h"

#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::ostream;
using std::istream;
using std::stringstream;


/** Constructor that takes in name and year
 * @param name of the book
 * @param year it of publication
 */
Book::Book(const string& name, const int& year){
    _name = name;
    _year = year;
}
// Implementation of
/** Constructor that takes in name, isbn and year
 * @param name of the book
 * @param year it of publication
 * @param isbn of the book
 */
Book::Book(const string& name, const string& isbn,const int& year){
    _name = name;
    _isbn = isbn;
    _year = year;
}
/** Copy constructor for the book
 * @param other the book that is going to be copied
 */
Book::Book(const Book& other){
    _name = other._name;
    _isbn = other._isbn;
    _year = other._year;
}
/** adding copy assigment operator to follow rule of 3
 * @param rhs is right hand side operand of the assignment
 * @return a reference to the caller object
 */
const Book& Book::operator=(const Book& rhs){
    return *this;
}
/** adding destructor to follow rule of 3
 *  destructor deallocates the memory that is allocated for the book
 * @param none
 */
Book::~Book(){
    //default
}
/** Implementation of ToString method
 * adds a period between the book information fields
 * @param none
 * @return output to the string
 */
string Book::ToString()const{
    stringstream out;
    out << _name << "." << _isbn << "." << _year;
    return out.str();
}
/** getter/accessor method for the book class
 * @param none
 * @return isbn of the book if valid, empty string otherwise
 */
string Book::GetISBN() const{
    return _isbn;
}
/** Name getter/accessor method  for the book class
 * @param none
 * @return name of the book
 */
string Book::GetName() const{
    return _name;
}
/**Year getter/accessor method
 * @param none
 * @return year of publication
 */
int Book::GetYear() const{
    return _year;
}
/** Implementation of ToJSON method
 * adds quotation marks and title to each book info field
 * @param none
 * @return output to the output string
 */
string Book::ToJSON()const{
    stringstream out;

    out << "{\"name\":\"" << _name << "\", \"isbn\":\"" << _isbn << "\", \"year\":" << _year << "}";

    return out.str();
}
/**  Remember that each book is in a single line, and that the fields are separated by period
 set those values to the data members of book, validate the isbn, return input
  * @param inputStream
 * @return input
 */

istream& Book::Read(istream& inputStream){
    string line; //variable to get the line of text
    string name, possibleIsbn, isbn, yearValue; // variables to extract
    int year;

    getline(inputStream, line);
    //check if the line is not an empty string then extract fields
    if(!line.empty()){
        //find the position of the first period and the last
        size_t breakPoint = line.find('.');
        size_t lastPoint = line.find('.', breakPoint + 1);

        //extract the name
        name = line.substr(0,breakPoint);

        //extract the isbn
        possibleIsbn = line.substr(breakPoint + 1, lastPoint - breakPoint - 1);
        //Check if isbn is valid, else return empty string
        if (IsValidISBN(possibleIsbn)) {
            isbn = possibleIsbn;
        } else {
            isbn = "";
        }

        //extract the year pull the string in yearValue
        yearValue = line.substr(lastPoint + 1);
        //use stoi() to convert the sting to int
        year = stoi(yearValue);
        //set those values to the data members of book
        _name = name;
        _isbn = isbn;
        _year = year;
    }
    //return the input
    return inputStream;
}

/** Implementation of Write to ostream method
 * This output *does not* include an end-line
 * @param output that writes book info, adds a period between each book info field
 * @return none
 */
void Book::Write(ostream& output) const{
    output << _name << "." << _isbn << "." << _year;
}


/**
 * This function checks if the string passed as parameter, isbn, represents a valid
 * isbn. To implement this function you will need to do research on how to validate ISBN.
 * Both ISBN10 and ISBN13 are expected to work with this function.
 * @param isbn the isbn that is going to be checked
 * @return true if the isbn given is a valid isbn, false otherwise
 */
bool IsValidISBN(const string& isbn){
    string temp = isbn;
    int num;
    int sum = 0;
    int checkLastNum;
    char lastDigit;

    //check if the isbn length is 10
    //for isbn 10, sum of numbers multiplied by each of its index is divisible by 11, exclude the last digit as the checker
    if(temp.length() == 10){
        //the value of 10 digits codes that end with X is 10
        if(temp[9] == 'X'){
            lastDigit = 10;
        }
        else{
            //the character '0' ascii code is 48, so subtract each char of the string by 48 to get int value
            lastDigit = temp[9] - 48;
        }
        for (int i = 0; i < 9; i++) {
            if(!isdigit(temp[i]) && lastDigit != 'X') {
                return false;
            }
            else{
                if(isdigit(temp[i])){
                    //the character '0' ascii code is 48, so subtract each char of the string by 48 to get int value
                    num = temp[i] - 48;
                    sum += num * (i+1);
                }
            }
        }
        //check the modulus of the sum
        checkLastNum = sum % 11;
        if(lastDigit == 'X'){
            lastDigit = 10;
        }
        //if the modulus is the same number as the last digit of the isbn, return true
        if(lastDigit == checkLastNum)
            return true;
    }
    else{
        //check for the 13 digit, each should be multiplied by 1 or 3 alternatively
        if (temp.length() == 13){
            //the character '0' ascii code is 48, so subtract each char of the string by 48 to get int value
            lastDigit = temp[12] - 48;
            for (int i = 0; i < 12; i++){
                //the character '0' ascii code is 48, so subtract each char of the string by 48 to get int value
                num = temp[i] - 48;
                //if the index is even, multiply by 1
                if(i % 2 == 0){
                    sum += num * 1;
                }
                    // if the index is odd, multiply by 3
                else{
                    sum += num * 3;
                }
            }
            //check the modulus of the sum, 10 minus the remainder gives the last digit for the 13 digit
            checkLastNum = 10 - (sum % 10);
            //if the modulus minus 10 is the same number as the last digit of the isbn, return true
            if(lastDigit == checkLastNum)
                return true;
        }
    }
    //this function will return false if the above conditions are not met
    return false;

}