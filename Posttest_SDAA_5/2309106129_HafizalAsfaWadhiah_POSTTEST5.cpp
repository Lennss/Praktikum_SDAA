#include <iostream>
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

// Fungsi untuk membagi linked list menjadi dua bagian
void splitList(Barang *source, Barang **frontRef, Barang **backRef)
{
    Barang *fast;
    Barang *slow;
    slow = source;
    fast = source->next;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;
}

// Fungsi untuk menggabungkan dua linked list yang sudah di-sort
Barang *mergeSorted(Barang *a, Barang *b)
{
    Barang *result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->harga <= b->harga)
    {
        result = a;
        result->next = mergeSorted(a->next, b);
    }
    else
    {
        result = b;
        result->next = mergeSorted(a, b->next);
    }
    return result;
}

// Merge Sort secara ascending
void mergeSort(Barang **headRef)
{
    Barang *head = *headRef;
    Barang *a;
    Barang *b;

    if ((head == nullptr) || (head->next == nullptr))
    {
        return;
    }

    splitList(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);

    *headRef = mergeSorted(a, b);
}

// Fungsi untuk mencari tail dari linked list
Barang *getTail(Barang *cur)
{
    while (cur != nullptr && cur->next != nullptr)
        cur = cur->next;
    return cur;
}

// Fungsi partition untuk Quick Sort
Barang *partition(Barang *head, Barang *end, Barang **newHead, Barang **newEnd)
{
    Barang *pivot = end;
    Barang *prev = nullptr, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (cur->harga > pivot->harga)
        {
            if ((*newHead) == nullptr)
                (*newHead) = cur;

            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;

            Barang *temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newHead) == nullptr)
        (*newHead) = pivot;

    (*newEnd) = tail;

    return pivot;
}

// Quick Sort rekursif
Barang *quickSortRecur(Barang *head, Barang *end)
{
    if (!head || head == end)
        return head;

    Barang *newHead = nullptr, *newEnd = nullptr;
    Barang *pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        Barang *temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);

        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// Quick Sort secara descending
void quickSort(Barang **headRef)
{
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
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
        cout << "5. Keluar\n";
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
        case 3:
            system("cls");
            mergeSort(&head);
            cout << "Barang berhasil di-sort secara ascending (harga) menggunakan Merge Sort." << endl;
            break;
        case 4:
            system("cls");
            quickSort(&head);
            cout << "Barang berhasil di-sort secara descending (harga) menggunakan Quick Sort." << endl;
            break;
        case 5:
            cout << "Keluar dari program." << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}
