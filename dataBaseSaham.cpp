#include <vector>
#include <string>
using namespace std;

struct dataBaseSaham
{
    string namaSaham;
    string sektorSaham;
    double ROI;
    double volatilitas;
    int valueSaham; //Dalam Rupiah (Rp.)
};

vector<dataBaseSaham> saham = {
    // Finansial
    {"BBCA", "Finansial", 0.012, 0.02, 410000},
    {"BNGA", "Finansial", 0.018, 0.035, 1300},
    {"BMRI", "Finansial", 0.010, 0.015, 7200},

    // Teknologi
    {"GOTO", "Teknologi", 0.020, 0.05, 300},
    {"MAPI", "Teknologi", 0.008, 0.012, 6000},

    // Konsumer
    {"ICBP", "Konsumer", 0.011, 0.018, 8000},
    {"UNVR", "Konsumer", 0.009, 0.012, 44000},
    {"MYOR", "Konsumer", 0.015, 0.022, 7200},

    // Energi
    {"PGAS", "Energi", 0.007, 0.025, 1200},
    {"MEDC", "Energi", 0.014, 0.03, 1200},

    // Infrastruktur
    {"JSMR", "Infrastruktur", 0.013, 0.02, 4000},
    {"WIKA", "Infrastruktur", 0.01, 0.024, 2000}

    //
};