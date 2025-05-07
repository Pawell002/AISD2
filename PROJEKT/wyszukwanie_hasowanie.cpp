///Alfabet angielski male litery

#include <iostream>
#include <math.h>

using namespace std;

///int alfabet = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

int main(){
    int temp = 0, znak, hash_wz = 0, ob_hash = 0, wynik_hash, p = 89;
    string wzorzec;
    string wyrazenie;

    cout << "Wzorzec zlo¿ony z malych liter: ";
    cin >> wzorzec;
    while(temp < wzorzec.size()){
        znak = wzorzec[temp];
        if(znak > 122 || znak < 97){
            cout << "Nieprawidlowy wzorzec! Wprowadz poprawny wzorzec: ";
            temp = 0;
            cin >> wzorzec;
        }
        temp++;
    }

    for(int i = 0; i < wzorzec.size(); i++){
        znak = wzorzec[i];
        hash_wz += znak*pow(26, wzorzec.size() - (i+1));
    }

    hash_wz = hash_wz%p;

    cout << "wzorzec hasha: " << hash_wz << endl;

    cout << "Podaj wyrazenie zgodne ze slownikiem: ";
    cin >> wyrazenie;

    while(temp < wyrazenie.size()){
        znak = wyrazenie[temp];
        if(znak > 122 || znak < 97){
            cout << "Nieprawidlowe wyrazenie! Wprowadz poprawne wyrazenie: ";
            temp = 0;
            cin >> wyrazenie;
        }
        temp++;
    }


    for(int i = 0; i < wyrazenie.size() - wzorzec.size(); i++){
        znak = wyrazenie[i];
        if(i < wzorzec.size()){
            ob_hash += znak*pow(26, wzorzec.size() - (1+i%wzorzec.size()));
        }
        else{
            ob_hash = ob_hash - wyrazenie[wzorzec.size()]*pow(26, wzorzec.size() - (1+i%wzorzec.size()))*26 + wyrazenie[i];
        }
        cout << "obecny hash: " << ob_hash;
        wynik_hash = ob_hash%p;

        cout << " wynik hash: " << wynik_hash << endl;
        if(wynik_hash == hash_wz){
            temp = i;
            for(int j = 0; j < wzorzec.size(); j++){
                if(wzorzec[j] != wyrazenie[temp]){
                    break;
                }
                temp++;
                if(j == wzorzec.size()-1){
                    cout << i << " ";
                }
            }
        }
    }

    cout << endl;


    return 0;
}
