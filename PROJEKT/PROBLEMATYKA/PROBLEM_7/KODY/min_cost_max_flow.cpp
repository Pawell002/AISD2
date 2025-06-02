#include "min_cost_max_flow.h"
#include "graf_budowa.h"
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

bool dijkstra_z_pot(vector<vector<Krawedz>>& graf, vector<int>& poprzednik, vector<int>& krawedz_id, vector<int>& potencjal, vector<int>& min_koszt,int start,int koniec)
{
    int n = graf.size();
    for (int i = 0; i < n; i++)
    {
        min_koszt[i] = INT_MAX;
        poprzednik[i] = -1;
        krawedz_id[i] = -1;
    }
    min_koszt[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0,start});

    while (pq.size() != 0)
    {
        int v = pq.top().second;
        int koszt_dotarcia = pq.top().first;
        pq.pop();

        if (koszt_dotarcia <= min_koszt[v])
        {
            for (int i = 0; i < graf[v].size(); i++)
            {
                Krawedz& kr = graf[v][i];

                if (kr.pojemnosc - kr.przeplyw > 0)
                {
                    int nowy_koszt = kr.koszt + potencjal[v] - potencjal[kr.do_id];

                    if (min_koszt[v] + nowy_koszt <min_koszt[kr.do_id])
                    {
                        min_koszt[kr.do_id] = min_koszt[v] + nowy_koszt;
                        poprzednik[kr.do_id] = v;
                        krawedz_id[kr.do_id] = i;
                        pq.push({min_koszt[kr.do_id], kr.do_id});
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (min_koszt[i] < INT_MAX)
        {
            potencjal[i] += min_koszt[i];
        }

    }

    if (min_koszt[koniec] < INT_MAX)
    {
        return true;
    }
    else
    {
        return false;
    }
}

pair<int, int> min_cost_max_flow(vector<vector<Krawedz>>& graf, int start, int koniec)
{
    int n = graf.size();
    vector<int> potencjal(n,0);
    vector<int> poprzednik(n);
    vector<int> krawedz_id(n);
    vector<int> min_koszt(n);

    int max_flow = 0;
    int min_cost = 0;

    while (dijkstra_z_pot(graf,poprzednik,krawedz_id, potencjal, min_koszt, start, koniec))
    {
        int sciezka = INT_MAX;
        int v = koniec;

        while (v != start)
        {
            int u = poprzednik[v];
            int id = krawedz_id[v];
            sciezka = min(sciezka, graf[u][id].pojemnosc - graf[u][id].przeplyw);
            v = u;
        }
        v = koniec;
        while (v != start)
        {
            int u = poprzednik[v];
            int id = krawedz_id[v];
            int odwrotna_id = graf[u][id].odwrotna;

            graf[u][id].przeplyw += sciezka;
            graf[v][odwrotna_id].przeplyw -= sciezka;
            min_cost += sciezka * graf[u][id].koszt;
            v = u;
        }
        max_flow += sciezka;
    }
    return {max_flow, min_cost};
}

