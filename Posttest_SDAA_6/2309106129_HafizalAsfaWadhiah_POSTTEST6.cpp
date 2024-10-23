#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

// Struct untuk menyimpan data barang dalam single linked list
struct Barang
{
    int id;
    char nama[50];
    int harga;
    int stok;
    Barang *next;
};

// Fungsi untuk menambahkan barang ke dalam linked list
void tambahBarang(Barang **head, int id, const char *nama, int harga, int stok)
{
    Barang *newBarang = new Barang(); // Membuat node baru
    newBarang->id = id;

    // Menyalin nama barang
    int i = 0;
    while (nama[i] != '\0' && i < 49)
    {
        newBarang->nama[i] = nama[i];
        i++;
    }
    newBarang->nama[i] = '\0'; // Menambahkan karakter null di akhir string

    newBarang->harga = harga;
    newBarang->stok = stok;
    newBarang->next = nullptr;

    // Jika list kosong, jadikan node baru sebagai head
    if (*head == nullptr)
    {
        *head = newBarang;
    }
    else
    {
        // Jika tidak, tambahkan node baru di akhir list
        Barang *temp = *head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newBarang;
    }
}

// Fungsi untuk menampilkan semua barang dalam linked list
void tampilBarang(Barang *head)
{
    Barang *temp = head;

    while (temp != nullptr)
    {
        cout << "ID Barang: " << temp->id << endl;
        cout << "Nama Barang: " << temp->nama << endl;
        cout << "Harga Barang: " << temp->harga << endl;
        cout << "Stok Barang: " << temp->stok << endl;
        cout << "------------------------" << endl;
        temp = temp->next;
    }
}

// Fungsi untuk menghitung jumlah node dalam linked list
int getLength(Barang *head)
{
    int n = 0;
    while (head != nullptr)
    {
        n++;
        head = head->next;
    }
    return n;
}

// Fungsi Fibonacci Search pada harga
int fibonacciSearch(Barang *head, int hargaDicari)
{
    int n = getLength(head);

    // Initialize fibonacci numbers
    int fibMMm2 = 0; // (m-2)'th Fibonacci No.
    int fibMMm1 = 1; // (m-1)'th Fibonacci No.
    int fibM = fibMMm2 + fibMMm1; // m'th Fibonacci

    // fibM is the smallest Fibonacci number greater or equal to n
    while (fibM < n)
    {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    Barang *temp = head;
    for (int i = 0; i < n; i++)
    {
        while (fibM > 1)
        {
            int i = min(offset + fibMMm2, n - 1);
            Barang *curr = head;
            for (int j = 0; j < i; j++) curr = curr->next;

            if (curr->harga == hargaDicari)
                return i;

            else if (curr->harga < hargaDicari)
            {
                fibM = fibMMm1;
                fibMMm1 = fibMMm2;
                fibMMm2 = fibM - fibMMm1;
                offset = i;
            }
            else
            {
                fibM = fibMMm2;
                fibMMm1 -= fibMMm2;
                fibMMm2 = fibM - fibMMm1;
            }
        }
    }

    if (fibMMm1 && temp->harga == hargaDicari)
        return n - 1;

    return -1;
}

// Fungsi Jump Search pada harga
int jumpSearch(Barang *head, int hargaDicari)
{
    int n = getLength(head);
    int step = sqrt(n);
    int prev = 0;

    Barang *temp = head;
    while (temp != nullptr && temp->harga < hargaDicari)
    {
        prev += step;
        for (int i = 0; i < step && temp != nullptr; i++)
        {
            temp = temp->next;
        }
    }

    Barang *start = head;
    for (int i = 0; i < prev && start != nullptr; i++)
    {
        start = start->next;
    }

    while (start != nullptr && start->harga < hargaDicari)
    {
        start = start->next;
        prev++;
    }

    if (start != nullptr && start->harga == hargaDicari)
        return prev;

    return -1;
}

// Fungsi Boyer-Moore Search pada nama barang
int boyerMooreSearch(const char *text, const char *pattern)
{
    int m = strlen(pattern);
    int n = strlen(text);

    int badChar[256];

    for (int i = 0; i < 256; i++)
        badChar[i] = -1;

    for (int i = 0; i < m; i++)
        badChar[(int)pattern[i]] = i;

    int shift = 0;
    while (shift <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0)
        {
            return shift; // Match found
            shift += (shift + m < n) ? m - badChar[text[shift + m]] : 1;
        }
        else
        {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }

    return -1; // No match
}

// Menu Utama
int main()
{
    Barang *head = nullptr; // Head dari linked list
    int pilihan, id, harga, stok;
    char nama[50];

    do
    {
        cout << "\nMenu Manajemen Penjualan Barang Mikrokontroler:\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Sort Barang Ascending (Merge Sort)\n";
        cout << "4. Sort Barang Descending (Quick Sort)\n";
        cout << "5. Cari Barang Berdasarkan Harga (Fibonacci Search)\n";
        cout << "6. Cari Barang Berdasarkan Harga (Jump Search)\n";
        cout << "7. Cari Barang Berdasarkan Nama (Boyer-Moore Search)\n";
        cout << "8. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cout << "Masukkan ID Barang: ";
            cin >> id;
            cout << "Masukkan Nama Barang: ";
            cin >> ws;
            cin.getline(nama, 50);
            cout << "Masukkan Harga Barang: ";
            cin >> harga;
            cout << "Masukkan Stok Barang: ";
            cin >> stok;
            tambahBarang(&head, id, nama, harga, stok);
            break;
        case 2:
            system("cls");
            tampilBarang(head);
            break;
        case 5:
            cout << "Masukkan harga yang dicari (Fibonacci Search): ";
            cin >> harga;
            if (fibonacciSearch(head, harga) != -1)
                cout << "Harga ditemukan." << endl;
            else
                cout << "Harga tidak ditemukan." << endl;
            break;
        case 6:
            cout << "Masukkan harga yang dicari (Jump Search): ";
            cin >> harga;
            if (jumpSearch(head, harga) != -1)
                cout << "Harga ditemukan." << endl;
            else
                cout << "Harga tidak ditemukan." << endl;
            break;
        case 7:
            cout << "Masukkan nama barang yang dicari (Boyer-Moore Search): ";
            cin >> ws;
            cin.getline(nama, 50);
            if (boyerMooreSearch(head->nama, nama) != -1)
                cout << "Nama ditemukan." << endl;
            else
                cout << "Nama tidak ditemukan." << endl;
            break;
        case 8:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 8);

    return 0;
}
