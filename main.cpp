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