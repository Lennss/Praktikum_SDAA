#include <iostream>
using namespace std;

// Fungsi untuk menamplkan piringan
void printTowers(int asal[], int tujuan[], int sementara[], int size) {
    cout << "Tower A: ";
    for (int i = 0; i < size; ++i) {
        if (asal[i] > 0) cout << asal[i] << " ";
    }
    cout << endl;

    cout << "Tower B: ";
    for (int i = 0; i < size; ++i) {
        if (tujuan[i] > 0) cout << tujuan[i] << " ";
    }
    cout << endl;

    cout << "Tower C: ";
    for (int i = 0; i < size; ++i) {
        if (sementara[i] > 0) cout << sementara[i] << " ";
    }
    cout << endl;

    cout << "=========" << endl;
}

// Fungsi rekursif
void pindahkanPiringan(int jumlahPiringan, int asal[], int tujuan[], int sementara[], int size, char menaraAsal, char menaraTujuan, char menaraSementara) {
    if (jumlahPiringan == 1) {
        for (int i = 0; i < size; ++i) {
            if (asal[i] > 0) {
                tujuan[i] = asal[i];
                asal[i] = 0;
                break;
            }
        }
        cout << "Pindahkan piringan dari " << menaraAsal << " ke " << menaraTujuan << endl;
        printTowers(asal, tujuan, sementara, size);
        return;
    }
    
    pindahkanPiringan(jumlahPiringan - 1, asal, sementara, tujuan, size, menaraAsal, menaraSementara, menaraTujuan);
    
    for (int i = 0; i < size; ++i) {
        if (asal[i] > 0) {
            tujuan[i] = asal[i];
            asal[i] = 0;
            break;
        }
    }
    cout << "Pindahkan piringan dari " << menaraAsal << " ke " << menaraTujuan << endl;
    printTowers(asal, tujuan, sementara, size);
    
    pindahkanPiringan(jumlahPiringan - 1, sementara, tujuan, asal, size, menaraSementara, menaraTujuan, menaraAsal);
}

int main() {
    const int jumlahPiringan = 3;
    int menaraAsal[jumlahPiringan] = {3, 2, 1}; 
    int menaraTujuan[jumlahPiringan] = {0}; 
    int menaraSementara[jumlahPiringan] = {0}; 
    
    cout << "Solusi Menara Hanoi dengan " << jumlahPiringan << " piringan:\n";
    printTowers(menaraAsal, menaraTujuan, menaraSementara, jumlahPiringan);
    pindahkanPiringan(jumlahPiringan, menaraAsal, menaraTujuan, menaraSementara, jumlahPiringan, 'A', 'B', 'C');
    
    return 0;
}
