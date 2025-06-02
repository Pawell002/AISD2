#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <unordered_map>

class Huffman {
public:
    // Skonstruowanie na podstawie tekstu źródłowego
    void kompresuj(const std::string& tekst);

    // Dekompresja z zakodowanego ciągu binarnego
    std::string dekompresuj(const std::string& zakodowanyTekst);

    // Pobierz zakodowany tekst
    std::string getZakodowanyTekst() const;

    const std::unordered_map<char, std::string>& getMapaKodow() const;

    // Wyświetl przypisane kody Huffmana
    void wypiszKody() const;

private:
    struct Node {
        char znak;
        int czestosc;
        Node* lewy;
        Node* prawy;
        Node(char z, int c);
    };

    struct Porownaj {
        bool operator()(Node* a, Node* b);
    };

    Node* korzen;
    std::unordered_map<char, std::string> mapaKodow;
    std::unordered_map<std::string, char> mapaDekodowania;
    std::string zakodowanyTekst;

    void generujKody(Node* wezel, const std::string& kod);
    void usunDrzewo(Node* wezel);
};

#endif // HUFFMAN_H

