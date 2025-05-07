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

void lewa_rotacja(wierzcholek *x){
    wierzcholek *y = x->prawy;
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

void prawa_rotacja(wierzcholek *x){
    wierzcholek *y = x->lewy;
    x->lewy = y->prawy;
    if(y->prawy != nullptr){
        y->prawy->rodzic = x;
    }
    y->rodzic = x->rodzic;
    if(x->rodzic == nullptr){
        korzen = y;
    }
    else if(x == x->rodzic->prawy){
        x->rodzic->prawy = y;
    }
    else{
        x->rodzic->lewy = y;
    }
    y->prawy = x;
    x->rodzic = y;
}

void napraw(wierzcholek *z){
    while(z->rodzic != nullptr && z->rodzic->color == RED){
        if(z->rodzic == z->rodzic->rodzic->lewy){
            wierzcholek *wujek = z->rodzic->rodzic->prawy;
            if(wujek != nullptr && wujek->color == RED){
                z->rodzic->color = BLACK;
                wujek->color = BLACK;
                z->rodzic->rodzic->color = RED;
                z = z->rodzic->rodzic;
            } else{
                if(z == z->rodzic->prawy){
                    z = z->rodzic;
                    lewa_rotacja(z);
                }
                z->rodzic->color = BLACK;
                z->rodzic->rodzic->color = RED;
                prawa_rotacja(z->rodzic->rodzic);
            }
        } else{
            wierzcholek *wujek = z->rodzic->rodzic->lewy;
            if(wujek != nullptr && wujek->color == RED){
                z->rodzic->color = BLACK;
                wujek->color = BLACK;
                z->rodzic->rodzic->color = RED;
                z = z->rodzic->rodzic;
            } else{
                if(z == z->rodzic->lewy){
                    z = z->rodzic;
                    prawa_rotacja(z);
                }
                z->rodzic->color = BLACK;
                z->rodzic->rodzic->color = RED;
                lewa_rotacja(z->rodzic->rodzic);
            }
        }
    }
    korzen->color = BLACK;
}


void dodaj(int wartosc) {
    wierzcholek *z = new wierzcholek{wartosc, RED, nullptr, nullptr, nullptr};
    wierzcholek *y = nullptr;
    wierzcholek *x = korzen;

    while (x != nullptr) {
        y = x;
        if (z->wartosc < x->wartosc)
            x = x->lewy;
        else
            x = x->prawy;
    }

    z->rodzic = y;
    if (y == nullptr)
        korzen = z;
    else if (z->wartosc < y->wartosc)
        y->lewy = z;
    else
        y->prawy = z;

    napraw(z);
}

void preorder(wierzcholek *wiersz){
    if(wiersz != nullptr){
        cout << wiersz->wartosc << " (" << (wiersz->color == RED ? "R" : "B") << ") ";
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
