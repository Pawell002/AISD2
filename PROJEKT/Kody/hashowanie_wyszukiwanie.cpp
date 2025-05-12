#include <iostream>
#include <math.h>

using namespace std;

///int alfabet = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

int main(){
    int temp = 0, znak, hash_wz = 0, ob_hash = 0, p = 89, h;
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

    h = 1;
    for(int i = 0; i < wzorzec.size()-1; i++){
        h = (h * 26) % p;
    }

    cout << "Podaj wyrazenie zgodne ze slownikiem: ";
    cin >> wyrazenie;

    temp = 0;

    while(temp < wyrazenie.size()){
        znak = wyrazenie[temp];
        if(znak > 122 || znak < 97){
            cout << "Nieprawidlowe wyrazenie! Wprowadz poprawne wyrazenie: ";
            temp = 0;
            cin >> wyrazenie;
        }
        temp++;
    }

    for(int i = 0; i < wzorzec.size(); i++){
        hash_wz = (26 * hash_wz + wzorzec[i]) % p;
        ob_hash = (26 * ob_hash + wyrazenie[i]) % p;
    }

    cout << "wzorzec hasha: " << hash_wz << endl;
    cout << "obecny hasha: " << ob_hash << endl;

    for(int i = 0; i <= wyrazenie.size() - wzorzec.size(); i++){
        if(hash_wz == ob_hash){
            for(int j = 0; j < wzorzec.size(); j++){
                if(wzorzec[j] != wyrazenie[j+i]){
                    break;
                } else if(j == wzorzec.size()-1){
                    cout << i << " ";
                }
            }
        }
        else{
            ob_hash = (26 * (ob_hash - h * wyrazenie[i]) + wyrazenie[i + wzorzec.size()]) % p;
            if(ob_hash < 0){
                ob_hash = (ob_hash + p) % p;
            }
        }

    }

    cout << endl;


    return 0;
}
