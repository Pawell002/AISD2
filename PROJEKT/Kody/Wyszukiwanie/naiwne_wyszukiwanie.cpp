#include <iostream>

using namespace std;

int main(){
    int temp, znak;
    string wyrazenie;
    string wzorzec;

    cout << "Podaj wzorzec: ";
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
    temp = 0;

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

    for(int i = 0; i <= wyrazenie.size() - wzorzec.size(); i++){
        for(int j = 0; j < wzorzec.size(); j++){
            if(wzorzec[j] != wyrazenie[j+i]){
                break;
            } else if(j == wzorzec.size()-1){
                cout << i << " ";
            }
        }
    }
    cout << endl;


    return 0;
}
