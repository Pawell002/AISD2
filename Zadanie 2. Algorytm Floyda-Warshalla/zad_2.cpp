#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m, waga, wierz1, wierz2;
    cin >> n >> m;

    vector<vector<int>> macierz(n, vector<int>(n, 2000000));
    vector<vector<int>> tab2(n, vector<int>(n,-1));

    for(int i = 0; i<n; i++)
    {
        tab2[i][i] = i;
    }

    for(int i = 0; i < m; i++)
    {
        cin >> wierz1 >> wierz2 >> waga;
        macierz[wierz1-1][wierz2-1] = waga;
        tab2[wierz1-1][wierz2-1] = wierz1-1;
    }

    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            if(macierz[i][k] != 2000000)
            {
                for(int j = 0; j < n; j++)
                {
                    if (macierz[i][j] > macierz[i][k] + macierz[k][j])
                    {
                        tab2[i][j] = tab2[k][j];
                    }
                    macierz[i][j] = min(macierz[i][j], macierz[i][k] + macierz[k][j]);
                }
            }
        }
    }

    //podawanie
    cin >> wierz1 >> wierz2;
    int index = wierz2 - 1;
    vector<int> sciez;
    while(index !=wierz1-1)
    {
        sciez.push_back(index);
        index = tab2[wierz1-1][index];
    }
    sciez.push_back(wierz1-1);

    //podawanie2
    int wierz3;
    cin>>wierz3;

    int index2 = wierz3 - 1;
    vector<int> sciez2;
    sciez2.push_back(wierz3-1);

    for(int i = 0; i<n; i++)
    {
        if(tab2[i][i] == index2)
        {
            index2 = i;
            break;
        }
    }

    while(index2 != wierz3 -1)
    {
        sciez2.push_back(index2);
        for(int i = 0; i<n; i++)
        {
            if(tab2[i][i] == index2)
            {
                index2 = i;
                break;
            }
        }
    }
    sciez2.push_back(wierz3-1);

    cout<<endl;
    //Wypisanie macierzy
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << macierz[i][j] << " ";
        }
        cout << endl;
    }

    //Wypisanie drogi z wierz1 do wierz2
    cout<<endl;
    cout<<macierz[wierz1 - 1][wierz2 -1]<<" ";
    for(int i = sciez.size() - 1; i>=0; i--)
    {
        cout<<sciez[i] + 1<<" ";
    }

    //Wypisanie drogi z wierz3 do wierz3
    cout<<endl;
    cout<<macierz[wierz3 - 1][wierz3 -1]<<" ";
    for(int i = 0; i < sciez2.size(); i++)
    {
        cout<<sciez2[i] + 1<<" ";
    }

    return 0;
}
