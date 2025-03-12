#include <iostream>
#include <vector>

using namespace std;

void odwiedzone(vector<vector<int>> &lista, vector<bool> &wierzcholki, int start){
    wierzcholki[start] = true;

    for(int i : lista[start]){
        if(wierzcholki[i] == false){
            odwiedzone(lista, wierzcholki, i);
        }
    }

}

void DFS(vector<vector<int>> lista, int start){
    vector<bool> wierzcholki(lista.size(), false);
    odwiedzone(lista, wierzcholki, start);
}

int main(){

    int u, v, n, m, wart, wynik;

    cin >> n >> m;

    vector<vector<int>> macierz(n, vector<int>(n, 0));
    vector<vector<int>> lista(n);

    for(int i = 0; i < m; i++){
        cin >> u >> v >> wart;
        macierz[u][v] = wart;
        lista[u].push_back(v);
    }

    while(true){

        break;
    }
    DFS(lista, 0);

    return 0;
}
