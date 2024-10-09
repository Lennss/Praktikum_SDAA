#include <iostream>
using namespace std;

// Struct untuk menyimpan data barang dalam single linked list
struct Barang {
    int id;
    char nama[50];
    int harga;
    int stok;
    Barang* next;
};

// Fungsi untuk menambahkan barang ke dalam linked list (digunakan untuk Queue)
void tambahBarang(Barang** head, int id, const char* nama, int harga, int stok) {
    Barang* newBarang = new Barang();  // Membuat node baru
    newBarang->id = id;

    // Menyalin nama barang
    int i = 0;
    while (nama[i] != '\0' && i < 49) {
        newBarang->nama[i] = nama[i];
        i++;
    }
    newBarang->nama[i] = '\0';  // Menambahkan karakter null di akhir string

    newBarang->harga = harga;
    newBarang->stok = stok;
    newBarang->next = nullptr;

    // Jika list kosong, jadikan node baru sebagai head
    if (*head == nullptr) {
        *head = newBarang;
    } else {
        // Jika tidak, tambahkan node baru di akhir list
        Barang* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newBarang;
    }
}

// Fungsi untuk menghapus barang dari linked list
void hapusBarang(Barang** head, int id) {
    Barang* temp = *head;
    Barang* prev = nullptr;

    // Jika node yang ingin dihapus adalah head
    if (temp != nullptr && temp->id == id) {
        *head = temp->next;
        delete temp;
        return;
    }

    // Mencari node yang akan dihapus
    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // Jika barang tidak ditemukan
    if (temp == nullptr) {
        cout << "Barang tidak ditemukan." << endl;
        return;
    }

    // Menghapus node
    prev->next = temp->next;
    delete temp;
}

// Fungsi untuk mengupdate barang
void updateBarang(Barang* head, int id, const char* nama, int harga, int stok) {
    Barang* temp = head;
    bool ditemukan = false;

    // Mencari barang yang akan diupdate
    while (temp != nullptr) {
        if (temp->id == id) {
            // Menyalin nama barang baru
            int i = 0;
            while (nama[i] != '\0' && i < 49) {
                temp->nama[i] = nama[i];
                i++;
            }
            temp->nama[i] = '\0';  // Menambahkan karakter null di akhir string

            // Mengupdate harga dan stok
            temp->harga = harga;
            temp->stok = stok;
            ditemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Barang tidak ditemukan." << endl;
    }
}

// Fungsi untuk menampilkan semua barang dalam linked list
void tampilBarang(Barang* head) {
    Barang* temp = head;

    while (temp != nullptr) {
        cout << "ID Barang: " << temp->id << endl;
        cout << "Nama Barang: " << temp->nama << endl;
        cout << "Harga Barang: " << temp->harga << endl;
        cout << "Stok Barang: " << temp->stok << endl;
        cout << "------------------------" << endl;
        temp = temp->next;
    }
}

// Stack Operations (LIFO)
void push(Barang** head, int id, const char* nama, int harga, int stok) {
    Barang* newBarang = new Barang();
    newBarang->id = id;

    // Menyalin nama barang
    int i = 0;
    while (nama[i] != '\0' && i < 49) {
        newBarang->nama[i] = nama[i];
        i++;
    }
    newBarang->nama[i] = '\0';

    newBarang->harga = harga;
    newBarang->stok = stok;
    
    // Push ke stack (di depan)
    newBarang->next = *head;
    *head = newBarang;
}

void pop(Barang** head) {
    if (*head == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }
    
    Barang* temp = *head;
    *head = (*head)->next;
    cout << "Barang dengan ID " << temp->id << " di-pop." << endl;
    delete temp;
}

// Queue Operations (FIFO)
void enqueue(Barang** head, int id, const char* nama, int harga, int stok) {
    Barang* newBarang = new Barang();
    newBarang->id = id;

    // Menyalin nama barang
    int i = 0;
    while (nama[i] != '\0' && i < 49) {
        newBarang->nama[i] = nama[i];
        i++;
    }
    newBarang->nama[i] = '\0';

    newBarang->harga = harga;
    newBarang->stok = stok;
    newBarang->next = nullptr;

    // Enqueue ke queue (di belakang)
    if (*head == nullptr) {
        *head = newBarang;
    } else {
        Barang* temp = *head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newBarang;
    }
}

void dequeue(Barang** head) {
    if (*head == nullptr) {
        cout << "Queue kosong!" << endl;
        return;
    }

    Barang* temp = *head;
    *head = (*head)->next;
    cout << "Barang dengan ID " << temp->id << " di-dequeue." << endl;
    delete temp;
}

// Menu Utama
int main() {
    Barang* head = nullptr;  // Head dari linked list
    int pilihan, id, harga, stok;
    char nama[50];

    do {
        cout << "\nMenu Manajemen Penjualan Barang Mikrokontroler:\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Hapus Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Tampilkan Barang\n";
        cout << "5. Keluar\n";
        cout << "6. Push Barang ke Stack\n";
        cout << "7. Pop Barang dari Stack\n";
        cout << "8. Enqueue Barang ke Queue\n";
        cout << "9. Dequeue Barang dari Queue\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Barang (Angka): ";
                cin >> id;
                cout << "Masukkan Nama Barang: ";
                cin >> ws;
                cin.getline(nama, 50);
                cout << "Masukkan Harga Barang (Angka): ";
                cin >> harga;
                cout << "Masukkan Stok Barang: ";
                cin >> stok;
                tambahBarang(&head, id, nama, harga, stok);
                break;
            case 2:
                cout << "Masukkan ID Barang yang akan dihapus (Angka): ";
                cin >> id;
                hapusBarang(&head, id);
                break;
            case 3:
                cout << "Masukkan ID Barang yang akan diupdate: ";
                cin >> id;
                cout << "Masukkan Nama Barang baru: ";
                cin >> ws;
                cin.getline(nama, 50);
                cout << "Masukkan Harga Barang baru: ";
                cin >> harga;
                cout << "Masukkan Stok Barang baru: ";
                cin >> stok;
                updateBarang(head, id, nama, harga, stok);
                break;
            case 4:
                system("cls");  // Hanya untuk Windows, bisa dihapus atau ganti "clear" untuk Linux/Mac
                tampilBarang(head);
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            case 6:
                cout << "Masukkan ID Barang: ";
                cin >> id;
                cout << "Masukkan Nama Barang: ";
                cin >> ws;
                cin.getline(nama, 50);
                cout << "Masukkan Harga Barang: ";
                cin >> harga;
                cout << "Masukkan Stok Barang: ";
                cin >> stok;
                push(&head, id, nama, harga, stok);
                break;
            case 7:
                pop(&head);
                break;
            case 8:
                cout << "Masukkan ID Barang: ";
                cin >> id;
                cout << "Masukkan Nama Barang: ";
                cin >> ws;
                cin.getline(nama, 50);
                cout << "Masukkan Harga Barang: ";
                cin >> harga;
                cout << "Masukkan Stok Barang: ";
                cin >> stok;
                enqueue(&head, id, nama, harga, stok);
                break;
            case 9:
                dequeue(&head);
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}
