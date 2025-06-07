#include "huffman.h"
#include <queue>
#include <iostream>

Huffman::Node::Node(char z, int c) {
    znak = z;
    czestosc = c;
    lewy = nullptr;
    prawy = nullptr;
}

bool Huffman::Porownaj::operator()(Node* a, Node* b) {
    return a->czestosc > b->czestosc;
}

void Huffman::kompresuj(const std::string& tekst) {
    std::unordered_map<char, int> czestosci;
    for (char z : tekst) {
        czestosci[z]++;
    }

    std::priority_queue<Node*, std::vector<Node*>, Porownaj> kolejka;

    for (auto para : czestosci) {
        kolejka.push(new Node(para.first, para.second));
    }

    while (kolejka.size() > 1) {
        Node* lewy = kolejka.top(); kolejka.pop();
        Node* prawy = kolejka.top(); kolejka.pop();

        Node* nowy = new Node('\0', lewy->czestosc + prawy->czestosc);
        nowy->lewy = lewy;
        nowy->prawy = prawy;

        kolejka.push(nowy);
    }

    korzen = kolejka.top();
    generujKody(korzen, "");

    // Tworzenie zakodowanego tekstu
    zakodowanyTekst = "";
    for (char z : tekst) {
        zakodowanyTekst += mapaKodow[z];
    }
}

void Huffman::generujKody(Node* wezel, const std::string& kod) {
    if (!wezel) return;

    if (!wezel->lewy && !wezel->prawy) {
        mapaKodow[wezel->znak] = kod;
        mapaDekodowania[kod] = wezel->znak;
    }

    generujKody(wezel->lewy, kod + "0");
    generujKody(wezel->prawy, kod + "1");
}

std::string Huffman::getZakodowanyTekst() const {
    return zakodowanyTekst;
}

void Huffman::wypiszKody() const {
    std::cout << "Kody Huffmana:\n";
    for (auto para : mapaKodow) {
        std::cout << para.first << " : " << para.second << "\n";
    }
}

std::string Huffman::dekompresuj(const std::string& zakodowanyTekst) {
    std::string wynik = "";
    std::string bufor = "";

    for (char bit : zakodowanyTekst) {
        bufor += bit;
        if (mapaDekodowania.find(bufor) != mapaDekodowania.end()) {
            wynik += mapaDekodowania[bufor];
            bufor = "";
        }
    }

    return wynik;
}

void Huffman::ustawMapeKodow(const std::unordered_map<char, std::string>& mapa) {
    mapaKodow = mapa;
    mapaDekodowania.clear();
    for (const auto& [znak, kod] : mapaKodow) {
        mapaDekodowania[kod] = znak;
    }
}

const std::unordered_map<char, std::string>& Huffman::getMapaKodow() const {
    return mapaKodow;
}

void Huffman::usunDrzewo(Node* wezel) {
    if (!wezel) return;
    usunDrzewo(wezel->lewy);
    usunDrzewo(wezel->prawy);
    delete wezel;
}
