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
void bubbleSort(Hero* hero_list, int count);
void selectionSort(Hero* hero_list, int count);
void quickSort(Hero* hero_list, int low, int high);
int partition(Hero* hero_list, int low, int high);
void tampilkanSetelahDiurutkan(Hero* hero_list, int count);
int binarySearch(Hero* hero_list, int l, int r, const string& nama);
int interpolationSearchDescending(Hero* hero_list, int l, int r, const string& nama);

int main() {
    if (!login()) {
        return 0;
    }

    int pil;
    do {
        system("cls");
        cout << "Honor of King`s:\n";
        cout << "1. Tambah Hero Meta\n";
        cout << "2. Lihat Hero Meta (Diurutkan berdasarkan nama secara ascending)\n";
        cout << "3. Hapus Hero Meta\n";
        cout << "4. Ubah Hero Meta\n";
        cout << "5. Hitung Jumlah Hero di dalam role\n";
        cout << "6. Tampilkan Hero Setelah Diurutkan berdasarkan Tingkat Damage (Descending)\n";
        cout << "7. Tampilkan Hero Setelah Diurutkan berdasarkan Kesulitan (Ascending)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pil;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pil) {
            case 1:
                tambah();
                break;
            case 2:
                bubbleSort(hero, heroCount);
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
            case 6:
                selectionSort(hero, heroCount);
                tampilkanSetelahDiurutkan(hero, heroCount);
                break;
             case 7:
                {
                    quickSort(hero, 0, heroCount - 1);
                    tampilkanSetelahDiurutkan(hero, heroCount);

                    // Pencarian hero berdasarkan nama secara descending
                    cout << "\nCari Hero berdasarkan nama secara descending!\n";
                    cout << "Nama Hero: ";
                    string nama_desc;
                    getline(cin >> ws, nama_desc);
                    int result_desc = interpolationSearchDescending(hero, 0, heroCount - 1, nama_desc);
                    if (result_desc != -1) {
                        cout << "Hero " << nama_desc << " ditemukan pada indeks " << result_desc << endl;
                    } else {
                        cout << "Hero " << nama_desc << " tidak ditemukan\n";
                    }

                    cout << "Tekan Enter untuk kembali ke menu utama.\n";
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

    // Bubble sort berdasarkan nama sebelum menampilkan
    bubbleSort(hero_list, count);

    for (int i = 0; i < count; ++i) {
        cout << setw(20) << left << hero_list[i].nama << setw(20) << hero_list[i].role;

        for (int j = 0; j < hero_list[i].numAbilities; ++j) {
            cout << setw(15) << left << "Damage: " << hero_list[i].abilities[j].damage;
            cout << setw(10) << left << "Kesulitan: " << hero_list[i].abilities[j].difficulty;
            cout << endl;
        }
    }

    // Pencarian hero berdasarkan nama
    cout << "\nCari Hero berdasarkan nama!\n";
    cout << "Nama Hero: ";
    string nama;
    getline(cin >> ws, nama);
    int result = binarySearch(hero_list, 0, count - 1, nama);
    if (result != -1) {
        cout << "Hero " << nama << " ditemukan pada indeks " << result << endl;
    } else {
        cout << "Hero " << nama << " tidak ditemukan\n";
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

void bubbleSort(Hero* hero_list, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (hero_list[j].nama > hero_list[j + 1].nama) {
                // Tukar posisi
                Hero temp = hero_list[j];
                hero_list[j] = hero_list[j + 1];
                hero_list[j + 1] = temp;
            }
        }
    }
}

void selectionSort(Hero* hero_list, int count) {
    for (int i = 0; i < count - 1; ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if (hero_list[j].abilities[0].damage > hero_list[maxIndex].abilities[0].damage) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            // Tukar posisi
            Hero temp = hero_list[i];
            hero_list[i] = hero_list[maxIndex];
            hero_list[maxIndex] = temp;
        }
    }
}

void quickSort(Hero* hero_list, int low, int high) {
    if (low < high) {
        int pi = partition(hero_list, low, high);

        quickSort(hero_list, low, pi - 1);
        quickSort(hero_list, pi + 1, high);
    }
}

int partition(Hero* hero_list, int low, int high) {
    int pivot = hero_list[high].abilities[0].difficulty;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (hero_list[j].abilities[0].difficulty < pivot) {
            i++;
            Hero temp = hero_list[i];
            hero_list[i] = hero_list[j];
            hero_list[j] = temp;
        }
    }
    Hero temp = hero_list[i + 1];
    hero_list[i + 1] = hero_list[high];
    hero_list[high] = temp;
    return (i + 1);
}

void tampilkanSetelahDiurutkan(Hero* hero_list, int count) {
    clearScreen();
    cout << "List Hero Setelah Diurutkan\n";
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

int binarySearch(Hero* hero_list, int l, int r, const string& nama) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (hero_list[mid].nama == nama)
            return mid;
        if (hero_list[mid].nama > nama)
            return binarySearch(hero_list, l, mid - 1, nama);
        return binarySearch(hero_list, mid + 1, r, nama);
    }
    return -1;
}

int interpolationSearchDescending(Hero* hero_list, int l, int r, const string& nama) {
    while (l <= r && hero_list[r].nama >= nama && hero_list[l].nama <= nama) {
        if (hero_list[r].nama == hero_list[l].nama) {
            if (hero_list[l].nama == nama) return l;
            return -1;
        }

        // Perbaikan pada bagian perhitungan fraction
        double fraction = static_cast<double>(nama[0] - hero_list[l].nama[0]) / (hero_list[l].nama[0] - hero_list[r].nama[0]);
        int pos = l + static_cast<int>((r - l) * fraction);

        // Perbaikan untuk memastikan posisi tidak melebihi r
        if (pos > r) pos = r;

        if (hero_list[pos].nama == nama) return pos;
        if (hero_list[pos].nama < nama) r = pos - 1;
        else l = pos + 1;
    }
    return -1;
}




