def DT(wierz, kraw):
    tab_dane = [[0] * 3 for i in range(kraw)]
    tab_roz = [0] * (wierz + 1)
    tab_kraw = [0] * (kraw * 2)
    tab_wagi = [0] * (kraw * 2)
    tab_temp = []
    for i in range(kraw):
        wierz1, wierz2, waga= map(int, input().split())
        tab_dane[i][0] = wierz1
        tab_dane[i][1] = wierz2
        tab_dane[i][2] = waga
        tab_roz[wierz1 + 1] += 1
        tab_roz[wierz2 + 1] += 1
    for i in range(wierz):
        tab_roz[i + 1] += tab_roz[i]
    tab_temp = tab_roz.copy()
    for i in range(kraw):
        tab_kraw[tab_temp[tab_dane[i][0]]] = tab_dane[i][1]
        tab_wagi[tab_temp[tab_dane[i][0]]] = tab_dane[i][2]
        tab_temp[tab_dane[i][0]] += 1
        tab_kraw[tab_temp[tab_dane[i][1]]] = tab_dane[i][0]
        tab_wagi[tab_temp[tab_dane[i][1]]] = tab_dane[i][2]
        tab_temp[tab_dane[i][1]] += 1
    print(tab_roz)
    print(tab_kraw)
    print(tab_wagi)

l_wierz, l_kraw = map(int, input().split())
DT(l_wierz, l_kraw)



