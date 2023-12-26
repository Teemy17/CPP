#include <iostream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class Book
{
private:
    string title;
    string author;
    int quantity;

public:
    Book(string title, string author, int quantity)
    {
        this->title = title;
        this->author = author;
        this->quantity = quantity;
    }

    string get_title()
    {
        return title;
    }

    string get_author()
    {
        return author;
    }

    int get_quantity()
    {
        return quantity;
    }

    void set_quantity(int quantity)
    {
        this->quantity = quantity;
    }
};

class Inventory
{
private:
    vector<Book> books;

public:
    void add_book(Book book)
    {
        books.push_back(book);
    }

    void remove_book(string title)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].get_title() == title)
            {
                books.erase(books.begin() + i);
                break;
            }
        }
    }

    void find_book(string title)
    {
        for (Book book : books)
        {
            if (book.get_title() == title)
            {
                cout << book.get_title() << "," << book.get_author() << "," << book.get_quantity() << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }

    void print()
    {
        for (Book book : books)
        {
            cout << "Title: " << book.get_title() << ","
                 << " Author: " << book.get_author() << ","
                 << " Quantity: " << book.get_quantity() << endl;
        }
    }
};

int main()
{
    Inventory inventory;
    while (true)
    {
        cout << "Enter command (a: add, r: remove, s: search, l: list, q: quit ): ";
        string choice;
        cin >> choice;
        if (choice == "a")
        {
            cout << "Enter title: ";
            string title;
            cin >> title;
            cout << "Enter author: ";
            string author;
            cin >> author;
            cout << "Enter quantity: ";
            int quantity;
            while (!(cin >> quantity) || quantity < 0)
            {
                cout << "Invalid input. Please enter a valid quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            Book book(title, author, quantity);
            inventory.add_book(book);
        }
        else if (choice == "r")
        {
            cout << "Enter title: ";
            string title;
            cin >> title;
            inventory.remove_book(title);
        }
        else if (choice == "s")
        {
            cout << "Enter title: ";
            string title;
            cin >> title;
            inventory.find_book(title);
        }
        else if (choice == "l")
        {
            inventory.print();
        }
        else if (choice == "q")
        {
            break;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
}
