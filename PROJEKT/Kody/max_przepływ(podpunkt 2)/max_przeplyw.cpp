#include "max_przeplyw.h"
#include <vector>
#include <queue>
#include <climits>

using namespace std;

bool BFS(vector<vector<int>> &macierz, vector<int> &sciezka, int start, int koniec)
{
    queue<int> kolej;
    vector<bool> wierzcholki(macierz.size(), false);
    kolej.push(start);
    wierzcholki[start] = true;

    while(kolej.size() > 0)
    {
        int obecny = kolej.front();
        kolej.pop();

        for(int i = 0; i < macierz.size(); i++)
        {
            if(!wierzcholki[i] && macierz[obecny][i] > 0)
            {
                kolej.push(i);
                sciezka[i] = obecny;
                wierzcholki[i] = true;
                if(i == koniec)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int Edmonds(vector<vector<int>> &macierz, int start, int koniec)
{
    int n = macierz.size();
    vector<vector<int>> mac_residualna = macierz;
    vector<int> sciezka(n, -1);
    int maxPrzeplyw = 0;
    int przeplyw, v, u;

    while(BFS(mac_residualna, sciezka, start, koniec))
    {
        przeplyw = INT_MAX;

        v = koniec;

        while(v != start)
        {
            u = sciezka[v];
            przeplyw = min(przeplyw, mac_residualna[u][v]);
            v = u;
        }

        v = koniec;

        while(v != start)
        {
            u = sciezka[v];
            mac_residualna[u][v] -= przeplyw;
            mac_residualna[v][u] += przeplyw;
            v = u;
        }

        maxPrzeplyw += przeplyw;
    }

    return maxPrzeplyw;
}
