#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int temp = 0, znak, m, n;
    string wyrazenie;
    string wzorzec;
    vector<int> ostatni(128, -1);  // inicjalizacja na -1, aby wskazywać brak znaku

    cout << "Podaj wzorzec: ";
    cin >> wzorzec;

    // Sprawdzenie czy wzorzec zawiera poprawne znaki ASCII
    while (temp < (int)wzorzec.size()) {
        znak = (unsigned char)wzorzec[temp];
        if (znak < 0 || znak > 127) {
            cout << "Nieprawidlowy wzorzec! Wpisz poprawny wzorzec: ";
            cin >> wzorzec;
            temp = 0;
        }
        else {
            temp++;
        }
    }

    m = (int)wzorzec.size();

    // Wypełnienie tablicy ostatnich wystąpień
    for (int i = 0; i < m; i++) {
        ostatni[(unsigned char)wzorzec[i]] = i;
    }

    cout << "Podaj wyrazenie zgodne ze slownikiem: ";
    cin >> wyrazenie;

    temp = 0;

    // Sprawdzenie poprawności wyrazenia
    while (temp < (int)wyrazenie.size()) {
        znak = (unsigned char)wyrazenie[temp];
        if (znak < 0 || znak > 127) {
            cout << "Nieprawidlowe wyrazenie! Wprowadz poprawne wyrazenie: ";
            cin >> wyrazenie;
            temp = 0;
        }
        else {
            temp++;
        }
    }

    n = (int)wyrazenie.size();

    int pp = 0;
    temp = 0;
    bool znaleziono = false;

    while (temp <= n - m) {
        int j = m - 1;
        // Porównujemy wzorzec z tekstem od końca wzorca
        while (j >= 0 && wzorzec[j] == wyrazenie[temp + j]) {
            j--;
        }
        if (j < 0) {
            // Znaleziono wzorzec na pozycji temp
            pp = temp;
            cout << "Wzorzec wystepuje na pozycji: " << temp << endl;
            znaleziono = true;
            temp += 1; // przesuwamy o 1, żeby znaleźć kolejne wystąpienia
        }
        else {
            // przesunięcie wg tablicy ostatnich wystąpień
            int last = ostatni[(unsigned char)wyrazenie[temp + j]];
            temp += max(1, j - last);
        }
    }

    if (!znaleziono) {
        cout << "Wzorzec: " << wzorzec << " nie wystepuje w tekscie" << endl;
    }

    return 0;
}
