#include <iostream>
#include <vector>

using namespace std;

void SortBiegunowe(vector<vector<int>> &tab_xy, int n, int index){
    vector<vector<int>> tab_pos(n, vector<int>(2));
    vector<int> wyznaczniki(n);
    int x_0, y_0;


    tab_pos[0][0] = tab_xy[index][0];
    tab_pos[0][1] = tab_xy[index][1];

    x_0 = tab_pos[0][0];
    y_0 = tab_pos[0][1];


    for(int i = 0; i < n; i++){
        if(index != i){
            wyznaczniki[i] = (100 - x_0)*(tab_xy[i][1] - y_0) - (tab_xy[i][0] - x_0)*(y_0 - y_0);
            cout << wyznaczniki[i] << endl;
        } else{
            wyznaczniki[i] = -1;
        }
    }

    for(int i = 0; i < n; i++){
        if(wyznaczniki[i] != -1)
    }

}

void Graham(vector<vector<int>> &tab_xy, int n){


}

void Jarvis(){

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

    for(int i = 0; i < n; i++){
        cout << tab_xy[i][0] << ":" << tab_xy[i][1] << endl;
    }

    SortBiegunowe(tab_xy, n, index);

    return 0;
}
