#ifndef LIBRARY_MANAGEMENT_SYSTEM_H_INCLUDED
#define LIBRARY_MANAGEMENT_SYSTEM_H_INCLUDED

// Functions' Prototypes
void Library_Initialization();  // initialize the library wth some books with their information
void Menu();            //
void Add_Book();        // add a book that is not existing before at the library
int Search_For_Book(const char* Book_Title);    // search about a specific book using its title
void Print_Book();      // print the whole details of a specific book
void Print_Library();   // Print all books' name of the library
void Borrow_Book();     // decrease the number of copies of a specific book
void Delete_Book();     // delete all information about a specific book
void Buy_Book();        // add new copies of an existed book
int Exit();             // Finish the program
void Swap(Book* book1 , Book* book2);   // swap to element in the array that contains books to make the empty element at the end of this array

#endif // LIBRARY_MANAGEMENT_SYSTEM_H_INCLUDED
