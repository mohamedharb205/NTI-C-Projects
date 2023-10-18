#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure
typedef struct Library
{
    char Book_Title[50];
    char Author_Name[40];
    int Publication_Year;
    int Copies_No;
    float price;
    char Status[20];
    char Shelf_No[20];
}Book;


// Constants
#define Max_Copies    100
#define ARM_Copies    5
#define AVR_Copies    7


// Global Variables
Book Books[Max_Copies];
unsigned int Book_Index = 0;
unsigned int All_Copies = ARM_Copies + AVR_Copies;



void Library_Initialization()
{
    strcpy(Books[Book_Index].Book_Title , "ARM");
    strcpy(Books[Book_Index].Author_Name , "arm");
    Books[Book_Index].Copies_No = ARM_Copies;
    Books[Book_Index].Publication_Year = 2023;
    Books[Book_Index].price = 50;
    strcpy(Books[Book_Index].Status , "Available");
    strcpy(Books[Book_Index].Shelf_No , "A1");

    Book_Index++;
    strcpy(Books[Book_Index].Book_Title , "AVR");
    strcpy(Books[Book_Index].Author_Name , "avr");
    Books[Book_Index].Copies_No = AVR_Copies;
    Books[Book_Index].Publication_Year = 2010;
    Books[Book_Index].price = 30;
    strcpy(Books[Book_Index].Status , "Available");
    strcpy(Books[Book_Index].Status , "A6");
    Book_Index++;

}


void Menu()
{
    printf("\n\n Welcome to menu! \n");
    printf("1. Add_Book \n");
    printf("2. Print_Book \n");
    printf("3. Print_Library \n");
    printf("4. Borrow_Book \n");
    printf("5. Delete_Book \n");
    printf("6. Buy_Book \n");
    printf("7. Exit \n");

    unsigned int choice = 0;
    printf("\n Enter Choice: \t");
    scanf("%d", &choice);   // error    scanf("%d \n", &choice);

    switch(choice)
    {
        case 1  :    Add_Book();        break;
        case 2  :    Print_Book();      break;
        case 3  :    Print_Library();   break;
        case 4  :    Borrow_Book();     break;
        case 5  :    Delete_Book();     break;
        case 6  :    Buy_Book();        break;
        case 7  :    Exit();            break;
        default :    Menu();            break;
    }
}


void Add_Book()
{
    char title[50];
    printf("Please Enter the Book Title: ");
    scanf(" %[^\n]s", title);   // " %[^\n]s" >>> allow me to enter a string consists of more than one word

    unsigned int try_again;
    unsigned int index = Search_For_Book(title);
    if(index != -1)
    {
        printf("This book is already existing! \n");
        printf("The current No of Copies = %d \n", Books[index].Copies_No);
        printf("The current No of All Copies = %d \n", All_Copies);
    }
    else
    {
        do
        {
            //printf("The current No of Copies = %d \n", Books[Book_Index].Copies_No);
            printf("The current No of All Copies = %d \n", All_Copies);

            unsigned int no_of_copies;
            printf("\n To add this book please Enter the No of Copies \n");
            scanf("%d", &no_of_copies);

            if(All_Copies >= Max_Copies)
            {
                printf("It is not allowed to add a new book, you already reached the max limit! \n");
                break;
            }
            else if(All_Copies < Max_Copies)
            {
                if((All_Copies + no_of_copies) <= Max_Copies)
                {
                    Books[Book_Index].Copies_No += no_of_copies;
                    strcpy(Books[Book_Index].Book_Title, title);

                    printf("Please Enter the Author Name \n");
                    scanf(" %[^\n]s", &Books[Book_Index].Author_Name);

                    printf("Please Enter the Publication Year \n");
                    scanf("%d", &Books[Book_Index].Publication_Year);

                    printf("Please Enter the price \n");
                    scanf("%f", &Books[Book_Index].price);

                    strcpy(Books[Book_Index].Status , "Available");

                    printf("Please Enter the Shelf Number \n");
                    scanf(" %[^\n]s", &Books[Book_Index].Shelf_No);

                    All_Copies += no_of_copies;

                    printf("The new Copies added correctly. \n");
                    printf("The current No of Copies of this Book = %d \n", Books[Book_Index].Copies_No);
                    printf("The current No of All Copies = %d \n", All_Copies);

                    Book_Index++;
                    break;
                }
                else
                {
                    printf("There is not an enough space for this number of copies!!! \n");
                    printf(" 0 : Try again \n");
                    printf(" 1 : Main Menu \n");
                    scanf("%d", &try_again);
                }
            }

        }while(try_again == 0);
    }

    Menu();
}


int Search_For_Book(const char* Book_Title)
{
    for(int i=0; i<Max_Copies; i++)
    {
        if(strcmp(Book_Title , Books[i].Book_Title) == 0)
        {
            if(Books[i].Copies_No > 0)
            {
                strcpy(Books[i].Status , "Available");
                printf("Book is Existing and Available \n");
                return i;
            }
            else if(Books[i].Copies_No == 0)
            {
                strcpy(Books[i].Status , "Unavailable");
                printf("Book is Existing but is not Available now! \n");
                return i;
            }
        }
    }
    printf("Book is not Existing !!! \n");
    return -1;
}


void Print_Book()
{
    char title[50];
    printf("Please Enter the Book Title \n");
    scanf(" %[^\n]s", &title);
    int index = Search_For_Book(title);
    if (index != -1)
    {
        printf("Book Title: %s\n", Books[index].Book_Title);
        printf("Author: %s\n", Books[index].Author_Name);
        printf("Publication Year: %d\n", Books[index].Publication_Year);
        printf("Number of Copies: %d\n", Books[index].Copies_No);
        printf("Price: $%.2f\n", Books[index].price);
        printf("Status: %s\n", Books[index].Status);
        printf("Shelf Number: %s\n", Books[index].Shelf_No);

        printf("The current No of All Copies: %d \n", All_Copies);

        printf(" Index: %d \n", index);
        //printf("%s \n", Books[index].Shelf_No);
    }
    Menu();
}


void Print_Library()
{
    if(Book_Index == 0)
    {
        printf("The Library is empty !!! \n");
    }
    else if(Book_Index > 0)
    {
        for (int i = 0; i <= Book_Index; i++)
        {
            if(strcmp(Books[i].Book_Title , "NULL") != 0)
            {
                printf("%s \n", Books[i].Book_Title);
            }
            else
            {
                break;
            }
        }
    }

    Menu();
}


void Buy_Book()
{
    char title[50];
    printf("Please Enter the Book Title: ");
    scanf(" %[^\n]s", title);
    unsigned int index = Search_For_Book(title);
    if(index != -1)
    {
        unsigned int try_again;
        do
        {
            printf("The current No of Copies for this Book = %d \n", Books[index].Copies_No);
            printf("The current No of All Copies = %d \n", All_Copies);

            unsigned int no_of_copies;
            printf("Please Enter the No of Copies \n");
            scanf("%d", &no_of_copies);

            if(All_Copies >= Max_Copies)
            {
                printf("It is not allowed to add a new book, you already reached the max limit! \n");
                break;
            }
            else if(All_Copies < Max_Copies)
            {
                if((All_Copies + no_of_copies) <= Max_Copies)
                {
                    Books[index].Copies_No += no_of_copies;
                    All_Copies += no_of_copies;
                    printf("The current No of Copies for this Book = %d \n", Books[index].Copies_No);
                    printf("The current No of All Copies = %d \n", All_Copies);
                    printf("The new Copies added correctly. \n");
                    break;
                }
                else
                {
                    printf("There is not an enough space for this number of copies!!! \n");
                    printf(" 0 : Try again \n");
                    printf(" 1 : Main Menu \n");
                    scanf("%d", &try_again);
                }
            }
        }while(try_again == 0);

        Menu();
    }
}


void Borrow_Book(int no_of_copies)
{
    char title[50];
    printf("Please Enter the Book Title: ");
    scanf(" %[^\n]s", title);

    int index = Search_For_Book(title);
    if (index != -1)
        {
            printf("The current No of Copies for this Book = %d \n", Books[index].Copies_No);
            int no_of_copies;
            printf("Please Enter the No of Copies \n");
            scanf("%d", &no_of_copies);

            if((Books[index].Copies_No - no_of_copies) >= 0)
            {
                Books[index].Copies_No -= no_of_copies;
                All_Copies -= no_of_copies;
                printf("The current No of Copies for this Book = %d \n", Books[index].Copies_No);
            }
            else
            printf("There are not Enough Copies of This Book!!!");
        }

    Menu();
}


void Delete_Book()
{
    char title[50];
    printf("Please Enter the Book Title: ");
    scanf(" %[^\n]s", title);

    int index = Search_For_Book(title);
    if (index != -1)
        {
            All_Copies -= Books[index].Copies_No;

            strcpy(Books[index].Book_Title , "NULL");
            strcpy(Books[index].Author_Name , "NULL");
            Books[index].Publication_Year = 0;
            Books[index].Copies_No = 0;
            Books[index].price = 0;
            strcpy(Books[index].Status , "NULL");
            strcpy(Books[index].Shelf_No , "NULL");

            //memset(&Books[index], 0, sizeof(Book));
            printf("The Book is already deleted !!! \n");
            printf("The current No of All Copies = %d \n", All_Copies);

            printf("previous index = %d\n", index);
           /* do
            {
                Swap(&Books[index+1] , &Books[index]);
                index ++;
            }while(strcmp(Books[index+1].Book_Title , "NULL") != 0 && index < 100);
            */
            for( ; index < Max_Copies; index++)
            {
                if(strcmp(Books[index+1].Book_Title , "NULL") != 0)
                {
                    Swap(&Books[index+1] , &Books[index]);
                    continue;
                }
                else
                {
                    break;
                }
            }
            printf("current index = %d\n", index);
            Book_Index--;
        }

    else
        {
            printf("The Book not found or the Title is wrong !!! \n");
        }

    Menu();
}


int Exit()
{
    return 0;
}


void Swap(Book* book1 , Book* book2)
{
    Book temp = *book1;
    *book1 = *book2;
    *book2 = temp;
}






