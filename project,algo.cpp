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
iyaa
}