#include <iostream>
#include <vector>

using namespace std;

int main(){

    int n, m, waga, wierz1, wierz2, wierz3;

    cin >> n >> m;

    vector<vector<int>> macierz(n, vector<int>(n, 2000000));

    for(int i = 0; i < m; i++){
        cin >> wierz1 >> wierz2 >> waga;
        macierz[wierz1-1][wierz2-1] = waga;
    }
    cout << endl;

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            if(macierz[i][k] != 2000000){
                for(int j = 0; j < n; j++){
                    macierz[i][j] = min(macierz[i][j], macierz[i][k] + macierz[k][j]);
                }
            }
        }
    }
    //podawanie
    cin >> wierz1 >> wierz2;
    int index = wierz1;
    do{
        for(int i = 0; i < n; i++){

        }
    } while(index != wierz2);

    cout << endl;
    //Wypisanie macierzy
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << macierz[i][j] << " ";
        }
        cout << endl;
    }
    //Wypisanie drogi z wierz1 do wierz2

    //Wypisanie drogi z wierz3 do wierz3



    return 0;
}
