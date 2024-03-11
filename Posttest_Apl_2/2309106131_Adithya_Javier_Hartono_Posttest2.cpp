#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int max_hero = 100;

//karena saya menggunakan array kosong jadi saya kasih list hero
// Clash:
// -Kaizer
// -Charlotte
// -biron

// Mid:
// -Angela
// -Milady
// -Mozi
// -Lady Zhen

// Farm:
// -Hou yi
// -Luban no.7
// -Fang
// -Huang Zhong

// Roaming (Tank/Support):
// -Donghuang
// -Dolia
// -Yaria
// -Kui

// Jungling(Assassin/Clash/Farm):
// -Lam
// -Prince of Lanling
// -Musashi
// -Butterfly
// -Li Bai

struct Hero {
    string nama;
    string role;
};

Hero hero[max_hero];
int heroCount = 0;

bool nama_duplikat(const string& nama_baru, const string& role) {
    for (int i = 0; i < heroCount; ++i) {
        if (hero[i].nama == nama_baru && hero[i].role == role) {
            return true;
        }
    }
    return false;
}
void clearScreen() {
    system("cls");
}
void tambah() {
    system("cls");
    cout << "Tambah Hero Meta\n";
    cout << "Pilih Role (Assassin, Mid, Farm, Clash, Support, Tank): ";
    string role;
    getline(cin >> ws, role);

    if (heroCount < max_hero) {
        cout << "Masukkan nama hero: ";
        string nama;
        getline(cin >> ws, nama);

        if (nama.empty() || any_of(nama.begin(), nama.end(), ::isdigit)) {
            cout << "Nama hero tidak valid!\n";
            return;
        }

        if (nama_duplikat(nama, role)) {
            cout << "Hero sudah ada dalam role tersebut!\n";
            return;
        }

        hero[heroCount].nama = nama;
        hero[heroCount].role = role;
        heroCount++;

        cout << "Hero berhasil masuk list >///<\n";
    } else {
        cout << "List hero sudah penuh!\n";
    }
}

void edit() {
    system("cls");
    cout << "Ubah Hero Meta\n";
    cout << "Pilih Role (Assassin, Mid, Farm, Clash, Support, Tank): ";
    string role;
    getline(cin >> ws, role);

    bool found = false;
    for (int i = 0; i < heroCount; ++i) {
        if (hero[i].role == role) {
            found = true;
            cout << i + 1 << ". " << hero[i].nama << endl;
        }
    }

    if (!found) {
        cout << "Hero yang anda cari tidak ada dalam role tersebut!\n";
        return;
    }

    cout << "Pilih nomor hero yang ingin diganti: ";
    int pil;
    cin >> pil;
    if (pil > 0 && pil <= heroCount) {
        cout << "Masukkan nama hero: ";
        string nama_baru;
        getline(cin >> ws, nama_baru);

        if (nama_baru.empty() || any_of(nama_baru.begin(), nama_baru.end(), ::isdigit)) {
            cout << "Tidak valid.\n";
            return;
        }

        if (nama_duplikat(nama_baru, role)) {
            cout << "Hero sudah ada dalam role tersebut!\n";
            return;
        }

        hero[pil - 1].nama = nama_baru;
        cout << "Hero berhasil diubah >///<\n";
    } else {
        cout << "Input tidak valid!\n";
    }
}

void lihat_hero() {
    system("cls");
    cout << "List Hero Meta \n";
    cout << setw(20) << left << "Nama" << setw(20) << "Role" << endl;
    cout << "-------------------------\n";
    for (int i = 0; i < heroCount; ++i) {
        cout << setw(20) << left << hero[i].nama << setw(20) << hero[i].role << endl;
    }
}

void hapus() {
    system("cls");
    cout << "Hapus Hero Meta\n";
    cout << "Pilih Role (Assassin, Mid, Farm, Clash, Support, Tank): ";
    string role;
    getline(cin >> ws, role);

    bool found = false;
    for (int i = 0; i < heroCount; ++i) {
        if (hero[i].role == role) {
            found = true;
            cout << i + 1 << ". " << hero[i].nama << endl;
        }
    }

    if (!found) {
        cout << "Hero yang anda cari tidak ada dalam role tersebut!\n";
        return;
    }

    cout << "Pilih nomor hero yang ingin dihapus: ";
    int pil;
    cin >> pil;
    if (pil > 0 && pil <= heroCount) {
        for (int i = pil - 1; i < heroCount - 1; ++i) {
            hero[i] = hero[i + 1];
        }
        heroCount--;
        cout << "Hero berhasil dihapus\n";
    } else {
        cout << "Input tidak valid!\n";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool login() {
    int attempts = 3;
    string username, password;
    system("cls");
    while (attempts > 0) {
        cout << "Log in Honor of King`s\n";
        cout << endl;
        cout << "Username: ";
        getline(cin, username);
        cout << "Kata Sandi: ";
        getline(cin, password);

        if (username == "javier" && password == "131") {
            cout << "Selamat datang, " << username << "!" << endl;
            return true;
        } else {
            attempts--;
            cout << "Username atau password salah!\n";
            if (attempts == 0) {
                cout << "AKUN TERBLOKIR!!!" << endl;
                return false;
            }
        }
    }
    return false;
}

int main() {
    
    if (!login()) {
        return 0;
    }

    int pil;
    do {
        system("cls");
        cout << "Honor of King`s:\n";
        cout << "1. Tambah Hero Meta\n";
        cout << "2. Lihat Hero Meta\n";
        cout << "3. Hapus Hero Meta\n";
        cout << "4. Ubah Hero Meta\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> pil;

        switch (pil) {
            case 1:
                tambah();
                break;
            case 2:
                lihat_hero();
                break;
            case 3:
                hapus();
                break;
            case 4:
                edit();
                break;
            case 5:
                cout << "Ihhh jahat banget mau pergi sekarang-_-  Yaudah Selamat Tinggal >///<\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Tekan Enter untuk melanjutkan...";
        cin.get();
    } while (pil != 5);

    return 0;
}
 