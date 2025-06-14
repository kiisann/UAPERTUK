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
