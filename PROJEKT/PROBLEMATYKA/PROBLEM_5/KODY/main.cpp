#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include "reprezentacja_danych.h"
#include "graf_budowa.h"
#include "min_cost_max_flow.h"
#include "algorytmy_tekstowe.h"
#include "wypukla_otoczka.h" 

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


    ofstream plikWyj("wynik.txt");
    if(!plikWyj){
        cout << "Nie mozna otworzyc pliku do zapisu" << endl;
        return 1;
    }

    plikWyj<<"=================================================================================="<<endl;
    plikWyj<<"|                        PODSUMOWANIE TRANSPORTU                                 |"<<endl;
    plikWyj<<"=================================================================================="<<endl<<endl;
    plikWyj<<"Przewozony surowiec: jeczmien, piwo"<<endl;
    plikWyj<<"Przelicznik: 1 jednostka jeczmienia = 1 jednostka piwa"<<endl;
    plikWyj<<"----------------------------------------------------------------------------------"<<endl;
    plikWyj<<"Maksymalna ilosc piwa dostarczonego do karczm: "<<wynik.first<<" litrow"<<endl;
    plikWyj<<"----------------------------------------------------------------------------------"<<endl;
    plikWyj<<"Calkowity koszt naprawy drog: "<<wynik.second<<" zlotych monet"<<endl;
    plikWyj<<"=================================================================================="<<endl;

    plikWyj.close();

    double laczna_ilosc_jeczmienia = 0.0;

    for (const auto& pole : pola) {
    // Tworzymy sztuczne punkty wokół (x, y) pola (np. kwadrat 1x1)
    std::vector<Punkt> punktyOtoczki = {
        Punkt(pole.x - 0.5, pole.y - 0.5),
        Punkt(pole.x + 0.5, pole.y - 0.5),
        Punkt(pole.x + 0.5, pole.y + 0.5),
        Punkt(pole.x - 0.5, pole.y + 0.5)
    };

    auto otoczka = wypuklaOtoczka(punktyOtoczki);
    double powierzchnia = poleWielokata(otoczka);
    double ilosc = powierzchnia * pole.ilosc_jeczmienia;

    cout << "Pole id=" << pole.id << " o srodku (" << pole.x << ", " << pole.y 
         << ") ma powierzchnie ~" << powierzchnia 
         << " i produkuje " << ilosc << " jednostek jeczmienia." << endl;

    laczna_ilosc_jeczmienia += ilosc;
}

cout << "\nLaczna ilosc jeczmienia: " << laczna_ilosc_jeczmienia << endl;
    
    ifstream plikWej("wynik.txt");
    vector<string> linie;
    string linia;


    if(!plikWej){
        cout << "Nie mozna otworzyc pliku do czytania" << endl;
        return 1;
    }

    while (getline(plikWej, linia)) {
        linie.push_back(linia);
    }

    plikWej.close();

    int wybor;
    string wzorzec;


    cout << "Wybierz algorytm wyszukujacy" << endl;
    cout << "0 - koniec wyszukiwania, 1 - naiwny, 2 - Rabina-Karpa, 3 - KMP, 4 - Trie: ";
    cin >> wybor;

    vector<pair<int,int>> wyniki;
    vector<WynikTrie> wynikiTrie;

    while(wybor != 0){
        wyniki.clear();
        wynikiTrie.clear();
        cin.ignore();
        switch(wybor){
            case 0:
                cout << "Koniec" << endl;
                return 0;
            case 1:
                cout << "Podaj wzorzec: " << endl;
                getline(cin, wzorzec);
                for(int i = 0; i < (int)linie.size(); i++) {
                    wyszukajNaiwnie(linie[i], wzorzec, wyniki, i);
                }
                cout << endl;
                break;
            case 2:
                cout << "Podaj wzorzec: " << endl;
                getline(cin, wzorzec);
                for(int i = 0; i < (int)linie.size(); i++) {
                    znajdzRabinKarp(wzorzec, linie[i], 101, 128, wyniki, i);
                }
                cout << endl;
                break;
            case 3:{
                cout << "Podaj wzorzec: " << endl;;
                getline(cin, wzorzec);

                vector<int> P(wzorzec.length());
                tablica_P(wzorzec, P);

                for(int i = 0; i < (int)linie.size(); i++) {
                    KMP(linie[i], wzorzec, P, wyniki, i);
                }
                cout << endl;
                break;
            }
            case 4: {
                TrieWezel* korzen = new TrieWezel();

                vector<string> wzorce;
                int l_wzor;

                cout << "Podaj liczbe wzorcow: " << endl;
                cin >> l_wzor;

                for(int i = 0; i < l_wzor; i++){
                    cin >> wzorzec;
                    wstaw(korzen, wzorzec, i);
                }

                for (int i = 0; i < (int)linie.size(); i++) {
                    auto dopasowania = znajdzWTekscie(korzen, linie[i]);
                    for (auto& d : dopasowania){
                        wynikiTrie.push_back({i, get<0>(d), get<2>(d)});
                    }
                }
                usun(korzen);
                break;
            }

        case 5:
            cout << "Podaj wzorzec: " << endl;
            getline(cin, wzorzec);
            for (int i = 0; i < (int)linie.size(); i++) {
                boyerMoore(linie[i], wzorzec, wyniki, i);
            }
            cout << endl;
            break;
            
        default:
                cout << "Nie ma takiego algorytmu" << endl;
                break;
        }
        if (wyniki.empty() && wynikiTrie.empty()) {
            cout << "Brak dopasowan." << endl;
        } else {
            cout << "\nZnalezione dopasowania:" << endl;

            for (auto& wynik : wyniki) {
                cout << "Linia: " << wynik.first + 1 << ", Pozycja: " << wynik.second + 1 << endl;
            }

            for (auto& wynik : wynikiTrie) {
                cout << "Linia: " << wynik.linia + 1
                     << ", Pozycja: " << wynik.pozycja + 1
                     << ", ID wzorca: " << wynik.wzorzecID << endl;
            }
        }
        cin >> wybor;
    }

    return 0;
}
