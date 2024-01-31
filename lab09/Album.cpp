#include "Album.h"
#include <iostream>
using namespace std;

int Album::totalAlbums = 0;
double Album::totalSales = 0;


void Album::purchaseAlbum()
{
    if (copiesAvailable > 0)
    {
        copiesAvailable--;
        totalAlbums--;
        totalSales += price;
    }
    else
    {
        cout << "Sorry, this album is out of stock." << endl;
    }
}
int Album::getTotalAlbum()
{
    return totalAlbums;
}
double Album::getTotalSales()
{
    return totalSales;
}

string Album::getTitle()
{
    return this->title;
}

string Album::getArtist()
{
    return this->artist;
}

double Album::getPrice()
{
    return this->price;
}
int Album::getCopiesAvailable()
{
    return this->copiesAvailable;
}

