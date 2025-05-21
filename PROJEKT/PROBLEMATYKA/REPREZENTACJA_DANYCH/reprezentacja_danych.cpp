struct Pole {
    int id;
    double x,y;
    double ilosc_jeczmienia;
};

struct Browar {
    int id;
    double x,y;
    double pojemnosc;
    double wyprodukowane;
};

struct Karczma {
    int id;
    double x,y;
    double zapotrzebowanie;
};

struct Droga {
    int id;
    int zrodlo_id;
    int cel_id;
    string produkt;
    double przepustowosc;
    double koszt_naprawy;
};

struct Wezel {
    int id;
    string typ;
    int id_strukt;
    double przepustowosc;
};

struct Krawedz {
    int id;
    int zrodlo_id;
    int cel_id;
    double maks_przepustowosc;
    double koszt;
    double przeplyw;
};

struct Graf {
    vector<Wezel> wezly;
    vector<Krawedz> krawedzie;
    map<int,vector<int>> lista_sasiedztwa;
};




