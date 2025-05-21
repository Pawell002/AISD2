#include <iostream>
#include <vector>

using namespace std;


int main(){
    int temp = 0, znak, m, n;
    string wyrazenie;
    string wzorzec;
    vector<int> ostatni(128, 0);

    cout << "Podaj wzorzec: ";

    cin >> wzorzec;
    while(temp < wzorzec.size()){
        znak = wzorzec[temp];
        if(znak < 0 || znak > 127 ){
            cout << "Nieprawidlowy wzorzec! Wpisz poprawny wzorzec: ";
            cin >> wzorzec;
            temp = 0;
        } else{
            temp++;
        }
    }

    m = wzorzec.size();

    for(int i = 0; i < wzorzec.size(); i++){
        ostatni[wzorzec[i]] = i;
    }

    cout << "Podaj wyrazenie zgodne ze slownikiem: ";
    cin >> wyrazenie;

    temp = 0;

    while(temp < wyrazenie.size()){
        znak = wyrazenie[temp];
        if(znak > 127 || znak < 0){
            cout << "Nieprawidlowe wyrazenie! Wprowadz poprawne wyrazenie: ";
            cin >> wyrazenie;
            temp = 0;
        } else{
            temp++;
        }
    }

    n = wyrazenie.size();

    int pp = 0;
    temp = 0;
    bool znaleziono = false;

    while(temp < n - m + 1){
        int j = m - 1;
        while(j >= 0 && wzorzec[j] == wyrazenie[temp+j]){
            j -= 1;
        }
        if(j >= 0){
            temp += max(1, j - ostatni[wyrazenie[temp+j]]);
        } else{
            pp = temp;
            cout << "Wzorzec wystepuje na pozycji: " << temp << endl;
            znaleziono = true;
            temp++;
        }
    }
    if(!znaleziono){
        cout << "Wzorzec: " << wzorzec << " nie wystepuje w tekscie" << endl;
    }

    return 0;
}
