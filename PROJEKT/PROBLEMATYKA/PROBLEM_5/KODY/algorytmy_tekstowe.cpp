#include "algorytmy_tekstowe.h"
#include <iostream>

// ----- Naiwny algorytm -----
void wyszukajNaiwnie(const string& tekst, const string& wzorzec, vector<pair<int,int>>& wyniki, int nrLinii){
    if (wzorzec.empty() || wzorzec.size() > tekst.size()){
        return;
    }

    for (size_t i = 0; i <= tekst.size() - wzorzec.size(); i++) {
        size_t j = 0;
        while (j < wzorzec.size() && tekst[i + j] == wzorzec[j]) {
            j++;
        }
        if (j == wzorzec.size()) {
            wyniki.emplace_back(nrLinii, i);
        }
    }
}

// ----- Rabin-Karp -----
int znajdzRabinKarp(const string& wzorzec, const string& tekst, int p, int podstawa, vector<pair<int,int>>& wyniki, int nrLinii) {
    if (wzorzec.empty() || wzorzec.size() > tekst.size()){
        return -1;
    }

    int h = 1, hash_wz = 0, ob_hash = 0;
    for (size_t i = 0; i < wzorzec.size() - 1; i++)
        h = (h*podstawa)%p;

    for (size_t i = 0; i < wzorzec.size(); i++) {
        hash_wz = (podstawa*hash_wz+(unsigned char)wzorzec[i])%p;
        ob_hash = (podstawa*ob_hash+(unsigned char)tekst[i])%p;
    }

    for (size_t i = 0; i <= tekst.size() - wzorzec.size(); i++) {
        if (hash_wz == ob_hash) {
            if (tekst.substr(i, wzorzec.size()) == wzorzec){
                wyniki.emplace_back(nrLinii, i);
            }
        }

        if (i < tekst.size() - wzorzec.size()) {
            ob_hash = (podstawa * (ob_hash - h * (unsigned char)tekst[i]) +
                       (unsigned char)tekst[i + wzorzec.size()]) % p;
            if (ob_hash < 0){
                ob_hash += p;
            }
        }
    }

    return -1;
}

// ----- KMP -----
void tablica_P(const string &w, vector<int> &P){
    if (w.empty()){
        return;
    }
    int m = w.size();
    P[0] = 0;
    int t = 0;
    for (int j = 1; j < m; j++){
        while (t > 0 && w[t] != w[j]){
            t = P[t - 1];
        }
        if (w[t] == w[j]){
            t++;
        }
        P[j] = t;
    }
}

void KMP(const string &T, const string &w, const vector<int> &P, vector<pair<int,int>>& wyniki, int nrLinii){
    if (w.empty()){
        return;
    }
    int n = T.size();
    int m = w.size();
    int i = 0, j = 0;

    while(i < n){
        if (w[j] == T[i]){
            i++;
            j++;
            if(j == m) {
                wyniki.emplace_back(nrLinii, i-j);
                j = P[j-1];
            }
        } else{
            if(j > 0){
                j = P[j-1];
            } else {
                i++;
            }
        }
    }
}

// ----- Trie -----
TrieWezel::TrieWezel(){
    czyKoniecSlowa = false;

    for(int i = 0; i < 128; i++){
        dzieci[i] = nullptr;
    }
}

void wstaw(TrieWezel* korzen, const string& wzorzec, int id) {
    TrieWezel* wezel = korzen;
    for (char z : wzorzec) {
        int index = static_cast<unsigned char>(z);
        if (!wezel->dzieci[index]) {
            wezel->dzieci[index] = new TrieWezel();
        }
        wezel = wezel->dzieci[index];
    }
    wezel->czyKoniecSlowa = true;
    wezel->wzorzecID = id;
}

vector<tuple<int, int, int>> znajdzWTekscie(TrieWezel* korzen, const string& wyrazenie){
    vector<tuple<int, int, int>> dopasowania;

    for (int i = 0; i < wyrazenie.size(); i++) {
        TrieWezel* wezel = korzen;
        int poz = i;
        string obecny;

        while (poz < wyrazenie.size()) {
            char z = wyrazenie[poz];
            int index = static_cast<unsigned char>(z);
            if (!wezel->dzieci[index]){
                break;
            }

            wezel = wezel->dzieci[index];
            obecny += z;

            if (wezel->czyKoniecSlowa) {
                dopasowania.emplace_back(i, poz - i + 1, wezel->wzorzecID);
            }
            poz++;
        }
    }
    return dopasowania;
}

void usun(TrieWezel* wezel) {
    if (!wezel) return;
    for (int i = 0; i < 128; ++i) {
        if (wezel->dzieci[i]) usun(wezel->dzieci[i]);
    }
    delete wezel;
}
