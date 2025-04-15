#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <cmath>

using namespace std;

void SortBiegunowe(vector<vector<int>> &tab_xy, int n, int index){
    int x_0 = tab_xy[index][0];
    int y_0 = tab_xy[index][1];

    vector<vector<int>> punkty = tab_xy;
    swap(punkty[0], punkty[index]);

    sort(punkty.begin() + 1, punkty.end(), [&](const vector<int>& a, const vector<int>& b){
        int cross = (a[0] - x_0) * (b[1] - y_0) - (a[1] - y_0) * (b[0] - x_0);
        if (cross > 0) return true;
        if (cross < 0) return false;

        int da = (a[0] - x_0) * (a[0] - x_0) + (a[1] - y_0) * (a[1] - y_0);
        int db = (b[0] - x_0) * (b[0] - x_0) + (b[1] - y_0) * (b[1] - y_0);
        return da < db;
    });

    tab_xy = punkty;

    cout << "\nPosortowane: \n";
    for(int i = 0; i < n; i++){
        cout << "(" << tab_xy[i][0] << "; " << tab_xy[i][1] << ")" << endl;
    }

}

int IloczynWektorowy(const vector<int>& O, const vector<int>& A, const vector<int>& B) {
    return (A[0] - O[0]) * (B[1] - O[1]) - (A[1] - O[1]) * (B[0] - O[0]);
}

void Graham(vector<vector<int>> &tab_xy, int n){
    vector<vector<int>> otoczka;

    otoczka.push_back(tab_xy[0]);

    for(int i = 1; i < n; i++){
        while(otoczka.size() >=2 && IloczynWektorowy(otoczka[otoczka.size()-2], otoczka[otoczka.size()-1], tab_xy[i]) <= 0){
            otoczka.pop_back();
        }
        otoczka.push_back(tab_xy[i]);
    }

    cout << "\nOtoczka wypukla metoda Grahama:" << endl;
    for(const auto &punkt : otoczka){
        cout << "(" << punkt[0] << "; " << punkt[1] << ")" <<  endl;
    }

}

void Jarvis(vector<vector<int>> &tab_xy, int n){
    vector<vector<int>> otoczka;
    int lewy = 0;

    for(int i = 1; i < n; i++){
        if(tab_xy[i][0] < tab_xy[lewy][0]){
            lewy = i;
        }
    }

    int p = lewy, q;

    do{
        otoczka.push_back(tab_xy[p]);
        q = (p+1)%n;

        for(int i = 0; i < n; i++){
            if(IloczynWektorowy(tab_xy[p], tab_xy[i], tab_xy[q]) > 0){
                q = i;
            }
        }
        p = q;
    } while(p != lewy);

    cout << "\nOtoczka wypukla metoda Jarvisa:" << endl;
    for (const auto& punkt : otoczka) {
        cout << "(" << punkt[0] << "; " << punkt[1] << ")" <<  endl;
    }
}

int main(){
    int n, min_y = 101, min_x = 101, index;
    cin >> n;
    vector<vector<int>> tab_xy(n, vector<int>(2));

    for(int i = 0; i < n; i++){
        cin >> tab_xy[i][0] >> tab_xy[i][1];
        if(min_y > tab_xy[i][1]){
            min_y = tab_xy[i][1];
            min_x = tab_xy[i][0];
            index = i;
        } else if(min_y == tab_xy[i][1] && min_x > tab_xy[i][0]){
            min_x = tab_xy[i][0];
            index = i;
        }
    }

    SortBiegunowe(tab_xy, n, index);

    Graham(tab_xy, n);
    Jarvis(tab_xy, n);

    return 0;
}
