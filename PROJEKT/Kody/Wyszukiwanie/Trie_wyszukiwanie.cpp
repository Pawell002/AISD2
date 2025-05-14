#include <iostream>
#include <vector>

using namespace std;


struct TrieWezel{
    TrieWezel* dzieci[26];
    bool czyKoniecSlowa;

    TrieWezel(){
        czyKoniecSlowa = false;
        for(int i = 0; i < 26; i++){
            dzieci[i] = nullptr;
        }
    }

};

void wstaw(TrieWezel* korzen, string wzorzec){
    TrieWezel* wezel = korzen;
    for(char z : wzorzec){
        int index = z - 'a';
        if(wezel->dzieci[index] == nullptr){
            wezel->dzieci[index] = new TrieWezel();
        }
        wezel = wezel->dzieci[index];
    }
    wezel->czyKoniecSlowa = true;
}

vector<pair<int, string>> znajdzWTekscie(TrieWezel* korzen, string wyrazenie){
    vector<pair<int, string>> dopasowania;

    for(int i = 0; i < wyrazenie.length(); i++){
        TrieWezel* wezel = korzen;
        int poz = i;
        string obecny;

        while(poz < wyrazenie.length()){
            char z = wyrazenie[poz];
            int index = z - 'a';

            if(wezel->dzieci[index] == nullptr){
                break;
            }
            wezel = wezel->dzieci[index];
            obecny += z;

            if(wezel->czyKoniecSlowa){
                dopasowania.push_back({i, obecny});
            }
            poz++;
        }
    }

    return dopasowania;
}

void usun(TrieWezel* wezel) {
    if (wezel == nullptr){
        return;
    }

    for (int i = 0; i < 26; ++i) {
        if (wezel->dzieci[i]) {
            usun(wezel->dzieci[i]);
        }
    }

    delete wezel;
}

int main(){
    TrieWezel* korzen = new TrieWezel();

    vector<string> wzorce;
    int n;
    string wzorzec, wyrazenie;

    cout << "podaj liczbe wzorcow: ";
    cin >> n;

    cout << "Podaj " << n << " wzorcow: " << endl;
    for(int i = 0; i < n; i++){
        cin >> wzorzec;
        wzorce.push_back(wzorzec);
    }

    for(const string& slowo : wzorce){
        wstaw(korzen, slowo);
    }

    cout << "podaj wyrazenie: " << endl;
    cin >> wyrazenie;

    vector<pair<int, string>> wynik = znajdzWTekscie(korzen, wyrazenie);

    for(auto& [poz, wzorzec] : wynik){
        cout << "Znalezniono slowo: " << wzorzec << " na pozycji: " << poz << endl;
    }

    usun(korzen);
}
