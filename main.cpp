#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iomanip>
#include <cstring>
using namespace std;

struct Saham {
    char kode[6];
    char sektor[20];
    double ROI;
    double volatilitas;
    int harga;
};

class Portofolio {
private:
    vector<Saham> database;
    queue<Saham> antrianAnalisis;
    stack<Saham> sahamRekomendasi;

    Saham* cariROITertinggi(Saham* arr, int low, int high);
    Saham* cariVolatilitasTerendah(Saham* arr, int low, int high);
    void knapsackOptimasi(int budget);

public:
    Portofolio();
    void inisialisasiData();
    void tambahSaham(const Saham& s);
    void tampilkanSemuaSaham();
    void rekomendasiSahamHarian();
    void urutkanBerdasarkanROI();
    void urutkanBerdasarkanVolatilitas();
    void optimasiPortofolio();
};

Portofolio::Portofolio() {
    inisialisasiData();
}

void Portofolio::inisialisasiData() {
    Saham saham[] = {
        {"BBCA", "Finansial", 0.012, 0.02, 410000},
        {"BNGA", "Finansial", 0.018, 0.035, 1300},
        {"BMRI", "Finansial", 0.010, 0.015, 7200},
        {"GOTO", "Teknologi", 0.020, 0.05, 300},
        {"MAPI", "Teknologi", 0.008, 0.012, 6000},
        {"ICBP", "Konsumer", 0.011, 0.018, 8000},
        {"UNVR", "Konsumer", 0.009, 0.012, 44000},
        {"MYOR", "Konsumer", 0.015, 0.022, 7200},
        {"PGAS", "Energi", 0.007, 0.025, 1200},
        {"MEDC", "Energi", 0.014, 0.03, 1200},
        {"JSMR", "Infrastruktur", 0.013, 0.02, 4000},
        {"WIKA", "Infrastruktur", 0.01, 0.024, 2000}
    };
    for (auto& s : saham) tambahSaham(s);
}

void Portofolio::tambahSaham(const Saham& s) {
    database.push_back(s);
    antrianAnalisis.push(s);
}

void Portofolio::tampilkanSemuaSaham() {
    cout << "\nDaftar Saham:\n";
    cout << "------------------------------------------------------------\n";
    cout << left << setw(6) << "Kode" << setw(15) << "Sektor"
         << setw(10) << "ROI" << setw(15) << "Volatilitas"
         << setw(10) << "Harga" << endl;
    cout << "------------------------------------------------------------\n";
    for (const auto& s : database) {
        cout << left << setw(6) << s.kode
             << setw(15) << s.sektor
             << setw(10) << fixed << setprecision(3) << s.ROI
             << setw(15) << s.volatilitas
             << setw(10) << s.harga << endl;
    }
    cout << "------------------------------------------------------------\n";
}

void Portofolio::rekomendasiSahamHarian() {
    while (!sahamRekomendasi.empty()) sahamRekomendasi.pop();
    queue<Saham> tempQueue = antrianAnalisis;
    while (!tempQueue.empty()) {
        Saham s = tempQueue.front(); tempQueue.pop();
        if (s.ROI > 0.01 && s.volatilitas < 0.03)
            sahamRekomendasi.push(s);
    }

    cout << "\nRekomendasi Saham Harian (ROI > 1% & Volatilitas < 3%):\n";
    if (sahamRekomendasi.empty()) {
        cout << "Tidak ada saham yang memenuhi kriteria.\n";
    } else {
        stack<Saham> tempStack = sahamRekomendasi;
        while (!tempStack.empty()) {
            Saham s = tempStack.top(); tempStack.pop();
            cout << "- " << s.kode << " (ROI: " << s.ROI * 100
                 << "%, Vol: " << s.volatilitas * 100 << "%, Harga: Rp."
                 << s.harga << ")\n";
        }
    }
}

void Portofolio::urutkanBerdasarkanROI() {
    vector<Saham> sorted = database;
    sort(sorted.begin(), sorted.end(), [](const Saham& a, const Saham& b) {
        return a.ROI > b.ROI;
    });

    cout << "\nSaham Terurut berdasarkan ROI Tertinggi:\n";
    for (const auto& s : sorted) {
        cout << s.kode << " - ROI: " << s.ROI * 100 << "% (Harga: Rp." << s.harga << ")\n";
    }
}

void Portofolio::urutkanBerdasarkanVolatilitas() {
    vector<Saham> sorted = database;
    sort(sorted.begin(), sorted.end(), [](const Saham& a, const Saham& b) {
        return a.volatilitas < b.volatilitas;
    });

    cout << "\nSaham Terurut berdasarkan Volatilitas Terendah:\n";
    for (const auto& s : sorted) {
        cout << s.kode << " - Vol: " << s.volatilitas * 100 << "% (ROI: "
             << s.ROI * 100 << "%)\n";
    }
}

void Portofolio::optimasiPortofolio() {
    int budget;
    cout << "\nMasukkan budget investasi (Rp.): ";
    cin >> budget;
    knapsackOptimasi(budget);
}

Saham* Portofolio::cariROITertinggi(Saham* arr, int low, int high) {
    if (low == high) return &arr[low];
    int mid = (low + high) / 2;
    Saham* left = cariROITertinggi(arr, low, mid);
    Saham* right = cariROITertinggi(arr, mid + 1, high);
    return (left->ROI > right->ROI) ? left : right;
}

Saham* Portofolio::cariVolatilitasTerendah(Saham* arr, int low, int high) {
    if (low == high) return &arr[low];
    int mid = (low + high) / 2;
    Saham* left = cariVolatilitasTerendah(arr, low, mid);
    Saham* right = cariVolatilitasTerendah(arr, mid + 1, high);
    return (left->volatilitas < right->volatilitas) ? left : right;
}

void Portofolio::knapsackOptimasi(int budget) {
    vector<pair<double, Saham*>> valuePerRupiah;
    for (auto& s : database) {
        valuePerRupiah.push_back({s.ROI / s.harga, &s});
    }
    sort(valuePerRupiah.rbegin(), valuePerRupiah.rend());

    cout << "\nRekomendasi Pembelian dengan Budget Rp." << budget << ":\n";
    int sisa = budget;
    for (auto& item : valuePerRupiah) {
        if (item.second->harga <= sisa) {
            int jumlah = sisa / item.second->harga;
            cout << "- " << item.second->kode << ": " << jumlah
                 << " lot (Rp." << jumlah * item.second->harga << ")\n";
            sisa -= jumlah * item.second->harga;
        }
    }
    cout << "Sisa budget: Rp." << sisa << endl;
}

int main() {
    Portofolio portofolio;
    int pilih;
    do {
        cout << "\n=== MENU SAHAM ===\n";
        cout << "1. Tampilkan saham\n2. Tambah saham baru\n3. Rekomendasi harian\n";
        cout << "4. Urut ROI\n5. Urut Volatilitas\n6. Optimasi Portofolio\n7. Keluar\n";
        cout << "Pilihan: "; cin >> pilih;
        switch (pilih) {
            case 1: portofolio.tampilkanSemuaSaham(); break;
            case 2: {
                Saham s;
                cout << "Kode: "; cin >> s.kode;
                cout << "Sektor: "; cin >> s.sektor;
                cout << "ROI: "; cin >> s.ROI;
                cout << "Volatilitas: "; cin >> s.volatilitas;
                cout << "Harga: "; cin >> s.harga;
                portofolio.tambahSaham(s); break;
            }
            case 3: portofolio.rekomendasiSahamHarian(); break;
            case 4: portofolio.urutkanBerdasarkanROI(); break;
            case 5: portofolio.urutkanBerdasarkanVolatilitas(); break;
            case 6: portofolio.optimasiPortofolio(); break;
            case 7: cout << "Keluar...\n"; break;
            default: cout << "Pilihan salah!\n";
        }
    } while (pilih != 7);
}