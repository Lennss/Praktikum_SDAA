#include <iostream>
using namespace std;

// Struct untuk menyimpan data barang
struct Barang {
    int id;
    char nama[50];
    int harga;
    int stok;
};

// Fungsi untuk menambahkan barang
void tambahBarang(Barang* daftarBarang, int* jumlahBarang, int id, const char* nama, int harga, int stok) {
    daftarBarang[*jumlahBarang].id = id;
    int i = 0;
    while (nama[i] != '\0' && i < 49) {
        daftarBarang[*jumlahBarang].nama[i] = nama[i];
        i++;
    }
    daftarBarang[*jumlahBarang].nama[i] = '\0';
    daftarBarang[*jumlahBarang].harga = harga;
    daftarBarang[*jumlahBarang].stok = stok;
    (*jumlahBarang)++;
}

// Fungsi untuk menghapus barang
void hapusBarang(Barang* daftarBarang, int* jumlahBarang, int id) {
    bool ditemukan = false;
    for (int i = 0; i < *jumlahBarang; i++) {
        if (daftarBarang[i].id == id) {
            ditemukan = true;
            for (int j = i; j < *jumlahBarang - 1; j++) {
                daftarBarang[j] = daftarBarang[j + 1];
            }
            (*jumlahBarang)--;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Barang tidak ditemukan." << endl;
    }
}

// Fungsi untuk Mengubah barang
void updateBarang(Barang* daftarBarang, int jumlahBarang, int id, const char* nama, int harga, int stok) {
    bool ditemukan = false;
    for (int i = 0; i < jumlahBarang; i++) {
        if (daftarBarang[i].id == id) {
            int j = 0;
            while (nama[j] != '\0' && j < 49) {
                daftarBarang[i].nama[j] = nama[j];
                j++;
            }
            daftarBarang[i].nama[j] = '\0';
            daftarBarang[i].harga = harga;
            daftarBarang[i].stok = stok;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Barang tidak ditemukan." << endl;
    }
}

// Fungsi untuk menampilkan data barang yang tersimpan
void tampilBarang(Barang* daftarBarang, int jumlahBarang) {
    for (int i = 0; i < jumlahBarang; i++) {
        cout << "ID Barang: " << daftarBarang[i].id << endl;
        cout << "Nama Barang: " << daftarBarang[i].nama << endl;
        cout << "Harga Barang: " << daftarBarang[i].harga << endl;
        cout << "Stok Barang: " << daftarBarang[i].stok << endl;
        cout << "------------------------" << endl;
    }
}

// Menu Utama
int main() {
    const int maxBarang = 100;
    Barang daftarBarang[maxBarang];
    int jumlahBarang = 0;

    int pilihan, id, harga, stok;
    char nama[50];
    
    do {
        cout << "\nMenu Manajemen Penjualan Barang Mikrokontroler:\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Hapus Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Tampilkan Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
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
                tambahBarang(daftarBarang, &jumlahBarang, id, nama, harga, stok);
                break;
            case 2:
                cout << "Masukkan ID Barang yang akan dihapus: ";
                cin >> id;
                hapusBarang(daftarBarang, &jumlahBarang, id);
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
                updateBarang(daftarBarang, jumlahBarang, id, nama, harga, stok);
                break;
            case 4:
                system("cls");
                tampilBarang(daftarBarang, jumlahBarang);
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
