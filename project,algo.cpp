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
// ======================================================
// STACK - UNDO
// ======================================================
struct StackNode {

    string aktivitas;
    StackNode* next;
};

StackNode* topStack = NULL;

// ======================================================
// QUEUE - ANTREAN
// ======================================================
struct QueueNode {

    string nama;
    QueueNode* next;
};

QueueNode* frontQueue = NULL;
QueueNode* rearQueue = NULL;

// ======================================================
// BST - SEARCHING
// ======================================================
struct BSTNode {

    int id;
    string nama;

    BSTNode* left;
    BSTNode* right;
};

BSTNode* rootBST = NULL;

// ======================================================
// VALIDASI INPUT
// ======================================================
int inputAngka() {

    int angka;

    while (!(cin >> angka)) {

        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Input harus angka : ";
    }

    return angka;
}

// ======================================================
// LOGIN ADMIN
// ======================================================
bool login() {

    string user;
    string pass;

    cout << "Username : ";
    cin >> user;

    cout << "Password : ";
    cin >> pass;

    return (user == "admin" && pass == "123");
}

// ======================================================
// STACK PUSH
// ======================================================
void pushStack(string aktivitas) {

    StackNode* baru = new StackNode;

    baru->aktivitas = aktivitas;
    baru->next = topStack;

    topStack = baru;
}

// ======================================================
// STACK POP
// ======================================================
void popStack() {

    if (topStack == NULL) {

        cout << "Undo kosong\n";
        return;
    }

    cout << "Undo : "
         << topStack->aktivitas << endl;

    StackNode* hapus = topStack;

    topStack = topStack->next;

    delete hapus;
}

// ======================================================
// QUEUE ENQUEUE
// ======================================================
void enqueue(string nama) {

    QueueNode* baru = new QueueNode;

    baru->nama = nama;
    baru->next = NULL;

    if (frontQueue == NULL) {

        frontQueue = rearQueue = baru;

    } else {

        rearQueue->next = baru;
        rearQueue = baru;
    }
}

// ======================================================
// TAMPIL QUEUE
// ======================================================
void tampilQueue() {

    QueueNode* temp = frontQueue;

    if (temp == NULL) {

        cout << "Queue kosong\n";
        return;
    }

    while (temp != NULL) {

        cout << "- "
             << temp->nama << endl;

        temp = temp->next;
    }
}

// ======================================================
// INSERT BST
// ======================================================
BSTNode* insertBST(BSTNode* root,
                   int id,
                   string nama) {

    if (root == NULL) {

        BSTNode* baru = new BSTNode;

        baru->id = id;
        baru->nama = nama;

        baru->left = NULL;
        baru->right = NULL;

        return baru;
    }

    if (id < root->id)
        root->left =
            insertBST(root->left,
                      id,
                      nama);

    else
        root->right =
            insertBST(root->right,
                      id,
                      nama);

    return root;
}

// ======================================================
// SEARCH BST
// ======================================================
BSTNode* cariBST(BSTNode* root,
                 int id) {

    if (root == NULL ||
        root->id == id)
        return root;

    if (id < root->id)
        return cariBST(root->left, id);

    return cariBST(root->right, id);
}

// ======================================================
// SAVE DATA
// ======================================================
void saveData() {

    ofstream file("mobil.txt");

    Mobil* temp = headMobil;

    while (temp != NULL) {

        file << temp->id << "|";
        file << temp->nama << "|";
        file << temp->plat << "|";
        file << temp->tahun << "|";
        file << temp->harga << "|";
        file << temp->status << "|";
        file << temp->jumlahRental << endl;

        temp = temp->next;
    }

    file.close();
}

// ======================================================
// LOAD DATA
// ======================================================
void loadData() {

    ifstream file("mobil.txt");

    if (!file.is_open())
        return;

    while (!file.eof()) {

        Mobil* baru = new Mobil;

        file >> baru->id;
        file.ignore();

        getline(file, baru->nama, '|');
        getline(file, baru->plat, '|');

        file >> baru->tahun;
        file.ignore();

        file >> baru->harga;
        file.ignore();

        getline(file, baru->status, '|');

        file >> baru->jumlahRental;

        baru->next = NULL;

        if (file.fail()) {

            delete baru;
            break;
        }

        if (headMobil == NULL) {

            headMobil = baru;

        } else {

            Mobil* temp = headMobil;

            while (temp->next != NULL)
                temp = temp->next;

            temp->next = baru;
        }

        rootBST =
            insertBST(rootBST,
                      baru->id,
                      baru->nama);
    }

    file.close();
}

// ======================================================
// TAMBAH MOBIL
// ======================================================
void tambahMobil() {

    Mobil* baru = new Mobil;

    cout << "ID Mobil : ";
    baru->id = inputAngka();
    cin.ignore();

    cout << "Nama Mobil : ";
    getline(cin, baru->nama);

    cout << "Plat : ";
    getline(cin, baru->plat);

    cout << "Tahun : ";
    baru->tahun = inputAngka();

    cout << "Harga : ";
    cin >> baru->harga;

    baru->status = "Tersedia";
    baru->jumlahRental = 0;
    baru->next = NULL;

    if (headMobil == NULL) {

        headMobil = baru;

    } else {

        Mobil* temp = headMobil;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = baru;
    }

    rootBST =
        insertBST(rootBST,
                  baru->id,
                  baru->nama);

    pushStack("Tambah Mobil");

    saveData();

    cout << "Mobil berhasil ditambahkan\n";
}