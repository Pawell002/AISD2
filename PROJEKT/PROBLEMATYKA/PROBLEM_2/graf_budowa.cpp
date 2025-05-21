#include "graf_budowa.h"
using namespace std;

int macierz_przeplywu(vector<Pole>& pola,vector<Browar>& browary,vector<Karczma>& karczmy,vector<Droga>& drogi,vector<vector<int>>& macierz)
{
    int n = pola.size() + 2*browary.size() + karczmy.size() +2;
    int index_pola = 1;
    int index_browary_we = index_pola + pola.size();
    int index_browary_wy = index_browary_we + browary.size();
    int index_karczmy = index_browary_wy + browary.size();
    int start = 0;
    int koniec = n-1;

    macierz = vector<vector<int>>(n,vector<int>(n, 0));
    for(int i = 0;i < pola.size();i++)
    {
        int id = index_pola + i;
        macierz[start][id] = pola[i].ilosc_jeczmienia;
    }

    for(int i = 0;i < drogi.size();i++)
    {
        if(drogi[i].produkt =="jeczmien")
        {
            int z = index_pola + drogi[i].zrodlo_id;
            int doo = index_browary_we + drogi[i].cel_id;
            macierz[z][doo] = drogi[i].przepustowosc;
        }
        else if(drogi[i].produkt == "piwo")
        {
            int z = index_browary_wy + drogi[i].zrodlo_id;
            int doo = index_karczmy+ drogi[i].cel_id;
            macierz[z][doo] = drogi[i].przepustowosc;
        }
    }
    for(int i = 0;i <browary.size();i++)
    {
        int we_id = index_browary_we + i;
        int wy_id = index_browary_wy + i;
        macierz[we_id][wy_id] = browary[i].pojemnosc;
    }

    for(int i = 0;i < karczmy.size();i++)
    {
        int id = index_karczmy + i;
        macierz[id][koniec] = karczmy[i].zapotrzebowanie;
    }
    return n;
}
