#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;


bool DFS(vector<vector<int>> &macierz, vector<bool> &wierzcholki, vector<int> &sciezka, int start, int koniec){
    wierzcholki[start] = true;
    if(start == koniec){
        return true;
    }

    for(int i = 0; i < macierz.size(); i++){
        if(!wierzcholki[i] && macierz[start][i] > 0){
            sciezka[i] = start;
            if(DFS(macierz, wierzcholki, sciezka, i, koniec)){
                return true;
            }
        }
    }
    return false;
}

bool sprawdzPolaczenie(vector<vector<int>> &macierz, vector<int> &sciezka, int start, int koniec){
    vector<bool> wierzcholki(macierz.size(), false);
    return DFS(macierz, wierzcholki, sciezka, start, koniec);
}

int FordFulkerson(vector<vector<int>> &macierz, int start, int koniec){
    int n = macierz.size();
    vector<vector<int>> mac_residualna = macierz;
    vector<int> sciezka(n, -1);
    int maxPrzeplyw = 0;
    int przeplyw, v, u;

    while(sprawdzPolaczenie(mac_residualna, sciezka, start, koniec)){
        przeplyw = INT_MAX; //symbol nieskonczonosci

        v = koniec;

        while(v != start){
            u = sciezka[v];
            przeplyw = min(przeplyw, mac_residualna[u][v]);
            v = u;
        }

        v = koniec;

        while(v != start){
            u = sciezka[v];
            mac_residualna[u][v] -= przeplyw;
            mac_residualna[v][u] += przeplyw;
            v = u;
        }

        maxPrzeplyw += przeplyw;
    }

    return maxPrzeplyw;
}

int main(){

    int u, v, n, m, wart, wynik;

    cin >> n >> m;

    vector<vector<int>> macierz(n, vector<int>(n, 0));

    for(int i = 0; i < m; i++){
        cin >> u >> v >> wart;
        macierz[u][v] = wart;
    }

    wynik = FordFulkerson(macierz, 0, n-1);

    cout << wynik << endl;

    return 0;
}
