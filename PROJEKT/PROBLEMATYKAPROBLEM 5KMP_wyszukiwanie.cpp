#include <iostream>
#include <vector>

using namespace std;

void tablica_P(const string &w, vector<int> &P){
    int m = w.size();
    P[0] = 0;
    int t = 0;

    for (int j = 1; j < m; j++) {
        while (t > 0 && w[t] != w[j]) {
            t = P[t - 1];
        }
        if (w[t] == w[j]) {
            t++;
        }
        P[j] = t;
    }
}

void KMP(const string &T, const string &w, const vector<int> &P){
    int n = T.size();
    int m = w.size();
    int i = 0, j = 0;

    while (i < n) {
        if (w[j] == T[i]) {
            i++;
            j++;
            if (j == m) {
                cout << (i - j) << " ";
                j = P[j - 1];
            }
        } else {
            if (j > 0) {
                j = P[j - 1];
            } else {
                i++;
            }
        }
    }
    cout << endl;
}

int main() {
    string wzorzec, wyrazenie;

    cout << "Wzorzec zlozony z malych liter: ";
    cin >> wzorzec;
    for (char c : wzorzec) {
        if (c < 'a' || c > 'z') {
            cout << "Nieprawidlowy wzorzec!" << endl;
            return 1;
        }
    }

    cout << "Podaj wyrazenie zgodne ze slownikiem: ";
    cin >> wyrazenie;
    for (char c : wyrazenie) {
        if (c < 'a' || c > 'z') {
            cout << "Nieprawidlowe wyrazenie!" << endl;
            return 1;
        }
    }

    vector<int> P(wzorzec.size());
    tablica_P(wzorzec, P);

    cout << "Tablica prefix-sufix: ";
    for (int i = 0; i < P.size(); i++) {
        cout << P[i] << " ";
    }
    cout << endl;

    KMP(wyrazenie, wzorzec, P);

    return 0;
}
