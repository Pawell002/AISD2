#include <iostream>

using namespace std;

enum Color{RED, BLACK};

struct wierzcholek{
    int wartosc;
    Color color;
    wierzcholek *lewy;
    wierzcholek *prawy;
    wierzcholek *rodzic;
};

wierzcholek *korzen = nullptr;

void lewa_rotacja(wierzcholek* x){
    cout << "Rotuje..." << endl;
    wierzcholek* y = x->prawy;
    x->prawy = y->lewy;
    if(y->lewy != nullptr){
        y->lewy->rodzic = x;
    }
    y->rodzic = x->rodzic;
    if(x->rodzic == nullptr){
        korzen = y;
    }
    else if(x == x->rodzic->lewy){
        x->rodzic->lewy = y;
    }
    else{
        x->rodzic->prawy = y;
    }
    y->lewy = x;
    x->rodzic = y;
}

void dodaj(int w){
    wierzcholek *nowy = new wierzcholek{w, RED, nullptr, nullptr, nullptr};
    if(korzen == nullptr){
        nowy->color = BLACK;
        korzen = nowy;
        return;
    }
    else{
        wierzcholek *obecny = korzen;
        while(true){
            if(w < obecny->wartosc){
                if(obecny->lewy != nullptr){
                    obecny = obecny->lewy;
                    nowy->rodzic = obecny;
                }
                else{
                    obecny->lewy = nowy;
                    return;
                }
            }
            else{
                if(obecny->prawy != nullptr){
                    obecny = obecny->prawy;
                    nowy->rodzic = obecny;
                }
                else{
                    obecny->prawy = nowy;
                    cout << "Debug: przed rotacja" << endl;
                    cout << obecny->color << endl;
                    cout << obecny->lewy << endl;
                    if(obecny->rodzic->color == RED && obecny->rodzic->lewy == nullptr){
                        lewa_rotacja(obecny->rodzic);
                    }
                    return;
                }
            }
        }
    }
}

void preorder(wierzcholek *wiersz){
    if(wiersz != nullptr){
        cout << wiersz -> wartosc << " ";
        preorder(wiersz->lewy);
        preorder(wiersz->prawy);
    }
}


void clearTree(wierzcholek *wiersz){
    if(wiersz != nullptr){
        clearTree(wiersz->lewy);
        clearTree(wiersz->prawy);
        delete wiersz;
    }
}

int main(){

    int n, w;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> w;
        dodaj(w);
    }

    preorder(korzen);
    cout << endl;
    clearTree(korzen);

    return 0;
}
