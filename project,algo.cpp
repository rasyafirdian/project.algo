#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

// ======================================================
// CLEAR SCREEN
// ======================================================
void cls() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ======================================================
// SINGLE LINKED LIST - DATA MOBIL
// ======================================================
struct Mobil {

    int id;
    string nama;
    string plat;
    int tahun;
    double harga;
    string status;
    int jumlahRental;

    Mobil* next;
};

Mobil* headMobil = NULL;

// ======================================================
// DOUBLE LINKED LIST - HISTORI
// ======================================================
struct Histori {

    string customer;
    string mobil;
    int lama;
    double total;

    Histori* prev;
    Histori* next;
};

Histori* headHistori = NULL;
Histori* tailHistori = NULL;
kf