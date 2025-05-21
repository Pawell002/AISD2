#include "graf_budowa.h"
using namespace std;

void dodaj_krawedz(vector<vector<Krawedz>>& graf, int z, int doo, int pojemnosc,int koszt)
{
    Krawedz k1;
    k1.do_id = doo;
    k1.koszt = koszt;
    k1.pojemnosc = pojemnosc;
    k1.przeplyw = 0;
    k1.odwrotna = graf[doo].size();

    Krawedz k2;
    k2.do_id = z;
    k2.koszt = -koszt;
    k2.pojemnosc = 0;
    k2.przeplyw = 0;
    k2.odwrotna = graf[z].size();

    graf[z].push_back(k1);
    graf[doo].push_back(k2);
}

void zbuduj_graf(vector<Pole>& pola, vector<Browar>& browary, vector<Karczma>& karczmy, vector<Droga>& drogi, vector<vector<Krawedz>>& graf, int& start, int& koniec)
{
    int n = pola.size() + 2 * browary.size() + 2 * karczmy.size()+2;
    graf.resize(n);

    int index_pola = 1;
    int index_browary_we = index_pola + pola.size();
    int index_browary_wy = index_browary_we + browary.size();
    int index_karczmy_we = index_browary_wy + browary.size();
    int index_karczmy_wy = index_karczmy_we + karczmy.size();

    start = 0;
    koniec = n - 1;

    for (int i = 0; i < pola.size(); i++)
    {
        int id = index_pola + i;
        dodaj_krawedz(graf, start, id, pola[i].ilosc_jeczmienia, 0);
    }

    for (int i = 0; i < drogi.size(); i++)
    {
        if (drogi[i].produkt =="jeczmien")
        {
            int z = index_pola + drogi[i].zrodlo_id;
            int doo = index_browary_we + drogi[i].cel_id;
            dodaj_krawedz(graf,z, doo, drogi[i].przepustowosc, drogi[i].koszt_naprawy);
        }
    }

    for (int i = 0; i < browary.size(); i++)
    {
        int we_id = index_browary_we + i;
        int wy_id = index_browary_wy + i;
        dodaj_krawedz(graf, we_id, wy_id, browary[i].pojemnosc, 0);
    }

    for (int i = 0; i < drogi.size(); i++)
    {
        if (drogi[i].produkt == "piwo")
        {
            int z = index_browary_wy + drogi[i].zrodlo_id;
            int doo = index_karczmy_we + drogi[i].cel_id;
            dodaj_krawedz(graf, z, doo, drogi[i].przepustowosc,drogi[i].koszt_naprawy);
        }
    }

    for (int i = 0; i < karczmy.size(); i++)
    {
        int wejscie = index_karczmy_we + i;
        int wyjscie = index_karczmy_wy + i;
        dodaj_krawedz(graf, wejscie, wyjscie, karczmy[i].zapotrzebowanie, 0);
    }

    for (int i = 0; i < karczmy.size(); i++)
    {
        int id = index_karczmy_wy + i;
        dodaj_krawedz(graf, id, koniec, karczmy[i].zapotrzebowanie, 0);
    }

    for (int i = 0; i < drogi.size(); i++)
    {
        if (drogi[i].produkt == "jeczmien_z_browaru_do_browaru")
        {
            int z = index_browary_we + drogi[i].zrodlo_id;
            int doo = index_browary_we + drogi[i].cel_id;
            dodaj_krawedz(graf, z, doo,drogi[i].przepustowosc,drogi[i].koszt_naprawy);
        }
        else if (drogi[i].produkt == "piwo_z_karczmy_do_karczmy")
        {
            int z = index_karczmy_we + drogi[i].zrodlo_id;
            int doo = index_karczmy_we + drogi[i].cel_id;
            dodaj_krawedz(graf, z,doo, drogi[i].przepustowosc, drogi[i].koszt_naprawy);
        }
    }
}
