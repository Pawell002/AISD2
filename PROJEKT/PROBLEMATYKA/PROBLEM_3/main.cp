#include <iostream>
#include <fstream>
#include <string>
#include "reprezentacja_danych.h"
#include "graf_budowa.h"
#include "min_cost_max_flow.h"
using namespace std;
int main()
{
    vector<Pole> pola;
    vector<Browar> browary;
    vector<Karczma> karczmy;
    vector<Droga> drogi;
    ifstream plik("dane3.txt");
    if (!plik.is_open())
    {
        cout<<"Nie mozna otworzyc pliku!"<<endl;
        return 1;
    }
    int l_pola,l_browary,l_karczmy,l_drogi;
    plik>>l_pola>>l_browary>>l_karczmy>>l_drogi;
    for (int i = 0; i < l_pola; i++)
    {
        Pole p;
        plik>>p.id>>p.x>>p.y>>p.ilosc_jeczmienia;
        pola.push_back(p);
    }
    for (int i = 0; i <l_browary; i++)
    {
        Browar b;
        plik>>b.id>>b.x>>b.y>>b.pojemnosc;
        browary.push_back(b);
    }
    for (int i = 0; i < l_karczmy; i++)
    {
        Karczma k;
        plik>>k.id>> k.x>>k.y>>k.zapotrzebowanie;
        karczmy.push_back(k);
    }
    for (int i = 0; i<l_drogi; i++)
    {
        Droga d;
        plik >>d.id>>d.zrodlo_id>>d.cel_id>>d.produkt>>d.przepustowosc>>d.koszt_naprawy;
        drogi.push_back(d);
    }
    plik.close();

    int start, koniec;
    vector<vector<Krawedz>> graf;

    zbuduj_graf(pola,browary,karczmy,drogi,graf,start,koniec);
    pair<int,int> wynik = min_cost_max_flow(graf,start,koniec);

    cout<<"=================================================================================="<<endl;
    cout<<"|                        PODSUMOWANIE TRANSPORTU                                 |"<<endl;
    cout<<"=================================================================================="<<endl<<endl;
    cout<<"Przewozony surowiec: jeczmien, piwo"<<endl;
    cout<<"Przelicznik: 1 jednostka jeczmienia = 1 jednostka piwa"<<endl;
    cout<<"----------------------------------------------------------------------------------"<<endl;
    cout<<"Maksymalna ilosc piwa dostarczonego do karczm: "<<wynik.first<<" litrow"<<endl;
    cout<<"----------------------------------------------------------------------------------"<<endl;
    cout<<"Calkowity koszt naprawy drog: "<<wynik.second<<" zlotych monet"<<endl;
    cout<<"=================================================================================="<<endl;

    return 0;
}
