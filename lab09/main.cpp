#include <iostream>
#include <vector>
#include "Album.h"
// Other code here


int main()
{
    vector<Album> albums;
    albums.emplace_back("Abbey Road", "The Beatles", 19.99, 5);
    albums.emplace_back("The Dark Side of the Moon", "Pink Floyd", 21.99, 3);
    albums.emplace_back("Hotel California", "Eagles", 15.99, 4);
    albums.emplace_back("Back in Black", "AC/DC", 20.99, 2);
    albums.emplace_back("Rumours", "Fleetwood Mac", 16.99, 3);
    albums.emplace_back("Thriller", "Michael Jackson", 18.99, 5);
    albums.emplace_back("The Wall", "Pink Floyd", 22.99, 2);
    albums.emplace_back("Led Zeppelin IV", "Led Zeppelin", 17.99, 3);
    
    while (true) {
        cout << "Welcome to the Music Store!" << endl;
        cout << "Please select an option:" << endl;
        cout << "1. Album list" << endl;
        cout << "2. Purchase Album" << endl;
        cout << "3. View total albums in stock" << endl;
        cout << "4. View total sales" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            cout << "Please select an album to purchase:" << endl;
            for (int i = 0; i < albums.size(); i++) {
                cout << i + 1 << ". " << albums[i].getTitle() << " by " << albums[i].getArtist() << " Copies available: " << albums[i].getCopiesAvailable() << endl;
            }
        } else if (choice == 2) {
            cout << "Please select an album to purchase:" << endl;
            int albumChoice;
            cin >> albumChoice;
            albums[albumChoice - 1].purchaseAlbum();
        } else if (choice == 3) {
            std::cout << "Total albums in stock: " << Album::getTotalAlbum() << std::endl;
        } else if (choice == 4) {
            std::cout << "Total sales: " << Album::getTotalSales() << std::endl;
        } else if (choice == 5) {
            cout << "Thank You. Goodbye!" << endl;
            break;
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    
    }
}