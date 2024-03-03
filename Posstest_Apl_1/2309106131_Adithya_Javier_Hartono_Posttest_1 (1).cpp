#include <iostream>
using namespace std;

int main() {
    string username, sandi;
    float celcius, farenheit, kelvin, reamur;
    int count = 3;

    while (count > 0) {
        cout <<"Progam Konversi Suhu"<< endl;
        cout <<"Username: ";
        getline(cin, username);
        cout <<"Sandi: ";
        getline(cin, sandi);

        if (username == "javier" && sandi == "131") {
            cout << endl;
            cout << "Welcome ngab " << username << "!" << endl;
            break;
        } else {
            count--;
            cout <<"Username atau password salah " << endl;
            cout << endl;
            if (count == 0) {
                cout <<"AKUN TERBLOKIR!!!" << endl;
                return 0;
            }
        }
    }
    
    cout <<"---KONVERSI SUHU---"<< endl;
    cout << endl;
    char suhu;
    do {
        int pilihan;    
        cout <<"1.Celcius"<< endl;
        cout <<"2.Farenheit"<< endl;
        cout <<"3.Kelvin"<< endl;
        cout <<"4.Reamur"<< endl;
        cout <<"5.OUT"<< endl;
        cout <<"Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout <<"Masukan Suhu Celcius: ";
                cin >> celcius;
                farenheit = (celcius * 1.8) + 32;
                kelvin = celcius + 273.15;
                reamur = celcius * 0.8;
                cout <<"Hasil"<< endl;
                cout <<"Farenheit = "<< farenheit << endl;
                cout <<"Kelvin = "<< kelvin << endl;
                cout <<"Reamur = "<< reamur << endl;
                break;

            case 2:
                cout <<"Masukan Suhu Farenheit: ";
                cin >> farenheit;
                celcius = (farenheit - 32) / 1.8;
                kelvin = (farenheit + 459.67) / 1.8;
                reamur = (farenheit - 32) * 0.44;
                cout <<"Hasil"<< endl;
                cout <<"Celcius = "<< celcius << endl;
                cout <<"Kelvin = "<< kelvin << endl;
                cout <<"Reamur = "<< reamur << endl;
                break;

            case 3:
                cout <<"Masukan Suhu Kelvin: ";
                cin >> kelvin;
                celcius = kelvin - 273.15;
                farenheit = kelvin * 1.8 - 459.67;
                reamur = (kelvin - 273.15) * 0.8;
                cout <<"Hasil"<< endl;
                cout <<"Celcius = "<< celcius << endl;
                cout <<"Farenheit = "<< farenheit << endl;
                cout <<"Reamur = "<< reamur << endl;
                break;

            case 4:
                cout <<"Masukan Suhu Reamur: ";
                cin >> reamur;
                celcius = reamur / 0.8;
                farenheit = reamur *2.25 +32;
                kelvin = reamur / 0.8 + 273.15;
                cout <<"Hasil"<< endl;
                cout <<"Celcius = "<< celcius << endl;
                cout <<"Farenheit = "<< farenheit << endl;
                cout <<"Kelvin = "<< kelvin << endl;
                break;

            case 5:
                cout <<"TAMAT";
                return 0;

            default:
                cout <<"Masukan Pilihan Yang Benar OIII!!!";
                cout<<endl;
        } 

        cout <<"Hitung Lagi?: ";
        cin >> suhu;  
    } while (suhu == 'y' || suhu == 'Y' || suhu == 'ya' || suhu == 'YA');
    return 0;
}
