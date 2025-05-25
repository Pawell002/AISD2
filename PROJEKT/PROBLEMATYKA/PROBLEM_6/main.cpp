// main.cpp

#include "Huffman.h"
#include <iostream>

int main() {
    Huffman huffman;
    std::string tekst;

    std::cout << "Podaj tekst do kompresji: ";
    std::getline(std::cin, tekst);

    huffman.kompresuj(tekst);

    std::cout << "\nZakodowany tekst (binarnie):\n" << huffman.getZakodowanyTekst() << "\n";
    huffman.wypiszKody();

    std::string zdekompresowany = huffman.dekompresuj(huffman.getZakodowanyTekst());

    std::cout << "\nZdekompresowany tekst:\n" << zdekompresowany << "\n";

    return 0;
}
