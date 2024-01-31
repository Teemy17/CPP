#ifndef ALBUM_H
#define ALBUM_H
#include <string>
using namespace std;
class Album
{
private:
    string title;
    string artist;
    double price;
    int copies;
    int copiesAvailable;
    static int totalAlbums;
    static double totalSales;

public:

    Album(const std::string& title, const std::string& artist, double price, int copies) 
    : title(title), artist(artist), price(price), copiesAvailable(copies) {totalAlbums += copies;};
    void purchaseAlbum();
    static int getTotalAlbum();
    static double getTotalSales();
    string getTitle();
    string getArtist();
    double getPrice();
    int getCopiesAvailable();

};
#endif