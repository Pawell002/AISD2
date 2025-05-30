#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include "reprezentacja_danych.h"
#include "graf_budowa.h"
#include "min_cost_max_flow.h"
#include "algorytmy_tekstowe.h"
#include "wypukla_otoczka.h" 
#include "Huffman.h"

using namespace std;

// Funkcja do czytania danych z pliku
bool wczytajDane(const string& nazwaPliku, 
                 vector<Pole>& pola, 
                 vector<Browar>& browary, 
                 vector<Karczma>& karczmy, 
                 vector<Droga>& drogi,
                 int& l_pola, int& l_browary, int& l_karczmy, int& l_drogi)
{
    ifstream plik(nazwaPliku);
    if (!plik.is_open()) {
        cerr << "Nie mozna otworzyc pliku " << nazwaPliku << "!" << endl;
        return false;
    }
    plik >> l_pola >> l_browary >> l_karczmy >> l_drogi;
    if (plik.fail()) {
        cerr << "Blad podczas wczytywania rozmiarow danych!" << endl;
        return false;
    }

    pola.reserve(l_pola);
    browary.reserve(l_browary);
    karczmy.reserve(l_karczmy);
    drogi.reserve(l_drogi);

    for (int i = 0; i < l_pola; i++) {
        Pole p;
        plik >> p.id >> p.x >> p.y >> p.ilosc_jeczmienia;
        if (plik.fail()) {
            cerr << "Blad wczytywania pola nr " << i << endl;
            return false;
        }
        pola.push_back(p);
    }
    for (int i = 0; i < l_browary; i++) {
        Browar b;
        plik >> b.id >> b.x >> b.y >> b.pojemnosc;
        if (plik.fail()) {
            cerr << "Blad wczytywania browaru nr " << i << endl;
            return false;
        }
        browary.push_back(b);
    }
    for (int i = 0; i < l_karczmy; i++) {
        Karczma k;
        plik >> k.id >> k.x >> k.y >> k.zapotrzebowanie;
        if (plik.fail()) {
            cerr << "Blad wczytywania karczmy nr " << i << endl;
            return false;
        }
        karczmy.push_back(k);
    }
    for (int i = 0; i < l_drogi; i++) {
        Droga d;
        plik >> d.id >> d.zrodlo_id >> d.cel_id >> d.produkt >> d.przepustowosc >> d.koszt_naprawy;
        if (plik.fail()) {
            cerr << "Blad wczytywania drogi nr " << i << endl;
            return false;
        }
        drogi.push_back(d);
    }
    plik.close();
    return true;
}

// Funkcja do zapisu wyniku do pliku
bool zapiszWynik(const string& nazwaPliku, const pair<int,int>& wynik)
{
    ofstream plikWyj(nazwaPliku);
    if (!plikWyj.is_open()) {
        cerr << "Nie mozna otworzyc pliku do zapisu: " << nazwaPliku << endl;
        return false;
    }
    plikWyj << "==================================================================================" << endl;
    plikWyj << "|                        PODSUMOWANIE TRANSPORTU                                 |" << endl;
    plikWyj << "==================================================================================" << endl << endl;
    plikWyj << "Przewozony surowiec: jeczmien, piwo" << endl;
    plikWyj << "Przelicznik: 1 jednostka jeczmienia = 1 jednostka piwa" << endl;
    plikWyj << "----------------------------------------------------------------------------------" << endl;
    plikWyj << "Maksymalna ilosc piwa dostarczonego do karczm: " << wynik.first << " litrow" << endl;
    plikWyj << "----------------------------------------------------------------------------------" << endl;
    plikWyj << "Calkowity koszt naprawy drog: " << wynik.second << " zlotych monet" << endl;
    plikWyj << "==================================================================================" << endl;
    plikWyj.close();
    return true;
}

// Funkcja do wyszukiwania wzorców i wypisywania wyników (oprócz Trie)
void wyszukajIWypisz(const vector<string>& linie, int algorytm)
{
    string wzorzec;
    cout << "Podaj wzorzec: " << endl;
    getline(cin, wzorzec);

    vector<pair<int,int>> wyniki;
    for (int i = 0; i < (int)linie.size(); i++) {
        switch(algorytm) {
            case 1:
                wyszukajNaiwnie(linie[i], wzorzec, wyniki, i);
                break;
            case 2:
                znajdzRabinKarp(wzorzec, linie[i], 101, 128, wyniki, i);
                break;
            case 3: {
                vector<int> P(wzorzec.length());
                tablica_P(wzorzec, P);
                KMP(linie[i], wzorzec, P, wyniki, i);
                break;
            }
            case 5:
                boyerMoore(linie[i], wzorzec, wyniki, i);
                break;
            default:
                cerr << "Nieznany algorytm wyszukiwania." << endl;
                return;
        }
    }
    if (wyniki.empty()) {
        cout << "Brak dopasowan." << endl;
    } else {
        cout << "\nZnalezione dopasowania:" << endl;
        for (const auto& wynik : wyniki) {
            cout << "Linia: " << wynik.first + 1 << ", Pozycja: " << wynik.second + 1 << endl;
        }
    }
}

// Funkcja do obsługi wyszukiwania wzorców z Trie (wiele wzorców)
void wyszukajTrieIWypisz(const vector<string>& linie)
{
    TrieWezel* korzen = new TrieWezel();

    int l_wzor;
    cout << "Podaj liczbe wzorcow: " << endl;
    cin >> l_wzor;
    cin.ignore();  // czyścimy znak nowej linii po cin

    for (int i = 0; i < l_wzor; i++) {
        string wzorzec;
        cout << "Podaj wzorzec nr " << (i+1) << ": ";
        getline(cin, wzorzec);
        wstaw(korzen, wzorzec, i);
    }

    vector<WynikTrie> wynikiTrie;
    for (int i = 0; i < (int)linie.size(); i++) {
        auto dopasowania = znajdzWTekscie(korzen, linie[i]);
        for (const auto& d : dopasowania) {
            wynikiTrie.push_back({i, get<0>(d), get<2>(d)});
        }
    }

    if (wynikiTrie.empty()) {
        cout << "Brak dopasowan." << endl;
    } else {
        cout << "\nZnalezione dopasowania (Trie):" << endl;
        for (const auto& wynik : wynikiTrie) {
            cout << "Linia: " << wynik.linia + 1
                 << ", Pozycja: " << wynik.pozycja + 1
                 << ", ID wzorca: " << wynik.wzorzecID << endl;
        }
    }

    usun(korzen);
}

int main()
{
    vector<Pole> pola;
    vector<Browar> browary;
    vector<Karczma> karczmy;
    vector<Droga> drogi;

    int l_pola = 0, l_browary = 0, l_karczmy = 0, l_drogi = 0;

    if (!wczytajDane("dane3.txt", pola, browary, karczmy, drogi, l_pola, l_browary, l_karczmy, l_drogi)) {
        return 1;
    }

    int start, koniec;
    vector<vector<Krawedz>> graf;
    zbuduj_graf(pola, browary, karczmy, drogi, graf, start, koniec);

    pair<int,int> wynik = min_cost_max_flow(graf, start, koniec);

    if (!zapiszWynik("wynik.txt", wynik)) {
        return 1;
    }

    double laczna_ilosc_jeczmienia = 0.0;

    for (const auto& pole : pola) {
        // Tworzymy sztuczne punkty wokół pola (kwadrat 1x1)
        vector<Punkt> punktyOtoczki = {
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

    // Wczytujemy linie z pliku wynikowego
    ifstream plikWej("wynik.txt");
    if (!plikWej.is_open()) {
        cerr << "Nie mozna otworzyc pliku do czytania: wynik.txt" << endl;
        return 1;
    }

    vector<string> linie;
    string linia;
    while (getline(plikWej, linia)) {
        linie.push_back(linia);
    }
    plikWej.close();

    int wybor;
    cout << "\nWybierz algorytm wyszukujacy" << endl;
    cout << "0 - koniec wyszukiwania, 1 - naiwny, 2 - Rabina-Karpa, 3 - KMP, 4 - Trie, 5 - Boyer-Moore" << endl;

    while (true) {
        cout << "Twoj wybor: ";
        if (!(cin >> wybor)) {
            cerr << "Niepoprawny wybor. Koncze program." << endl;
            break;
        }
        cin.ignore(); // czyścimy enter po wyborze

        if (wybor == 0) {
            cout << "Koniec wyszukiwania." << endl;
            break;
        }

        if (wybor == 4) {
            wyszukajTrieIWypisz(linie);
        } else {
            wyszukajIWypisz(linie, wybor);
        }
    }

    // Kompresja Huffmana
    Huffman huffman;
    string tekst;

    cout << "\nPodaj tekst do kompresji: ";
    getline(cin, tekst);

    huffman.kompresuj(tekst);

    cout << "\nZakodowany tekst (binarnie):\n" << huffman.getZakodowanyTekst() << "\n";
    huffman.wypiszKody();

    string zdekompresowany = huffman.dekompresuj(huffman.getZakodowanyTekst());

    cout << "\nZdekompresowany tekst:\n" << zdekompresowany << "\n";

    return 0;
}
