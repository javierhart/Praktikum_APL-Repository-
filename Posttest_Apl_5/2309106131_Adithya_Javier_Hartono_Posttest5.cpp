#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int max_hero = 100;

struct Ability {
    string name;
    int damage;
    int difficulty;
};

struct Hero {
    string nama;
    string role;
    Ability* abilities;
    int numAbilities;
};

Hero hero[max_hero];
int heroCount = 0;

bool nama_duplikat(const string& nama_baru, const string& role);
void clearScreen();
void tambah();
void edit(Hero* hero_list, int count);
void lihat_hero(Hero* hero_list, int count);
void hapus();
bool login();
int hitung_role_hero(const string& role, int index = 0, int count = 0);

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
        cout << "5. Hitung Jumlah Hero di dalam role\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pil;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pil) {
            case 1:
                tambah();
                break;
            case 2:
                lihat_hero(hero, heroCount);
                break;
            case 3:
                hapus();
                break;
            case 4:
                edit(hero, heroCount);
                break;
            case 5:
                {
                    clearScreen();
                    cout << "Hitung Jumlah Hero dalam role\n";
                    cout << "Pilih Role (Assassin, Mid, Farm, Clash, Support, Tank): ";
                    string role;
                    cin >> role;
                    int count = hitung_role_hero(role);
                    cout << "Jumlah hero dalam role " << role << " adalah: " << count << endl;
                    cout << "Tekan Enter untuk melanjutkan...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                }
                break;
            case 0:
                cout << "Ihhh jahat banget mau pergi sekarang-_-  Yaudah Selamat Tinggal >///<\n";
                return 0; 
            default:
                cout << "Pilihan tidak valid.\n";
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (pil != 0); 

    return 0;
}

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
    clearScreen();
    cout << "Tambah Hero Meta:\n";
    cout << "Role Tersedia (Assassin, Mid, Farm, Clash, Support, Tank)\n";

    cout << "Nama: ";
    string nama_baru;
    getline(cin >> ws, nama_baru);

    cout << "Role: ";
    string role_baru;
    getline(cin >> ws, role_baru);

    Ability* abilities = new Ability[1];

    Ability ability;

    cout << "Tingkat Damage (1-5): ";
    cin >> ability.damage;
    cout << "Kesulitan Hero(1-5): ";
    cin >> ability.difficulty;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    abilities[0] = ability;
    hero[heroCount].nama = nama_baru;
    hero[heroCount].role = role_baru;
    hero[heroCount].abilities = abilities;
    hero[heroCount].numAbilities = 1; 
    heroCount++;

    cout << "Berhasil ditambahkan.\n";
    cout << "Tekan Enter untuk kembali ke menu utama.\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cin.get();
}

void edit(Hero* hero_list, int count) {
    clearScreen();
    cout << "Ubah Hero Meta\n";
    cout << "Pilih Role (Assassin, Mid, Farm, Clash, Support, Tank): ";
    string role;
    getline(cin >> ws, role);

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (hero_list[i].role == role) {
            found = true;
            cout << i + 1 << ". " << hero_list[i].nama << endl;
        }
    }

    if (!found) {
        cout << "Hero yang anda cari tidak ada dalam role tersebut!\n";
        return;
    }

    cout << "Pilih nomor hero yang ingin diganti: ";
    int pil;
    cin >> pil;
    if (pil > 0 && pil <= count) {
        cout << "Masukkan nama hero: ";
        string nama_baru;
        getline(cin >> ws, nama_baru);

        if (nama_baru != hero_list[pil - 1].nama && nama_duplikat(nama_baru, role)) {
            cout << "Hero sudah ada dalam role tersebut!\n";
            return;
        }

        Ability ability;

        cout << "Tingkat Damage (1-5): ";
        cin >> ability.damage;
        cout << "Kesulitan Hero(1-5): ";
        cin >> ability.difficulty;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        hero_list[pil - 1].nama = nama_baru;
        cout << "Hero berhasil diubah >///<\n";
    } else {
        cout << "Input tidak valid!\n";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void lihat_hero(Hero* hero_list, int count) {
    clearScreen();
    cout << "List Hero Meta \n";
    cout << setw(20) << left << "Nama" << setw(20) << "Role" << setw(20) << "Abilities" << endl;
    cout << "--------------------------------------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        cout << setw(20) << left << hero_list[i].nama << setw(20) << hero_list[i].role;

        for (int j = 0; j < hero_list[i].numAbilities; ++j) {
            cout << setw(15) << left << "Damage: " << hero_list[i].abilities[j].damage;
            cout << setw(10) << left << "Kesulitan: " << hero_list[i].abilities[j].difficulty;
            cout << endl;
        }
    }
    cout << "Tekan Enter untuk kembali ke menu utama.\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void hapus() {
    clearScreen();
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
        delete[] hero[pil - 1].abilities;
        for (int i = pil - 1; i < heroCount - 1; ++i) {
            hero[i] = hero[i + 1];
        }
        heroCount--;
        cout << "Hero berhasil dihapus\n";
    } else {
        cout << "Input tidak valid!\n";
    }

    cout << "Tekan Enter untuk kembali ke menu utama.\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool login() {
    int attempts = 3;
    string username, password;
    clearScreen();
    while (attempts > 0) {
        cout << "Log in Honor of King`s\n\n";
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return false;
            }
        }
    }
    return false;
}

int hitung_role_hero(const string& role, int index, int count) {
    if (index >= heroCount) {
        return count;
    }
    if (hero[index].role == role) {
        count++;
    }
    return hitung_role_hero(role, index + 1, count);
}
