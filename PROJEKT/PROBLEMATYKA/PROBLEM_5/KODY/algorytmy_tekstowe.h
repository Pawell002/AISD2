#ifndef ALGORYTMY_H
#define ALGORYTMY_H

#include <string>
#include <vector>
#include <tuple>

using namespace std;

// ----- Naiwne wyszukiwanie -----
void wyszukajNaiwnie(const string& tekst, const string& wzorzec, vector<pair<int,int>>& wyniki, int nrLinii);

// ----- Rabin-Karp -----
int znajdzRabinKarp(const string& wzorzec, const string& tekst, int p, int podstawa, vector<pair<int,int>>& wyniki, int nrLinii);

// ----- KMP -----
void tablica_P(const string &w, vector<int> &P);
void KMP(const string &T, const string &w, const vector<int> &P, vector<pair<int,int>>& wyniki, int nrLinii);

// ----- Trie -----
struct TrieWezel {
    TrieWezel* dzieci[128];
    bool czyKoniecSlowa;
    int wzorzecID;

    TrieWezel();
};

void wstaw(TrieWezel* korzen, const string& wzorzec, int id);
vector<tuple<int, int, int>> znajdzWTekscie(TrieWezel* korzen, const string& wyrazenie);
void usun(TrieWezel* wezel);

// ----- Boyer-Moore -----
void boyerMoore(const string& tekst, const string& wzorzec, vector<pair<int,int>>& wyniki, int nrLinii);

#endif
