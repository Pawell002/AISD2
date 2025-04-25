#include <iostream>
#include <fstream>
#include <string>
#include "reprezentacja_danych.h"
#include "graf_budowa.h"
#include "max_przeplyw.h"
using namespace std;
int main()
{
    vector<Pole> pola;
    vector<Browar> browary;
    vector<Karczma> karczmy;
    vector<Droga> drogi;
    ifstream plik("dane.txt");
    if (!plik.is_open())
    {
        cout<<"Nie mozna otworzyc pliku!"<<endl;
        return 1;
    }
    int l_pola,l_browary,l_karczmy,l_drogi;
    plik>>l_pola>>l_browary>>l_karczmy>>l_drogi;
    for (int i = 0;i < l_pola;i++)
    {
        Pole p;
        plik>>p.id>>p.x>>p.y>>p.ilosc_jeczmienia;
        pola.push_back(p);
    }
    for (int i = 0;i <l_browary;i++)
    {
        Browar b;
        plik>>b.id>>b.x>>b.y>>b.pojemnosc;
        browary.push_back(b);
    }
    for (int i = 0;i < l_karczmy;i++)
    {
        Karczma k;
        plik>>k.id>> k.x>>k.y>>k.zapotrzebowanie;
        karczmy.push_back(k);
    }
    for (int i = 0;i<l_drogi;i++)
    {
        Droga d;
        plik >>d.id>>d.zrodlo_id>>d.cel_id>>d.produkt>>d.przepustowosc>>d.koszt_naprawy;
        drogi.push_back(d);
    }
    plik.close();

    vector<vector<int>> macierz;
    int wierzcholki = macierz_przeplywu(pola,browary,karczmy,drogi,macierz);
    int wynik = Edmonds(macierz,0,wierzcholki-1);
    cout<<wynik<<endl;
    return 0;
}
